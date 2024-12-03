#include "tb_same1/generated/nats/samestruct2interfaceservice.h"
#include "tb_same1/generated/core/tb_same1.json.adapter.h"
#include <iostream>

using namespace Test::TbSame1;
using namespace Test::TbSame1::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 2;
const uint32_t  expectedPropertiesSubscriptions = 2;
const uint32_t  initRespSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = initRespSubscription + expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

SameStruct2InterfaceService::SameStruct2InterfaceService(std::shared_ptr<ISameStruct2Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void SameStruct2InterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<SameStruct2InterfaceService> SameStruct2InterfaceService::create(std::shared_ptr<ISameStruct2Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<SameStruct2InterfaceService> obj(new SameStruct2InterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> SameStruct2InterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


SameStruct2InterfaceService::~SameStruct2InterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void SameStruct2InterfaceService::onConnected()
{
    m_onReadySubscriptionId= _subscribeForIsReady([this](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string topic = "tb.same1.SameStruct2Interface.service.available";
        m_service->publish(topic, "");
        _unsubscribeFromIsReady(m_onReadySubscriptionId);
    });
    subscribeTopic("tb.same1.SameStruct2Interface.set.prop1", [this](const auto& value){ onSetProp1(value); });
    subscribeTopic("tb.same1.SameStruct2Interface.set.prop2", [this](const auto& value){ onSetProp2(value); });
    subscribeRequest("tb.same1.SameStruct2Interface.rpc.func1", [this](const auto& args){  return onInvokeFunc1(args); });
    subscribeRequest("tb.same1.SameStruct2Interface.rpc.func2", [this](const auto& args){  return onInvokeFunc2(args); });

    const std::string initRequestTopic = "tb.same1.SameStruct2Interface.init";
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

nlohmann::json SameStruct2InterfaceService::getState()
{
    return nlohmann::json::object({
        { "prop1", m_impl->getProp1() },
        { "prop2", m_impl->getProp2() }
    });
}
void SameStruct2InterfaceService::onSetProp1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop1 = json_args.get<Struct2>();
    m_impl->setProp1(prop1);
}
void SameStruct2InterfaceService::onSetProp2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop2 = json_args.get<Struct2>();
    m_impl->setProp2(prop2);
}
void SameStruct2InterfaceService::onSig1(const Struct1& param1)
{
    (void) param1;
    static const std::string topic = "tb.same1.SameStruct2Interface.sig.sig1";
    nlohmann::json args = { param1 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SameStruct2InterfaceService::onSig2(const Struct1& param1, const Struct2& param2)
{
    (void) param1;
    (void) param2;
    static const std::string topic = "tb.same1.SameStruct2Interface.sig.sig2";
    nlohmann::json args = { param1, param2 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SameStruct2InterfaceService::onProp1Changed(const Struct2& prop1)
{
    static const std::string topic = "tb.same1.SameStruct2Interface.prop.prop1";
    m_service->publish(topic, nlohmann::json(prop1).dump());
}
void SameStruct2InterfaceService::onProp2Changed(const Struct2& prop2)
{
    static const std::string topic = "tb.same1.SameStruct2Interface.prop.prop2";
    m_service->publish(topic, nlohmann::json(prop2).dump());
}
std::string SameStruct2InterfaceService::onInvokeFunc1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Struct1& param1 = json_args.at(0).get<Struct1>();
    auto result = m_impl->func1(param1);
    return nlohmann::json(result).dump();
}
std::string SameStruct2InterfaceService::onInvokeFunc2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Struct1& param1 = json_args.at(0).get<Struct1>();
    const Struct2& param2 = json_args.at(1).get<Struct2>();
    auto result = m_impl->func2(param1, param2);
    return nlohmann::json(result).dump();
}
