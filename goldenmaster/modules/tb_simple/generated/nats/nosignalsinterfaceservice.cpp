#include "tb_simple/generated/nats/nosignalsinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <iostream>

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 2;
const uint32_t  expectedPropertiesSubscriptions = 2;
const uint32_t  initRespSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = initRespSubscription + expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

NoSignalsInterfaceService::NoSignalsInterfaceService(std::shared_ptr<INoSignalsInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void NoSignalsInterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<NoSignalsInterfaceService> NoSignalsInterfaceService::create(std::shared_ptr<INoSignalsInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<NoSignalsInterfaceService> obj(new NoSignalsInterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> NoSignalsInterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


NoSignalsInterfaceService::~NoSignalsInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void NoSignalsInterfaceService::onConnected()
{
    m_onReadySubscriptionId= _subscribeForIsReady([this](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string topic = "tb.simple.NoSignalsInterface.service.available";
        m_service->publish(topic, "");
        _unsubscribeFromIsReady(m_onReadySubscriptionId);
    });
    subscribeTopic("tb.simple.NoSignalsInterface.set.propBool", [this](const auto& value){ onSetPropBool(value); });
    subscribeTopic("tb.simple.NoSignalsInterface.set.propInt", [this](const auto& value){ onSetPropInt(value); });
    subscribeRequest("tb.simple.NoSignalsInterface.rpc.funcVoid", [this](const auto& args){  return onInvokeFuncVoid(args); });
    subscribeRequest("tb.simple.NoSignalsInterface.rpc.funcBool", [this](const auto& args){  return onInvokeFuncBool(args); });

    const std::string initRequestTopic = "tb.simple.NoSignalsInterface.init";
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

nlohmann::json NoSignalsInterfaceService::getState()
{
    return nlohmann::json::object({
        { "propBool", m_impl->getPropBool() },
        { "propInt", m_impl->getPropInt() }
    });
}
void NoSignalsInterfaceService::onSetPropBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propBool = json_args.get<bool>();
    m_impl->setPropBool(propBool);
}
void NoSignalsInterfaceService::onSetPropInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propInt = json_args.get<int>();
    m_impl->setPropInt(propInt);
}
void NoSignalsInterfaceService::onPropBoolChanged(bool propBool)
{
    static const std::string topic = "tb.simple.NoSignalsInterface.prop.propBool";
    m_service->publish(topic, nlohmann::json(propBool).dump());
}
void NoSignalsInterfaceService::onPropIntChanged(int propInt)
{
    static const std::string topic = "tb.simple.NoSignalsInterface.prop.propInt";
    m_service->publish(topic, nlohmann::json(propInt).dump());
}
std::string NoSignalsInterfaceService::onInvokeFuncVoid(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_impl->funcVoid();
    return "0";
}
std::string NoSignalsInterfaceService::onInvokeFuncBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const bool& paramBool = json_args.at(0).get<bool>();
    auto result = m_impl->funcBool(paramBool);
    return nlohmann::json(result).dump();
}
