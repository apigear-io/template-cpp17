

#include "tb_simple/generated/api/datastructs.api.h"
#include "tb_simple/generated/olink/voidinterfaceservice.h"
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
const std::string interfaceId = "tb.simple.VoidInterface";
}

VoidInterfaceService::VoidInterfaceService(std::shared_ptr<IVoidInterface> VoidInterface, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_VoidInterface(VoidInterface)
    , m_registry(registry)
{
    m_VoidInterface->_getPublisher().subscribeToAllChanges(*this);
}

VoidInterfaceService::~VoidInterfaceService()
{
    m_VoidInterface->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string VoidInterfaceService::olinkObjectName() {
    return interfaceId;
}

nlohmann::json VoidInterfaceService::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    try {
    (void) fcnArgs;
    AG_LOG_DEBUG("VoidInterfaceService invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "funcVoid") {
        m_VoidInterface->funcVoid();
        return nlohmann::json{};
    }
    return nlohmann::json();
    } catch (const std::exception& e) {
        AG_LOG_ERROR("OLink JSON error in VoidInterface: " + std::string(e.what()));
        return nlohmann::json();
    }
}

void VoidInterfaceService::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    try {
    AG_LOG_DEBUG("VoidInterfaceService set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    // no properties to set
    (void) value;
    (void) memberProperty;
    } catch (const std::exception& e) {
        AG_LOG_ERROR("OLink JSON error in VoidInterface: " + std::string(e.what()));
    }
}

void VoidInterfaceService::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("VoidInterfaceService linked " + objectId);
}

void VoidInterfaceService::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("VoidInterfaceService unlinked " + objectId);
}

nlohmann::json VoidInterfaceService::olinkCollectProperties()
{
    return nlohmann::json::object({
    });
}
void VoidInterfaceService::onSigVoid()
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

