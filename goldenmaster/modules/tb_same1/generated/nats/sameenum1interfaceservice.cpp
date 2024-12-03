#include "tb_same1/generated/nats/sameenum1interfaceservice.h"
#include "tb_same1/generated/core/tb_same1.json.adapter.h"
#include <iostream>

using namespace Test::TbSame1;
using namespace Test::TbSame1::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 1;
const uint32_t  expectedPropertiesSubscriptions = 1;
const uint32_t  initRespSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = initRespSubscription + expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

SameEnum1InterfaceService::SameEnum1InterfaceService(std::shared_ptr<ISameEnum1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void SameEnum1InterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<SameEnum1InterfaceService> SameEnum1InterfaceService::create(std::shared_ptr<ISameEnum1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<SameEnum1InterfaceService> obj(new SameEnum1InterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> SameEnum1InterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


SameEnum1InterfaceService::~SameEnum1InterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void SameEnum1InterfaceService::onConnected()
{
    m_onReadySubscriptionId= _subscribeForIsReady([this](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string topic = "tb.same1.SameEnum1Interface.service.available";
        m_service->publish(topic, "");
        _unsubscribeFromIsReady(m_onReadySubscriptionId);
    });
    subscribeTopic("tb.same1.SameEnum1Interface.set.prop1", [this](const auto& value){ onSetProp1(value); });
    subscribeRequest("tb.same1.SameEnum1Interface.rpc.func1", [this](const auto& args){  return onInvokeFunc1(args); });

    const std::string initRequestTopic = "tb.same1.SameEnum1Interface.init";
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

nlohmann::json SameEnum1InterfaceService::getState()
{
    return nlohmann::json::object({
        { "prop1", m_impl->getProp1() }
    });
}
void SameEnum1InterfaceService::onSetProp1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop1 = json_args.get<Enum1Enum>();
    m_impl->setProp1(prop1);
}
void SameEnum1InterfaceService::onSig1(Enum1Enum param1)
{
    (void) param1;
    static const std::string topic = "tb.same1.SameEnum1Interface.sig.sig1";
    nlohmann::json args = { param1 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SameEnum1InterfaceService::onProp1Changed(Enum1Enum prop1)
{
    static const std::string topic = "tb.same1.SameEnum1Interface.prop.prop1";
    m_service->publish(topic, nlohmann::json(prop1).dump());
}
std::string SameEnum1InterfaceService::onInvokeFunc1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Enum1Enum& param1 = json_args.at(0).get<Enum1Enum>();
    auto result = m_impl->func1(param1);
    return nlohmann::json(result).dump();
}
