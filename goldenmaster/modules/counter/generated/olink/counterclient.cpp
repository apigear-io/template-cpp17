

#include "counter/generated/olink/counterclient.h"
#include "counter/generated/core/counter.publisher.h"
#include "counter/generated/core/counter.json.adapter.h"
#include "custom_types/generated/core/custom_types.json.adapter.h"
#include "extern_types/generated/core/extern_types.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::Counter;
using namespace Test::Counter::olink;

namespace 
{
const std::string interfaceId = "counter.Counter";
}

CounterClient::CounterClient()
    : m_publisher(std::make_unique<CounterPublisher>())
{}

void CounterClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("vector")) {
        setVectorLocal(fields["vector"].get<Test::CustomTypes::Vector3D>());
    }
    if(fields.contains("extern_vector")) {
        setExternVectorLocal(fields["extern_vector"].get<Eigen::Vector3f>());
    }
}

void CounterClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "vector") {
        setVectorLocal(value.get<Test::CustomTypes::Vector3D>());
    }
    else if ( propertyName == "extern_vector") {
        setExternVectorLocal(value.get<Eigen::Vector3f>());
    }
}

void CounterClient::setVector(const Test::CustomTypes::Vector3D& vector)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "vector");
    m_node->setRemoteProperty(propertyId, vector);
}

void CounterClient::setVectorLocal(const Test::CustomTypes::Vector3D& vector)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_vectorMutex);
        if (m_data.m_vector == vector) {
            return;
        }
        m_data.m_vector = vector;
    }

    m_publisher->publishVectorChanged(vector);
}

const Test::CustomTypes::Vector3D& CounterClient::getVector() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_vectorMutex);
    return m_data.m_vector;
}

void CounterClient::setExternVector(const Eigen::Vector3f& extern_vector)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "extern_vector");
    m_node->setRemoteProperty(propertyId, extern_vector);
}

void CounterClient::setExternVectorLocal(const Eigen::Vector3f& extern_vector)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_externVectorMutex);
        if (m_data.m_extern_vector == extern_vector) {
            return;
        }
        m_data.m_extern_vector = extern_vector;
    }

    m_publisher->publishExternVectorChanged(extern_vector);
}

const Eigen::Vector3f& CounterClient::getExternVector() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_externVectorMutex);
    return m_data.m_extern_vector;
}

Eigen::Vector3f CounterClient::increment(const Eigen::Vector3f& vec)
{
    return incrementAsync(vec).get();
}

std::future<Eigen::Vector3f> CounterClient::incrementAsync(const Eigen::Vector3f& vec)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<Eigen::Vector3f>{};
    }
    std::shared_ptr<std::promise<Eigen::Vector3f>> resultPromise = std::make_shared<std::promise<Eigen::Vector3f>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "increment");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({vec}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const Eigen::Vector3f& value = arg.value.get<Eigen::Vector3f>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

Test::CustomTypes::Vector3D CounterClient::decrement(const Test::CustomTypes::Vector3D& vec)
{
    return decrementAsync(vec).get();
}

std::future<Test::CustomTypes::Vector3D> CounterClient::decrementAsync(const Test::CustomTypes::Vector3D& vec)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<Test::CustomTypes::Vector3D>{};
    }
    std::shared_ptr<std::promise<Test::CustomTypes::Vector3D>> resultPromise = std::make_shared<std::promise<Test::CustomTypes::Vector3D>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "decrement");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({vec}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const Test::CustomTypes::Vector3D& value = arg.value.get<Test::CustomTypes::Vector3D>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::string CounterClient::olinkObjectName()
{
    return interfaceId;
}

void CounterClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    (void) args;
    (void) signalName;
}

void CounterClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void CounterClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void CounterClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool CounterClient::isReady() const
{
    return m_node != nullptr;
}

ICounterPublisher& CounterClient::_getPublisher() const
{
    return *m_publisher;
}
