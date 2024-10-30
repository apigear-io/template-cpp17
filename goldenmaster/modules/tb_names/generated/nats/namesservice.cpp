#include "tb_names/generated/nats/namesservice.h"
#include "tb_names/generated/core/tb_names.json.adapter.h"
#include <iostream>

using namespace Test::TbNames;
using namespace Test::TbNames::Nats;

Nam_EsService::Nam_EsService(std::shared_ptr<INamEs> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    : m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

Nam_EsService::~Nam_EsService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void Nam_EsService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // TODO send current values through service
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
//TODO use service to notify clients
}
void Nam_EsService::onSomeSignal2(bool Some_Param)
{
    (void) Some_Param;
//TODO use service to notify clients
}
void Nam_EsService::onSwitchChanged(bool Switch)
{
    (void)Switch;
    //TODO use service to notify clients
}
void Nam_EsService::onSomePropertyChanged(int SOME_PROPERTY)
{
    (void)SOME_PROPERTY;
    //TODO use service to notify clients
}
void Nam_EsService::onSomePoperty2Changed(int Some_Poperty2)
{
    (void)Some_Poperty2;
    //TODO use service to notify clients
}
void Nam_EsService::onEnumPropertyChanged(Enum_With_Under_scoresEnum enum_property)
{
    (void)enum_property;
    //TODO use service to notify clients
}
