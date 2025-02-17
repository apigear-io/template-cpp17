

#include "testbed1/generated/api/datastructs.api.h"
#include "testbed1/generated/olink/structarrayinterfaceservice.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"

#include "olink/iremotenode.h"
#include "olink/remoteregistry.h"
#include "apigear/utilities/logger.h"

#include <iostream>


using namespace Test::Testbed1;
using namespace Test::Testbed1::olink;

namespace 
{
const std::string interfaceId = "testbed1.StructArrayInterface";
}

StructArrayInterfaceService::StructArrayInterfaceService(std::shared_ptr<IStructArrayInterface> StructArrayInterface, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_StructArrayInterface(StructArrayInterface)
    , m_registry(registry)
{
    m_StructArrayInterface->_getPublisher().subscribeToAllChanges(*this);
}

StructArrayInterfaceService::~StructArrayInterfaceService()
{
    m_StructArrayInterface->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string StructArrayInterfaceService::olinkObjectName() {
    return interfaceId;
}

nlohmann::json StructArrayInterfaceService::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("StructArrayInterfaceService invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "funcBool") {
        const std::list<StructBool>& paramBool = fcnArgs.at(0);
        std::list<StructBool> result = m_StructArrayInterface->funcBool(paramBool);
        return result;
    }
    if(memberMethod == "funcInt") {
        const std::list<StructInt>& paramInt = fcnArgs.at(0);
        std::list<StructInt> result = m_StructArrayInterface->funcInt(paramInt);
        return result;
    }
    if(memberMethod == "funcFloat") {
        const std::list<StructFloat>& paramFloat = fcnArgs.at(0);
        std::list<StructFloat> result = m_StructArrayInterface->funcFloat(paramFloat);
        return result;
    }
    if(memberMethod == "funcString") {
        const std::list<StructString>& paramString = fcnArgs.at(0);
        std::list<StructString> result = m_StructArrayInterface->funcString(paramString);
        return result;
    }
    return nlohmann::json();
}

void StructArrayInterfaceService::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("StructArrayInterfaceService set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    if(memberProperty == "propBool") {
        std::list<StructBool> propBool = value.get<std::list<StructBool>>();
        m_StructArrayInterface->setPropBool(propBool);
    }
    if(memberProperty == "propInt") {
        std::list<StructInt> propInt = value.get<std::list<StructInt>>();
        m_StructArrayInterface->setPropInt(propInt);
    }
    if(memberProperty == "propFloat") {
        std::list<StructFloat> propFloat = value.get<std::list<StructFloat>>();
        m_StructArrayInterface->setPropFloat(propFloat);
    }
    if(memberProperty == "propString") {
        std::list<StructString> propString = value.get<std::list<StructString>>();
        m_StructArrayInterface->setPropString(propString);
    } 
}

void StructArrayInterfaceService::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("StructArrayInterfaceService linked " + objectId);
}

void StructArrayInterfaceService::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("StructArrayInterfaceService unlinked " + objectId);
}

nlohmann::json StructArrayInterfaceService::olinkCollectProperties()
{
    return nlohmann::json::object({
        { "propBool", m_StructArrayInterface->getPropBool() },
        { "propInt", m_StructArrayInterface->getPropInt() },
        { "propFloat", m_StructArrayInterface->getPropFloat() },
        { "propString", m_StructArrayInterface->getPropString() }
    });
}
void StructArrayInterfaceService::onSigBool(const std::list<StructBool>& paramBool)
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
void StructArrayInterfaceService::onSigInt(const std::list<StructInt>& paramInt)
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
void StructArrayInterfaceService::onSigFloat(const std::list<StructFloat>& paramFloat)
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
void StructArrayInterfaceService::onSigString(const std::list<StructString>& paramString)
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
void StructArrayInterfaceService::onPropBoolChanged(const std::list<StructBool>& propBool)
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
void StructArrayInterfaceService::onPropIntChanged(const std::list<StructInt>& propInt)
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
void StructArrayInterfaceService::onPropFloatChanged(const std::list<StructFloat>& propFloat)
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
void StructArrayInterfaceService::onPropStringChanged(const std::list<StructString>& propString)
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

