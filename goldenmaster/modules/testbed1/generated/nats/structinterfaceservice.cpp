#include "testbed1/generated/nats/structinterfaceservice.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include <iostream>

using namespace Test::Testbed1;
using namespace Test::Testbed1::Nats;

StructInterfaceService::StructInterfaceService(std::shared_ptr<IStructInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    : m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

StructInterfaceService::~StructInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void StructInterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // TODO send current values through service
}
void StructInterfaceService::onSetPropBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propBool = json_args.get<StructBool>();
    m_impl->setPropBool(propBool);
}
void StructInterfaceService::onSetPropInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propInt = json_args.get<StructInt>();
    m_impl->setPropInt(propInt);
}
void StructInterfaceService::onSetPropFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propFloat = json_args.get<StructFloat>();
    m_impl->setPropFloat(propFloat);
}
void StructInterfaceService::onSetPropString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propString = json_args.get<StructString>();
    m_impl->setPropString(propString);
}
void StructInterfaceService::onSigBool(const StructBool& paramBool)
{
    (void) paramBool;
//TODO use service to notify clients
}
void StructInterfaceService::onSigInt(const StructInt& paramInt)
{
    (void) paramInt;
//TODO use service to notify clients
}
void StructInterfaceService::onSigFloat(const StructFloat& paramFloat)
{
    (void) paramFloat;
//TODO use service to notify clients
}
void StructInterfaceService::onSigString(const StructString& paramString)
{
    (void) paramString;
//TODO use service to notify clients
}
void StructInterfaceService::onPropBoolChanged(const StructBool& propBool)
{
    (void)propBool;
    //TODO use service to notify clients
}
void StructInterfaceService::onPropIntChanged(const StructInt& propInt)
{
    (void)propInt;
    //TODO use service to notify clients
}
void StructInterfaceService::onPropFloatChanged(const StructFloat& propFloat)
{
    (void)propFloat;
    //TODO use service to notify clients
}
void StructInterfaceService::onPropStringChanged(const StructString& propString)
{
    (void)propString;
    //TODO use service to notify clients
}
