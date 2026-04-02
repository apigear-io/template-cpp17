#include <iostream>
#include "mqttcwrapper.h"
#include "utilities/logger.h"
#include <chrono>
#include <memory>

using namespace ApiGear::MQTT;
#define QOS         2

namespace
{
    int timeoutWhileWaitingForUnsubscribe = 7; //Milliseconds
    int  maxBufferedMessages = 10000;
}

struct subscribeTopicContext {
    std::string topic;
    CallbackFunction func;
    OnSubscriptionStatusChanged onSubscribedCallback;
    std::weak_ptr<CWrapper> client;
};

namespace ApiGear { namespace MQTT {
struct genericContext {
    std::weak_ptr<CWrapper> client;
};
}} // namespace ApiGear::MQTT
using ApiGear::MQTT::genericContext;

void onSendSuccess(void* context, MQTTAsync_successData5* /*response*/)
{
    std::unique_ptr<genericContext> ctx(static_cast<genericContext*>(context));
}

void onSendFailure(void* context, MQTTAsync_failureData5* response)
{
    std::unique_ptr<genericContext> ctx(static_cast<genericContext*>(context));
    AG_LOG_ERROR("Send failed, ResponseCode " +  std::to_string(response->code));
}

void onSubscribeSuccess(void* context, MQTTAsync_successData5* /*response*/)
{
    std::unique_ptr<subscribeTopicContext> ctx(static_cast<subscribeTopicContext*>(context));
    if (auto client = ctx->client.lock())
    {
        client->onSubscribed(ctx->topic, ctx->func, ctx->onSubscribedCallback);
    }
}

void onSubscribeFailure(void* context, MQTTAsync_failureData5* response)
{
    std::unique_ptr<subscribeTopicContext> ctx(static_cast<subscribeTopicContext*>(context));
    if (auto client = ctx->client.lock())
    {
        ctx->onSubscribedCallback(ctx->topic, false);
    }
    AG_LOG_ERROR("Subscribe failed, ResponseCode " +  std::to_string(response->code));
}

void onUnsubscribeSuccess(void* context, MQTTAsync_successData5* /*response*/)
{
    std::unique_ptr<subscribeTopicContext> ctx(static_cast<subscribeTopicContext*>(context));
    if (auto client = ctx->client.lock())
    {
        client->onUnsubscribed(ctx->topic);
    }
}

void onUnsubscribeFailure(void* context, MQTTAsync_failureData5* response)
{
    std::unique_ptr<subscribeTopicContext> ctx(static_cast<subscribeTopicContext*>(context));
    AG_LOG_ERROR("Unsubscribe failed, ResponseCode " + std::to_string(response->code));
}

void onConnected(void* context, MQTTAsync_successData5* /*response*/)
{
    genericContext* ctx = static_cast<genericContext*>(context);
    if (auto client = ctx->client.lock())
    {
        client->onConnected();
    }
}

void onConnectedFail(void* context,  MQTTAsync_failureData5* response)
{
    genericContext* ctx = static_cast<genericContext*>(context);
    AG_LOG_ERROR("Connect failed, ResponseCode " + std::to_string(response->code));
    if (auto client = ctx->client.lock())
    {
        client->onDisconnected();
    }
}

void onDisconnected(void* context, MQTTAsync_successData5* /*response*/)
{
    std::unique_ptr<genericContext> ctx(static_cast<genericContext*>(context));
    if (auto client = ctx->client.lock())
    {
        client->onDisconnected();
    }
}


int OnMessageArrived(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
    Message mqtt_message {};
    mqtt_message.topic = std::string(topicName, static_cast<size_t>(topicLen));
    mqtt_message.content.assign(static_cast<char*>(message->payload), static_cast<size_t>(message->payloadlen));

    if(MQTTProperties_hasProperty(&(message->properties), MQTTPROPERTY_CODE_RESPONSE_TOPIC))
    {
        MQTTProperty* responseTopicProperty = MQTTProperties_getProperty(&(message->properties), MQTTPROPERTY_CODE_RESPONSE_TOPIC);
        mqtt_message.responseTopic = std::string(responseTopicProperty->value.data.data, static_cast<size_t>(responseTopicProperty->value.data.len));
    }

    if(MQTTProperties_hasProperty(&(message->properties), MQTTPROPERTY_CODE_CORRELATION_DATA))
    {
        MQTTProperty* correlationDataProperty = MQTTProperties_getProperty(&(message->properties), MQTTPROPERTY_CODE_CORRELATION_DATA);
        mqtt_message.correlationData.assign(correlationDataProperty->value.data.data, static_cast<size_t>(correlationDataProperty->value.data.len));
    }

    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);

    genericContext* ctx = static_cast<genericContext*>(context);
    if (auto client = ctx->client.lock())
    {
        client->handleTextMessage(mqtt_message);
    }

    return 1;
}

void OnConnectionLost(void *context, char * /*cause*/)
{
    AG_LOG_ERROR("Connection lost");
    genericContext* ctx = static_cast<genericContext*>(context);
    if (auto client = ctx->client.lock())
    {
        client->onDisconnected();
    }
}

CWrapper::CWrapper(const std::string& clientID)
    : m_client(nullptr)
    , m_clientID(clientID)
    , m_disconnectRequested(false)
{
}

CWrapper::~CWrapper()
{
    m_disconnectRequested = true;
    {
        std::lock_guard<std::mutex> lock(m_lifecycleMutex);
        if (m_reconnectThread.joinable()) {
            if (m_reconnectThread.get_id() == std::this_thread::get_id()) {
                m_reconnectThread.detach();
            } else {
                m_reconnectThread.join();
            }
        }
    }
    if (m_mainMQTTThread.joinable()) {
        {
            std::lock_guard<std::mutex> l{m_waitForSubscriptionChangesMutex};
            m_waitForSubscriptionChanges = false;
        }
        m_synchronizeSubscriptionChanges.notify_one();
        if (m_mainMQTTThread.get_id() != std::this_thread::get_id()) {
            m_mainMQTTThread.join();
        } else {
            m_mainMQTTThread.detach();
        }
    }
    m_client.reset();
    m_connectionContext.reset();
}


void CWrapper::MqttClientDeleter::operator()(MQTTAsync* cli)
{
    MQTTAsync_destroy(cli);
    delete cli;
};


int CWrapper::subscribeToConnectionStatus(OnConnectionStatusChangedCallBackFunction callBack)
{
    std::lock_guard<std::mutex> lock(m_onConnectionStatusChangedCallbacksMutex);
    int subscriptionId;
    std::uniform_int_distribution<> distribution(0, 100000);
    do {
        subscriptionId = distribution(m_randomNumberGenerator);
    } while (m_onConnectionStatusChangedCallbacks.find(subscriptionId) != m_onConnectionStatusChangedCallbacks.end());
    m_onConnectionStatusChangedCallbacks.insert({subscriptionId, callBack});
    return subscriptionId;
}

void CWrapper::unsubscribeToConnectionStatus(int subscriptionID)
{
    std::lock_guard<std::mutex> lock(m_onConnectionStatusChangedCallbacksMutex);
    if((m_onConnectionStatusChangedCallbacks.find(subscriptionID) != m_onConnectionStatusChangedCallbacks.end()))
    {
        m_onConnectionStatusChangedCallbacks.erase(subscriptionID);
    }
}

void CWrapper::run()
{
    do
    {
        std::unique_lock<std::mutex> lock{m_waitForSubscriptionChangesMutex};
        m_synchronizeSubscriptionChanges.wait(lock, [this]() { return !m_waitForSubscriptionChanges; });
        m_waitForSubscriptionChanges = true;
        lock.unlock();

        addNewSubscriptions();
        removeOldSubscriptions();

    }
    while (m_connected && !m_disconnectRequested);

    unsubscribeAllTopics();
    waitForPendingMessages();
}

void CWrapper::addNewSubscriptions()
{
    m_toBeSubscribedTopicsMutex.lock();
    const auto toBeSubscribedTopics(std::move(m_toBeSubscribedTopics));
    m_toBeSubscribedTopics.clear();
    m_toBeSubscribedTopicsMutex.unlock();
    for (const auto& topic : toBeSubscribedTopics) {
        MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
        opts.onSuccess5 = onSubscribeSuccess;
        opts.onFailure5 = onSubscribeFailure;
        auto ctx = std::make_unique<subscribeTopicContext>(subscribeTopicContext{topic.first, topic.second.topicCallback, topic.second.subscribedCallback, getPtr()});
        opts.context = ctx.release();
        int responseCode = MQTTAsync_subscribe(*m_client.get(), topic.first.c_str(), QOS, &opts);
        if (responseCode != MQTTASYNC_SUCCESS)
        {
            AG_LOG_ERROR("Failed to start subscribe, return code " + std::to_string(responseCode));
        }
    }
}

void CWrapper::removeOldSubscriptions()
{
    m_toBeUnsubscribedTopicsMutex.lock();
    const auto toBeUnsubscribedTopics(std::move(m_toBeUnsubscribedTopics));
    m_toBeUnsubscribedTopics.clear();
    m_toBeUnsubscribedTopicsMutex.unlock();
    for (const auto& topic : toBeUnsubscribedTopics) {
        MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
        opts.onSuccess5 = onUnsubscribeSuccess;
        opts.onFailure5 = onUnsubscribeFailure;
        auto ctx = std::make_unique<subscribeTopicContext>(subscribeTopicContext{topic, nullptr, nullptr, getPtr()});
        opts.context = ctx.release();
        int responseCode = MQTTAsync_unsubscribe(*m_client.get(), topic.c_str(), &opts);
        if (responseCode != MQTTASYNC_SUCCESS)
        {
            AG_LOG_WARNING("Failed to start unsubscribe, return code " + std::to_string(responseCode));
        }
    }
}

void CWrapper::unsubscribeAllTopics()
{
    if(!m_connected)
    {
        return;
    }

    m_subscribedTopicsMutex.lock();
    m_toBeUnsubscribedTopicsMutex.lock();
    for (const auto& entry : m_subscribedTopics)
    {
        m_toBeUnsubscribedTopics.insert(entry.first);
    }
    m_toBeUnsubscribedTopicsMutex.unlock();
    m_subscribedTopicsMutex.unlock();

    removeOldSubscriptions();
}

void CWrapper::waitForPendingMessages()
{
    bool unsubscribedFromAllTopics = false;
    // wait for unsubscription to complete
    while(m_connected && !unsubscribedFromAllTopics)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutWhileWaitingForUnsubscribe));

        std::lock_guard<std::mutex> guard(m_subscribedTopicsMutex);
        unsubscribedFromAllTopics = m_subscribedTopics.empty();
    }
}

void CWrapper::connectToHost(const std::string& brokerURL)
{
    m_disconnectRequested = false;
    if(brokerURL.empty()) {
        m_serverUrl = "tcp://localhost:1883";
    } else {
        m_serverUrl = brokerURL;
    }
    AG_LOG_DEBUG("Connecting to host " + m_serverUrl);

    if(!m_client && !m_connecting.exchange(true)) {
        try {
            m_client = std::unique_ptr<MQTTAsync, MqttClientDeleter>(new MQTTAsync());
            MQTTAsync_createOptions create_opts = MQTTAsync_createOptions_initializer5;
            create_opts.maxBufferedMessages = maxBufferedMessages;
            MQTTAsync_createWithOptions(m_client.get(), m_serverUrl.c_str(), m_clientID.c_str(), MQTTCLIENT_PERSISTENCE_NONE, NULL, &create_opts);

            MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer5;
            conn_opts.keepAliveInterval = 20;
            conn_opts.onSuccess5 = ::onConnected;
            conn_opts.onFailure5 = onConnectedFail;
            m_connectionContext = std::make_unique<genericContext>(genericContext{getPtr()});
            conn_opts.context = m_connectionContext.get();

            MQTTAsync_setCallbacks(*m_client.get(), conn_opts.context, OnConnectionLost, OnMessageArrived, NULL);
            int responseCode = MQTTAsync_connect(*m_client.get(), &conn_opts);
            if (responseCode != MQTTASYNC_SUCCESS)
            {
                AG_LOG_ERROR("Failed to connect, return code " + std::to_string(responseCode));
                m_connecting = false;
                m_client.reset();
                return;
            }

        } catch (std::exception &e) {
            m_client.reset();
            AG_LOG_ERROR("Exception " + std::string(e.what()));
        }
        m_connecting = false;
    }
}

void CWrapper::disconnect() {
    m_disconnectRequested = true;
    if (m_mainMQTTThread.joinable())
    {
        {
            std::lock_guard<std::mutex> l{m_waitForSubscriptionChangesMutex};
            m_waitForSubscriptionChanges = false;
        }
        m_synchronizeSubscriptionChanges.notify_one();
        m_mainMQTTThread.join();
    }
    m_connected = false;
    MQTTAsync_disconnectOptions disconn_opts = MQTTAsync_disconnectOptions_initializer5;
    disconn_opts.timeout = 10;
    MQTTAsync_disconnect(*m_client.get(), &disconn_opts);
    // Notify listeners synchronously — no async callback needed for intentional disconnect
    m_onConnectionStatusChangedCallbacksMutex.lock();
    auto callbacks(m_onConnectionStatusChangedCallbacks);
    m_onConnectionStatusChangedCallbacksMutex.unlock();
    for (auto& cb : callbacks) {
        cb.second(false);
    }
}

void CWrapper::onConnected()
{
    m_connected = true;
    AG_LOG_DEBUG("socket connected");
    m_onConnectionStatusChangedCallbacksMutex.lock();
    auto onConnectionStatusChangedCallbacks { m_onConnectionStatusChangedCallbacks };
    m_onConnectionStatusChangedCallbacksMutex.unlock();
    for (auto& callback: onConnectionStatusChangedCallbacks){
        callback.second(true);
    }
    {
        std::lock_guard<std::mutex> lock(m_lifecycleMutex);
        if (m_mainMQTTThread.joinable()) {
            m_mainMQTTThread.join();
        }
        m_mainMQTTThread = std::thread(&CWrapper::run, this);
    }
}

void CWrapper::resubscribeAllTopics()
{
    m_subscribedTopicsMutex.lock();
    m_toBeSubscribedTopicsMutex.lock();
    if(!m_subscribedTopics.empty())
    {
        m_subscribedTopics.insert(m_toBeSubscribedTopics.begin(),m_toBeSubscribedTopics.end());
        m_toBeSubscribedTopics = m_subscribedTopics;
        m_subscribedTopics.clear();
    }
    m_toBeSubscribedTopicsMutex.unlock();
    m_subscribedTopicsMutex.unlock();
}

void CWrapper::onDisconnected()
{
    m_connected = false;
    bool disconnectRequested = m_disconnectRequested.load();
    AG_LOG_DEBUG("socket disconnected");

    // if we have not waited for our thread to finish, do it now
    if (m_mainMQTTThread.joinable())
    {
        {
            std::lock_guard<std::mutex> l{m_waitForSubscriptionChangesMutex};
            m_waitForSubscriptionChanges = false;
        }
        m_synchronizeSubscriptionChanges.notify_one();
        m_mainMQTTThread.join();
    }
    m_onConnectionStatusChangedCallbacksMutex.lock();
    auto onConnectionStatusChangedCallbacks(std::move(m_onConnectionStatusChangedCallbacks));
    m_onConnectionStatusChangedCallbacks.clear();
    m_onConnectionStatusChangedCallbacksMutex.unlock();
    for (auto& callback : onConnectionStatusChangedCallbacks) {
        callback.second(false);
    }
    // reconnect if the connection was not dropped intentionally by us
    if (!disconnectRequested)
    {
        // this function is called from within the MQTTAsync client
        // therefore the client must be reset in a separate thread afterwards
        std::lock_guard<std::mutex> lock(m_lifecycleMutex);
        if (m_reconnectThread.joinable()) {
            m_reconnectThread.detach();  // previous reconnect still running
        }
        std::weak_ptr<CWrapper> weak_self = shared_from_this();
        m_reconnectThread = std::thread([weak_self]() {
            auto self = weak_self.lock();
            if (!self) return;
            self->m_client.reset();
            self->resubscribeAllTopics();
            self->connectToHost(self->m_serverUrl);
        });
    }
}

bool CWrapper::isConnected() const
{
    return m_connected;
}

void CWrapper::handleTextMessage(const Message& message)
{
    auto subscribedTopicsRange = m_subscribedTopics.equal_range(message.topic);
    for (auto iter = subscribedTopicsRange.first; iter != subscribedTopicsRange.second; ++iter)
    {
        if(iter->second.topicCallback != nullptr)
        {
            try {
                iter->second.topicCallback(message.content, message.responseTopic, message.correlationData);
            } catch (const std::exception& e) {
                AG_LOG_ERROR("MQTT message handling error on topic " + message.topic + ": " + std::string(e.what()));
            }
        }
    }
}

/**
 * @brief helper function to wrap the c call
 * 
 * @param options reference to the options which where the topic should be added
 * @param responseTopic the topic which is set as response topic
 */
void MQTTProperties_addResponseTopic(MQTTAsync_responseOptions& options, const std::string& responseTopic)
{
    MQTTProperty responseTopicProperty;
    responseTopicProperty.identifier = MQTTPROPERTY_CODE_RESPONSE_TOPIC;
    responseTopicProperty.value.data = { static_cast<int>(responseTopic.size()), const_cast<char*>(responseTopic.c_str()) };
    MQTTProperties_add(&(options.properties), &responseTopicProperty);
}

/**
 * @brief helper function to wrap the c call
 * 
 * @param options reference to the options which where the topic should be added
 * @param responseId the Id which is used as correlation data
 */
void MQTTProperties_addResponseIdAsCorrData(MQTTAsync_responseOptions& options, int responseId)
{
    MQTTProperty correlationDataProperty;
    correlationDataProperty.identifier = MQTTPROPERTY_CODE_CORRELATION_DATA;
    const std::string correlationData = { std::to_string(responseId) } ;
    correlationDataProperty.value.data = { static_cast<int>(correlationData.size()), const_cast<char*>(correlationData.c_str()) };
    MQTTProperties_add(&(options.properties), &correlationDataProperty);

}

void CWrapper::invokeRemote(const std::string& topic, const std::string& responseTopic, const std::string& value, int responseId)
{
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    MQTTAsync_message pubmsg = MQTTAsync_message_initializer;

    MQTTProperties_addResponseTopic(opts, responseTopic);
    MQTTProperties_addResponseIdAsCorrData(opts, responseId);

    opts.onSuccess5 = onSendSuccess;
    opts.onFailure5 = onSendFailure;
    auto ctx = std::make_unique<genericContext>(genericContext{getPtr()});
    opts.context = ctx.release();
    pubmsg.payload = const_cast<void*>(static_cast<const void*>(value.c_str()));
    pubmsg.payloadlen = static_cast<int>(value.size());
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    // the responseOptions properties do get overwritten by the msg properties later
    pubmsg.properties = opts.properties;

    sendMessage(topic, &pubmsg, &opts);
}

void CWrapper::notifyPropertyChange(const std::string& topic, const std::string& value)
{
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    MQTTAsync_message pubmsg = MQTTAsync_message_initializer;

    opts.onSuccess5 = onSendSuccess;
    opts.onFailure5 = onSendFailure;
    auto ctx = std::make_unique<genericContext>(genericContext{getPtr()});
    opts.context = ctx.release();
    pubmsg.payload = const_cast<void*>(static_cast<const void*>(value.c_str()));
    pubmsg.payloadlen = static_cast<int>(value.size());
    pubmsg.qos = QOS;
    // property changes shall be retained and automatically send to new clients
    pubmsg.retained = 1;

    sendMessage(topic, &pubmsg, &opts);
}

void CWrapper::notifySignal(const std::string& topic, const std::string& args)
{
	MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
	MQTTAsync_message pubmsg = MQTTAsync_message_initializer;

	pubmsg.payload = const_cast<void*>(static_cast<const void*>(args.c_str()));
	pubmsg.payloadlen = static_cast<int>(args.size());
	pubmsg.qos = QOS;
	pubmsg.retained = 0;

    sendMessage(topic, &pubmsg, &opts);
}

void CWrapper::notifyInvokeResponse(const std::string& responseTopic, const std::string& value, const std::string& correlationData)
{
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    MQTTAsync_message pubmsg = MQTTAsync_message_initializer;

    MQTTProperty correlationDataProperty;
    correlationDataProperty.identifier = MQTTPROPERTY_CODE_CORRELATION_DATA;
    correlationDataProperty.value.data = { static_cast<int>(correlationData.size()), const_cast<char*>(correlationData.c_str()) };
    MQTTProperties_add(&(opts.properties), &correlationDataProperty);

    opts.onSuccess5 = onSendSuccess;
    opts.onFailure5 = onSendFailure;
    auto ctx = std::make_unique<genericContext>(genericContext{getPtr()});
    opts.context = ctx.release();
    pubmsg.payload = const_cast<void*>(static_cast<const void*>(value.c_str()));
    pubmsg.payloadlen = static_cast<int>(value.size());
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    // the responseOptions properties do get overwritten by the msg properties later
    pubmsg.properties = opts.properties;

    sendMessage(responseTopic, &pubmsg, &opts);
}

void CWrapper::setRemoteProperty(const std::string& topic, const std::string& value)
{
	MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
	MQTTAsync_message pubmsg = MQTTAsync_message_initializer;

	pubmsg.payload = const_cast<void*>(static_cast<const void*>(value.c_str()));
	pubmsg.payloadlen = static_cast<int>(value.size());
	pubmsg.qos = QOS;
	pubmsg.retained = 0;

    sendMessage(topic, &pubmsg, &opts);
}

void CWrapper::subscribeTopic(const std::string& topic, CallbackFunction func, OnSubscriptionStatusChanged subscriptionCallback)
{
    {
        std::lock_guard<std::mutex> guard(m_toBeSubscribedTopicsMutex);
        m_toBeSubscribedTopics.insert({ topic, {func, subscriptionCallback} });
    }

    {
        std::lock_guard<std::mutex> l{m_waitForSubscriptionChangesMutex};
        m_waitForSubscriptionChanges = false;
    }
    m_synchronizeSubscriptionChanges.notify_one();
}

void CWrapper::onSubscribed(const std::string& topic, CallbackFunction func, OnSubscriptionStatusChanged subscriptionCallback)
{
    subscriptionCallback(topic, true);
    AG_LOG_INFO("Subscribed to " + topic);
    std::lock_guard<std::mutex> guard(m_subscribedTopicsMutex);
    m_subscribedTopics.insert({ topic, {func, subscriptionCallback} });
}

void CWrapper::onUnsubscribed(const std::string& topic)
{
    AG_LOG_INFO("Unsubscribed from " + topic);
    std::lock_guard<std::mutex> guard(m_subscribedTopicsMutex);
    auto unsubscribedTopicsRange = m_subscribedTopics.equal_range(topic);
    for (auto iter = unsubscribedTopicsRange.first; iter != unsubscribedTopicsRange.second; ++iter)
    {
        if (iter->second.subscribedCallback != nullptr)
        {
            iter->second.subscribedCallback(topic, false);
        }
    }
    m_subscribedTopics.erase(topic);
}

void CWrapper::unsubscribeTopic(const std::string& topic)
{
    {
        std::lock_guard<std::mutex> guard(m_toBeUnsubscribedTopicsMutex);
        m_toBeUnsubscribedTopics.insert(topic);
    }

    {
        std::lock_guard<std::mutex> l{m_waitForSubscriptionChangesMutex};
        m_waitForSubscriptionChanges = false;
    }
    m_synchronizeSubscriptionChanges.notify_one();
}

int CWrapper::sendMessage(const std::string& destinationName, const MQTTAsync_message* msg, MQTTAsync_responseOptions* response)
{
    int responseCode = 0;
    responseCode = MQTTAsync_sendMessage(*m_client.get(), destinationName.c_str(), msg, response);
	if (responseCode != MQTTASYNC_SUCCESS)
	{
        AG_LOG_ERROR("Failed to start sendMessage, return code " + std::to_string(responseCode));
	}

    return responseCode;
}
