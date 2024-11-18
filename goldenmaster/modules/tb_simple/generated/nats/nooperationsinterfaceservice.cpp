#include "tb_simple/generated/nats/nooperationsinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <iostream>

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 0;
const uint32_t  expectedPropertiesSubscriptions = 2;
constexpr uint32_t expectedSubscriptionsCount = expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

NoOperationsInterfaceService::NoOperationsInterfaceService(std::shared_ptr<INoOperationsInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void NoOperationsInterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<NoOperationsInterfaceService> NoOperationsInterfaceService::create(std::shared_ptr<INoOperationsInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<NoOperationsInterfaceService> obj(new NoOperationsInterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> NoOperationsInterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


NoOperationsInterfaceService::~NoOperationsInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void NoOperationsInterfaceService::onConnected()
{
    subscribeTopic("tb.simple.NoOperationsInterface.set.propBool", [this](const auto& value){ onSetPropBool(value); });
    subscribeTopic("tb.simple.NoOperationsInterface.set.propInt", [this](const auto& value){ onSetPropInt(value); });
}
void NoOperationsInterfaceService::onSetPropBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propBool = json_args.get<bool>();
    m_impl->setPropBool(propBool);
}
void NoOperationsInterfaceService::onSetPropInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propInt = json_args.get<int>();
    m_impl->setPropInt(propInt);
}
void NoOperationsInterfaceService::onSigVoid()
{
    static const std::string topic = "tb.simple.NoOperationsInterface.sig.sigVoid";
    nlohmann::json args = {  };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void NoOperationsInterfaceService::onSigBool(bool paramBool)
{
    (void) paramBool;
    static const std::string topic = "tb.simple.NoOperationsInterface.sig.sigBool";
    nlohmann::json args = { paramBool };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void NoOperationsInterfaceService::onPropBoolChanged(bool propBool)
{
    static const std::string topic = "tb.simple.NoOperationsInterface.prop.propBool";
    m_service->publish(topic, nlohmann::json(propBool).dump());
}
void NoOperationsInterfaceService::onPropIntChanged(int propInt)
{
    static const std::string topic = "tb.simple.NoOperationsInterface.prop.propInt";
    m_service->publish(topic, nlohmann::json(propInt).dump());
}
