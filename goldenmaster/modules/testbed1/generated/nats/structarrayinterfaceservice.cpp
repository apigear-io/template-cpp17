#include "testbed1/generated/nats/structarrayinterfaceservice.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include <iostream>

using namespace Test::Testbed1;
using namespace Test::Testbed1::Nats;

StructArrayInterfaceService::StructArrayInterfaceService(std::shared_ptr<IStructArrayInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    : m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

StructArrayInterfaceService::~StructArrayInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void StructArrayInterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // TODO send current values through service
}
void StructArrayInterfaceService::onSetPropBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propBool = json_args.get<std::list<StructBool>>();
    m_impl->setPropBool(propBool);
}
void StructArrayInterfaceService::onSetPropInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propInt = json_args.get<std::list<StructInt>>();
    m_impl->setPropInt(propInt);
}
void StructArrayInterfaceService::onSetPropFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propFloat = json_args.get<std::list<StructFloat>>();
    m_impl->setPropFloat(propFloat);
}
void StructArrayInterfaceService::onSetPropString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propString = json_args.get<std::list<StructString>>();
    m_impl->setPropString(propString);
}
void StructArrayInterfaceService::onSigBool(const std::list<StructBool>& paramBool)
{
    (void) paramBool;
//TODO use service to notify clients
}
void StructArrayInterfaceService::onSigInt(const std::list<StructInt>& paramInt)
{
    (void) paramInt;
//TODO use service to notify clients
}
void StructArrayInterfaceService::onSigFloat(const std::list<StructFloat>& paramFloat)
{
    (void) paramFloat;
//TODO use service to notify clients
}
void StructArrayInterfaceService::onSigString(const std::list<StructString>& paramString)
{
    (void) paramString;
//TODO use service to notify clients
}
void StructArrayInterfaceService::onPropBoolChanged(const std::list<StructBool>& propBool)
{
    (void)propBool;
    //TODO use service to notify clients
}
void StructArrayInterfaceService::onPropIntChanged(const std::list<StructInt>& propInt)
{
    (void)propInt;
    //TODO use service to notify clients
}
void StructArrayInterfaceService::onPropFloatChanged(const std::list<StructFloat>& propFloat)
{
    (void)propFloat;
    //TODO use service to notify clients
}
void StructArrayInterfaceService::onPropStringChanged(const std::list<StructString>& propString)
{
    (void)propString;
    //TODO use service to notify clients
}
