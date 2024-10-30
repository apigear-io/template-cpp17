#include "tb_simple/generated/nats/simplearrayinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <iostream>

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

SimpleArrayInterfaceService::SimpleArrayInterfaceService(std::shared_ptr<ISimpleArrayInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    : m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

SimpleArrayInterfaceService::~SimpleArrayInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void SimpleArrayInterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // TODO send current values through service
}
void SimpleArrayInterfaceService::onSetPropBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propBool = json_args.get<std::list<bool>>();
    m_impl->setPropBool(propBool);
}
void SimpleArrayInterfaceService::onSetPropInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propInt = json_args.get<std::list<int>>();
    m_impl->setPropInt(propInt);
}
void SimpleArrayInterfaceService::onSetPropInt32(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propInt32 = json_args.get<std::list<int32_t>>();
    m_impl->setPropInt32(propInt32);
}
void SimpleArrayInterfaceService::onSetPropInt64(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propInt64 = json_args.get<std::list<int64_t>>();
    m_impl->setPropInt64(propInt64);
}
void SimpleArrayInterfaceService::onSetPropFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propFloat = json_args.get<std::list<float>>();
    m_impl->setPropFloat(propFloat);
}
void SimpleArrayInterfaceService::onSetPropFloat32(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propFloat32 = json_args.get<std::list<float>>();
    m_impl->setPropFloat32(propFloat32);
}
void SimpleArrayInterfaceService::onSetPropFloat64(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propFloat64 = json_args.get<std::list<double>>();
    m_impl->setPropFloat64(propFloat64);
}
void SimpleArrayInterfaceService::onSetPropString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propString = json_args.get<std::list<std::string>>();
    m_impl->setPropString(propString);
}
void SimpleArrayInterfaceService::onSigBool(const std::list<bool>& paramBool)
{
    (void) paramBool;
//TODO use service to notify clients
}
void SimpleArrayInterfaceService::onSigInt(const std::list<int>& paramInt)
{
    (void) paramInt;
//TODO use service to notify clients
}
void SimpleArrayInterfaceService::onSigInt32(const std::list<int32_t>& paramInt32)
{
    (void) paramInt32;
//TODO use service to notify clients
}
void SimpleArrayInterfaceService::onSigInt64(const std::list<int64_t>& paramInt64)
{
    (void) paramInt64;
//TODO use service to notify clients
}
void SimpleArrayInterfaceService::onSigFloat(const std::list<float>& paramFloat)
{
    (void) paramFloat;
//TODO use service to notify clients
}
void SimpleArrayInterfaceService::onSigFloat32(const std::list<float>& paramFloa32)
{
    (void) paramFloa32;
//TODO use service to notify clients
}
void SimpleArrayInterfaceService::onSigFloat64(const std::list<double>& paramFloat64)
{
    (void) paramFloat64;
//TODO use service to notify clients
}
void SimpleArrayInterfaceService::onSigString(const std::list<std::string>& paramString)
{
    (void) paramString;
//TODO use service to notify clients
}
void SimpleArrayInterfaceService::onPropBoolChanged(const std::list<bool>& propBool)
{
    (void)propBool;
    //TODO use service to notify clients
}
void SimpleArrayInterfaceService::onPropIntChanged(const std::list<int>& propInt)
{
    (void)propInt;
    //TODO use service to notify clients
}
void SimpleArrayInterfaceService::onPropInt32Changed(const std::list<int32_t>& propInt32)
{
    (void)propInt32;
    //TODO use service to notify clients
}
void SimpleArrayInterfaceService::onPropInt64Changed(const std::list<int64_t>& propInt64)
{
    (void)propInt64;
    //TODO use service to notify clients
}
void SimpleArrayInterfaceService::onPropFloatChanged(const std::list<float>& propFloat)
{
    (void)propFloat;
    //TODO use service to notify clients
}
void SimpleArrayInterfaceService::onPropFloat32Changed(const std::list<float>& propFloat32)
{
    (void)propFloat32;
    //TODO use service to notify clients
}
void SimpleArrayInterfaceService::onPropFloat64Changed(const std::list<double>& propFloat64)
{
    (void)propFloat64;
    //TODO use service to notify clients
}
void SimpleArrayInterfaceService::onPropStringChanged(const std::list<std::string>& propString)
{
    (void)propString;
    //TODO use service to notify clients
}
void SimpleArrayInterfaceService::onPropReadOnlyStringChanged(const std::string& propReadOnlyString)
{
    (void)propReadOnlyString;
    //TODO use service to notify clients
}
