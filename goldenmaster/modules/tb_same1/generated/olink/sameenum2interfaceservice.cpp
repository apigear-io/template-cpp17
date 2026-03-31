

#include "tb_same1/generated/api/datastructs.api.h"
#include "tb_same1/generated/olink/sameenum2interfaceservice.h"
#include "tb_same1/generated/core/tb_same1.json.adapter.h"

THIRD_PARTY_INCLUDES_START
#include "olink/iremotenode.h"
#include "olink/remoteregistry.h"
THIRD_PARTY_INCLUDES_END
#include "apigear/utilities/logger.h"

#include <iostream>


using namespace Test::TbSame1;
using namespace Test::TbSame1::olink;

namespace 
{
const std::string interfaceId = "tb.same1.SameEnum2Interface";
}

SameEnum2InterfaceService::SameEnum2InterfaceService(std::shared_ptr<ISameEnum2Interface> SameEnum2Interface, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_SameEnum2Interface(SameEnum2Interface)
    , m_registry(registry)
{
    m_SameEnum2Interface->_getPublisher().subscribeToAllChanges(*this);
}

SameEnum2InterfaceService::~SameEnum2InterfaceService()
{
    m_SameEnum2Interface->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string SameEnum2InterfaceService::olinkObjectName() {
    return interfaceId;
}

nlohmann::json SameEnum2InterfaceService::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("SameEnum2InterfaceService invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "func1") {
        const Enum1Enum& param1 = fcnArgs.at(0);
        Enum1Enum result = m_SameEnum2Interface->func1(param1);
        return result;
    }
    if(memberMethod == "func2") {
        const Enum1Enum& param1 = fcnArgs.at(0);
        const Enum2Enum& param2 = fcnArgs.at(1);
        Enum1Enum result = m_SameEnum2Interface->func2(param1, param2);
        return result;
    }
    return nlohmann::json();
}

void SameEnum2InterfaceService::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("SameEnum2InterfaceService set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    if(memberProperty == "prop1") {
        Enum1Enum prop1 = value.get<Enum1Enum>();
        m_SameEnum2Interface->setProp1(prop1);
    }
    if(memberProperty == "prop2") {
        Enum2Enum prop2 = value.get<Enum2Enum>();
        m_SameEnum2Interface->setProp2(prop2);
    } 
}

void SameEnum2InterfaceService::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("SameEnum2InterfaceService linked " + objectId);
}

void SameEnum2InterfaceService::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("SameEnum2InterfaceService unlinked " + objectId);
}

nlohmann::json SameEnum2InterfaceService::olinkCollectProperties()
{
    return nlohmann::json::object({
        { "prop1", m_SameEnum2Interface->getProp1() },
        { "prop2", m_SameEnum2Interface->getProp2() }
    });
}
void SameEnum2InterfaceService::onSig1(Enum1Enum param1)
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
void SameEnum2InterfaceService::onSig2(Enum1Enum param1, Enum2Enum param2)
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
void SameEnum2InterfaceService::onProp1Changed(Enum1Enum prop1)
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
void SameEnum2InterfaceService::onProp2Changed(Enum2Enum prop2)
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

