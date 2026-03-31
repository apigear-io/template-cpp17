

#include "tb_same1/generated/api/datastructs.api.h"
#include "tb_same1/generated/olink/sameenum1interfaceservice.h"
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
const std::string interfaceId = "tb.same1.SameEnum1Interface";
}

SameEnum1InterfaceService::SameEnum1InterfaceService(std::shared_ptr<ISameEnum1Interface> SameEnum1Interface, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_SameEnum1Interface(SameEnum1Interface)
    , m_registry(registry)
{
    m_SameEnum1Interface->_getPublisher().subscribeToAllChanges(*this);
}

SameEnum1InterfaceService::~SameEnum1InterfaceService()
{
    m_SameEnum1Interface->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string SameEnum1InterfaceService::olinkObjectName() {
    return interfaceId;
}

nlohmann::json SameEnum1InterfaceService::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("SameEnum1InterfaceService invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "func1") {
        const Enum1Enum& param1 = fcnArgs.at(0);
        Enum1Enum result = m_SameEnum1Interface->func1(param1);
        return result;
    }
    return nlohmann::json();
}

void SameEnum1InterfaceService::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("SameEnum1InterfaceService set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    if(memberProperty == "prop1") {
        Enum1Enum prop1 = value.get<Enum1Enum>();
        m_SameEnum1Interface->setProp1(prop1);
    } 
}

void SameEnum1InterfaceService::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("SameEnum1InterfaceService linked " + objectId);
}

void SameEnum1InterfaceService::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("SameEnum1InterfaceService unlinked " + objectId);
}

nlohmann::json SameEnum1InterfaceService::olinkCollectProperties()
{
    return nlohmann::json::object({
        { "prop1", m_SameEnum1Interface->getProp1() }
    });
}
void SameEnum1InterfaceService::onSig1(Enum1Enum param1)
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
void SameEnum1InterfaceService::onProp1Changed(Enum1Enum prop1)
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

