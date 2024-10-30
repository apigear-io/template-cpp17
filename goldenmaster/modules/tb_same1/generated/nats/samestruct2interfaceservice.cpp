#include "tb_same1/generated/nats/samestruct2interfaceservice.h"
#include "tb_same1/generated/core/tb_same1.json.adapter.h"
#include <iostream>

using namespace Test::TbSame1;
using namespace Test::TbSame1::Nats;

SameStruct2InterfaceService::SameStruct2InterfaceService(std::shared_ptr<ISameStruct2Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    : m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

SameStruct2InterfaceService::~SameStruct2InterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void SameStruct2InterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // TODO send current values through service
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
//TODO use service to notify clients
}
void SameStruct2InterfaceService::onSig2(const Struct1& param1, const Struct2& param2)
{
    (void) param1;
    (void) param2;
//TODO use service to notify clients
}
void SameStruct2InterfaceService::onProp1Changed(const Struct2& prop1)
{
    (void)prop1;
    //TODO use service to notify clients
}
void SameStruct2InterfaceService::onProp2Changed(const Struct2& prop2)
{
    (void)prop2;
    //TODO use service to notify clients
}
