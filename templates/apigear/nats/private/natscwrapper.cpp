#include <iostream>
#include "natscwrapper.h"
#include "utilities/logger.h"
#include <memory>
#include <functional>

using namespace ApiGear::Nats;

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

struct NatsSOptionsDeleter
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
        callbackWrapper->callback(natsMsg_GetData(msg));
    }
    else
    {
        //TODO HANDLE / LOG 
    }
}

static void onError(natsConnection* connection, natsSubscription* subscription, natsStatus status, void* context)
{
    uint64_t connection_id = 0;
    natsConnection_GetClientID(connection, &connection_id);
    auto subscription_id = natsSubscription_GetID(subscription);
    auto callbackStruct = static_cast<CWrapper::SubscriptionErrorContext*>(context);
    if (callbackStruct && callbackStruct->object.lock())
    {
        callbackStruct->function(connection_id, subscription_id, status);
    }
}

static void conntectionHandler(natsConnection* connection, void* context)
{
    uint64_t id;
    natsConnection_GetClientID(connection, &id);
    auto callbackStruct = static_cast<CWrapper::ConnectionCallbackContext*>(context);
    if (callbackStruct && callbackStruct->object.lock())
    {
        callbackStruct->function(id);
    }
}

static void removeSubscriptionResources(void* context)
{
    std::unique_ptr<cleanSubscriptionResourcesContext> ctx(static_cast<cleanSubscriptionResourcesContext*>(context));
    if (!ctx)
    {
        //TODO log
    }
    else if (auto client = ctx->client.lock())
    {
        ctx->function(ctx->id);
    }
}


CWrapper::CWrapper()
{
}

CWrapper::~CWrapper()
{
    natsConnection_Close(m_connection.get());
}




void CWrapper::NatsConnectionDeleter::operator()(natsConnection* conn)
{
    natsConnection_Destroy(conn);
};




void CWrapper::connect(std::string address, std::function<void(void)> connectionStateChangedCallback)
{
    m_connectionStateChangedCallback = connectionStateChangedCallback;
    if (!m_connectionHandlerContext.object.lock())
    {
        m_connectionHandlerContext.object = shared_from_this();
        m_connectionHandlerContext.function = [this](uint64_t connection_id) {handleConnectionStateChanged(connection_id); };
    }
    if (!m_subscriptionErrorContext.object.lock())
    {
        m_subscriptionErrorContext.object = shared_from_this();
        m_subscriptionErrorContext.function = [this](uint64_t connection_id, int64_t subscription_id, int status) {handleSubscriptionError(connection_id, subscription_id, status); };
    }

    natsOptions* tmp_opts;
    auto status = natsOptions_Create(&tmp_opts);
    std::unique_ptr<natsOptions, NatsSOptionsDeleter> opts(tmp_opts, NatsSOptionsDeleter());
    if (status != NATS_OK) { /*handle*/ return; }
    //status = natsOptions_SetEventLoop(natsOptions * opts, void* loop, natsEvLoop_Attach 	attachCb, natsEvLoop_ReadAddRemove 	readCb, natsEvLoop_WriteAddRemove 	writeCb, natsEvLoop_Detach 	detachCb);
    if (status != NATS_OK) { /*handle*/ return; }
    //set error handler
    status = natsOptions_SetErrorHandler(opts.get(), onError, &m_subscriptionErrorContext);
    if (status != NATS_OK) { /*handle*/ return; }
    status = natsOptions_SetURL(opts.get(), address.c_str());
    if (status != NATS_OK) { /*handle*/ return; }
    status = natsOptions_SetDisconnectedCB(opts.get(), conntectionHandler, &m_connectionHandlerContext);
    if (status != NATS_OK) { /*handle*/ return; }
    status = natsOptions_SetReconnectedCB(opts.get(), conntectionHandler, &m_connectionHandlerContext);
    if (status != NATS_OK) { /*handle*/ return; }
    status = natsOptions_SetRetryOnFailedConnect(opts.get(), true, conntectionHandler, &m_connectionHandlerContext);
    if (status != NATS_OK) { /*handle*/ return; }
    status = natsOptions_SetClosedCB(opts.get(), conntectionHandler, &m_connectionHandlerContext);
    if (status != NATS_OK) { /*handle*/ return; }
    status = natsOptions_UseGlobalMessageDelivery(opts.get(), true);
    if (status != NATS_OK) { /*handle*/ return; }
    natsConnection* connection = NULL;
    status = natsConnection_Connect(&connection, opts.get());
    m_connection.reset(connection);
    if (status != NATS_OK) { /*TODO HANDLE */ return;}
}

ConnectionStatus CWrapper::getStatus()
{
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

void CWrapper::handleConnectionStateChanged(uint64_t connection_id)
{
    uint64_t stored_connection_id;
    natsConnection_GetClientID(m_connection.get(), &stored_connection_id);
    if (connection_id == stored_connection_id && m_connectionStateChangedCallback)
    {
        m_connectionStateChangedCallback();
    }
}

void CWrapper::handleSubscriptionError(uint64_t connection_id, int64_t subscription_id, int status)
{
    uint64_t stored_connection_id;
    natsConnection_GetClientID(m_connection.get(), &stored_connection_id);
    if (connection_id != stored_connection_id)
    {
        return;
    }
    std::cout << "Error for subscription: " << subscription_id << " with status " << status;
    
}

//TODO pass eiher const& or string_view
int64_t CWrapper::subscribe(std::string topic, SimpleOnMessageCallback callback)
{
    // store callback
    std::unique_lock<std::mutex> lockCallback(m_simpleCallbacksMutex);
    m_simpleCallbacks.emplace_back(std::make_shared<SimpleCallbackWrapper>(callback));
    auto storedCallback = m_simpleCallbacks.back();
    lockCallback.unlock();
    // nats library prepares a subscription which later will be stored, it is this class responsibility to free the resources.
    natsSubscription* tmp;
    auto status = natsConnection_Subscribe(&tmp, m_connection.get(), topic.c_str(), onMsg, storedCallback.get());
    std::shared_ptr< natsSubscription> subscription_ptr(tmp, NatsSubscriptionDeleter());
    auto sub_id = natsSubscription_GetID(subscription_ptr.get());

    if (status != NATS_OK) { /*TODO HANDLE */ };
    std::unique_lock<std::mutex> lockSubscription{ m_subscriptionsMutex };
    m_subscriptions[sub_id] = subscription_ptr;
    lockSubscription.unlock();

    storedCallback->id = sub_id;
    // This callback removes all resources, the nats library states that after unsubscribe call there might be still message to serve
    // Nats library guarantees that after SetOnCompleteCB there will be no more calls for message handler for this subscription and resources can be safely cleaned up.
    status = natsSubscription_SetOnCompleteCB(subscription_ptr.get(), &removeSubscriptionResources, new cleanSubscriptionResourcesContext{sub_id, shared_from_this(), [this](uint64_t id) {cleanSubscription(id); }});
    if (status != NATS_OK) { /*TODO HANDLE */ };
    return sub_id;
}

void CWrapper::unsubscribe(int64_t id)
{
    std::unique_lock<std::mutex> lock{ m_subscriptionsMutex };
    auto found = m_subscriptions.find(id);
    lock.unlock();
    auto status = natsSubscription_Unsubscribe(found->second.get());
    if (status != NATS_OK) { /*TODO HANDLE */ };
}

void CWrapper::cleanSubscription(int64_t id)
{
    std::unique_lock<std::mutex> lockSubscriptions{ m_subscriptionsMutex };
    auto foundSubscription = m_subscriptions.find(id);
    if (foundSubscription != m_subscriptions.end())
    {
        m_subscriptions.erase(foundSubscription);
    }
    else
    {
        //TODO LOG
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
        //TODO LOG
    }
    lockCallbacks.unlock();
}

void CWrapper::publish(std::string topic, std::string payload)
{
    auto status = natsConnection_PublishString(m_connection.get(), topic.c_str(), payload.c_str());
    if (status != NATS_OK) { /*handle*/ return; }
}

