#include "testbed2/generated/nats/manyparaminterfaceservice.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"
#include <iostream>

using namespace Test::Testbed2;
using namespace Test::Testbed2::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 4;
const uint32_t  expectedPropertiesSubscriptions = 4;
const uint32_t  initRespSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = initRespSubscription + expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

ManyParamInterfaceService::ManyParamInterfaceService(std::shared_ptr<IManyParamInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void ManyParamInterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<ManyParamInterfaceService> ManyParamInterfaceService::create(std::shared_ptr<IManyParamInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<ManyParamInterfaceService> obj(new ManyParamInterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> ManyParamInterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


ManyParamInterfaceService::~ManyParamInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void ManyParamInterfaceService::onConnected()
{
    m_onReadySubscriptionId= _subscribeForIsReady([this](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string topic = "testbed2.ManyParamInterface.service.available";
        m_service->publish(topic, "");
        _unsubscribeFromIsReady(m_onReadySubscriptionId);
    });
    subscribeTopic("testbed2.ManyParamInterface.set.prop1", [this](const auto& value){ onSetProp1(value); });
    subscribeTopic("testbed2.ManyParamInterface.set.prop2", [this](const auto& value){ onSetProp2(value); });
    subscribeTopic("testbed2.ManyParamInterface.set.prop3", [this](const auto& value){ onSetProp3(value); });
    subscribeTopic("testbed2.ManyParamInterface.set.prop4", [this](const auto& value){ onSetProp4(value); });
    subscribeRequest("testbed2.ManyParamInterface.rpc.func1", [this](const auto& args){  return onInvokeFunc1(args); });
    subscribeRequest("testbed2.ManyParamInterface.rpc.func2", [this](const auto& args){  return onInvokeFunc2(args); });
    subscribeRequest("testbed2.ManyParamInterface.rpc.func3", [this](const auto& args){  return onInvokeFunc3(args); });
    subscribeRequest("testbed2.ManyParamInterface.rpc.func4", [this](const auto& args){  return onInvokeFunc4(args); });

    const std::string initRequestTopic = "testbed2.ManyParamInterface.init";
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

nlohmann::json ManyParamInterfaceService::getState()
{
    return nlohmann::json::object({
        { "prop1", m_impl->getProp1() },
        { "prop2", m_impl->getProp2() },
        { "prop3", m_impl->getProp3() },
        { "prop4", m_impl->getProp4() }
    });
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
    static const std::string topic = "testbed2.ManyParamInterface.sig.sig1";
    nlohmann::json args = { param1 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void ManyParamInterfaceService::onSig2(int param1, int param2)
{
    (void) param1;
    (void) param2;
    static const std::string topic = "testbed2.ManyParamInterface.sig.sig2";
    nlohmann::json args = { param1, param2 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void ManyParamInterfaceService::onSig3(int param1, int param2, int param3)
{
    (void) param1;
    (void) param2;
    (void) param3;
    static const std::string topic = "testbed2.ManyParamInterface.sig.sig3";
    nlohmann::json args = { param1, param2, param3 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void ManyParamInterfaceService::onSig4(int param1, int param2, int param3, int param4)
{
    (void) param1;
    (void) param2;
    (void) param3;
    (void) param4;
    static const std::string topic = "testbed2.ManyParamInterface.sig.sig4";
    nlohmann::json args = { param1, param2, param3, param4 };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void ManyParamInterfaceService::onProp1Changed(int prop1)
{
    static const std::string topic = "testbed2.ManyParamInterface.prop.prop1";
    m_service->publish(topic, nlohmann::json(prop1).dump());
}
void ManyParamInterfaceService::onProp2Changed(int prop2)
{
    static const std::string topic = "testbed2.ManyParamInterface.prop.prop2";
    m_service->publish(topic, nlohmann::json(prop2).dump());
}
void ManyParamInterfaceService::onProp3Changed(int prop3)
{
    static const std::string topic = "testbed2.ManyParamInterface.prop.prop3";
    m_service->publish(topic, nlohmann::json(prop3).dump());
}
void ManyParamInterfaceService::onProp4Changed(int prop4)
{
    static const std::string topic = "testbed2.ManyParamInterface.prop.prop4";
    m_service->publish(topic, nlohmann::json(prop4).dump());
}
std::string ManyParamInterfaceService::onInvokeFunc1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const int& param1 = json_args.at(0).get<int>();
    auto result = m_impl->func1(param1);
    return nlohmann::json(result).dump();
}
std::string ManyParamInterfaceService::onInvokeFunc2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const int& param1 = json_args.at(0).get<int>();
    const int& param2 = json_args.at(1).get<int>();
    auto result = m_impl->func2(param1, param2);
    return nlohmann::json(result).dump();
}
std::string ManyParamInterfaceService::onInvokeFunc3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const int& param1 = json_args.at(0).get<int>();
    const int& param2 = json_args.at(1).get<int>();
    const int& param3 = json_args.at(2).get<int>();
    auto result = m_impl->func3(param1, param2, param3);
    return nlohmann::json(result).dump();
}
std::string ManyParamInterfaceService::onInvokeFunc4(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const int& param1 = json_args.at(0).get<int>();
    const int& param2 = json_args.at(1).get<int>();
    const int& param3 = json_args.at(2).get<int>();
    const int& param4 = json_args.at(3).get<int>();
    auto result = m_impl->func4(param1, param2, param3, param4);
    return nlohmann::json(result).dump();
}
