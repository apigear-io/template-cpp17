#include <iostream>
#include "natscwrapper.h"
#include "utilities/logger.h"
#include <memory>
#include <functional>

using namespace ApiGear::Nats;

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

static void onMsg(natsConnection* /*connection*/, natsSubscription* /*subscription*/, natsMsg* msg, void* /*context*/)
{
    // Make sure msg will be properly destroyed.
    std::shared_ptr<natsMsg> message(msg, NatsMsgDeleter());
    std::cout << "received " << natsMsg_GetData(message.get()) << std::endl;
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

CWrapper::CWrapper()
{
}

CWrapper::~CWrapper()
{
    if (m_subscription)
    {
        natsSubscription_Destroy(m_subscription);
    }
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
        m_connectionHandlerContext.object = getPtr();
        m_connectionHandlerContext.function = [this](uint64_t connection_id) {handleConnectionStateChanged(connection_id); };
    }

    natsOptions* tmp_opts;
    auto status = natsOptions_Create(&tmp_opts);
    if (status != NATS_OK) { 
        auto log = "Failed to connect. Could not configure connection. Check your connection. Error code " + std::to_string(static_cast<int>(status));
        AG_LOG_ERROR(log);
        return;
    }
    std::unique_ptr<natsOptions, NatsOptionsDeleter> opts(tmp_opts, NatsOptionsDeleter());
    status = natsOptions_SetURL(opts.get(), address.c_str());
    if (status != NATS_OK) {
        auto log = "Failed to connect. Could not configure connection (On setting host address). Error code " + std::to_string(static_cast<int>(status));
        AG_LOG_ERROR(log);
        return;
    }
    status = natsOptions_SetDisconnectedCB(opts.get(), conntectionHandler, &m_connectionHandlerContext);
    if (status != NATS_OK) {
        auto log = "Failed to connect. Could not configure connection (On configuring disconnect callback). Error code " + std::to_string(static_cast<int>(status));
        AG_LOG_ERROR(log);
        return;
    }
    status = natsOptions_SetReconnectedCB(opts.get(), conntectionHandler, &m_connectionHandlerContext);
    if (status != NATS_OK) {
        auto log = "Failed to connect. Could not configure connection (On configuring disconnect callback). Error code " + std::to_string(static_cast<int>(status));
        AG_LOG_ERROR(log);
        return;
    }
    status = natsOptions_SetRetryOnFailedConnect(opts.get(), true, conntectionHandler, &m_connectionHandlerContext);
    if (status != NATS_OK) {
        auto log = "Failed to connect. Could not configure connection (On configuring disconnect callback). Error code " + std::to_string(static_cast<int>(status));
        AG_LOG_ERROR(log);
        return;
    }
    status = natsOptions_SetClosedCB(opts.get(), conntectionHandler, &m_connectionHandlerContext);
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
    natsConnection* connection = NULL;
    status = natsConnection_Connect(&connection, opts.get());
    m_connection.reset(connection);
    if (status != NATS_OK) {
        auto log = "Failed to connect. Check your connection. Status " + std::to_string(static_cast<int>(status));
        AG_LOG_ERROR(log);
        return;
    }
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

//TODO pass eiher const& or string_view
void CWrapper::subscribe(std::string topic)
{
    auto status = natsConnection_Subscribe(&m_subscription, m_connection.get(), topic.c_str(), onMsg, NULL);
    if (status != NATS_OK) { /*TODO HANDLE */ };
}

void CWrapper::unsubscribe(std::string topic)
{
    auto status = natsSubscription_Unsubscribe(m_subscription);
    natsSubscription_Destroy(m_subscription);
    if (status != NATS_OK) { /*TODO HANDLE */ };
}

void CWrapper::publish(std::string topic, std::string payload)
{
    auto status = natsConnection_PublishString(m_connection.get(), topic.c_str(), payload.c_str());
    if (status != NATS_OK) { /*handle*/ return; }
}

