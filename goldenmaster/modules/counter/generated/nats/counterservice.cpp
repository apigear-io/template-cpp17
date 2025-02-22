#include "counter/generated/nats/counterservice.h"
#include "counter/generated/core/counter.json.adapter.h"
#include "custom_types/generated/core/custom_types.json.adapter.h"
#include "extern_types/generated/core/extern_types.json.adapter.h"
#include <iostream>

using namespace Test::Counter;
using namespace Test::Counter::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 4;
const uint32_t  expectedPropertiesSubscriptions = 4;
const uint32_t  initRespSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = initRespSubscription + expectedMethodSubscriptions + expectedPropertiesSubscriptions;
}

CounterService::CounterService(std::shared_ptr<ICounter> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void CounterService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<CounterService> CounterService::create(std::shared_ptr<ICounter> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<CounterService> obj(new CounterService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> CounterService::getSharedFromDerrived()
{
    return shared_from_this();
}


CounterService::~CounterService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void CounterService::onConnected()
{
    m_onReadySubscriptionId= _subscribeForIsReady([this](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string topic = "counter.Counter.service.available";
        m_service->publish(topic, "");
        _unsubscribeFromIsReady(m_onReadySubscriptionId);
    });
    subscribeTopic("counter.Counter.set.vector", [this](const auto& value){ onSetVector(value); });
    subscribeTopic("counter.Counter.set.extern_vector", [this](const auto& value){ onSetExternVector(value); });
    subscribeTopic("counter.Counter.set.vectorArray", [this](const auto& value){ onSetVectorArray(value); });
    subscribeTopic("counter.Counter.set.extern_vectorArray", [this](const auto& value){ onSetExternVectorArray(value); });
    subscribeRequest("counter.Counter.rpc.increment", [this](const auto& args){  return onInvokeIncrement(args); });
    subscribeRequest("counter.Counter.rpc.incrementArray", [this](const auto& args){  return onInvokeIncrementArray(args); });
    subscribeRequest("counter.Counter.rpc.decrement", [this](const auto& args){  return onInvokeDecrement(args); });
    subscribeRequest("counter.Counter.rpc.decrementArray", [this](const auto& args){  return onInvokeDecrementArray(args); });

    const std::string initRequestTopic = "counter.Counter.init";
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

nlohmann::json CounterService::getState()
{
    return nlohmann::json::object({
        { "vector", m_impl->getVector() },
        { "extern_vector", m_impl->getExternVector() },
        { "vectorArray", m_impl->getVectorArray() },
        { "extern_vectorArray", m_impl->getExternVectorArray() }
    });
}
void CounterService::onSetVector(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto vector = json_args.get<Test::CustomTypes::Vector3D>();
    m_impl->setVector(vector);
}
void CounterService::onSetExternVector(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto extern_vector = json_args.get<Eigen::Vector3f>();
    m_impl->setExternVector(extern_vector);
}
void CounterService::onSetVectorArray(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto vectorArray = json_args.get<std::list<Test::CustomTypes::Vector3D>>();
    m_impl->setVectorArray(vectorArray);
}
void CounterService::onSetExternVectorArray(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto extern_vectorArray = json_args.get<std::list<Eigen::Vector3f>>();
    m_impl->setExternVectorArray(extern_vectorArray);
}
void CounterService::onValueChanged(const Test::CustomTypes::Vector3D& vector, const Eigen::Vector3f& extern_vector, const std::list<Test::CustomTypes::Vector3D>& vectorArray, const std::list<Eigen::Vector3f>& extern_vectorArray)
{
    (void) vector;
    (void) extern_vector;
    (void) vectorArray;
    (void) extern_vectorArray;
    static const std::string topic = "counter.Counter.sig.valueChanged";
    nlohmann::json args = { vector, extern_vector, vectorArray, extern_vectorArray };
    m_service->publish(topic, nlohmann::json(args).dump());
}
void CounterService::onVectorChanged(const Test::CustomTypes::Vector3D& vector)
{
    static const std::string topic = "counter.Counter.prop.vector";
    m_service->publish(topic, nlohmann::json(vector).dump());
}
void CounterService::onExternVectorChanged(const Eigen::Vector3f& extern_vector)
{
    static const std::string topic = "counter.Counter.prop.extern_vector";
    m_service->publish(topic, nlohmann::json(extern_vector).dump());
}
void CounterService::onVectorArrayChanged(const std::list<Test::CustomTypes::Vector3D>& vectorArray)
{
    static const std::string topic = "counter.Counter.prop.vectorArray";
    m_service->publish(topic, nlohmann::json(vectorArray).dump());
}
void CounterService::onExternVectorArrayChanged(const std::list<Eigen::Vector3f>& extern_vectorArray)
{
    static const std::string topic = "counter.Counter.prop.extern_vectorArray";
    m_service->publish(topic, nlohmann::json(extern_vectorArray).dump());
}
std::string CounterService::onInvokeIncrement(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Eigen::Vector3f& vec = json_args.at(0).get<Eigen::Vector3f>();
    auto result = m_impl->increment(vec);
    return nlohmann::json(result).dump();
}
std::string CounterService::onInvokeIncrementArray(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<Eigen::Vector3f>& vec = json_args.at(0).get<std::list<Eigen::Vector3f>>();
    auto result = m_impl->incrementArray(vec);
    return nlohmann::json(result).dump();
}
std::string CounterService::onInvokeDecrement(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Test::CustomTypes::Vector3D& vec = json_args.at(0).get<Test::CustomTypes::Vector3D>();
    auto result = m_impl->decrement(vec);
    return nlohmann::json(result).dump();
}
std::string CounterService::onInvokeDecrementArray(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<Test::CustomTypes::Vector3D>& vec = json_args.at(0).get<std::list<Test::CustomTypes::Vector3D>>();
    auto result = m_impl->decrementArray(vec);
    return nlohmann::json(result).dump();
}
