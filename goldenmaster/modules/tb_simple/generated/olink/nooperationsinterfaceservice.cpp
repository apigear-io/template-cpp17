

#include "tb_simple/generated/api/datastructs.api.h"
#include "tb_simple/generated/olink/nooperationsinterfaceservice.h"
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
const std::string interfaceId = "tb.simple.NoOperationsInterface";
}

NoOperationsInterfaceService::NoOperationsInterfaceService(std::shared_ptr<INoOperationsInterface> NoOperationsInterface, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_NoOperationsInterface(NoOperationsInterface)
    , m_registry(registry)
{
    m_NoOperationsInterface->_getPublisher().subscribeToAllChanges(*this);
}

NoOperationsInterfaceService::~NoOperationsInterfaceService()
{
    m_NoOperationsInterface->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string NoOperationsInterfaceService::olinkObjectName() {
    return interfaceId;
}

nlohmann::json NoOperationsInterfaceService::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("NoOperationsInterfaceService invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    // no operations to invoke
    (void) fcnArgs;
    (void) memberMethod;
    return nlohmann::json();
}

void NoOperationsInterfaceService::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("NoOperationsInterfaceService set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    if(memberProperty == "propBool") {
        bool propBool = value.get<bool>();
        m_NoOperationsInterface->setPropBool(propBool);
    }
    if(memberProperty == "propInt") {
        int propInt = value.get<int>();
        m_NoOperationsInterface->setPropInt(propInt);
    } 
}

void NoOperationsInterfaceService::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("NoOperationsInterfaceService linked " + objectId);
}

void NoOperationsInterfaceService::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("NoOperationsInterfaceService unlinked " + objectId);
}

nlohmann::json NoOperationsInterfaceService::olinkCollectProperties()
{
    return nlohmann::json::object({
        { "propBool", m_NoOperationsInterface->getPropBool() },
        { "propInt", m_NoOperationsInterface->getPropInt() }
    });
}
void NoOperationsInterfaceService::onSigVoid()
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
void NoOperationsInterfaceService::onSigBool(bool paramBool)
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
void NoOperationsInterfaceService::onPropBoolChanged(bool propBool)
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
void NoOperationsInterfaceService::onPropIntChanged(int propInt)
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

