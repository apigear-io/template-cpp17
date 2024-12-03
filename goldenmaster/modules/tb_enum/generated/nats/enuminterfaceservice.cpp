#include "tb_enum/generated/nats/enuminterfaceservice.h"
#include "tb_enum/generated/core/tb_enum.json.adapter.h"
#include <iostream>

using namespace Test::TbEnum;
using namespace Test::TbEnum::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 4;
const uint32_t  expectedPropertiesSubscriptions = 4;
const uint32_t  initRespSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = initRespSubscription + expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

EnumInterfaceService::EnumInterfaceService(std::shared_ptr<IEnumInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void EnumInterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<EnumInterfaceService> EnumInterfaceService::create(std::shared_ptr<IEnumInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<EnumInterfaceService> obj(new EnumInterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> EnumInterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


EnumInterfaceService::~EnumInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void EnumInterfaceService::onConnected()
{
    m_onReadySubscriptionId= _subscribeForIsReady([this](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string topic = "tb.enum.EnumInterface.service.available";
        m_service->publish(topic, "");
        _unsubscribeFromIsReady(m_onReadySubscriptionId);
    });
    subscribeTopic("tb.enum.EnumInterface.set.prop0", [this](const auto& value){ onSetProp0(value); });
    subscribeTopic("tb.enum.EnumInterface.set.prop1", [this](const auto& value){ onSetProp1(value); });
    subscribeTopic("tb.enum.EnumInterface.set.prop2", [this](const auto& value){ onSetProp2(value); });
    subscribeTopic("tb.enum.EnumInterface.set.prop3", [this](const auto& value){ onSetProp3(value); });
    subscribeRequest("tb.enum.EnumInterface.rpc.func0", [this](const auto& args){  return onInvokeFunc0(args); });
    subscribeRequest("tb.enum.EnumInterface.rpc.func1", [this](const auto& args){  return onInvokeFunc1(args); });
    subscribeRequest("tb.enum.EnumInterface.rpc.func2", [this](const auto& args){  return onInvokeFunc2(args); });
    subscribeRequest("tb.enum.EnumInterface.rpc.func3", [this](const auto& args){  return onInvokeFunc3(args); });

    const std::string initRequestTopic = "tb.enum.EnumInterface.init";
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

nlohmann::json EnumInterfaceService::getState()
{
    return nlohmann::json::object({
        { "prop0", m_impl->getProp0() },
        { "prop1", m_impl->getProp1() },
        { "prop2", m_impl->getProp2() },
        { "prop3", m_impl->getProp3() }
    });
}
void EnumInterfaceService::onSetProp0(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop0 = json_args.get<Enum0Enum>();
    m_impl->setProp0(prop0);
}
void EnumInterfaceService::onSetProp1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop1 = json_args.get<Enum1Enum>();
    m_impl->setProp1(prop1);
}
void EnumInterfaceService::onSetProp2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop2 = json_args.get<Enum2Enum>();
    m_impl->setProp2(prop2);
}
void EnumInterfaceService::onSetProp3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop3 = json_args.get<Enum3Enum>();
    m_impl->setProp3(prop3);
}
void EnumInterfaceService::onSig0(Enum0Enum param0)
{
    (void) param0;
    static const std::string topic = "tb.enum.EnumInterface.sig.sig0";
    nlohmann::json args = { param0 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void EnumInterfaceService::onSig1(Enum1Enum param1)
{
    (void) param1;
    static const std::string topic = "tb.enum.EnumInterface.sig.sig1";
    nlohmann::json args = { param1 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void EnumInterfaceService::onSig2(Enum2Enum param2)
{
    (void) param2;
    static const std::string topic = "tb.enum.EnumInterface.sig.sig2";
    nlohmann::json args = { param2 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void EnumInterfaceService::onSig3(Enum3Enum param3)
{
    (void) param3;
    static const std::string topic = "tb.enum.EnumInterface.sig.sig3";
    nlohmann::json args = { param3 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void EnumInterfaceService::onProp0Changed(Enum0Enum prop0)
{
    static const std::string topic = "tb.enum.EnumInterface.prop.prop0";
    m_service->publish(topic, nlohmann::json(prop0).dump());
}
void EnumInterfaceService::onProp1Changed(Enum1Enum prop1)
{
    static const std::string topic = "tb.enum.EnumInterface.prop.prop1";
    m_service->publish(topic, nlohmann::json(prop1).dump());
}
void EnumInterfaceService::onProp2Changed(Enum2Enum prop2)
{
    static const std::string topic = "tb.enum.EnumInterface.prop.prop2";
    m_service->publish(topic, nlohmann::json(prop2).dump());
}
void EnumInterfaceService::onProp3Changed(Enum3Enum prop3)
{
    static const std::string topic = "tb.enum.EnumInterface.prop.prop3";
    m_service->publish(topic, nlohmann::json(prop3).dump());
}
std::string EnumInterfaceService::onInvokeFunc0(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Enum0Enum& param0 = json_args.at(0).get<Enum0Enum>();
    auto result = m_impl->func0(param0);
    return nlohmann::json(result).dump();
}
std::string EnumInterfaceService::onInvokeFunc1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Enum1Enum& param1 = json_args.at(0).get<Enum1Enum>();
    auto result = m_impl->func1(param1);
    return nlohmann::json(result).dump();
}
std::string EnumInterfaceService::onInvokeFunc2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Enum2Enum& param2 = json_args.at(0).get<Enum2Enum>();
    auto result = m_impl->func2(param2);
    return nlohmann::json(result).dump();
}
std::string EnumInterfaceService::onInvokeFunc3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Enum3Enum& param3 = json_args.at(0).get<Enum3Enum>();
    auto result = m_impl->func3(param3);
    return nlohmann::json(result).dump();
}
