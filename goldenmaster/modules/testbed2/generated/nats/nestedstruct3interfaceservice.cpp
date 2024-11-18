#include "testbed2/generated/nats/nestedstruct3interfaceservice.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"
#include <iostream>

using namespace Test::Testbed2;
using namespace Test::Testbed2::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 3;
const uint32_t  expectedPropertiesSubscriptions = 3;
constexpr uint32_t expectedSubscriptionsCount = expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

NestedStruct3InterfaceService::NestedStruct3InterfaceService(std::shared_ptr<INestedStruct3Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void NestedStruct3InterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<NestedStruct3InterfaceService> NestedStruct3InterfaceService::create(std::shared_ptr<INestedStruct3Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<NestedStruct3InterfaceService> obj(new NestedStruct3InterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> NestedStruct3InterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


NestedStruct3InterfaceService::~NestedStruct3InterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void NestedStruct3InterfaceService::onConnected()
{
    subscribeTopic("testbed2.NestedStruct3Interface.set.prop1", [this](const auto& value){ onSetProp1(value); });
    subscribeTopic("testbed2.NestedStruct3Interface.set.prop2", [this](const auto& value){ onSetProp2(value); });
    subscribeTopic("testbed2.NestedStruct3Interface.set.prop3", [this](const auto& value){ onSetProp3(value); });
    subscribeRequest("testbed2.NestedStruct3Interface.rpc.func1", [this](const auto& args){  return onInvokeFunc1(args); });
    subscribeRequest("testbed2.NestedStruct3Interface.rpc.func2", [this](const auto& args){  return onInvokeFunc2(args); });
    subscribeRequest("testbed2.NestedStruct3Interface.rpc.func3", [this](const auto& args){  return onInvokeFunc3(args); });
}
void NestedStruct3InterfaceService::onSetProp1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop1 = json_args.get<NestedStruct1>();
    m_impl->setProp1(prop1);
}
void NestedStruct3InterfaceService::onSetProp2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop2 = json_args.get<NestedStruct2>();
    m_impl->setProp2(prop2);
}
void NestedStruct3InterfaceService::onSetProp3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop3 = json_args.get<NestedStruct3>();
    m_impl->setProp3(prop3);
}
void NestedStruct3InterfaceService::onSig1(const NestedStruct1& param1)
{
    (void) param1;
    static const std::string topic = "testbed2.NestedStruct3Interface.sig.sig1";
    nlohmann::json args = { param1 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void NestedStruct3InterfaceService::onSig2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    (void) param1;
    (void) param2;
    static const std::string topic = "testbed2.NestedStruct3Interface.sig.sig2";
    nlohmann::json args = { param1, param2 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void NestedStruct3InterfaceService::onSig3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3)
{
    (void) param1;
    (void) param2;
    (void) param3;
    static const std::string topic = "testbed2.NestedStruct3Interface.sig.sig3";
    nlohmann::json args = { param1, param2, param3 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void NestedStruct3InterfaceService::onProp1Changed(const NestedStruct1& prop1)
{
    static const std::string topic = "testbed2.NestedStruct3Interface.prop.prop1";
    m_service->publish(topic, nlohmann::json(prop1).dump());
}
void NestedStruct3InterfaceService::onProp2Changed(const NestedStruct2& prop2)
{
    static const std::string topic = "testbed2.NestedStruct3Interface.prop.prop2";
    m_service->publish(topic, nlohmann::json(prop2).dump());
}
void NestedStruct3InterfaceService::onProp3Changed(const NestedStruct3& prop3)
{
    static const std::string topic = "testbed2.NestedStruct3Interface.prop.prop3";
    m_service->publish(topic, nlohmann::json(prop3).dump());
}
std::string NestedStruct3InterfaceService::onInvokeFunc1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const NestedStruct1& param1 = json_args.at(0).get<NestedStruct1>();
    auto result = m_impl->func1(param1);
    return nlohmann::json(result).dump();
}
std::string NestedStruct3InterfaceService::onInvokeFunc2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const NestedStruct1& param1 = json_args.at(0).get<NestedStruct1>();
    const NestedStruct2& param2 = json_args.at(1).get<NestedStruct2>();
    auto result = m_impl->func2(param1, param2);
    return nlohmann::json(result).dump();
}
std::string NestedStruct3InterfaceService::onInvokeFunc3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const NestedStruct1& param1 = json_args.at(0).get<NestedStruct1>();
    const NestedStruct2& param2 = json_args.at(1).get<NestedStruct2>();
    const NestedStruct3& param3 = json_args.at(2).get<NestedStruct3>();
    auto result = m_impl->func3(param1, param2, param3);
    return nlohmann::json(result).dump();
}
