

#include "tb_simple/generated/api/datastructs.api.h"
#include "tb_simple/generated/olink/emptyinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"

#include "olink/iremotenode.h"
#include "olink/remoteregistry.h"
#include "apigear/utilities/logger.h"

#include <iostream>


using namespace Test::TbSimple;
using namespace Test::TbSimple::olink;

namespace 
{
const std::string interfaceId = "tb.simple.EmptyInterface";
}

EmptyInterfaceService::EmptyInterfaceService(std::shared_ptr<IEmptyInterface> EmptyInterface, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_EmptyInterface(EmptyInterface)
{
    // if no properties and no signals, the registry is not necessary.
    (void)registry;
    m_EmptyInterface->_getPublisher().subscribeToAllChanges(*this);
}

EmptyInterfaceService::~EmptyInterfaceService()
{
    m_EmptyInterface->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string EmptyInterfaceService::olinkObjectName() {
    return interfaceId;
}

nlohmann::json EmptyInterfaceService::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("EmptyInterfaceService invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    // no operations to invoke
    (void) fcnArgs;
    (void) memberMethod;
    return nlohmann::json();
}

void EmptyInterfaceService::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("EmptyInterfaceService set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    // no properties to set
    (void) value;
    (void) memberProperty; 
}

void EmptyInterfaceService::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("EmptyInterfaceService linked " + objectId);
}

void EmptyInterfaceService::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("EmptyInterfaceService unlinked " + objectId);
}

nlohmann::json EmptyInterfaceService::olinkCollectProperties()
{
    return nlohmann::json::object({
    });
}

