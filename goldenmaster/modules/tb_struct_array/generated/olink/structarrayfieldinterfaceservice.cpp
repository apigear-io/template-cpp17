

#include "tb_struct_array/generated/api/datastructs.api.h"
#include "tb_struct_array/generated/olink/structarrayfieldinterfaceservice.h"
#include "tb_struct_array/generated/core/tb_struct_array.json.adapter.h"

THIRD_PARTY_INCLUDES_START
#include "olink/iremotenode.h"
#include "olink/remoteregistry.h"
THIRD_PARTY_INCLUDES_END
#include "apigear/utilities/logger.h"

#include <iostream>


using namespace Test::TbStructArray;
using namespace Test::TbStructArray::olink;

namespace 
{
const std::string interfaceId = "tb.struct.array.StructArrayFieldInterface";
}

StructArrayFieldInterfaceService::StructArrayFieldInterfaceService(std::shared_ptr<IStructArrayFieldInterface> StructArrayFieldInterface, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_StructArrayFieldInterface(StructArrayFieldInterface)
    , m_registry(registry)
{
    m_StructArrayFieldInterface->_getPublisher().subscribeToAllChanges(*this);
}

StructArrayFieldInterfaceService::~StructArrayFieldInterfaceService()
{
    m_StructArrayFieldInterface->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string StructArrayFieldInterfaceService::olinkObjectName() {
    return interfaceId;
}

nlohmann::json StructArrayFieldInterfaceService::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("StructArrayFieldInterfaceService invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "funcMixed") {
        const MixedStruct& paramMixed = fcnArgs.at(0);
        MixedStruct result = m_StructArrayFieldInterface->funcMixed(paramMixed);
        return result;
    }
    if(memberMethod == "funcStructArray") {
        const StructWithArrayOfStructs& paramPoints = fcnArgs.at(0);
        StructWithArrayOfStructs result = m_StructArrayFieldInterface->funcStructArray(paramPoints);
        return result;
    }
    return nlohmann::json();
}

void StructArrayFieldInterfaceService::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("StructArrayFieldInterfaceService set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    if(memberProperty == "propStructArray") {
        StructWithArrayOfStructs propStructArray = value.get<StructWithArrayOfStructs>();
        m_StructArrayFieldInterface->setPropStructArray(propStructArray);
    }
    if(memberProperty == "propEnumArray") {
        StructWithArrayOfEnums propEnumArray = value.get<StructWithArrayOfEnums>();
        m_StructArrayFieldInterface->setPropEnumArray(propEnumArray);
    }
    if(memberProperty == "propIntArray") {
        StructWithArrayOfInts propIntArray = value.get<StructWithArrayOfInts>();
        m_StructArrayFieldInterface->setPropIntArray(propIntArray);
    }
    if(memberProperty == "propMixed") {
        MixedStruct propMixed = value.get<MixedStruct>();
        m_StructArrayFieldInterface->setPropMixed(propMixed);
    } 
}

void StructArrayFieldInterfaceService::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("StructArrayFieldInterfaceService linked " + objectId);
}

void StructArrayFieldInterfaceService::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("StructArrayFieldInterfaceService unlinked " + objectId);
}

nlohmann::json StructArrayFieldInterfaceService::olinkCollectProperties()
{
    return nlohmann::json::object({
        { "propStructArray", m_StructArrayFieldInterface->getPropStructArray() },
        { "propEnumArray", m_StructArrayFieldInterface->getPropEnumArray() },
        { "propIntArray", m_StructArrayFieldInterface->getPropIntArray() },
        { "propMixed", m_StructArrayFieldInterface->getPropMixed() }
    });
}
void StructArrayFieldInterfaceService::onSigMixed(const MixedStruct& paramMixed)
{
    const nlohmann::json args = { paramMixed };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sigMixed");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
void StructArrayFieldInterfaceService::onSigStructArray(const StructWithArrayOfStructs& paramPoints)
{
    const nlohmann::json args = { paramPoints };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sigStructArray");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
void StructArrayFieldInterfaceService::onPropStructArrayChanged(const StructWithArrayOfStructs& propStructArray)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propStructArray");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, propStructArray);
        }
    }
}
void StructArrayFieldInterfaceService::onPropEnumArrayChanged(const StructWithArrayOfEnums& propEnumArray)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propEnumArray");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, propEnumArray);
        }
    }
}
void StructArrayFieldInterfaceService::onPropIntArrayChanged(const StructWithArrayOfInts& propIntArray)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propIntArray");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, propIntArray);
        }
    }
}
void StructArrayFieldInterfaceService::onPropMixedChanged(const MixedStruct& propMixed)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propMixed");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, propMixed);
        }
    }
}

