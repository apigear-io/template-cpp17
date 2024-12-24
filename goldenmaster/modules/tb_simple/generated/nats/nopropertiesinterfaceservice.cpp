#include "tb_simple/generated/nats/nopropertiesinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <iostream>

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 2;
const uint32_t  initRespSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = initRespSubscription + expectedMethodSubscriptions;
}

NoPropertiesInterfaceService::NoPropertiesInterfaceService(std::shared_ptr<INoPropertiesInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void NoPropertiesInterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<NoPropertiesInterfaceService> NoPropertiesInterfaceService::create(std::shared_ptr<INoPropertiesInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<NoPropertiesInterfaceService> obj(new NoPropertiesInterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> NoPropertiesInterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


NoPropertiesInterfaceService::~NoPropertiesInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void NoPropertiesInterfaceService::onConnected()
{
    m_onReadySubscriptionId= _subscribeForIsReady([this](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string topic = "tb.simple.NoPropertiesInterface.service.available";
        m_service->publish(topic, "");
        _unsubscribeFromIsReady(m_onReadySubscriptionId);
    });
    subscribeRequest("tb.simple.NoPropertiesInterface.rpc.funcVoid", [this](const auto& args){  return onInvokeFuncVoid(args); });
    subscribeRequest("tb.simple.NoPropertiesInterface.rpc.funcBool", [this](const auto& args){  return onInvokeFuncBool(args); });

    const std::string initRequestTopic = "tb.simple.NoPropertiesInterface.init";
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

nlohmann::json NoPropertiesInterfaceService::getState()
{
    return nlohmann::json::object({
    });
}
void NoPropertiesInterfaceService::onSigVoid()
{
    static const std::string topic = "tb.simple.NoPropertiesInterface.sig.sigVoid";
    nlohmann::json args = {  };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void NoPropertiesInterfaceService::onSigBool(bool paramBool)
{
    (void) paramBool;
    static const std::string topic = "tb.simple.NoPropertiesInterface.sig.sigBool";
    nlohmann::json args = { paramBool };
    m_service->publish(topic, nlohmann::json(args).dump());
}
std::string NoPropertiesInterfaceService::onInvokeFuncVoid(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_impl->funcVoid();
    return "0";
}
std::string NoPropertiesInterfaceService::onInvokeFuncBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const bool& paramBool = json_args.at(0).get<bool>();
    auto result = m_impl->funcBool(paramBool);
    return nlohmann::json(result).dump();
}
