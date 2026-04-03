#include "tb_struct_array/generated/nats/structarrayfieldinterfaceservice.h"
#include "tb_struct_array/generated/core/tb_struct_array.json.adapter.h"
#include "apigear/utilities/logger.h"
#include <iostream>

using namespace Test::TbStructArray;
using namespace Test::TbStructArray::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 2;
const uint32_t  expectedPropertiesSubscriptions = 4;
const uint32_t  initRespSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = initRespSubscription + expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

StructArrayFieldInterfaceService::StructArrayFieldInterfaceService(std::shared_ptr<IStructArrayFieldInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void StructArrayFieldInterfaceService::init()
{
    if (m_initialized.exchange(true)) {
        AG_LOG_WARNING("init() called more than once on " "StructArrayFieldInterfaceService" ", ignoring");
        return;
    }
    std::weak_ptr<StructArrayFieldInterfaceService> weak_self = shared_from_this();
    BaseAdapter::init([weak_self](){
        if (auto self = weak_self.lock()) {
            self->onConnected();
        }
    });
}

std::shared_ptr<StructArrayFieldInterfaceService> StructArrayFieldInterfaceService::create(std::shared_ptr<IStructArrayFieldInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<StructArrayFieldInterfaceService> obj(new StructArrayFieldInterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> StructArrayFieldInterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


StructArrayFieldInterfaceService::~StructArrayFieldInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void StructArrayFieldInterfaceService::onConnected()
{
    m_onReadySubscriptionId= _subscribeForIsReady([this](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string topic = "tb.struct.array.StructArrayFieldInterface.service.available";
        m_service->publish(topic, "");
        _unsubscribeFromIsReady(m_onReadySubscriptionId);
    });
    subscribeTopic("tb.struct.array.StructArrayFieldInterface.set.propStructArray", [this](const auto& value){ onSetPropStructArray(value); });
    subscribeTopic("tb.struct.array.StructArrayFieldInterface.set.propEnumArray", [this](const auto& value){ onSetPropEnumArray(value); });
    subscribeTopic("tb.struct.array.StructArrayFieldInterface.set.propIntArray", [this](const auto& value){ onSetPropIntArray(value); });
    subscribeTopic("tb.struct.array.StructArrayFieldInterface.set.propMixed", [this](const auto& value){ onSetPropMixed(value); });
    subscribeRequest("tb.struct.array.StructArrayFieldInterface.rpc.funcMixed", [this](const auto& args){  return onInvokeFuncMixed(args); });
    subscribeRequest("tb.struct.array.StructArrayFieldInterface.rpc.funcStructArray", [this](const auto& args){  return onInvokeFuncStructArray(args); });

    const std::string initRequestTopic = "tb.struct.array.StructArrayFieldInterface.init";
    subscribeTopic(initRequestTopic, [this, initRequestTopic](const auto& value){
        nlohmann::json json_id = nlohmann::json::parse(value);
        if (json_id.empty())
        {
            return;
        }
        auto clientId = json_id.get<uint64_t>();
        auto topic = initRequestTopic + ".resp." +  std::to_string(clientId);
        auto properties = getState();
        m_service->publish(topic, properties.dump());
        }
    );

}

nlohmann::json StructArrayFieldInterfaceService::getState()
{
    return nlohmann::json::object({
        { "propStructArray", m_impl->getPropStructArray() },
        { "propEnumArray", m_impl->getPropEnumArray() },
        { "propIntArray", m_impl->getPropIntArray() },
        { "propMixed", m_impl->getPropMixed() }
    });
}
void StructArrayFieldInterfaceService::onSetPropStructArray(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propStructArray = json_args.get<StructWithArrayOfStructs>();
    m_impl->setPropStructArray(propStructArray);
}
void StructArrayFieldInterfaceService::onSetPropEnumArray(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propEnumArray = json_args.get<StructWithArrayOfEnums>();
    m_impl->setPropEnumArray(propEnumArray);
}
void StructArrayFieldInterfaceService::onSetPropIntArray(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propIntArray = json_args.get<StructWithArrayOfInts>();
    m_impl->setPropIntArray(propIntArray);
}
void StructArrayFieldInterfaceService::onSetPropMixed(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto propMixed = json_args.get<MixedStruct>();
    m_impl->setPropMixed(propMixed);
}
void StructArrayFieldInterfaceService::onSigMixed(const MixedStruct& paramMixed)
{
    (void) paramMixed;
    static const std::string topic = "tb.struct.array.StructArrayFieldInterface.sig.sigMixed";
    nlohmann::json args = { paramMixed };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void StructArrayFieldInterfaceService::onSigStructArray(const StructWithArrayOfStructs& paramPoints)
{
    (void) paramPoints;
    static const std::string topic = "tb.struct.array.StructArrayFieldInterface.sig.sigStructArray";
    nlohmann::json args = { paramPoints };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void StructArrayFieldInterfaceService::onPropStructArrayChanged(const StructWithArrayOfStructs& propStructArray)
{
    static const std::string topic = "tb.struct.array.StructArrayFieldInterface.prop.propStructArray";
    m_service->publish(topic, nlohmann::json(propStructArray).dump());
}
void StructArrayFieldInterfaceService::onPropEnumArrayChanged(const StructWithArrayOfEnums& propEnumArray)
{
    static const std::string topic = "tb.struct.array.StructArrayFieldInterface.prop.propEnumArray";
    m_service->publish(topic, nlohmann::json(propEnumArray).dump());
}
void StructArrayFieldInterfaceService::onPropIntArrayChanged(const StructWithArrayOfInts& propIntArray)
{
    static const std::string topic = "tb.struct.array.StructArrayFieldInterface.prop.propIntArray";
    m_service->publish(topic, nlohmann::json(propIntArray).dump());
}
void StructArrayFieldInterfaceService::onPropMixedChanged(const MixedStruct& propMixed)
{
    static const std::string topic = "tb.struct.array.StructArrayFieldInterface.prop.propMixed";
    m_service->publish(topic, nlohmann::json(propMixed).dump());
}
std::string StructArrayFieldInterfaceService::onInvokeFuncMixed(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const MixedStruct& paramMixed = json_args.at(0).get<MixedStruct>();
    auto result = m_impl->funcMixed(paramMixed);
    return nlohmann::json(result).dump();
}
std::string StructArrayFieldInterfaceService::onInvokeFuncStructArray(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const StructWithArrayOfStructs& paramPoints = json_args.at(0).get<StructWithArrayOfStructs>();
    auto result = m_impl->funcStructArray(paramPoints);
    return nlohmann::json(result).dump();
}
