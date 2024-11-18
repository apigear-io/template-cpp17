#include "counter/generated/nats/counterservice.h"
#include "counter/generated/core/counter.json.adapter.h"
#include "custom_types/generated/core/custom_types.json.adapter.h"
#include "extern_types/generated/core/extern_types.json.adapter.h"
#include <iostream>

using namespace Test::Counter;
using namespace Test::Counter::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 2;
const uint32_t  expectedPropertiesSubscriptions = 2;
constexpr uint32_t expectedSubscriptionsCount = expectedMethodSubscriptions + expectedPropertiesSubscriptions;
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
    subscribeTopic("counter.Counter.set.vector", [this](const auto& value){ onSetVector(value); });
    subscribeTopic("counter.Counter.set.extern_vector", [this](const auto& value){ onSetExternVector(value); });
    subscribeRequest("counter.Counter.rpc.increment", [this](const auto& args){  return onInvokeIncrement(args); });
    subscribeRequest("counter.Counter.rpc.decrement", [this](const auto& args){  return onInvokeDecrement(args); });
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
std::string CounterService::onInvokeIncrement(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Eigen::Vector3f& vec = json_args.at(0).get<Eigen::Vector3f>();
    auto result = m_impl->increment(vec);
    return nlohmann::json(result).dump();
}
std::string CounterService::onInvokeDecrement(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Test::CustomTypes::Vector3D& vec = json_args.at(0).get<Test::CustomTypes::Vector3D>();
    auto result = m_impl->decrement(vec);
    return nlohmann::json(result).dump();
}
