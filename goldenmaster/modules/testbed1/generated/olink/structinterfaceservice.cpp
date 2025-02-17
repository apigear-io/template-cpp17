

#include "testbed1/generated/api/datastructs.api.h"
#include "testbed1/generated/olink/structinterfaceservice.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"

#include "olink/iremotenode.h"
#include "olink/remoteregistry.h"
#include "apigear/utilities/logger.h"

#include <iostream>


using namespace Test::Testbed1;
using namespace Test::Testbed1::olink;

namespace 
{
const std::string interfaceId = "testbed1.StructInterface";
}

StructInterfaceService::StructInterfaceService(std::shared_ptr<IStructInterface> StructInterface, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_StructInterface(StructInterface)
    , m_registry(registry)
{
    m_StructInterface->_getPublisher().subscribeToAllChanges(*this);
}

StructInterfaceService::~StructInterfaceService()
{
    m_StructInterface->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string StructInterfaceService::olinkObjectName() {
    return interfaceId;
}

nlohmann::json StructInterfaceService::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("StructInterfaceService invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "funcBool") {
        const StructBool& paramBool = fcnArgs.at(0);
        StructBool result = m_StructInterface->funcBool(paramBool);
        return result;
    }
    if(memberMethod == "funcInt") {
        const StructInt& paramInt = fcnArgs.at(0);
        StructInt result = m_StructInterface->funcInt(paramInt);
        return result;
    }
    if(memberMethod == "funcFloat") {
        const StructFloat& paramFloat = fcnArgs.at(0);
        StructFloat result = m_StructInterface->funcFloat(paramFloat);
        return result;
    }
    if(memberMethod == "funcString") {
        const StructString& paramString = fcnArgs.at(0);
        StructString result = m_StructInterface->funcString(paramString);
        return result;
    }
    return nlohmann::json();
}

void StructInterfaceService::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("StructInterfaceService set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    if(memberProperty == "propBool") {
        StructBool propBool = value.get<StructBool>();
        m_StructInterface->setPropBool(propBool);
    }
    if(memberProperty == "propInt") {
        StructInt propInt = value.get<StructInt>();
        m_StructInterface->setPropInt(propInt);
    }
    if(memberProperty == "propFloat") {
        StructFloat propFloat = value.get<StructFloat>();
        m_StructInterface->setPropFloat(propFloat);
    }
    if(memberProperty == "propString") {
        StructString propString = value.get<StructString>();
        m_StructInterface->setPropString(propString);
    } 
}

void StructInterfaceService::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("StructInterfaceService linked " + objectId);
}

void StructInterfaceService::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("StructInterfaceService unlinked " + objectId);
}

nlohmann::json StructInterfaceService::olinkCollectProperties()
{
    return nlohmann::json::object({
        { "propBool", m_StructInterface->getPropBool() },
        { "propInt", m_StructInterface->getPropInt() },
        { "propFloat", m_StructInterface->getPropFloat() },
        { "propString", m_StructInterface->getPropString() }
    });
}
void StructInterfaceService::onSigBool(const StructBool& paramBool)
{
    const nlohmann::json args = { paramBool };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sigBool");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
void StructInterfaceService::onSigInt(const StructInt& paramInt)
{
    const nlohmann::json args = { paramInt };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sigInt");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
void StructInterfaceService::onSigFloat(const StructFloat& paramFloat)
{
    const nlohmann::json args = { paramFloat };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sigFloat");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
void StructInterfaceService::onSigString(const StructString& paramString)
{
    const nlohmann::json args = { paramString };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sigString");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
void StructInterfaceService::onPropBoolChanged(const StructBool& propBool)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propBool");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, propBool);
        }
    }
}
void StructInterfaceService::onPropIntChanged(const StructInt& propInt)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, propInt);
        }
    }
}
void StructInterfaceService::onPropFloatChanged(const StructFloat& propFloat)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propFloat");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, propFloat);
        }
    }
}
void StructInterfaceService::onPropStringChanged(const StructString& propString)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propString");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, propString);
        }
    }
}

