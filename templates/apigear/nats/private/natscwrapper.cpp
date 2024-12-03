#include <iostream>
#include "natscwrapper.h"
#include "utilities/logger.h"
#include <memory>

using namespace ApiGear::Nats;

CWrapper::CWrapper()
{
}

CWrapper::~CWrapper()
{
}

void CWrapper::connect(std::string address)//"nats://localhost:4222"
{
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
}

void CWrapper::unsubscribe(std::string topic)
{
}

void CWrapper::publish(std::string topic, std::string payload)
{
}

