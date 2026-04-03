#include "testbed1/generated/nats/structarray2interfaceservice.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include "apigear/utilities/logger.h"
#include <iostream>

using namespace Test::Testbed1;
using namespace Test::Testbed1::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 5;
const uint32_t  expectedPropertiesSubscriptions = 5;
const uint32_t  initRespSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = initRespSubscription + expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

StructArray2InterfaceService::StructArray2InterfaceService(std::shared_ptr<IStructArray2Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void StructArray2InterfaceService::init()
{
    if (m_initialized.exchange(true)) {
        AG_LOG_WARNING("init() called more than once on " "StructArray2InterfaceService" ", ignoring");
        return;
    }
    std::weak_ptr<StructArray2InterfaceService> weak_self = shared_from_this();
    BaseAdapter::init([weak_self](){
        if (auto self = weak_self.lock()) {
            self->onConnected();
        }
    });
}

std::shared_ptr<StructArray2InterfaceService> StructArray2InterfaceService::create(std::shared_ptr<IStructArray2Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<StructArray2InterfaceService> obj(new StructArray2InterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> StructArray2InterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


StructArray2InterfaceService::~StructArray2InterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void StructArray2InterfaceService::onConnected()
{
    m_onReadySubscriptionId= _subscribeForIsReady([this](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string topic = "testbed1.StructArray2Interface.service.available";
        m_service->publish(topic, "");
        _unsubscribeFromIsReady(m_onReadySubscriptionId);
    });
    subscribeTopic("testbed1.StructArray2Interface.set.propBool", [this](const auto& value){ onSetPropBool(value); });
    subscribeTopic("testbed1.StructArray2Interface.set.propInt", [this](const auto& value){ onSetPropInt(value); });
    subscribeTopic("testbed1.StructArray2Interface.set.propFloat", [this](const auto& value){ onSetPropFloat(value); });
    subscribeTopic("testbed1.StructArray2Interface.set.propString", [this](const auto& value){ onSetPropString(value); });
    subscribeTopic("testbed1.StructArray2Interface.set.propEnum", [this](const auto& value){ onSetPropEnum(value); });
    subscribeRequest("testbed1.StructArray2Interface.rpc.funcBool", [this](const auto& args){  return onInvokeFuncBool(args); });
    subscribeRequest("testbed1.StructArray2Interface.rpc.funcInt", [this](const auto& args){  return onInvokeFuncInt(args); });
    subscribeRequest("testbed1.StructArray2Interface.rpc.funcFloat", [this](const auto& args){  return onInvokeFuncFloat(args); });
    subscribeRequest("testbed1.StructArray2Interface.rpc.funcString", [this](const auto& args){  return onInvokeFuncString(args); });
    subscribeRequest("testbed1.StructArray2Interface.rpc.funcEnum", [this](const auto& args){  return onInvokeFuncEnum(args); });

    const std::string initRequestTopic = "testbed1.StructArray2Interface.init";
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

nlohmann::json StructArray2InterfaceService::getState()
{
    return nlohmann::json::object({
        { "propBool", m_impl->getPropBool() },
        { "propInt", m_impl->getPropInt() },
        { "propFloat", m_impl->getPropFloat() },
        { "propString", m_impl->getPropString() },
        { "propEnum", m_impl->getPropEnum() }
    });
}
void StructArray2InterfaceService::onSetPropBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propBool = json_args.get<StructBoolWithArray>();
    m_impl->setPropBool(propBool);
}
void StructArray2InterfaceService::onSetPropInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propInt = json_args.get<StructIntWithArray>();
    m_impl->setPropInt(propInt);
}
void StructArray2InterfaceService::onSetPropFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propFloat = json_args.get<StructFloatWithArray>();
    m_impl->setPropFloat(propFloat);
}
void StructArray2InterfaceService::onSetPropString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propString = json_args.get<StructStringWithArray>();
    m_impl->setPropString(propString);
}
void StructArray2InterfaceService::onSetPropEnum(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propEnum = json_args.get<StructEnumWithArray>();
    m_impl->setPropEnum(propEnum);
}
void StructArray2InterfaceService::onSigBool(const StructBoolWithArray& paramBool)
{
    (void) paramBool;
    static const std::string topic = "testbed1.StructArray2Interface.sig.sigBool";
    nlohmann::json args = { paramBool };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void StructArray2InterfaceService::onSigInt(const StructIntWithArray& paramInt)
{
    (void) paramInt;
    static const std::string topic = "testbed1.StructArray2Interface.sig.sigInt";
    nlohmann::json args = { paramInt };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void StructArray2InterfaceService::onSigFloat(const StructFloatWithArray& paramFloat)
{
    (void) paramFloat;
    static const std::string topic = "testbed1.StructArray2Interface.sig.sigFloat";
    nlohmann::json args = { paramFloat };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void StructArray2InterfaceService::onSigString(const StructStringWithArray& paramString)
{
    (void) paramString;
    static const std::string topic = "testbed1.StructArray2Interface.sig.sigString";
    nlohmann::json args = { paramString };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void StructArray2InterfaceService::onPropBoolChanged(const StructBoolWithArray& propBool)
{
    static const std::string topic = "testbed1.StructArray2Interface.prop.propBool";
    m_service->publish(topic, nlohmann::json(propBool).dump());
}
void StructArray2InterfaceService::onPropIntChanged(const StructIntWithArray& propInt)
{
    static const std::string topic = "testbed1.StructArray2Interface.prop.propInt";
    m_service->publish(topic, nlohmann::json(propInt).dump());
}
void StructArray2InterfaceService::onPropFloatChanged(const StructFloatWithArray& propFloat)
{
    static const std::string topic = "testbed1.StructArray2Interface.prop.propFloat";
    m_service->publish(topic, nlohmann::json(propFloat).dump());
}
void StructArray2InterfaceService::onPropStringChanged(const StructStringWithArray& propString)
{
    static const std::string topic = "testbed1.StructArray2Interface.prop.propString";
    m_service->publish(topic, nlohmann::json(propString).dump());
}
void StructArray2InterfaceService::onPropEnumChanged(const StructEnumWithArray& propEnum)
{
    static const std::string topic = "testbed1.StructArray2Interface.prop.propEnum";
    m_service->publish(topic, nlohmann::json(propEnum).dump());
}
std::string StructArray2InterfaceService::onInvokeFuncBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructBoolWithArray& paramBool = json_args.at(0).get<StructBoolWithArray>();
    auto result = m_impl->funcBool(paramBool);
    return nlohmann::json(result).dump();
}
std::string StructArray2InterfaceService::onInvokeFuncInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructIntWithArray& paramInt = json_args.at(0).get<StructIntWithArray>();
    auto result = m_impl->funcInt(paramInt);
    return nlohmann::json(result).dump();
}
std::string StructArray2InterfaceService::onInvokeFuncFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructFloatWithArray& paramFloat = json_args.at(0).get<StructFloatWithArray>();
    auto result = m_impl->funcFloat(paramFloat);
    return nlohmann::json(result).dump();
}
std::string StructArray2InterfaceService::onInvokeFuncString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructStringWithArray& paramString = json_args.at(0).get<StructStringWithArray>();
    auto result = m_impl->funcString(paramString);
    return nlohmann::json(result).dump();
}
std::string StructArray2InterfaceService::onInvokeFuncEnum(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructEnumWithArray& paramEnum = json_args.at(0).get<StructEnumWithArray>();
    auto result = m_impl->funcEnum(paramEnum);
    return nlohmann::json(result).dump();
}
