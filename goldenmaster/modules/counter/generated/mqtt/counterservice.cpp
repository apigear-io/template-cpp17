#include "counter/generated/mqtt/counterservice.h"
#include "counter/generated/core/counter.json.adapter.h"
#include "custom_types/generated/core/custom_types.json.adapter.h"
#include "extern_types/generated/core/extern_types.json.adapter.h"
#include <iostream>

using namespace Test::Counter;
using namespace Test::Counter::MQTT;

CounterService::CounterService(std::shared_ptr<ICounter> impl, std::shared_ptr<ApiGear::MQTT::Service> service)
    : m_impl(impl)
    , m_service(service)
    , m_topics(createTopicMap())
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);

    m_connectionStatusRegistrationID = m_service->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

CounterService::~CounterService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);

    m_service->unsubscribeToConnectionStatus(m_connectionStatusRegistrationID);

    for (const auto& topic: m_topics)
    {
        m_service->unsubscribeTopic(topic. first);
    }
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> CounterService::createTopicMap()
{
    return {
        {std::string("counter/Counter/set/vector"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetVector(args); } },
        {std::string("counter/Counter/set/extern_vector"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetExternVector(args); } },
        {std::string("counter/Counter/set/vectorArray"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetVectorArray(args); } },
        {std::string("counter/Counter/set/extern_vectorArray"), [this](const std::string& args, const std::string&, const std::string&){ this->onSetExternVectorArray(args); } },
        {std::string("counter/Counter/rpc/increment"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeIncrement(args, responseTopic, correlationData); } },
        {std::string("counter/Counter/rpc/incrementArray"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeIncrementArray(args, responseTopic, correlationData); } },
        {std::string("counter/Counter/rpc/decrement"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeDecrement(args, responseTopic, correlationData); } },
        {std::string("counter/Counter/rpc/decrementArray"), [this](const std::string& args, const std::string& responseTopic, const std::string& correlationData) { this->onInvokeDecrementArray(args, responseTopic, correlationData); } },
    };
}

void CounterService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }

    for (const auto& topic: m_topics)
    {
        m_service->subscribeTopic(topic. first, topic.second);
    }

    // send current values
    onVectorChanged(m_impl->getVector());
    onExternVectorChanged(m_impl->getExternVector());
    onVectorArrayChanged(m_impl->getVectorArray());
    onExternVectorArrayChanged(m_impl->getExternVectorArray());
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
void CounterService::onInvokeIncrement(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Eigen::Vector3f& vec = json_args.at(0).get<Eigen::Vector3f>();
    auto result = m_impl->increment(vec);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void CounterService::onInvokeIncrementArray(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<Eigen::Vector3f>& vec = json_args.at(0).get<std::list<Eigen::Vector3f>>();
    auto result = m_impl->incrementArray(vec);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void CounterService::onInvokeDecrement(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const Test::CustomTypes::Vector3D& vec = json_args.at(0).get<Test::CustomTypes::Vector3D>();
    auto result = m_impl->decrement(vec);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void CounterService::onInvokeDecrementArray(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    const std::list<Test::CustomTypes::Vector3D>& vec = json_args.at(0).get<std::list<Test::CustomTypes::Vector3D>>();
    auto result = m_impl->decrementArray(vec);
    m_service->notifyInvokeResponse(responseTopic, nlohmann::json(result).dump(), correlationData);
}
void CounterService::onValueChanged(const Test::CustomTypes::Vector3D& vector, const Eigen::Vector3f& extern_vector, const std::list<Test::CustomTypes::Vector3D>& vectorArray, const std::list<Eigen::Vector3f>& extern_vectorArray)
{
    if(m_service != nullptr) {
        const nlohmann::json& args = { vector, extern_vector, vectorArray, extern_vectorArray };
        static const auto topic = std::string("counter/Counter/sig/valueChanged");
        m_service->notifySignal(topic, nlohmann::json(args).dump());
    }
}
void CounterService::onVectorChanged(const Test::CustomTypes::Vector3D& vector)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("counter/Counter/prop/vector");
        m_service->notifyPropertyChange(topic, nlohmann::json(vector).dump());
    }
}
void CounterService::onExternVectorChanged(const Eigen::Vector3f& extern_vector)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("counter/Counter/prop/extern_vector");
        m_service->notifyPropertyChange(topic, nlohmann::json(extern_vector).dump());
    }
}
void CounterService::onVectorArrayChanged(const std::list<Test::CustomTypes::Vector3D>& vectorArray)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("counter/Counter/prop/vectorArray");
        m_service->notifyPropertyChange(topic, nlohmann::json(vectorArray).dump());
    }
}
void CounterService::onExternVectorArrayChanged(const std::list<Eigen::Vector3f>& extern_vectorArray)
{
    if(m_service != nullptr) {
        static const auto topic = std::string("counter/Counter/prop/extern_vectorArray");
        m_service->notifyPropertyChange(topic, nlohmann::json(extern_vectorArray).dump());
    }
}
