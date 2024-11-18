#include "tb_names/generated/nats/namesservice.h"
#include "tb_names/generated/core/tb_names.json.adapter.h"
#include <iostream>

using namespace Test::TbNames;
using namespace Test::TbNames::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 2;
const uint32_t  expectedPropertiesSubscriptions = 4;
constexpr uint32_t expectedSubscriptionsCount = expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

Nam_EsService::Nam_EsService(std::shared_ptr<INamEs> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void Nam_EsService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<Nam_EsService> Nam_EsService::create(std::shared_ptr<INamEs> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<Nam_EsService> obj(new Nam_EsService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> Nam_EsService::getSharedFromDerrived()
{
    return shared_from_this();
}


Nam_EsService::~Nam_EsService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void Nam_EsService::onConnected()
{
    subscribeTopic("tb.names.Nam_Es.set.Switch", [this](const auto& value){ onSetSwitch(value); });
    subscribeTopic("tb.names.Nam_Es.set.SOME_PROPERTY", [this](const auto& value){ onSetSomeProperty(value); });
    subscribeTopic("tb.names.Nam_Es.set.Some_Poperty2", [this](const auto& value){ onSetSomePoperty2(value); });
    subscribeTopic("tb.names.Nam_Es.set.enum_property", [this](const auto& value){ onSetEnumProperty(value); });
    subscribeRequest("tb.names.Nam_Es.rpc.SOME_FUNCTION", [this](const auto& args){  return onInvokeSomeFunction(args); });
    subscribeRequest("tb.names.Nam_Es.rpc.Some_Function2", [this](const auto& args){  return onInvokeSomeFunction2(args); });
}
void Nam_EsService::onSetSwitch(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto Switch = json_args.get<bool>();
    m_impl->setSwitch(Switch);
}
void Nam_EsService::onSetSomeProperty(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto SOME_PROPERTY = json_args.get<int>();
    m_impl->setSomeProperty(SOME_PROPERTY);
}
void Nam_EsService::onSetSomePoperty2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto Some_Poperty2 = json_args.get<int>();
    m_impl->setSomePoperty2(Some_Poperty2);
}
void Nam_EsService::onSetEnumProperty(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto enum_property = json_args.get<Enum_With_Under_scoresEnum>();
    m_impl->setEnumProperty(enum_property);
}
void Nam_EsService::onSomeSignal(bool SOME_PARAM)
{
    (void) SOME_PARAM;
    static const std::string topic = "tb.names.Nam_Es.sig.SOME_SIGNAL";
    nlohmann::json args = { SOME_PARAM };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void Nam_EsService::onSomeSignal2(bool Some_Param)
{
    (void) Some_Param;
    static const std::string topic = "tb.names.Nam_Es.sig.Some_Signal2";
    nlohmann::json args = { Some_Param };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void Nam_EsService::onSwitchChanged(bool Switch)
{
    static const std::string topic = "tb.names.Nam_Es.prop.Switch";
    m_service->publish(topic, nlohmann::json(Switch).dump());
}
void Nam_EsService::onSomePropertyChanged(int SOME_PROPERTY)
{
    static const std::string topic = "tb.names.Nam_Es.prop.SOME_PROPERTY";
    m_service->publish(topic, nlohmann::json(SOME_PROPERTY).dump());
}
void Nam_EsService::onSomePoperty2Changed(int Some_Poperty2)
{
    static const std::string topic = "tb.names.Nam_Es.prop.Some_Poperty2";
    m_service->publish(topic, nlohmann::json(Some_Poperty2).dump());
}
void Nam_EsService::onEnumPropertyChanged(Enum_With_Under_scoresEnum enum_property)
{
    static const std::string topic = "tb.names.Nam_Es.prop.enum_property";
    m_service->publish(topic, nlohmann::json(enum_property).dump());
}
std::string Nam_EsService::onInvokeSomeFunction(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const bool& SOME_PARAM = json_args.at(0).get<bool>();
    m_impl->sOME_FUNCTION(SOME_PARAM);
    return "0";
}
std::string Nam_EsService::onInvokeSomeFunction2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const bool& Some_Param = json_args.at(0).get<bool>();
    m_impl->some_Function2(Some_Param);
    return "0";
}
