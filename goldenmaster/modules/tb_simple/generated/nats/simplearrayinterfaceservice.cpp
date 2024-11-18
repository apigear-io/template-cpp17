#include "tb_simple/generated/nats/simplearrayinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <iostream>

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 8;
const uint32_t  expectedPropertiesSubscriptions = 8;
constexpr uint32_t expectedSubscriptionsCount = expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

SimpleArrayInterfaceService::SimpleArrayInterfaceService(std::shared_ptr<ISimpleArrayInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void SimpleArrayInterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<SimpleArrayInterfaceService> SimpleArrayInterfaceService::create(std::shared_ptr<ISimpleArrayInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<SimpleArrayInterfaceService> obj(new SimpleArrayInterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> SimpleArrayInterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


SimpleArrayInterfaceService::~SimpleArrayInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void SimpleArrayInterfaceService::onConnected()
{
    subscribeTopic("tb.simple.SimpleArrayInterface.set.propBool", [this](const auto& value){ onSetPropBool(value); });
    subscribeTopic("tb.simple.SimpleArrayInterface.set.propInt", [this](const auto& value){ onSetPropInt(value); });
    subscribeTopic("tb.simple.SimpleArrayInterface.set.propInt32", [this](const auto& value){ onSetPropInt32(value); });
    subscribeTopic("tb.simple.SimpleArrayInterface.set.propInt64", [this](const auto& value){ onSetPropInt64(value); });
    subscribeTopic("tb.simple.SimpleArrayInterface.set.propFloat", [this](const auto& value){ onSetPropFloat(value); });
    subscribeTopic("tb.simple.SimpleArrayInterface.set.propFloat32", [this](const auto& value){ onSetPropFloat32(value); });
    subscribeTopic("tb.simple.SimpleArrayInterface.set.propFloat64", [this](const auto& value){ onSetPropFloat64(value); });
    subscribeTopic("tb.simple.SimpleArrayInterface.set.propString", [this](const auto& value){ onSetPropString(value); });
    subscribeRequest("tb.simple.SimpleArrayInterface.rpc.funcBool", [this](const auto& args){  return onInvokeFuncBool(args); });
    subscribeRequest("tb.simple.SimpleArrayInterface.rpc.funcInt", [this](const auto& args){  return onInvokeFuncInt(args); });
    subscribeRequest("tb.simple.SimpleArrayInterface.rpc.funcInt32", [this](const auto& args){  return onInvokeFuncInt32(args); });
    subscribeRequest("tb.simple.SimpleArrayInterface.rpc.funcInt64", [this](const auto& args){  return onInvokeFuncInt64(args); });
    subscribeRequest("tb.simple.SimpleArrayInterface.rpc.funcFloat", [this](const auto& args){  return onInvokeFuncFloat(args); });
    subscribeRequest("tb.simple.SimpleArrayInterface.rpc.funcFloat32", [this](const auto& args){  return onInvokeFuncFloat32(args); });
    subscribeRequest("tb.simple.SimpleArrayInterface.rpc.funcFloat64", [this](const auto& args){  return onInvokeFuncFloat64(args); });
    subscribeRequest("tb.simple.SimpleArrayInterface.rpc.funcString", [this](const auto& args){  return onInvokeFuncString(args); });
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
    static const std::string topic = "tb.simple.SimpleArrayInterface.sig.sigBool";
    nlohmann::json args = { paramBool };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleArrayInterfaceService::onSigInt(const std::list<int>& paramInt)
{
    (void) paramInt;
    static const std::string topic = "tb.simple.SimpleArrayInterface.sig.sigInt";
    nlohmann::json args = { paramInt };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleArrayInterfaceService::onSigInt32(const std::list<int32_t>& paramInt32)
{
    (void) paramInt32;
    static const std::string topic = "tb.simple.SimpleArrayInterface.sig.sigInt32";
    nlohmann::json args = { paramInt32 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleArrayInterfaceService::onSigInt64(const std::list<int64_t>& paramInt64)
{
    (void) paramInt64;
    static const std::string topic = "tb.simple.SimpleArrayInterface.sig.sigInt64";
    nlohmann::json args = { paramInt64 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleArrayInterfaceService::onSigFloat(const std::list<float>& paramFloat)
{
    (void) paramFloat;
    static const std::string topic = "tb.simple.SimpleArrayInterface.sig.sigFloat";
    nlohmann::json args = { paramFloat };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleArrayInterfaceService::onSigFloat32(const std::list<float>& paramFloa32)
{
    (void) paramFloa32;
    static const std::string topic = "tb.simple.SimpleArrayInterface.sig.sigFloat32";
    nlohmann::json args = { paramFloa32 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleArrayInterfaceService::onSigFloat64(const std::list<double>& paramFloat64)
{
    (void) paramFloat64;
    static const std::string topic = "tb.simple.SimpleArrayInterface.sig.sigFloat64";
    nlohmann::json args = { paramFloat64 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleArrayInterfaceService::onSigString(const std::list<std::string>& paramString)
{
    (void) paramString;
    static const std::string topic = "tb.simple.SimpleArrayInterface.sig.sigString";
    nlohmann::json args = { paramString };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SimpleArrayInterfaceService::onPropBoolChanged(const std::list<bool>& propBool)
{
    static const std::string topic = "tb.simple.SimpleArrayInterface.prop.propBool";
    m_service->publish(topic, nlohmann::json(propBool).dump());
}
void SimpleArrayInterfaceService::onPropIntChanged(const std::list<int>& propInt)
{
    static const std::string topic = "tb.simple.SimpleArrayInterface.prop.propInt";
    m_service->publish(topic, nlohmann::json(propInt).dump());
}
void SimpleArrayInterfaceService::onPropInt32Changed(const std::list<int32_t>& propInt32)
{
    static const std::string topic = "tb.simple.SimpleArrayInterface.prop.propInt32";
    m_service->publish(topic, nlohmann::json(propInt32).dump());
}
void SimpleArrayInterfaceService::onPropInt64Changed(const std::list<int64_t>& propInt64)
{
    static const std::string topic = "tb.simple.SimpleArrayInterface.prop.propInt64";
    m_service->publish(topic, nlohmann::json(propInt64).dump());
}
void SimpleArrayInterfaceService::onPropFloatChanged(const std::list<float>& propFloat)
{
    static const std::string topic = "tb.simple.SimpleArrayInterface.prop.propFloat";
    m_service->publish(topic, nlohmann::json(propFloat).dump());
}
void SimpleArrayInterfaceService::onPropFloat32Changed(const std::list<float>& propFloat32)
{
    static const std::string topic = "tb.simple.SimpleArrayInterface.prop.propFloat32";
    m_service->publish(topic, nlohmann::json(propFloat32).dump());
}
void SimpleArrayInterfaceService::onPropFloat64Changed(const std::list<double>& propFloat64)
{
    static const std::string topic = "tb.simple.SimpleArrayInterface.prop.propFloat64";
    m_service->publish(topic, nlohmann::json(propFloat64).dump());
}
void SimpleArrayInterfaceService::onPropStringChanged(const std::list<std::string>& propString)
{
    static const std::string topic = "tb.simple.SimpleArrayInterface.prop.propString";
    m_service->publish(topic, nlohmann::json(propString).dump());
}
void SimpleArrayInterfaceService::onPropReadOnlyStringChanged(const std::string& propReadOnlyString)
{
    static const std::string topic = "tb.simple.SimpleArrayInterface.prop.propReadOnlyString";
    m_service->publish(topic, nlohmann::json(propReadOnlyString).dump());
}
std::string SimpleArrayInterfaceService::onInvokeFuncBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<bool>& paramBool = json_args.at(0).get<std::list<bool>>();
    auto result = m_impl->funcBool(paramBool);
    return nlohmann::json(result).dump();
}
std::string SimpleArrayInterfaceService::onInvokeFuncInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<int>& paramInt = json_args.at(0).get<std::list<int>>();
    auto result = m_impl->funcInt(paramInt);
    return nlohmann::json(result).dump();
}
std::string SimpleArrayInterfaceService::onInvokeFuncInt32(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<int32_t>& paramInt32 = json_args.at(0).get<std::list<int32_t>>();
    auto result = m_impl->funcInt32(paramInt32);
    return nlohmann::json(result).dump();
}
std::string SimpleArrayInterfaceService::onInvokeFuncInt64(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<int64_t>& paramInt64 = json_args.at(0).get<std::list<int64_t>>();
    auto result = m_impl->funcInt64(paramInt64);
    return nlohmann::json(result).dump();
}
std::string SimpleArrayInterfaceService::onInvokeFuncFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<float>& paramFloat = json_args.at(0).get<std::list<float>>();
    auto result = m_impl->funcFloat(paramFloat);
    return nlohmann::json(result).dump();
}
std::string SimpleArrayInterfaceService::onInvokeFuncFloat32(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<float>& paramFloat32 = json_args.at(0).get<std::list<float>>();
    auto result = m_impl->funcFloat32(paramFloat32);
    return nlohmann::json(result).dump();
}
std::string SimpleArrayInterfaceService::onInvokeFuncFloat64(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<double>& paramFloat = json_args.at(0).get<std::list<double>>();
    auto result = m_impl->funcFloat64(paramFloat);
    return nlohmann::json(result).dump();
}
std::string SimpleArrayInterfaceService::onInvokeFuncString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<std::string>& paramString = json_args.at(0).get<std::list<std::string>>();
    auto result = m_impl->funcString(paramString);
    return nlohmann::json(result).dump();
}
