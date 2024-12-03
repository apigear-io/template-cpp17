#include <iostream>
#include "natscwrapper.h"
#include "utilities/logger.h"
#include <memory>
#include <functional>

using namespace ApiGear::Nats;

static void onMsg(natsConnection* /*connection*/, natsSubscription* /*subscription*/, natsMsg* msg, void* /*closure*/)
{
    std::cout<<"Received msg: "<<  natsMsg_GetSubject(msg) << " : "<<natsMsg_GetData(msg) << std::endl;
    natsMsg_Destroy(msg);
}

static void onError(natsConnection* /*connection*/, natsSubscription* subscription, natsStatus status, void* /*closure*/)
{
    if (status != NATS_OK)
    {
        //TODO LOG
    }
    std::cout << "subscribed for subscription" << natsSubscription_GetSubject(subscription) << std::endl;
}

static void conntectionHandler(natsConnection* connection, void* context)
{
    auto status = natsConnection_Status(connection);
    std::cout << "connection handler " << static_cast<int>(status)<< std::endl;
    auto callbackStruct = static_cast<CWrapper::ConnectionCallbackContext*>(context);
    if (callbackStruct && callbackStruct->function)
    {
        callbackStruct->function();
    }
    else
    {
        //TODO LOG
    }
}

static void alreadyUnsubscribed(void* /*closure*/)
{
    std::cout << "received message for already unsubscribed subscription - TODO pass name" << std::endl;
}


CWrapper::CWrapper()
{


}

CWrapper::~CWrapper()
{
    natsConnection_Close(m_connection);
    //natsSubscription_Destroy(m_subscription);
    natsConnection_Destroy(m_connection);
}


struct NatsSubscriptionDeleter
{
    void operator()(natsSubscription* s)
    {
        natsSubscription_Destroy(s);
    }
};


void CWrapper::connect(std::string address, std::function<void(void)> connectionStateChangedCallback)
{
    //TODO ensure that context is valid even if class is destroyed already;
    m_connectionStateChangedCallback = ConnectionCallbackContext{ connectionStateChangedCallback };

    natsOptions* opts;
    auto status = natsOptions_Create(&opts);
    if (status != NATS_OK) { /*handle*/ return; }
    //status = natsOptions_SetEventLoop(natsOptions * opts, void* loop, natsEvLoop_Attach 	attachCb, natsEvLoop_ReadAddRemove 	readCb, natsEvLoop_WriteAddRemove 	writeCb, natsEvLoop_Detach 	detachCb);
    if (status != NATS_OK) { /*handle*/ return; }
    //set error handler
    status = natsOptions_SetErrorHandler(opts, onError, NULL);
    if (status != NATS_OK) { /*handle*/ return; }
    status = natsOptions_SetURL(opts, address.c_str());
    if (status != NATS_OK) { /*handle*/ return; }
    status = natsOptions_SetDisconnectedCB(opts, conntectionHandler, &m_connectionStateChangedCallback);
    if (status != NATS_OK) { /*handle*/ return; }
    status = natsOptions_SetReconnectedCB(opts, conntectionHandler, &m_connectionStateChangedCallback);
    if (status != NATS_OK) { /*handle*/ return; }
    status = natsOptions_SetRetryOnFailedConnect(opts, true, conntectionHandler, &m_connectionStateChangedCallback);
    if (status != NATS_OK) { /*handle*/ return; }
    status = natsOptions_SetClosedCB(opts, conntectionHandler, &m_connectionStateChangedCallback);
    if (status != NATS_OK) { /*handle*/ return; }
    status = natsOptions_UseGlobalMessageDelivery(opts, true);
    if (status != NATS_OK) { /*handle*/ return; }
    status = natsConnection_Connect(&m_connection, opts);
    if (status != NATS_OK) { /*TODO HANDLE */ return;}
    natsOptions_Destroy(opts); // use custom deleter with this function call? and similar for all other nats *
}

ConnectionStatus CWrapper::getStatus()
{
    if (!m_connection)
    {
        return ConnectionStatus::disconnected;
    }
    auto status = natsConnection_Status(m_connection);
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

//TODO pass eiher const& or string_view
int64_t CWrapper::subscribe(std::string topic, SimpleOnMessageCallback callback)
{
    natsSubscription* tmp;
    auto status = natsConnection_Subscribe(&tmp, m_connection, topic.c_str(), onMsg, NULL);
    if (status != NATS_OK) { /*TODO HANDLE */ };
    std::shared_ptr< natsSubscription> sub(tmp, NatsSubscriptionDeleter());
    m_subscriptions.push_back(sub);
    auto subscription_ptr = m_subscriptions.back().get();
    status = natsSubscription_SetOnCompleteCB(subscription_ptr, &alreadyUnsubscribed, NULL);
    if (status != NATS_OK) { /*TODO HANDLE */ };
    return natsSubscription_GetID(subscription_ptr);
}

//TODO id not string
void CWrapper::unsubscribe(int64_t id)
{
    std::unique_lock<std::mutex> lock{ m_subscriptionsMutex };
    auto found = find_if(m_subscriptions.begin(), m_subscriptions.end(), [id](auto element) { return  natsSubscription_GetID(element.get()) == id; });
    lock.unlock();
    auto status = natsSubscription_Unsubscribe((*found).get());
    m_subscriptions.erase(found);
    lock.unlock();
    if (status != NATS_OK) { /*TODO HANDLE */ };
}

void CWrapper::publish(std::string topic, std::string payload)
{
    auto status = natsConnection_PublishString(m_connection, topic.c_str(), payload.c_str());
    if (status != NATS_OK) { /*handle*/ return; }
}

