#include <iostream>
#include "mqttcwrapper.h"
#include "utilities/logger.h"
#include <chrono>
#include <random>
#include <memory>

using namespace ApiGear::MQTT;
#define QOS         2

namespace
{
    int timeoutWhileWaitingForUnsubscribe = 7; //Milliseconds
    int  maxBufferedMessages = 10000;
}

std::mt19937 randomNumberGenerator (std::random_device{}());

struct subscribeTopicContext {
    std::string topic;
    CallbackFunction func;
    std::weak_ptr<CWrapper> client;
};

struct genericContext {
    std::weak_ptr<CWrapper> client;
};

void onSendFailure(void* /*context*/, MQTTAsync_failureData5* response)
{
    AG_LOG_ERROR("Send failed, ResponseCode " +  std::to_string(response->code));
}

void onSubscribeSuccess(void* context, MQTTAsync_successData5* /*response*/)
{
    subscribeTopicContext* ctx = static_cast<subscribeTopicContext*>(context);
    if (auto client = ctx->client.lock())
    {
        client->onSubscribed(ctx->topic, ctx->func);
    }
    delete ctx;
}

void onSubscribeFailure(void* context, MQTTAsync_failureData5* response)
{
    subscribeTopicContext* ctx = static_cast<subscribeTopicContext*>(context);
    AG_LOG_ERROR("Subscribe failed, ResponseCode " +  std::to_string(response->code));
    delete ctx;
}

void onUnsubscribeSuccess(void* context, MQTTAsync_successData5* /*response*/)
{
    subscribeTopicContext* ctx = static_cast<subscribeTopicContext*>(context);
    if (auto client = ctx->client.lock())
    {
        client->onUnsubscribed(ctx->topic);
    }
    delete ctx;
}

void onUnsubscribeFailure(void* context, MQTTAsync_failureData5* response)
{
    subscribeTopicContext* ctx = static_cast<subscribeTopicContext*>(context);
    AG_LOG_ERROR("Unsubscribe failed, ResponseCode " + std::to_string(response->code));
    delete ctx;
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
    delete ctx;
}

void onDisconnected(void* context, MQTTAsync_successData5* /*response*/)
{
    genericContext* ctx = static_cast<genericContext*>(context);
    if (auto client = ctx->client.lock())
    {
        client->onDisconnected();
    }
    delete ctx;
}


int OnMessageArrived(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
    Message mqtt_message {};
    mqtt_message.topic = std::string(topicName, topicLen);
    mqtt_message.content.assign(static_cast<char*>(message->payload), message->payloadlen);

    if(MQTTProperties_hasProperty(&(message->properties), MQTTPROPERTY_CODE_RESPONSE_TOPIC))
    {
        MQTTProperty* responseTopicProperty = MQTTProperties_getProperty(&(message->properties), MQTTPROPERTY_CODE_RESPONSE_TOPIC);
        mqtt_message.responseTopic = std::string(responseTopicProperty->value.data.data, responseTopicProperty->value.data.len);
    }

    if(MQTTProperties_hasProperty(&(message->properties), MQTTPROPERTY_CODE_CORRELATION_DATA))
    {
        MQTTProperty* correlationDataProperty = MQTTProperties_getProperty(&(message->properties), MQTTPROPERTY_CODE_CORRELATION_DATA);
        mqtt_message.correlationData.assign(correlationDataProperty->value.data.data, correlationDataProperty->value.data.len);
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
    delete ctx;
}

CWrapper::CWrapper(const std::string& clientID)
    : m_client(nullptr)
    , m_clientID(clientID)
    , m_disconnectRequested(false)
{
}

CWrapper::~CWrapper() = default;


void CWrapper::MqttClientDeleter::operator()(MQTTAsync* cli)
{
    MQTTAsync_destroy(cli);
};


int CWrapper::createUniqueConnectionStatusId()
{
    auto subscriptionId = 0;
    std::uniform_int_distribution<> distribution (0, 100000);
    m_onConnectionStatusChangedCallbacksMutex.lock();
    do {
        subscriptionId = distribution(randomNumberGenerator);
    } while (m_onConnectionStatusChangedCallbacks.find(subscriptionId) != m_onConnectionStatusChangedCallbacks.end());

    return subscriptionId;
}

int CWrapper::subscribeToConnectionStatus(OnConnectionStatusChangedCallBackFunction callBack)
{
    auto subscriptionId = createUniqueConnectionStatusId();
    m_onConnectionStatusChangedCallbacks.insert({subscriptionId, callBack});
    m_onConnectionStatusChangedCallbacksMutex.unlock();

    return subscriptionId;
}

void CWrapper::unsubscribeToConnectionStatus(int subscriptionID)
{
    m_onConnectionStatusChangedCallbacksMutex.lock();
    if((m_onConnectionStatusChangedCallbacks.find(subscriptionID) != m_onConnectionStatusChangedCallbacks.end()))
    {
        m_onConnectionStatusChangedCallbacks.erase(subscriptionID);
    }
    m_onConnectionStatusChangedCallbacksMutex.unlock();
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
        opts.context = new subscribeTopicContext{topic.first, topic.second, getPtr()};
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
        opts.context = new subscribeTopicContext{topic, nullptr, getPtr()};
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
    static bool connecting = false;

    if(brokerURL.empty()) {
        m_serverUrl = "tcp://localhost:1883";
    } else {
        m_serverUrl = brokerURL;
    }
    AG_LOG_DEBUG("Connecting to host " + m_serverUrl);
    
    if(!m_client && !connecting) {
        try {
            connecting = true;

            m_client = std::unique_ptr<MQTTAsync, MqttClientDeleter>(new MQTTAsync());
            MQTTAsync_createOptions create_opts = MQTTAsync_createOptions_initializer5;
            create_opts.maxBufferedMessages = maxBufferedMessages;
            MQTTAsync_createWithOptions(m_client.get(), m_serverUrl.c_str(), m_clientID.c_str(), MQTTCLIENT_PERSISTENCE_NONE, NULL, &create_opts);

            MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer5;
            conn_opts.keepAliveInterval = 20;
            conn_opts.onSuccess5 = ::onConnected;
            conn_opts.onFailure5 = onConnectedFail;
            conn_opts.context = new genericContext{getPtr()};

            MQTTAsync_setCallbacks(*m_client.get(), conn_opts.context, OnConnectionLost, OnMessageArrived, NULL);
            int responseCode = MQTTAsync_connect(*m_client.get(), &conn_opts);
            if (responseCode != MQTTASYNC_SUCCESS)
            {
                AG_LOG_ERROR("Failed to connect, return code " + std::to_string(responseCode));
                connecting = false;
                m_client.reset();
                return;
            }

        } catch (std::exception &e) {
            m_client.reset();
            AG_LOG_ERROR("Exception " + std::string(e.what()));
        }
        connecting = false;
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
    MQTTAsync_disconnectOptions disconn_opts = MQTTAsync_disconnectOptions_initializer5;
    disconn_opts.onSuccess5 = ::onDisconnected;
    disconn_opts.context = new genericContext{getPtr()};
    disconn_opts.timeout = 10;
    MQTTAsync_disconnect(*m_client.get(), &disconn_opts);
    m_onConnectionStatusChangedCallbacksMutex.lock();
    auto onConnectionStatusChangedCallbacks(std::move(m_onConnectionStatusChangedCallbacks));
    m_onConnectionStatusChangedCallbacks.clear();
    m_onConnectionStatusChangedCallbacksMutex.unlock();
    for (auto& callback: onConnectionStatusChangedCallbacks){
        callback.second(false);
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
    m_mainMQTTThread = std::thread(&CWrapper::run, this);
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
    bool disconnectRequested = m_disconnectRequested;
    m_disconnectRequested = false;
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
    std::weak_ptr<CWrapper> weakClient = getPtr();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // this function is called from within the MQTTAsync client
    // therefore the client must be reset in a separate thread afterwards
    std::thread([this, weakClient, disconnectRequested](){
        auto client = weakClient.lock();
        if (!client)
        {
            return;
        }
        m_client.reset();

        // reconnect if the connection was not dropped intentionally by us
        if(!disconnectRequested)
        {
            // we need to re-subscribe to all topics on re-connection
            resubscribeAllTopics();

            connectToHost(m_serverUrl);
        }
    }).detach();
}

void CWrapper::handleTextMessage(const Message& message)
{
    auto subscribedTopicsRange = m_subscribedTopics.equal_range(message.topic);
    for (auto iter = subscribedTopicsRange.first; iter != subscribedTopicsRange.second; ++iter)
    {
        if(iter->second != nullptr)
        {
            iter->second(message.content, message.responseTopic, message.correlationData);
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

    opts.onFailure5 = onSendFailure;
    opts.context = new genericContext{getPtr()};
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

    opts.onFailure5 = onSendFailure;
    opts.context = new genericContext{getPtr()};
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

    opts.onFailure5 = onSendFailure;
    opts.context = new genericContext{getPtr()};
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

void CWrapper::subscribeTopic(const std::string& topic, CallbackFunction func)
{
    {
        std::lock_guard<std::mutex> guard(m_toBeSubscribedTopicsMutex);
        m_toBeSubscribedTopics.insert({topic, func});
    }

    {
        std::lock_guard<std::mutex> l{m_waitForSubscriptionChangesMutex};
        m_waitForSubscriptionChanges = false;
    }
    m_synchronizeSubscriptionChanges.notify_one();
}

void CWrapper::onSubscribed(const std::string& topic, CallbackFunction func)
{
    AG_LOG_INFO("Subscribed to " + topic);
    std::lock_guard<std::mutex> guard(m_subscribedTopicsMutex);
    m_subscribedTopics.insert({topic, func});
}

void CWrapper::onUnsubscribed(const std::string& topic)
{
    AG_LOG_INFO("Unsubscribed from " + topic);
    std::lock_guard<std::mutex> guard(m_subscribedTopicsMutex);
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
