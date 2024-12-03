#include <iostream>
#include "natscwrapper.h"
#include "utilities/logger.h"
#include <memory>

using namespace ApiGear::Nats;

static void onMsg(natsConnection* /*connection*/, natsSubscription* /*subscription*/, natsMsg* msg, void* /*closure*/)
{

    std::cout<<"Received msg: "<<  natsMsg_GetSubject(msg) << " : "<<natsMsg_GetData(msg); 
    natsMsg_Destroy(msg);
}

static void asyncCb(natsConnection* /*connection*/, natsSubscription* subscription, natsStatus status, void* /*closure*/)
{
    if (status != NATS_OK)
    {
        //TODO LOG
    }
    std::cout << "subscribed for subscription" << natsSubscription_GetSubject(subscription);
}


CWrapper::CWrapper()
{


}

CWrapper::~CWrapper()
{
    natsConnection_Close(m_connection);
    natsSubscription_Destroy(m_subscription);
    natsConnection_Destroy(m_connection);
}

void CWrapper::connect(std::string address)//"nats://localhost:4222"
{
    natsOptions* opts;
    auto status = natsOptions_Create(&opts);
    if (status != NATS_OK) { /*handle*/ return; }
    //status = natsOptions_SetEventLoop(natsOptions * opts, void* loop, natsEvLoop_Attach 	attachCb, natsEvLoop_ReadAddRemove 	readCb, natsEvLoop_WriteAddRemove 	writeCb, natsEvLoop_Detach 	detachCb);
    if (status != NATS_OK) { /*handle*/ return; }
    //set error handler
    status = natsOptions_SetErrorHandler(opts, asyncCb, NULL);
    if (status != NATS_OK) { /*handle*/ return; }
    status = natsOptions_SetURL(opts, address.c_str());
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

void CWrapper::subscribe(std::string topic)
{
    auto status = natsConnection_Subscribe(&m_subscription, m_connection, topic.c_str(), onMsg, NULL);
    if (status != NATS_OK) { /*TODO HANDLE */ };
}
void CWrapper::unsubscribe(std::string topic)
{
    auto status = natsSubscription_Unsubscribe(m_subscription);
    if (status != NATS_OK) { /*TODO HANDLE */ };
}

void CWrapper::publish(std::string topic, std::string payload)
{
    auto status = natsConnection_PublishString(m_connection, topic.c_str(), payload.c_str());
    if (status != NATS_OK) { /*handle*/ return; }
}

