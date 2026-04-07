#include <iostream>
#include "natscwrapper.h"
#include "utilities/logger.h"
#include <memory>
#include <functional>
#include <chrono>

using namespace ApiGear::Nats;

namespace
{
    uint32_t reply_timeout = 2000;//[ms]
}

struct NatsSubscriptionDeleter
{
    void operator()(natsSubscription* s)
    {
        natsSubscription_Destroy(s);
    }
};

struct NatsMsgDeleter
{
    void operator()(natsMsg* msg)
    {
        natsMsg_Destroy(msg);
    }
};

struct NatsOptionsDeleter
{
    void operator()(natsOptions* o)
    {
        natsOptions_Destroy(o);
    }
};

struct cleanSubscriptionResourcesContext {
    int64_t id;
    std::weak_ptr<CWrapper> client;
    std::function<void(int64_t)> function;
};

static void onMsg(natsConnection* /*connection*/, natsSubscription* /*subscription*/, natsMsg* msg, void* context)
{
    // Make sure msg will be properly destroyed.
    std::shared_ptr<natsMsg> message(msg, NatsMsgDeleter());
    CWrapper::SimpleCallbackWrapper* callbackWrapper = static_cast<CWrapper::SimpleCallbackWrapper*>(context);
    if (callbackWrapper && callbackWrapper->callback)
    {
        callbackWrapper->callback(natsMsg_GetData(message.get()));
    }
    else
    {
        AG_LOG_WARNING("No handler for " + std::string(natsMsg_GetSubject(message.get())));
    }
}

static void onRequest(natsConnection* connection, natsSubscription* /*subscription*/, natsMsg* msg, void* context)
{
    // Make sure msg will be properly destroyed.
    std::shared_ptr<natsMsg> message(msg, NatsMsgDeleter());
    CWrapper::MessageCallbackWithResultWrapper* callbackWrapper = static_cast<CWrapper::MessageCallbackWithResultWrapper*>(context);
    if (callbackWrapper && callbackWrapper->callback)
    {
        std::string result = callbackWrapper->callback(natsMsg_GetData(message.get()));
        auto replyTopic = natsMsg_GetReply(message.get());
        if (replyTopic != NULL)
        {
            natsConnection_PublishString(connection, replyTopic, result.c_str());
        }
        else
        {
            AG_LOG_ERROR("Could not send a reply to  " + std::string(natsMsg_GetSubject(message.get())) + "no response topic." );
        }
    }
    else
    {
        AG_LOG_WARNING("No handler for " + std::string(natsMsg_GetSubject(message.get())));
    }
}

static void onError(natsConnection* /*connection*/, natsSubscription* subscription, natsStatus status, void* context)
{
    auto* ctx = static_cast<CWrapper::CallbackContext*>(context);
    std::lock_guard<std::mutex> lock(ctx->mutex);
    auto owner = ctx->owner.lock();
    if (!owner) return;
    auto subscription_id = natsSubscription_GetID(subscription);
    std::string errorMessage = "Error for subscription: " + std::to_string(subscription_id) + " with status " + std::to_string(status);
    AG_LOG_ERROR(errorMessage);
}

static void conntectionHandler(natsConnection* connection, void* context)
{
    auto* ctx = static_cast<CWrapper::CallbackContext*>(context);
    std::function<void(void)> callback;
    {
        std::lock_guard<std::mutex> lock(ctx->mutex);
        auto owner = ctx->owner.lock();
        if (!owner)
        {
            if (natsConnection_IsClosed(connection))
            {
                ctx->closed = true;
                ctx->closedCV.notify_all();
            }
            return;
        }
        callback = ctx->connectionStateChangedCallback;
    }
    if (callback)
    {
        callback();
    }
}

static void removeSubscriptionResources(void* context)
{
    std::unique_ptr<cleanSubscriptionResourcesContext> ctx(static_cast<cleanSubscriptionResourcesContext*>(context));
    if (!ctx)
    {
        AG_LOG_WARNING("Removing subscription resources failed.");
    }
    else if (auto client = ctx->client.lock())
    {
        ctx->function(ctx->id);
    }
}


CWrapper::CWrapper()
    : m_callbackContext(std::make_shared<CallbackContext>())
{
}

CWrapper::~CWrapper()
{
    {
        std::lock_guard<std::mutex> lock(m_callbackContext->mutex);
        m_callbackContext->owner.reset();
        m_callbackContext->connectionStateChangedCallback = nullptr;
        m_callbackContext->closed = false;
    }
    {
        std::lock_guard<std::mutex> lock(m_subscriptionsMutex);
        for (auto& [id, sub] : m_subscriptions)
        {
            natsSubscription_Drain(sub.get());
        }
    }
    std::unique_ptr<natsConnection, NatsConnectionDeleter> conn;
    {
        std::lock_guard<std::mutex> lock(m_connectionMutex);
        conn = std::move(m_connection);
    }
    if (conn)
    {
        natsConnection_Close(conn.get());
        std::unique_lock<std::mutex> lock(m_callbackContext->mutex);
        m_callbackContext->closedCV.wait_for(lock, std::chrono::seconds(5),
            [this] { return m_callbackContext->closed; });
    }
}

void CWrapper::NatsConnectionDeleter::operator()(natsConnection* conn)
{
    natsConnection_Destroy(conn);
};

void CWrapper::connect(const std::string& address, std::function<void(void)> connectionStateChangedCallback, bool sendAsap)
{
    {
        std::lock_guard<std::mutex> lock(m_callbackContext->mutex);
        m_callbackContext->owner = shared_from_this();
        m_callbackContext->connectionStateChangedCallback = connectionStateChangedCallback;
    }

    natsOptions* tmp_opts;
    auto status = natsOptions_Create(&tmp_opts);
    if (status != NATS_OK) {
        auto log = "Failed to connect. Could not configure connection. Check your connection. Error code " + std::to_string(static_cast<int>(status));
        AG_LOG_ERROR(log);
        return;
    }
    std::unique_ptr<natsOptions, NatsOptionsDeleter> opts(tmp_opts, NatsOptionsDeleter());

    status = natsOptions_SetErrorHandler(opts.get(), onError, m_callbackContext.get());
    if (status != NATS_OK) {
        AG_LOG_ERROR("Failed to connect. Could not configure connection (On configuring Error Handler). Check your connection");
        return;
    }
    status = natsOptions_SetURL(opts.get(), address.c_str());
    if (status != NATS_OK) {
        auto log = "Failed to connect. Could not configure connection (On setting host address). Error code " + std::to_string(static_cast<int>(status));
        AG_LOG_ERROR(log);
        return;
    }
    status = natsOptions_SetDisconnectedCB(opts.get(), conntectionHandler, m_callbackContext.get());
    if (status != NATS_OK) {
        auto log = "Failed to connect. Could not configure connection (On configuring disconnect callback). Error code " + std::to_string(static_cast<int>(status));
        AG_LOG_ERROR(log);
        return;
    }
    status = natsOptions_SetReconnectedCB(opts.get(), conntectionHandler, m_callbackContext.get());
    if (status != NATS_OK) {
        auto log = "Failed to connect. Could not configure connection (On configuring disconnect callback). Error code " + std::to_string(static_cast<int>(status));
        AG_LOG_ERROR(log);
        return;
    }
    status = natsOptions_SetRetryOnFailedConnect(opts.get(), true, conntectionHandler, m_callbackContext.get());
    if (status != NATS_OK) {
        auto log = "Failed to connect. Could not configure connection (On configuring disconnect callback). Error code " + std::to_string(static_cast<int>(status));
        AG_LOG_ERROR(log);
        return;
    }
    status = natsOptions_SetClosedCB(opts.get(), conntectionHandler, m_callbackContext.get());
    if (status != NATS_OK) {
        auto log = "Failed to connect. Could not configure connection (On configuring disconnect callback). Error code " + std::to_string(static_cast<int>(status));
        AG_LOG_ERROR(log);
        return;
    }
    // Use thread pool for message delivery - if set to false each subscription gets own thread for receiving messages.
    status = natsOptions_UseGlobalMessageDelivery(opts.get(), true);
    if (status != NATS_OK) {
        auto log = "Failed to connect. Could not configure connection (On setting message thread options). Error code " + std::to_string(static_cast<int>(status));
        AG_LOG_ERROR(log);
        return;
    }
    if (sendAsap)
    {
        status = natsOptions_SetSendAsap(opts.get(), true);
        if (status != NATS_OK) {
            auto log = "Failed to connect. Could not configure connection (On setting send asap). Error code " + std::to_string(static_cast<int>(status));
            AG_LOG_ERROR(log);
            return;
        }
    }
    natsConnection* connection = NULL;
    status = natsConnection_Connect(&connection, opts.get());
    {
        std::lock_guard<std::mutex> lock(m_connectionMutex);
        m_connection.reset(connection);
    }
    if (status != NATS_OK) {
        auto log = "Failed to connect. Check your connection. Status " + std::to_string(static_cast<int>(status));
        AG_LOG_ERROR(log);
        return;
    }
}

uint64_t CWrapper::getId() const
{
    uint64_t cid = 0;
    std::lock_guard<std::mutex> lock(m_connectionMutex);
    if (m_connection)
    {
        auto status = natsConnection_GetClientID(m_connection.get(), &cid);
        if (status != NATS_OK)
        {
            auto log = "Failed to get the id for client. Status " + std::to_string(static_cast<int>(status));
            AG_LOG_ERROR(log);
        }
    }
    return cid;
}


void CWrapper::disconnect(bool graceful)
{
    {
        std::lock_guard<std::mutex> lock(m_callbackContext->mutex);
        m_callbackContext->owner.reset();
        m_callbackContext->connectionStateChangedCallback = nullptr;
        m_callbackContext->closed = false;
    }
    if (graceful)
    {
        std::lock_guard<std::mutex> lock(m_subscriptionsMutex);
        for (auto& [id, sub] : m_subscriptions)
        {
            natsSubscription_Drain(sub.get());
        }
    }
    std::unique_ptr<natsConnection, NatsConnectionDeleter> conn;
    {
        std::lock_guard<std::mutex> lock(m_connectionMutex);
        if (!m_connection)
        {
            return;
        }
        conn = std::move(m_connection);
    }
    if (graceful)
    {
        natsConnection_Flush(conn.get());
    }
    natsConnection_Close(conn.get());
    {
        std::unique_lock<std::mutex> lock(m_callbackContext->mutex);
        m_callbackContext->closedCV.wait_for(lock, std::chrono::seconds(5),
            [this] { return m_callbackContext->closed; });
    }
}


ConnectionStatus CWrapper::getStatus()
{
    std::lock_guard<std::mutex> lock(m_connectionMutex);
    if (!m_connection)
    {
        return ConnectionStatus::disconnected;
    }
    auto status = natsConnection_Status(m_connection.get());
    switch (status)
    {
        case NATS_CONN_STATUS_DISCONNECTED: return ConnectionStatus::disconnected;
        case NATS_CONN_STATUS_CONNECTING: return ConnectionStatus::connecting;
        case NATS_CONN_STATUS_CONNECTED: return ConnectionStatus::connected;
        case NATS_CONN_STATUS_CLOSED: return ConnectionStatus::closed;
        case NATS_CONN_STATUS_RECONNECTING: return ConnectionStatus::reconnecting;
        case NATS_CONN_STATUS_DRAINING_SUBS: return ConnectionStatus::draining_subs;
        case NATS_CONN_STATUS_DRAINING_PUBS: return ConnectionStatus::draining_pubs;
    }
    return ConnectionStatus::disconnected;
}


void CWrapper::flush()
{
    natsConnection* conn = nullptr;
    {
        std::lock_guard<std::mutex> lock(m_connectionMutex);
        if (!m_connection)
        {
            return;
        }
        conn = m_connection.get();
    }
    natsConnection_Flush(conn);
}

int64_t CWrapper::subscribe(const std::string& topic, SimpleOnMessageCallback callback, SubscriptionClosedCallback onSubscriptionClosedCallback)
{
    AG_LOG_DEBUG("nats client: subscribe " + topic);
    // store callback
    std::unique_lock<std::mutex> lockCallback(m_simpleCallbacksMutex);
    m_simpleCallbacks.emplace_back(std::make_shared<SimpleCallbackWrapper>(callback));
    auto storedCallback = m_simpleCallbacks.back();
    lockCallback.unlock();

    // nats library prepares a subscription which later will be stored, it is this class responsibility to free the resources.
    natsSubscription* tmp;
    auto status = natsConnection_Subscribe(&tmp, m_connection.get(), topic.c_str(), onMsg, storedCallback.get());

    if (status != NATS_OK) {
        auto log = "Failed to subscribe " + topic + " Status " + std::to_string(static_cast<int>(status));
        AG_LOG_WARNING(log);
        lockCallback.lock();
        m_simpleCallbacks.remove(storedCallback);
        lockCallback.unlock();
        return 0;
    };
    std::shared_ptr<natsSubscription> subscription_ptr(tmp, NatsSubscriptionDeleter());
    auto sub_id = natsSubscription_GetID(subscription_ptr.get());
    std::unique_lock<std::mutex> lockSubscription{ m_subscriptionsMutex };
    m_subscriptions[static_cast<uint64_t>(sub_id)] = subscription_ptr;
    lockSubscription.unlock();

    storedCallback->id = sub_id;
    // This callback removes all resources, the nats library states that after unsubscribe call there might be still message to serve
    // Nats library guarantees that after SetOnCompleteCB there will be no more calls for message handler for this subscription and resources can be safely cleaned up.
    auto cleanCtx = std::make_unique<cleanSubscriptionResourcesContext>(cleanSubscriptionResourcesContext{ sub_id, shared_from_this(), [this, onSubscriptionClosedCallback](uint64_t clean_id) {onSubscriptionClosedCallback(clean_id); cleanSubscription(static_cast<int64_t>(clean_id)); } });

    status = natsSubscription_SetOnCompleteCB(subscription_ptr.get(), &removeSubscriptionResources, cleanCtx.get());
    if (status != NATS_OK) {
        AG_LOG_WARNING("Failed to add subscription clean up callback " + topic +" id " + std::to_string(sub_id));
        AG_LOG_WARNING("Please restart the client to clean up resources.");
    }
    else
    {
        // C API took ownership via the callback; release so unique_ptr won't delete it.
        cleanCtx.release();
    }
    return sub_id;
}

int64_t CWrapper::subscribeWithResponse(const std::string& topic, MessageCallbackWithResult callback, SubscriptionClosedCallback onSubscriptionClosedCallback)
{
    AG_LOG_DEBUG("nats client: subscribe " + topic);
    std::unique_lock<std::mutex> lockCallback(m_requestCallbacksMutex);
    m_requestCallbacks.emplace_back(std::make_shared<MessageCallbackWithResultWrapper>(callback));
    auto storedCallback = m_requestCallbacks.back();
    lockCallback.unlock();
    // nats library prepares a subscription which later will be stored, it is this class responsibility to free the resources.
    natsSubscription* tmp;
    auto status = natsConnection_Subscribe(&tmp, m_connection.get(), topic.c_str(), onRequest, storedCallback.get());

    if (status != NATS_OK) {
        AG_LOG_WARNING("Failed to subscribe " + topic + " with error code: " + std::to_string(status));
        lockCallback.lock();
        m_requestCallbacks.remove(storedCallback);
        lockCallback.unlock();
        return 0;
    };
    std::shared_ptr< natsSubscription> subscription_ptr(tmp, NatsSubscriptionDeleter());
    auto sub_id = natsSubscription_GetID(subscription_ptr.get());

    std::unique_lock<std::mutex> lockSubscription{ m_subscriptionsMutex };
    m_subscriptions[static_cast<uint64_t>(sub_id)] = subscription_ptr;
    lockSubscription.unlock();

    storedCallback->id = sub_id;
    // This callback removes all resources, the nats library states that after unsubscribe call there might be still message to serve
    // Nats library guarantees that after SetOnCompleteCB there will be no more calls for message handler for this subscription and resources can be safely cleaned up.
    auto cleanCtx = std::make_unique<cleanSubscriptionResourcesContext>(cleanSubscriptionResourcesContext{ sub_id, shared_from_this(), [this, onSubscriptionClosedCallback](uint64_t clean_id) {onSubscriptionClosedCallback(clean_id); cleanSubscription(static_cast<int64_t>(clean_id)); } });

    status = natsSubscription_SetOnCompleteCB(subscription_ptr.get(), &removeSubscriptionResources, cleanCtx.get());
    if (status != NATS_OK) {
        AG_LOG_WARNING("Failed to add subscription clean up callback " + topic + " id " + std::to_string(sub_id));
        AG_LOG_WARNING("Please restart the client to clean up resources.");
    }
    else
    {
        // C API took ownership via the callback; release so unique_ptr won't delete it.
        cleanCtx.release();
    }
    return sub_id;
}


void CWrapper::unsubscribe(int64_t id)
{
    AG_LOG_DEBUG("nats client: unsubscribe " + std::to_string(id));
    std::shared_ptr<natsSubscription> sub;
    {
        std::lock_guard<std::mutex> lock{ m_subscriptionsMutex };
        auto found = m_subscriptions.find(static_cast<uint64_t>(id));
        if (found == m_subscriptions.end())
        {
            // May happen if unsubscribe during connection disconnecting, the disconnect request removes the subscriptions.
            return;
        }
        sub = found->second;
    }
    auto status = natsSubscription_Unsubscribe(sub.get());
    if (status != NATS_OK && status != NATS_CONNECTION_CLOSED) {
        AG_LOG_WARNING("Failed to unsubscribe " + std::to_string(id)+ " status " + std::to_string(status));
        cleanSubscription(id);
    };
}

void CWrapper::cleanSubscription(int64_t id)
{
    std::unique_lock<std::mutex> lockSubscriptions{ m_subscriptionsMutex };
    auto foundSubscription = m_subscriptions.find(static_cast<uint64_t>(id));
    if (foundSubscription != m_subscriptions.end())
    {
        m_subscriptions.erase(foundSubscription);
    }
    else
    {
        AG_LOG_WARNING("No subscription to remove with id " + std::to_string(id));
    }
    lockSubscriptions.unlock();
    std::unique_lock<std::mutex> lockCallbacks{ m_simpleCallbacksMutex };
    auto foundCallback = find_if(m_simpleCallbacks.begin(), m_simpleCallbacks.end(), [id](auto element) { return  element->id == id; });
    if (foundCallback != m_simpleCallbacks.end())
    {
        m_simpleCallbacks.erase(foundCallback);
    }
    else
    {
        lockCallbacks.unlock();
        std::unique_lock<std::mutex> lockRequestCallbacks{ m_requestCallbacksMutex };
        auto requestCallback = find_if(m_requestCallbacks.begin(), m_requestCallbacks.end(), [id](auto element) { return  element->id == id; });
        if (requestCallback != m_requestCallbacks.end())
        {
            m_requestCallbacks.erase(requestCallback);
        }
        else
        {
            lockRequestCallbacks.unlock();
            AG_LOG_WARNING("No callback to remove for subscription with id " + std::to_string(id));
        }
    }
}

void CWrapper::publish(const std::string& topic, const std::string& payload)
{
    //TODO add a function that takes n arguments - avoid creating a string in this often called function.
    AG_LOG_DEBUG("nats client: publishing");
    AG_LOG_DEBUG(topic);
    AG_LOG_DEBUG(payload);
    auto status = natsConnection_PublishString(m_connection.get(), topic.c_str(), payload.c_str());
    if (status != NATS_OK) {
        AG_LOG_WARNING("Failed to publish message with status " + std::to_string(status) + " for topic " +  topic);
    }
}

std::string CWrapper::request(const std::string& topic, const std::string& payload)
{
    natsMsg* reply = nullptr;
    std::string result;
    auto status = natsConnection_RequestString(&reply, m_connection.get(), topic.c_str(), payload.c_str(), reply_timeout);
    if (status == NATS_OK)
    {
        // if status != NATS_OK the memory is not allocated, and should not be freed.
        std::unique_ptr<natsMsg, NatsMsgDeleter> reply_wrapped(reply, NatsMsgDeleter());
        result = std::string(natsMsg_GetData(reply_wrapped.get()));
    }
    else
    {
        AG_LOG_ERROR("No response received for "+ topic);
    }
    return result;
}
