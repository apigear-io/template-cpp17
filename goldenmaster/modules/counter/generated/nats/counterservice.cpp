#include "counter/generated/nats/counterservice.h"
#include "counter/generated/core/counter.json.adapter.h"
#include "custom_types/generated/core/custom_types.json.adapter.h"
#include "extern_types/generated/core/extern_types.json.adapter.h"
#include <iostream>

using namespace Test::Counter;
using namespace Test::Counter::Nats;

CounterService::CounterService(std::shared_ptr<ICounter> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    : m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

CounterService::~CounterService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void CounterService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // TODO send current values through service
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
//TODO use service to notify clients
}
void CounterService::onVectorChanged(const Test::CustomTypes::Vector3D& vector)
{
    (void)vector;
    //TODO use service to notify clients
}
void CounterService::onExternVectorChanged(const Eigen::Vector3f& extern_vector)
{
    (void)extern_vector;
    //TODO use service to notify clients
}
void CounterService::onVectorArrayChanged(const std::list<Test::CustomTypes::Vector3D>& vectorArray)
{
    (void)vectorArray;
    //TODO use service to notify clients
}
void CounterService::onExternVectorArrayChanged(const std::list<Eigen::Vector3f>& extern_vectorArray)
{
    (void)extern_vectorArray;
    //TODO use service to notify clients
}
