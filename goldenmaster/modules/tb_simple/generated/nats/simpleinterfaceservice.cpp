#include "tb_simple/generated/nats/simpleinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <iostream>

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 9;
const uint32_t  expectedPropertiesSubscriptions = 8;
constexpr uint32_t expectedSubscriptionsCount = expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

SimpleInterfaceService::SimpleInterfaceService(std::shared_ptr<ISimpleInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void SimpleInterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<SimpleInterfaceService> SimpleInterfaceService::create(std::shared_ptr<ISimpleInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<SimpleInterfaceService> obj(new SimpleInterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> SimpleInterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


SimpleInterfaceService::~SimpleInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void SimpleInterfaceService::onConnected()
{
    subscribeTopic("tb.simple.SimpleInterface.set.propBool", [this](const auto& value){ onSetPropBool(value); });
    subscribeTopic("tb.simple.SimpleInterface.set.propInt", [this](const auto& value){ onSetPropInt(value); });
    subscribeTopic("tb.simple.SimpleInterface.set.propInt32", [this](const auto& value){ onSetPropInt32(value); });
    subscribeTopic("tb.simple.SimpleInterface.set.propInt64", [this](const auto& value){ onSetPropInt64(value); });
    subscribeTopic("tb.simple.SimpleInterface.set.propFloat", [this](const auto& value){ onSetPropFloat(value); });
    subscribeTopic("tb.simple.SimpleInterface.set.propFloat32", [this](const auto& value){ onSetPropFloat32(value); });
    subscribeTopic("tb.simple.SimpleInterface.set.propFloat64", [this](const auto& value){ onSetPropFloat64(value); });
    subscribeTopic("tb.simple.SimpleInterface.set.propString", [this](const auto& value){ onSetPropString(value); });
    subscribeRequest("tb.simple.SimpleInterface.rpc.funcNoReturnValue", [this](const auto& args){  return onInvokeFuncNoReturnValue(args); });
    subscribeRequest("tb.simple.SimpleInterface.rpc.funcBool", [this](const auto& args){  return onInvokeFuncBool(args); });
    subscribeRequest("tb.simple.SimpleInterface.rpc.funcInt", [this](const auto& args){  return onInvokeFuncInt(args); });
    subscribeRequest("tb.simple.SimpleInterface.rpc.funcInt32", [this](const auto& args){  return onInvokeFuncInt32(args); });
    subscribeRequest("tb.simple.SimpleInterface.rpc.funcInt64", [this](const auto& args){  return onInvokeFuncInt64(args); });
    subscribeRequest("tb.simple.SimpleInterface.rpc.funcFloat", [this](const auto& args){  return onInvokeFuncFloat(args); });
    subscribeRequest("tb.simple.SimpleInterface.rpc.funcFloat32", [this](const auto& args){  return onInvokeFuncFloat32(args); });
    subscribeRequest("tb.simple.SimpleInterface.rpc.funcFloat64", [this](const auto& args){  return onInvokeFuncFloat64(args); });
    subscribeRequest("tb.simple.SimpleInterface.rpc.funcString", [this](const auto& args){  return onInvokeFuncString(args); });
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
    static const std::string topic = "tb.simple.SimpleInterface.sig.sigBool";
    nlohmann::json args = { paramBool };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleInterfaceService::onSigInt(int paramInt)
{
    (void) paramInt;
    static const std::string topic = "tb.simple.SimpleInterface.sig.sigInt";
    nlohmann::json args = { paramInt };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleInterfaceService::onSigInt32(int32_t paramInt32)
{
    (void) paramInt32;
    static const std::string topic = "tb.simple.SimpleInterface.sig.sigInt32";
    nlohmann::json args = { paramInt32 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleInterfaceService::onSigInt64(int64_t paramInt64)
{
    (void) paramInt64;
    static const std::string topic = "tb.simple.SimpleInterface.sig.sigInt64";
    nlohmann::json args = { paramInt64 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleInterfaceService::onSigFloat(float paramFloat)
{
    (void) paramFloat;
    static const std::string topic = "tb.simple.SimpleInterface.sig.sigFloat";
    nlohmann::json args = { paramFloat };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleInterfaceService::onSigFloat32(float paramFloa32)
{
    (void) paramFloa32;
    static const std::string topic = "tb.simple.SimpleInterface.sig.sigFloat32";
    nlohmann::json args = { paramFloa32 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleInterfaceService::onSigFloat64(double paramFloat64)
{
    (void) paramFloat64;
    static const std::string topic = "tb.simple.SimpleInterface.sig.sigFloat64";
    nlohmann::json args = { paramFloat64 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleInterfaceService::onSigString(const std::string& paramString)
{
    (void) paramString;
    static const std::string topic = "tb.simple.SimpleInterface.sig.sigString";
    nlohmann::json args = { paramString };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleInterfaceService::onPropBoolChanged(bool propBool)
{
    static const std::string topic = "tb.simple.SimpleInterface.prop.propBool";
    m_service->publish(topic, nlohmann::json(propBool).dump());
}
void SimpleInterfaceService::onPropIntChanged(int propInt)
{
    static const std::string topic = "tb.simple.SimpleInterface.prop.propInt";
    m_service->publish(topic, nlohmann::json(propInt).dump());
}
void SimpleInterfaceService::onPropInt32Changed(int32_t propInt32)
{
    static const std::string topic = "tb.simple.SimpleInterface.prop.propInt32";
    m_service->publish(topic, nlohmann::json(propInt32).dump());
}
void SimpleInterfaceService::onPropInt64Changed(int64_t propInt64)
{
    static const std::string topic = "tb.simple.SimpleInterface.prop.propInt64";
    m_service->publish(topic, nlohmann::json(propInt64).dump());
}
void SimpleInterfaceService::onPropFloatChanged(float propFloat)
{
    static const std::string topic = "tb.simple.SimpleInterface.prop.propFloat";
    m_service->publish(topic, nlohmann::json(propFloat).dump());
}
void SimpleInterfaceService::onPropFloat32Changed(float propFloat32)
{
    static const std::string topic = "tb.simple.SimpleInterface.prop.propFloat32";
    m_service->publish(topic, nlohmann::json(propFloat32).dump());
}
void SimpleInterfaceService::onPropFloat64Changed(double propFloat64)
{
    static const std::string topic = "tb.simple.SimpleInterface.prop.propFloat64";
    m_service->publish(topic, nlohmann::json(propFloat64).dump());
}
void SimpleInterfaceService::onPropStringChanged(const std::string& propString)
{
    static const std::string topic = "tb.simple.SimpleInterface.prop.propString";
    m_service->publish(topic, nlohmann::json(propString).dump());
}
std::string SimpleInterfaceService::onInvokeFuncNoReturnValue(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const bool& paramBool = json_args.at(0).get<bool>();
    m_impl->funcNoReturnValue(paramBool);
    return "0";
}
std::string SimpleInterfaceService::onInvokeFuncBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const bool& paramBool = json_args.at(0).get<bool>();
    auto result = m_impl->funcBool(paramBool);
    return nlohmann::json(result).dump();
}
std::string SimpleInterfaceService::onInvokeFuncInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const int& paramInt = json_args.at(0).get<int>();
    auto result = m_impl->funcInt(paramInt);
    return nlohmann::json(result).dump();
}
std::string SimpleInterfaceService::onInvokeFuncInt32(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const int32_t& paramInt32 = json_args.at(0).get<int32_t>();
    auto result = m_impl->funcInt32(paramInt32);
    return nlohmann::json(result).dump();
}
std::string SimpleInterfaceService::onInvokeFuncInt64(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const int64_t& paramInt64 = json_args.at(0).get<int64_t>();
    auto result = m_impl->funcInt64(paramInt64);
    return nlohmann::json(result).dump();
}
std::string SimpleInterfaceService::onInvokeFuncFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const float& paramFloat = json_args.at(0).get<float>();
    auto result = m_impl->funcFloat(paramFloat);
    return nlohmann::json(result).dump();
}
std::string SimpleInterfaceService::onInvokeFuncFloat32(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const float& paramFloat32 = json_args.at(0).get<float>();
    auto result = m_impl->funcFloat32(paramFloat32);
    return nlohmann::json(result).dump();
}
std::string SimpleInterfaceService::onInvokeFuncFloat64(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const double& paramFloat = json_args.at(0).get<double>();
    auto result = m_impl->funcFloat64(paramFloat);
    return nlohmann::json(result).dump();
}
std::string SimpleInterfaceService::onInvokeFuncString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::string& paramString = json_args.at(0).get<std::string>();
    auto result = m_impl->funcString(paramString);
    return nlohmann::json(result).dump();
}
