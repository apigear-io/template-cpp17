#include "tb_same2/generated/nats/samestruct1interfaceservice.h"
#include "tb_same2/generated/core/tb_same2.json.adapter.h"
#include <iostream>

using namespace Test::TbSame2;
using namespace Test::TbSame2::Nats;

SameStruct1InterfaceService::SameStruct1InterfaceService(std::shared_ptr<ISameStruct1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    : m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

SameStruct1InterfaceService::~SameStruct1InterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void SameStruct1InterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // TODO send current values through service
}
void SameStruct1InterfaceService::onSetProp1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop1 = json_args.get<Struct1>();
    m_impl->setProp1(prop1);
}
void SameStruct1InterfaceService::onSig1(const Struct1& param1)
{
    (void) param1;
//TODO use service to notify clients
}
void SameStruct1InterfaceService::onProp1Changed(const Struct1& prop1)
{
    (void)prop1;
    //TODO use service to notify clients
}
