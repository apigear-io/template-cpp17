

#include "counter/generated/api/datastructs.api.h"
#include "counter/generated/olink/counterservice.h"
#include "counter/generated/core/counter.json.adapter.h"
#include "custom_types/generated/core/custom_types.json.adapter.h"
#include "extern_types/generated/core/extern_types.json.adapter.h"

#include "olink/iremotenode.h"
#include "olink/remoteregistry.h"
#include "apigear/utilities/logger.h"

#include <iostream>


using namespace Test::Counter;
using namespace Test::Counter::olink;

namespace 
{
const std::string interfaceId = "counter.Counter";
}

CounterService::CounterService(std::shared_ptr<ICounter> Counter, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_Counter(Counter)
    , m_registry(registry)
{
    m_Counter->_getPublisher().subscribeToAllChanges(*this);
}

CounterService::~CounterService()
{
    m_Counter->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string CounterService::olinkObjectName() {
    return interfaceId;
}

nlohmann::json CounterService::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("CounterService invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "increment") {
        const Eigen::Vector3f& vec = fcnArgs.at(0);
        Eigen::Vector3f result = m_Counter->increment(vec);
        return result;
    }
    if(memberMethod == "incrementArray") {
        const std::list<Eigen::Vector3f>& vec = fcnArgs.at(0);
        std::list<Eigen::Vector3f> result = m_Counter->incrementArray(vec);
        return result;
    }
    if(memberMethod == "decrement") {
        const Test::CustomTypes::Vector3D& vec = fcnArgs.at(0);
        Test::CustomTypes::Vector3D result = m_Counter->decrement(vec);
        return result;
    }
    if(memberMethod == "decrementArray") {
        const std::list<Test::CustomTypes::Vector3D>& vec = fcnArgs.at(0);
        std::list<Test::CustomTypes::Vector3D> result = m_Counter->decrementArray(vec);
        return result;
    }
    return nlohmann::json();
}

void CounterService::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("CounterService set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    if(memberProperty == "vector") {
        Test::CustomTypes::Vector3D vector = value.get<Test::CustomTypes::Vector3D>();
        m_Counter->setVector(vector);
    }
    if(memberProperty == "extern_vector") {
        Eigen::Vector3f extern_vector = value.get<Eigen::Vector3f>();
        m_Counter->setExternVector(extern_vector);
    }
    if(memberProperty == "vectorArray") {
        std::list<Test::CustomTypes::Vector3D> vectorArray = value.get<std::list<Test::CustomTypes::Vector3D>>();
        m_Counter->setVectorArray(vectorArray);
    }
    if(memberProperty == "extern_vectorArray") {
        std::list<Eigen::Vector3f> extern_vectorArray = value.get<std::list<Eigen::Vector3f>>();
        m_Counter->setExternVectorArray(extern_vectorArray);
    } 
}

void CounterService::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("CounterService linked " + objectId);
}

void CounterService::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("CounterService unlinked " + objectId);
}

nlohmann::json CounterService::olinkCollectProperties()
{
    return nlohmann::json::object({
        { "vector", m_Counter->getVector() },
        { "extern_vector", m_Counter->getExternVector() },
        { "vectorArray", m_Counter->getVectorArray() },
        { "extern_vectorArray", m_Counter->getExternVectorArray() }
    });
}
void CounterService::onValueChanged(const Test::CustomTypes::Vector3D& vector, const Eigen::Vector3f& extern_vector, const std::list<Test::CustomTypes::Vector3D>& vectorArray, const std::list<Eigen::Vector3f>& extern_vectorArray)
{
    const nlohmann::json args = { vector, extern_vector, vectorArray, extern_vectorArray };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "valueChanged");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
void CounterService::onVectorChanged(const Test::CustomTypes::Vector3D& vector)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "vector");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, vector);
        }
    }
}
void CounterService::onExternVectorChanged(const Eigen::Vector3f& extern_vector)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "extern_vector");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, extern_vector);
        }
    }
}
void CounterService::onVectorArrayChanged(const std::list<Test::CustomTypes::Vector3D>& vectorArray)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "vectorArray");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, vectorArray);
        }
    }
}
void CounterService::onExternVectorArrayChanged(const std::list<Eigen::Vector3f>& extern_vectorArray)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "extern_vectorArray");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, extern_vectorArray);
        }
    }
}

