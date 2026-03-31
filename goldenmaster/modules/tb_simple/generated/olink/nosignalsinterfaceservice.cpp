

#include "tb_simple/generated/api/datastructs.api.h"
#include "tb_simple/generated/olink/nosignalsinterfaceservice.h"
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
const std::string interfaceId = "tb.simple.NoSignalsInterface";
}

NoSignalsInterfaceService::NoSignalsInterfaceService(std::shared_ptr<INoSignalsInterface> NoSignalsInterface, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_NoSignalsInterface(NoSignalsInterface)
    , m_registry(registry)
{
    m_NoSignalsInterface->_getPublisher().subscribeToAllChanges(*this);
}

NoSignalsInterfaceService::~NoSignalsInterfaceService()
{
    m_NoSignalsInterface->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string NoSignalsInterfaceService::olinkObjectName() {
    return interfaceId;
}

nlohmann::json NoSignalsInterfaceService::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("NoSignalsInterfaceService invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "funcVoid") {
        m_NoSignalsInterface->funcVoid();
        return nlohmann::json{};
    }
    if(memberMethod == "funcBool") {
        const bool& paramBool = fcnArgs.at(0);
        bool result = m_NoSignalsInterface->funcBool(paramBool);
        return result;
    }
    return nlohmann::json();
}

void NoSignalsInterfaceService::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("NoSignalsInterfaceService set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    if(memberProperty == "propBool") {
        bool propBool = value.get<bool>();
        m_NoSignalsInterface->setPropBool(propBool);
    }
    if(memberProperty == "propInt") {
        int propInt = value.get<int>();
        m_NoSignalsInterface->setPropInt(propInt);
    } 
}

void NoSignalsInterfaceService::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("NoSignalsInterfaceService linked " + objectId);
}

void NoSignalsInterfaceService::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("NoSignalsInterfaceService unlinked " + objectId);
}

nlohmann::json NoSignalsInterfaceService::olinkCollectProperties()
{
    return nlohmann::json::object({
        { "propBool", m_NoSignalsInterface->getPropBool() },
        { "propInt", m_NoSignalsInterface->getPropInt() }
    });
}
void NoSignalsInterfaceService::onPropBoolChanged(bool propBool)
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
void NoSignalsInterfaceService::onPropIntChanged(int propInt)
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

