

#include "testbed1/generated/api/datastructs.api.h"
#include "testbed1/generated/olink/structarray2interfaceservice.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"

THIRD_PARTY_INCLUDES_START
#include "olink/iremotenode.h"
#include "olink/remoteregistry.h"
THIRD_PARTY_INCLUDES_END
#include "apigear/utilities/logger.h"

#include <iostream>


using namespace Test::Testbed1;
using namespace Test::Testbed1::olink;

namespace 
{
const std::string interfaceId = "testbed1.StructArray2Interface";
}

StructArray2InterfaceService::StructArray2InterfaceService(std::shared_ptr<IStructArray2Interface> StructArray2Interface, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_StructArray2Interface(StructArray2Interface)
    , m_registry(registry)
{
    m_StructArray2Interface->_getPublisher().subscribeToAllChanges(*this);
}

StructArray2InterfaceService::~StructArray2InterfaceService()
{
    m_StructArray2Interface->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string StructArray2InterfaceService::olinkObjectName() {
    return interfaceId;
}

nlohmann::json StructArray2InterfaceService::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("StructArray2InterfaceService invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "funcBool") {
        const StructBoolWithArray& paramBool = fcnArgs.at(0);
        std::list<StructBool> result = m_StructArray2Interface->funcBool(paramBool);
        return result;
    }
    if(memberMethod == "funcInt") {
        const StructIntWithArray& paramInt = fcnArgs.at(0);
        std::list<StructInt> result = m_StructArray2Interface->funcInt(paramInt);
        return result;
    }
    if(memberMethod == "funcFloat") {
        const StructFloatWithArray& paramFloat = fcnArgs.at(0);
        std::list<StructFloat> result = m_StructArray2Interface->funcFloat(paramFloat);
        return result;
    }
    if(memberMethod == "funcString") {
        const StructStringWithArray& paramString = fcnArgs.at(0);
        std::list<StructString> result = m_StructArray2Interface->funcString(paramString);
        return result;
    }
    if(memberMethod == "funcEnum") {
        const StructEnumWithArray& paramEnum = fcnArgs.at(0);
        std::list<Enum0Enum> result = m_StructArray2Interface->funcEnum(paramEnum);
        return result;
    }
    return nlohmann::json();
}

void StructArray2InterfaceService::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("StructArray2InterfaceService set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    if(memberProperty == "propBool") {
        StructBoolWithArray propBool = value.get<StructBoolWithArray>();
        m_StructArray2Interface->setPropBool(propBool);
    }
    if(memberProperty == "propInt") {
        StructIntWithArray propInt = value.get<StructIntWithArray>();
        m_StructArray2Interface->setPropInt(propInt);
    }
    if(memberProperty == "propFloat") {
        StructFloatWithArray propFloat = value.get<StructFloatWithArray>();
        m_StructArray2Interface->setPropFloat(propFloat);
    }
    if(memberProperty == "propString") {
        StructStringWithArray propString = value.get<StructStringWithArray>();
        m_StructArray2Interface->setPropString(propString);
    }
    if(memberProperty == "propEnum") {
        StructEnumWithArray propEnum = value.get<StructEnumWithArray>();
        m_StructArray2Interface->setPropEnum(propEnum);
    } 
}

void StructArray2InterfaceService::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("StructArray2InterfaceService linked " + objectId);
}

void StructArray2InterfaceService::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("StructArray2InterfaceService unlinked " + objectId);
}

nlohmann::json StructArray2InterfaceService::olinkCollectProperties()
{
    return nlohmann::json::object({
        { "propBool", m_StructArray2Interface->getPropBool() },
        { "propInt", m_StructArray2Interface->getPropInt() },
        { "propFloat", m_StructArray2Interface->getPropFloat() },
        { "propString", m_StructArray2Interface->getPropString() },
        { "propEnum", m_StructArray2Interface->getPropEnum() }
    });
}
void StructArray2InterfaceService::onSigBool(const StructBoolWithArray& paramBool)
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
void StructArray2InterfaceService::onSigInt(const StructIntWithArray& paramInt)
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
void StructArray2InterfaceService::onSigFloat(const StructFloatWithArray& paramFloat)
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
void StructArray2InterfaceService::onSigString(const StructStringWithArray& paramString)
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
void StructArray2InterfaceService::onPropBoolChanged(const StructBoolWithArray& propBool)
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
void StructArray2InterfaceService::onPropIntChanged(const StructIntWithArray& propInt)
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
void StructArray2InterfaceService::onPropFloatChanged(const StructFloatWithArray& propFloat)
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
void StructArray2InterfaceService::onPropStringChanged(const StructStringWithArray& propString)
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
void StructArray2InterfaceService::onPropEnumChanged(const StructEnumWithArray& propEnum)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propEnum");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, propEnum);
        }
    }
}

