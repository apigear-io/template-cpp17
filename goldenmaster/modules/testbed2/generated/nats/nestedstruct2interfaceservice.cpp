#include "testbed2/generated/nats/nestedstruct2interfaceservice.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"
#include <iostream>

using namespace Test::Testbed2;
using namespace Test::Testbed2::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 2;
const uint32_t  expectedPropertiesSubscriptions = 2;
constexpr uint32_t expectedSubscriptionsCount = expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

NestedStruct2InterfaceService::NestedStruct2InterfaceService(std::shared_ptr<INestedStruct2Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void NestedStruct2InterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<NestedStruct2InterfaceService> NestedStruct2InterfaceService::create(std::shared_ptr<INestedStruct2Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<NestedStruct2InterfaceService> obj(new NestedStruct2InterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> NestedStruct2InterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


NestedStruct2InterfaceService::~NestedStruct2InterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void NestedStruct2InterfaceService::onConnected()
{
    subscribeTopic("testbed2.NestedStruct2Interface.set.prop1", [this](const auto& value){ onSetProp1(value); });
    subscribeTopic("testbed2.NestedStruct2Interface.set.prop2", [this](const auto& value){ onSetProp2(value); });
    subscribeRequest("testbed2.NestedStruct2Interface.rpc.func1", [this](const auto& args){  return onInvokeFunc1(args); });
    subscribeRequest("testbed2.NestedStruct2Interface.rpc.func2", [this](const auto& args){  return onInvokeFunc2(args); });
}
void NestedStruct2InterfaceService::onSetProp1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop1 = json_args.get<NestedStruct1>();
    m_impl->setProp1(prop1);
}
void NestedStruct2InterfaceService::onSetProp2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto prop2 = json_args.get<NestedStruct2>();
    m_impl->setProp2(prop2);
}
void NestedStruct2InterfaceService::onSig1(const NestedStruct1& param1)
{
    (void) param1;
    static const std::string topic = "testbed2.NestedStruct2Interface.sig.sig1";
    nlohmann::json args = { param1 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void NestedStruct2InterfaceService::onSig2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    (void) param1;
    (void) param2;
    static const std::string topic = "testbed2.NestedStruct2Interface.sig.sig2";
    nlohmann::json args = { param1, param2 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void NestedStruct2InterfaceService::onProp1Changed(const NestedStruct1& prop1)
{
    static const std::string topic = "testbed2.NestedStruct2Interface.prop.prop1";
    m_service->publish(topic, nlohmann::json(prop1).dump());
}
void NestedStruct2InterfaceService::onProp2Changed(const NestedStruct2& prop2)
{
    static const std::string topic = "testbed2.NestedStruct2Interface.prop.prop2";
    m_service->publish(topic, nlohmann::json(prop2).dump());
}
std::string NestedStruct2InterfaceService::onInvokeFunc1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const NestedStruct1& param1 = json_args.at(0).get<NestedStruct1>();
    auto result = m_impl->func1(param1);
    return nlohmann::json(result).dump();
}
std::string NestedStruct2InterfaceService::onInvokeFunc2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const NestedStruct1& param1 = json_args.at(0).get<NestedStruct1>();
    const NestedStruct2& param2 = json_args.at(1).get<NestedStruct2>();
    auto result = m_impl->func2(param1, param2);
    return nlohmann::json(result).dump();
}
