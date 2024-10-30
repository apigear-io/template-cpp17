#include "tb_enum/generated/nats/enuminterfaceservice.h"
#include "tb_enum/generated/core/tb_enum.json.adapter.h"
#include <iostream>

using namespace Test::TbEnum;
using namespace Test::TbEnum::Nats;

EnumInterfaceService::EnumInterfaceService(std::shared_ptr<IEnumInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    : m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

EnumInterfaceService::~EnumInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void EnumInterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // TODO send current values through service
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
//TODO use service to notify clients
}
void EnumInterfaceService::onSig1(Enum1Enum param1)
{
    (void) param1;
//TODO use service to notify clients
}
void EnumInterfaceService::onSig2(Enum2Enum param2)
{
    (void) param2;
//TODO use service to notify clients
}
void EnumInterfaceService::onSig3(Enum3Enum param3)
{
    (void) param3;
//TODO use service to notify clients
}
void EnumInterfaceService::onProp0Changed(Enum0Enum prop0)
{
    (void)prop0;
    //TODO use service to notify clients
}
void EnumInterfaceService::onProp1Changed(Enum1Enum prop1)
{
    (void)prop1;
    //TODO use service to notify clients
}
void EnumInterfaceService::onProp2Changed(Enum2Enum prop2)
{
    (void)prop2;
    //TODO use service to notify clients
}
void EnumInterfaceService::onProp3Changed(Enum3Enum prop3)
{
    (void)prop3;
    //TODO use service to notify clients
}
