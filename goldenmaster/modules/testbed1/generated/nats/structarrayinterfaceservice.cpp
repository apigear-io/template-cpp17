#include "testbed1/generated/nats/structarrayinterfaceservice.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include <iostream>

using namespace Test::Testbed1;
using namespace Test::Testbed1::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 4;
const uint32_t  expectedPropertiesSubscriptions = 4;
const uint32_t  initRespSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = initRespSubscription + expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

StructArrayInterfaceService::StructArrayInterfaceService(std::shared_ptr<IStructArrayInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void StructArrayInterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<StructArrayInterfaceService> StructArrayInterfaceService::create(std::shared_ptr<IStructArrayInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<StructArrayInterfaceService> obj(new StructArrayInterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> StructArrayInterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


StructArrayInterfaceService::~StructArrayInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void StructArrayInterfaceService::onConnected()
{
    m_onReadySubscriptionId= _subscribeForIsReady([this](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string topic = "testbed1.StructArrayInterface.service.available";
        m_service->publish(topic, "");
        _unsubscribeFromIsReady(m_onReadySubscriptionId);
    });
    subscribeTopic("testbed1.StructArrayInterface.set.propBool", [this](const auto& value){ onSetPropBool(value); });
    subscribeTopic("testbed1.StructArrayInterface.set.propInt", [this](const auto& value){ onSetPropInt(value); });
    subscribeTopic("testbed1.StructArrayInterface.set.propFloat", [this](const auto& value){ onSetPropFloat(value); });
    subscribeTopic("testbed1.StructArrayInterface.set.propString", [this](const auto& value){ onSetPropString(value); });
    subscribeRequest("testbed1.StructArrayInterface.rpc.funcBool", [this](const auto& args){  return onInvokeFuncBool(args); });
    subscribeRequest("testbed1.StructArrayInterface.rpc.funcInt", [this](const auto& args){  return onInvokeFuncInt(args); });
    subscribeRequest("testbed1.StructArrayInterface.rpc.funcFloat", [this](const auto& args){  return onInvokeFuncFloat(args); });
    subscribeRequest("testbed1.StructArrayInterface.rpc.funcString", [this](const auto& args){  return onInvokeFuncString(args); });

    const std::string initRequestTopic = "testbed1.StructArrayInterface.init";
    subscribeTopic(initRequestTopic, [this, initRequestTopic](const auto& value){
        nlohmann::json json_id = nlohmann::json::parse(value);
        if (json_id.empty())
        {
            return;
        }
        auto clientId = json_id.get<uint64_t>();
        auto topic = initRequestTopic + ".resp." +  std::to_string(clientId);
        auto properties = getState();
        m_service->publish(topic, properties.dump());
        }
    );

}

nlohmann::json StructArrayInterfaceService::getState()
{
    return nlohmann::json::object({
        { "propBool", m_impl->getPropBool() },
        { "propInt", m_impl->getPropInt() },
        { "propFloat", m_impl->getPropFloat() },
        { "propString", m_impl->getPropString() }
    });
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
    static const std::string topic = "testbed1.StructArrayInterface.sig.sigBool";
    nlohmann::json args = { paramBool };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void StructArrayInterfaceService::onSigInt(const std::list<StructInt>& paramInt)
{
    (void) paramInt;
    static const std::string topic = "testbed1.StructArrayInterface.sig.sigInt";
    nlohmann::json args = { paramInt };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void StructArrayInterfaceService::onSigFloat(const std::list<StructFloat>& paramFloat)
{
    (void) paramFloat;
    static const std::string topic = "testbed1.StructArrayInterface.sig.sigFloat";
    nlohmann::json args = { paramFloat };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void StructArrayInterfaceService::onSigString(const std::list<StructString>& paramString)
{
    (void) paramString;
    static const std::string topic = "testbed1.StructArrayInterface.sig.sigString";
    nlohmann::json args = { paramString };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void StructArrayInterfaceService::onPropBoolChanged(const std::list<StructBool>& propBool)
{
    static const std::string topic = "testbed1.StructArrayInterface.prop.propBool";
    m_service->publish(topic, nlohmann::json(propBool).dump());
}
void StructArrayInterfaceService::onPropIntChanged(const std::list<StructInt>& propInt)
{
    static const std::string topic = "testbed1.StructArrayInterface.prop.propInt";
    m_service->publish(topic, nlohmann::json(propInt).dump());
}
void StructArrayInterfaceService::onPropFloatChanged(const std::list<StructFloat>& propFloat)
{
    static const std::string topic = "testbed1.StructArrayInterface.prop.propFloat";
    m_service->publish(topic, nlohmann::json(propFloat).dump());
}
void StructArrayInterfaceService::onPropStringChanged(const std::list<StructString>& propString)
{
    static const std::string topic = "testbed1.StructArrayInterface.prop.propString";
    m_service->publish(topic, nlohmann::json(propString).dump());
}
std::string StructArrayInterfaceService::onInvokeFuncBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<StructBool>& paramBool = json_args.at(0).get<std::list<StructBool>>();
    auto result = m_impl->funcBool(paramBool);
    return nlohmann::json(result).dump();
}
std::string StructArrayInterfaceService::onInvokeFuncInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<StructInt>& paramInt = json_args.at(0).get<std::list<StructInt>>();
    auto result = m_impl->funcInt(paramInt);
    return nlohmann::json(result).dump();
}
std::string StructArrayInterfaceService::onInvokeFuncFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<StructFloat>& paramFloat = json_args.at(0).get<std::list<StructFloat>>();
    auto result = m_impl->funcFloat(paramFloat);
    return nlohmann::json(result).dump();
}
std::string StructArrayInterfaceService::onInvokeFuncString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<StructString>& paramString = json_args.at(0).get<std::list<StructString>>();
    auto result = m_impl->funcString(paramString);
    return nlohmann::json(result).dump();
}
