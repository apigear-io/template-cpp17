#include "tb_simple/generated/nats/nooperationsinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <iostream>

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

NoOperationsInterfaceService::NoOperationsInterfaceService(std::shared_ptr<INoOperationsInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    : m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

NoOperationsInterfaceService::~NoOperationsInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void NoOperationsInterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // TODO send current values through service
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
//TODO use service to notify clients
}
void NoOperationsInterfaceService::onSigBool(bool paramBool)
{
    (void) paramBool;
//TODO use service to notify clients
}
void NoOperationsInterfaceService::onPropBoolChanged(bool propBool)
{
    (void)propBool;
    //TODO use service to notify clients
}
void NoOperationsInterfaceService::onPropIntChanged(int propInt)
{
    (void)propInt;
    //TODO use service to notify clients
}
