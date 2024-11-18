#include "testbed1/generated/nats/structinterfaceservice.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include <iostream>

using namespace Test::Testbed1;
using namespace Test::Testbed1::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 4;
const uint32_t  expectedPropertiesSubscriptions = 4;
constexpr uint32_t expectedSubscriptionsCount = expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

StructInterfaceService::StructInterfaceService(std::shared_ptr<IStructInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void StructInterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<StructInterfaceService> StructInterfaceService::create(std::shared_ptr<IStructInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<StructInterfaceService> obj(new StructInterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> StructInterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


StructInterfaceService::~StructInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void StructInterfaceService::onConnected()
{
    subscribeTopic("testbed1.StructInterface.set.propBool", [this](const auto& value){ onSetPropBool(value); });
    subscribeTopic("testbed1.StructInterface.set.propInt", [this](const auto& value){ onSetPropInt(value); });
    subscribeTopic("testbed1.StructInterface.set.propFloat", [this](const auto& value){ onSetPropFloat(value); });
    subscribeTopic("testbed1.StructInterface.set.propString", [this](const auto& value){ onSetPropString(value); });
    subscribeRequest("testbed1.StructInterface.rpc.funcBool", [this](const auto& args){  return onInvokeFuncBool(args); });
    subscribeRequest("testbed1.StructInterface.rpc.funcInt", [this](const auto& args){  return onInvokeFuncInt(args); });
    subscribeRequest("testbed1.StructInterface.rpc.funcFloat", [this](const auto& args){  return onInvokeFuncFloat(args); });
    subscribeRequest("testbed1.StructInterface.rpc.funcString", [this](const auto& args){  return onInvokeFuncString(args); });
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
    static const std::string topic = "testbed1.StructInterface.sig.sigBool";
    nlohmann::json args = { paramBool };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void StructInterfaceService::onSigInt(const StructInt& paramInt)
{
    (void) paramInt;
    static const std::string topic = "testbed1.StructInterface.sig.sigInt";
    nlohmann::json args = { paramInt };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void StructInterfaceService::onSigFloat(const StructFloat& paramFloat)
{
    (void) paramFloat;
    static const std::string topic = "testbed1.StructInterface.sig.sigFloat";
    nlohmann::json args = { paramFloat };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void StructInterfaceService::onSigString(const StructString& paramString)
{
    (void) paramString;
    static const std::string topic = "testbed1.StructInterface.sig.sigString";
    nlohmann::json args = { paramString };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void StructInterfaceService::onPropBoolChanged(const StructBool& propBool)
{
    static const std::string topic = "testbed1.StructInterface.prop.propBool";
    m_service->publish(topic, nlohmann::json(propBool).dump());
}
void StructInterfaceService::onPropIntChanged(const StructInt& propInt)
{
    static const std::string topic = "testbed1.StructInterface.prop.propInt";
    m_service->publish(topic, nlohmann::json(propInt).dump());
}
void StructInterfaceService::onPropFloatChanged(const StructFloat& propFloat)
{
    static const std::string topic = "testbed1.StructInterface.prop.propFloat";
    m_service->publish(topic, nlohmann::json(propFloat).dump());
}
void StructInterfaceService::onPropStringChanged(const StructString& propString)
{
    static const std::string topic = "testbed1.StructInterface.prop.propString";
    m_service->publish(topic, nlohmann::json(propString).dump());
}
std::string StructInterfaceService::onInvokeFuncBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructBool& paramBool = json_args.at(0).get<StructBool>();
    auto result = m_impl->funcBool(paramBool);
    return nlohmann::json(result).dump();
}
std::string StructInterfaceService::onInvokeFuncInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructInt& paramInt = json_args.at(0).get<StructInt>();
    auto result = m_impl->funcInt(paramInt);
    return nlohmann::json(result).dump();
}
std::string StructInterfaceService::onInvokeFuncFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructFloat& paramFloat = json_args.at(0).get<StructFloat>();
    auto result = m_impl->funcFloat(paramFloat);
    return nlohmann::json(result).dump();
}
std::string StructInterfaceService::onInvokeFuncString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructString& paramString = json_args.at(0).get<StructString>();
    auto result = m_impl->funcString(paramString);
    return nlohmann::json(result).dump();
}
