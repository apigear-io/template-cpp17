#include "tb_same2/generated/nats/samestruct1interfaceservice.h"
#include "tb_same2/generated/core/tb_same2.json.adapter.h"
#include <iostream>

using namespace Test::TbSame2;
using namespace Test::TbSame2::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 1;
const uint32_t  expectedPropertiesSubscriptions = 1;
constexpr uint32_t expectedSubscriptionsCount = expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

SameStruct1InterfaceService::SameStruct1InterfaceService(std::shared_ptr<ISameStruct1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void SameStruct1InterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<SameStruct1InterfaceService> SameStruct1InterfaceService::create(std::shared_ptr<ISameStruct1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<SameStruct1InterfaceService> obj(new SameStruct1InterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> SameStruct1InterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


SameStruct1InterfaceService::~SameStruct1InterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void SameStruct1InterfaceService::onConnected()
{
    subscribeTopic("tb.same2.SameStruct1Interface.set.prop1", [this](const auto& value){ onSetProp1(value); });
    subscribeRequest("tb.same2.SameStruct1Interface.rpc.func1", [this](const auto& args){  return onInvokeFunc1(args); });
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
    static const std::string topic = "tb.same2.SameStruct1Interface.sig.sig1";
    nlohmann::json args = { param1 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void SameStruct1InterfaceService::onProp1Changed(const Struct1& prop1)
{
    static const std::string topic = "tb.same2.SameStruct1Interface.prop.prop1";
    m_service->publish(topic, nlohmann::json(prop1).dump());
}
std::string SameStruct1InterfaceService::onInvokeFunc1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Struct1& param1 = json_args.at(0).get<Struct1>();
    auto result = m_impl->func1(param1);
    return nlohmann::json(result).dump();
}
