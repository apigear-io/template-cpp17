#include "tb_simple/generated/nats/simpleinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <iostream>

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

SimpleInterfaceService::SimpleInterfaceService(std::shared_ptr<ISimpleInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    : m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

SimpleInterfaceService::~SimpleInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void SimpleInterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // TODO send current values through service
}
void SimpleInterfaceService::onSetPropBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propBool = json_args.get<bool>();
    m_impl->setPropBool(propBool);
}
void SimpleInterfaceService::onSetPropInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propInt = json_args.get<int>();
    m_impl->setPropInt(propInt);
}
void SimpleInterfaceService::onSetPropInt32(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propInt32 = json_args.get<int32_t>();
    m_impl->setPropInt32(propInt32);
}
void SimpleInterfaceService::onSetPropInt64(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propInt64 = json_args.get<int64_t>();
    m_impl->setPropInt64(propInt64);
}
void SimpleInterfaceService::onSetPropFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propFloat = json_args.get<float>();
    m_impl->setPropFloat(propFloat);
}
void SimpleInterfaceService::onSetPropFloat32(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propFloat32 = json_args.get<float>();
    m_impl->setPropFloat32(propFloat32);
}
void SimpleInterfaceService::onSetPropFloat64(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propFloat64 = json_args.get<double>();
    m_impl->setPropFloat64(propFloat64);
}
void SimpleInterfaceService::onSetPropString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propString = json_args.get<std::string>();
    m_impl->setPropString(propString);
}
void SimpleInterfaceService::onSigBool(bool paramBool)
{
    (void) paramBool;
//TODO use service to notify clients
}
void SimpleInterfaceService::onSigInt(int paramInt)
{
    (void) paramInt;
//TODO use service to notify clients
}
void SimpleInterfaceService::onSigInt32(int32_t paramInt32)
{
    (void) paramInt32;
//TODO use service to notify clients
}
void SimpleInterfaceService::onSigInt64(int64_t paramInt64)
{
    (void) paramInt64;
//TODO use service to notify clients
}
void SimpleInterfaceService::onSigFloat(float paramFloat)
{
    (void) paramFloat;
//TODO use service to notify clients
}
void SimpleInterfaceService::onSigFloat32(float paramFloa32)
{
    (void) paramFloa32;
//TODO use service to notify clients
}
void SimpleInterfaceService::onSigFloat64(double paramFloat64)
{
    (void) paramFloat64;
//TODO use service to notify clients
}
void SimpleInterfaceService::onSigString(const std::string& paramString)
{
    (void) paramString;
//TODO use service to notify clients
}
void SimpleInterfaceService::onPropBoolChanged(bool propBool)
{
    (void)propBool;
    //TODO use service to notify clients
}
void SimpleInterfaceService::onPropIntChanged(int propInt)
{
    (void)propInt;
    //TODO use service to notify clients
}
void SimpleInterfaceService::onPropInt32Changed(int32_t propInt32)
{
    (void)propInt32;
    //TODO use service to notify clients
}
void SimpleInterfaceService::onPropInt64Changed(int64_t propInt64)
{
    (void)propInt64;
    //TODO use service to notify clients
}
void SimpleInterfaceService::onPropFloatChanged(float propFloat)
{
    (void)propFloat;
    //TODO use service to notify clients
}
void SimpleInterfaceService::onPropFloat32Changed(float propFloat32)
{
    (void)propFloat32;
    //TODO use service to notify clients
}
void SimpleInterfaceService::onPropFloat64Changed(double propFloat64)
{
    (void)propFloat64;
    //TODO use service to notify clients
}
void SimpleInterfaceService::onPropStringChanged(const std::string& propString)
{
    (void)propString;
    //TODO use service to notify clients
}
