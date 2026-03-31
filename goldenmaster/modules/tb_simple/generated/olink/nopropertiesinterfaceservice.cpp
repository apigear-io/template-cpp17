

#include "tb_simple/generated/api/datastructs.api.h"
#include "tb_simple/generated/olink/nopropertiesinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"

THIRD_PARTY_INCLUDES_START
#include "olink/iremotenode.h"
#include "olink/remoteregistry.h"
THIRD_PARTY_INCLUDES_END
#include "apigear/utilities/logger.h"

#include <iostream>


using namespace Test::TbSimple;
using namespace Test::TbSimple::olink;

namespace 
{
const std::string interfaceId = "tb.simple.NoPropertiesInterface";
}

NoPropertiesInterfaceService::NoPropertiesInterfaceService(std::shared_ptr<INoPropertiesInterface> NoPropertiesInterface, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_NoPropertiesInterface(NoPropertiesInterface)
    , m_registry(registry)
{
    m_NoPropertiesInterface->_getPublisher().subscribeToAllChanges(*this);
}

NoPropertiesInterfaceService::~NoPropertiesInterfaceService()
{
    m_NoPropertiesInterface->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string NoPropertiesInterfaceService::olinkObjectName() {
    return interfaceId;
}

nlohmann::json NoPropertiesInterfaceService::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("NoPropertiesInterfaceService invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "funcVoid") {
        m_NoPropertiesInterface->funcVoid();
        return nlohmann::json{};
    }
    if(memberMethod == "funcBool") {
        const bool& paramBool = fcnArgs.at(0);
        bool result = m_NoPropertiesInterface->funcBool(paramBool);
        return result;
    }
    return nlohmann::json();
}

void NoPropertiesInterfaceService::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("NoPropertiesInterfaceService set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    // no properties to set
    (void) value;
    (void) memberProperty; 
}

void NoPropertiesInterfaceService::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("NoPropertiesInterfaceService linked " + objectId);
}

void NoPropertiesInterfaceService::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("NoPropertiesInterfaceService unlinked " + objectId);
}

nlohmann::json NoPropertiesInterfaceService::olinkCollectProperties()
{
    return nlohmann::json::object({
    });
}
void NoPropertiesInterfaceService::onSigVoid()
{
    const nlohmann::json args = {  };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sigVoid");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
void NoPropertiesInterfaceService::onSigBool(bool paramBool)
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

