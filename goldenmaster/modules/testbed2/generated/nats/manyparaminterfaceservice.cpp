#include "testbed2/generated/nats/manyparaminterfaceservice.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"
#include <iostream>

using namespace Test::Testbed2;
using namespace Test::Testbed2::Nats;

ManyParamInterfaceService::ManyParamInterfaceService(std::shared_ptr<IManyParamInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    : m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

ManyParamInterfaceService::~ManyParamInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void ManyParamInterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // TODO send current values through service
}
void ManyParamInterfaceService::onSetProp1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop1 = json_args.get<int>();
    m_impl->setProp1(prop1);
}
void ManyParamInterfaceService::onSetProp2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop2 = json_args.get<int>();
    m_impl->setProp2(prop2);
}
void ManyParamInterfaceService::onSetProp3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop3 = json_args.get<int>();
    m_impl->setProp3(prop3);
}
void ManyParamInterfaceService::onSetProp4(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop4 = json_args.get<int>();
    m_impl->setProp4(prop4);
}
void ManyParamInterfaceService::onSig1(int param1)
{
    (void) param1;
//TODO use service to notify clients
}
void ManyParamInterfaceService::onSig2(int param1, int param2)
{
    (void) param1;
    (void) param2;
//TODO use service to notify clients
}
void ManyParamInterfaceService::onSig3(int param1, int param2, int param3)
{
    (void) param1;
    (void) param2;
    (void) param3;
//TODO use service to notify clients
}
void ManyParamInterfaceService::onSig4(int param1, int param2, int param3, int param4)
{
    (void) param1;
    (void) param2;
    (void) param3;
    (void) param4;
//TODO use service to notify clients
}
void ManyParamInterfaceService::onProp1Changed(int prop1)
{
    (void)prop1;
    //TODO use service to notify clients
}
void ManyParamInterfaceService::onProp2Changed(int prop2)
{
    (void)prop2;
    //TODO use service to notify clients
}
void ManyParamInterfaceService::onProp3Changed(int prop3)
{
    (void)prop3;
    //TODO use service to notify clients
}
void ManyParamInterfaceService::onProp4Changed(int prop4)
{
    (void)prop4;
    //TODO use service to notify clients
}
