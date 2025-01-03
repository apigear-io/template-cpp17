#include "testbed2/generated/nats/nestedstruct1interfaceservice.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"
#include <iostream>

using namespace Test::Testbed2;
using namespace Test::Testbed2::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 1;
const uint32_t  expectedPropertiesSubscriptions = 1;
const uint32_t  initRespSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = initRespSubscription + expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

NestedStruct1InterfaceService::NestedStruct1InterfaceService(std::shared_ptr<INestedStruct1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void NestedStruct1InterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<NestedStruct1InterfaceService> NestedStruct1InterfaceService::create(std::shared_ptr<INestedStruct1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<NestedStruct1InterfaceService> obj(new NestedStruct1InterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> NestedStruct1InterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


NestedStruct1InterfaceService::~NestedStruct1InterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void NestedStruct1InterfaceService::onConnected()
{
    m_onReadySubscriptionId= _subscribeForIsReady([this](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string topic = "testbed2.NestedStruct1Interface.service.available";
        m_service->publish(topic, "");
        _unsubscribeFromIsReady(m_onReadySubscriptionId);
    });
    subscribeTopic("testbed2.NestedStruct1Interface.set.prop1", [this](const auto& value){ onSetProp1(value); });
    subscribeRequest("testbed2.NestedStruct1Interface.rpc.func1", [this](const auto& args){  return onInvokeFunc1(args); });

    const std::string initRequestTopic = "testbed2.NestedStruct1Interface.init";
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

nlohmann::json NestedStruct1InterfaceService::getState()
{
    return nlohmann::json::object({
        { "prop1", m_impl->getProp1() }
    });
}
void NestedStruct1InterfaceService::onSetProp1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop1 = json_args.get<NestedStruct1>();
    m_impl->setProp1(prop1);
}
void NestedStruct1InterfaceService::onSig1(const NestedStruct1& param1)
{
    (void) param1;
    static const std::string topic = "testbed2.NestedStruct1Interface.sig.sig1";
    nlohmann::json args = { param1 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void NestedStruct1InterfaceService::onProp1Changed(const NestedStruct1& prop1)
{
    static const std::string topic = "testbed2.NestedStruct1Interface.prop.prop1";
    m_service->publish(topic, nlohmann::json(prop1).dump());
}
std::string NestedStruct1InterfaceService::onInvokeFunc1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const NestedStruct1& param1 = json_args.at(0).get<NestedStruct1>();
    auto result = m_impl->func1(param1);
    return nlohmann::json(result).dump();
}
