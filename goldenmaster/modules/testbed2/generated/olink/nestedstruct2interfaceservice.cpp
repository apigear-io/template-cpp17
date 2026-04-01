

#include "testbed2/generated/api/datastructs.api.h"
#include "testbed2/generated/olink/nestedstruct2interfaceservice.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"

THIRD_PARTY_INCLUDES_START
#include "olink/iremotenode.h"
#include "olink/remoteregistry.h"
THIRD_PARTY_INCLUDES_END
#include "apigear/utilities/logger.h"

#include <iostream>


using namespace Test::Testbed2;
using namespace Test::Testbed2::olink;

namespace 
{
const std::string interfaceId = "testbed2.NestedStruct2Interface";
}

NestedStruct2InterfaceService::NestedStruct2InterfaceService(std::shared_ptr<INestedStruct2Interface> NestedStruct2Interface, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_NestedStruct2Interface(NestedStruct2Interface)
    , m_registry(registry)
{
    m_NestedStruct2Interface->_getPublisher().subscribeToAllChanges(*this);
}

NestedStruct2InterfaceService::~NestedStruct2InterfaceService()
{
    m_NestedStruct2Interface->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string NestedStruct2InterfaceService::olinkObjectName() {
    return interfaceId;
}

nlohmann::json NestedStruct2InterfaceService::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    try {
    AG_LOG_DEBUG("NestedStruct2InterfaceService invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "func1") {
        const NestedStruct1& param1 = fcnArgs.at(0);
        NestedStruct1 result = m_NestedStruct2Interface->func1(param1);
        return result;
    }
    if(memberMethod == "func2") {
        const NestedStruct1& param1 = fcnArgs.at(0);
        const NestedStruct2& param2 = fcnArgs.at(1);
        NestedStruct1 result = m_NestedStruct2Interface->func2(param1, param2);
        return result;
    }
    return nlohmann::json();
    } catch (const std::exception& e) {
        AG_LOG_ERROR("OLink JSON error in NestedStruct2Interface: " + std::string(e.what()));
        return nlohmann::json();
    }
}

void NestedStruct2InterfaceService::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    try {
    AG_LOG_DEBUG("NestedStruct2InterfaceService set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    if(memberProperty == "prop1") {
        NestedStruct1 prop1 = value.get<NestedStruct1>();
        m_NestedStruct2Interface->setProp1(prop1);
    }
    if(memberProperty == "prop2") {
        NestedStruct2 prop2 = value.get<NestedStruct2>();
        m_NestedStruct2Interface->setProp2(prop2);
    }
    } catch (const std::exception& e) {
        AG_LOG_ERROR("OLink JSON error in NestedStruct2Interface: " + std::string(e.what()));
    }
}

void NestedStruct2InterfaceService::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("NestedStruct2InterfaceService linked " + objectId);
}

void NestedStruct2InterfaceService::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("NestedStruct2InterfaceService unlinked " + objectId);
}

nlohmann::json NestedStruct2InterfaceService::olinkCollectProperties()
{
    return nlohmann::json::object({
        { "prop1", m_NestedStruct2Interface->getProp1() },
        { "prop2", m_NestedStruct2Interface->getProp2() }
    });
}
void NestedStruct2InterfaceService::onSig1(const NestedStruct1& param1)
{
    const nlohmann::json args = { param1 };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sig1");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
void NestedStruct2InterfaceService::onSig2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    const nlohmann::json args = { param1, param2 };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sig2");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
void NestedStruct2InterfaceService::onProp1Changed(const NestedStruct1& prop1)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop1");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, prop1);
        }
    }
}
void NestedStruct2InterfaceService::onProp2Changed(const NestedStruct2& prop2)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop2");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, prop2);
        }
    }
}

