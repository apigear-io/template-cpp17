

#include "tb_same2/generated/api/datastructs.api.h"
#include "tb_same2/generated/olink/samestruct1interfaceservice.h"
#include "tb_same2/generated/core/tb_same2.json.adapter.h"

THIRD_PARTY_INCLUDES_START
#include "olink/iremotenode.h"
#include "olink/remoteregistry.h"
THIRD_PARTY_INCLUDES_END
#include "apigear/utilities/logger.h"

#include <iostream>


using namespace Test::TbSame2;
using namespace Test::TbSame2::olink;

namespace 
{
const std::string interfaceId = "tb.same2.SameStruct1Interface";
}

SameStruct1InterfaceService::SameStruct1InterfaceService(std::shared_ptr<ISameStruct1Interface> SameStruct1Interface, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_SameStruct1Interface(SameStruct1Interface)
    , m_registry(registry)
{
    m_SameStruct1Interface->_getPublisher().subscribeToAllChanges(*this);
}

SameStruct1InterfaceService::~SameStruct1InterfaceService()
{
    m_SameStruct1Interface->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string SameStruct1InterfaceService::olinkObjectName() {
    return interfaceId;
}

nlohmann::json SameStruct1InterfaceService::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("SameStruct1InterfaceService invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "func1") {
        const Struct1& param1 = fcnArgs.at(0);
        Struct1 result = m_SameStruct1Interface->func1(param1);
        return result;
    }
    return nlohmann::json();
}

void SameStruct1InterfaceService::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("SameStruct1InterfaceService set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    if(memberProperty == "prop1") {
        Struct1 prop1 = value.get<Struct1>();
        m_SameStruct1Interface->setProp1(prop1);
    } 
}

void SameStruct1InterfaceService::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("SameStruct1InterfaceService linked " + objectId);
}

void SameStruct1InterfaceService::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("SameStruct1InterfaceService unlinked " + objectId);
}

nlohmann::json SameStruct1InterfaceService::olinkCollectProperties()
{
    return nlohmann::json::object({
        { "prop1", m_SameStruct1Interface->getProp1() }
    });
}
void SameStruct1InterfaceService::onSig1(const Struct1& param1)
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
void SameStruct1InterfaceService::onProp1Changed(const Struct1& prop1)
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

