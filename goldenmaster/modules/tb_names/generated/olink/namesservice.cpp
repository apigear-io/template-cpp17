

#include "tb_names/generated/api/datastructs.api.h"
#include "tb_names/generated/olink/namesservice.h"
#include "tb_names/generated/core/tb_names.json.adapter.h"

#include "olink/iremotenode.h"
#include "olink/remoteregistry.h"
#include "apigear/utilities/logger.h"

#include <iostream>


using namespace Test::TbNames;
using namespace Test::TbNames::olink;

namespace 
{
const std::string interfaceId = "tb.names.Nam_Es";
}

Nam_EsService::Nam_EsService(std::shared_ptr<INamEs> Nam_Es, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_Nam_Es(Nam_Es)
    , m_registry(registry)
{
    m_Nam_Es->_getPublisher().subscribeToAllChanges(*this);
}

Nam_EsService::~Nam_EsService()
{
    m_Nam_Es->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string Nam_EsService::olinkObjectName() {
    return interfaceId;
}

nlohmann::json Nam_EsService::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("Nam_EsService invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "SOME_FUNCTION") {
        const bool& SOME_PARAM = fcnArgs.at(0);
        m_Nam_Es->sOME_FUNCTION(SOME_PARAM);
        return nlohmann::json{};
    }
    if(memberMethod == "Some_Function2") {
        const bool& Some_Param = fcnArgs.at(0);
        m_Nam_Es->some_Function2(Some_Param);
        return nlohmann::json{};
    }
    return nlohmann::json();
}

void Nam_EsService::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("Nam_EsService set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    if(memberProperty == "Switch") {
        bool Switch = value.get<bool>();
        m_Nam_Es->setSwitch(Switch);
    }
    if(memberProperty == "SOME_PROPERTY") {
        int SOME_PROPERTY = value.get<int>();
        m_Nam_Es->setSomeProperty(SOME_PROPERTY);
    }
    if(memberProperty == "Some_Poperty2") {
        int Some_Poperty2 = value.get<int>();
        m_Nam_Es->setSomePoperty2(Some_Poperty2);
    }
    if(memberProperty == "enum_property") {
        Enum_With_Under_scoresEnum enum_property = value.get<Enum_With_Under_scoresEnum>();
        m_Nam_Es->setEnumProperty(enum_property);
    } 
}

void Nam_EsService::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("Nam_EsService linked " + objectId);
}

void Nam_EsService::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("Nam_EsService unlinked " + objectId);
}

nlohmann::json Nam_EsService::olinkCollectProperties()
{
    return nlohmann::json::object({
        { "Switch", m_Nam_Es->getSwitch() },
        { "SOME_PROPERTY", m_Nam_Es->getSomeProperty() },
        { "Some_Poperty2", m_Nam_Es->getSomePoperty2() },
        { "enum_property", m_Nam_Es->getEnumProperty() }
    });
}
void Nam_EsService::onSomeSignal(bool SOME_PARAM)
{
    const nlohmann::json args = { SOME_PARAM };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "SOME_SIGNAL");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
void Nam_EsService::onSomeSignal2(bool Some_Param)
{
    const nlohmann::json args = { Some_Param };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "Some_Signal2");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
void Nam_EsService::onSwitchChanged(bool Switch)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "Switch");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, Switch);
        }
    }
}
void Nam_EsService::onSomePropertyChanged(int SOME_PROPERTY)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "SOME_PROPERTY");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, SOME_PROPERTY);
        }
    }
}
void Nam_EsService::onSomePoperty2Changed(int Some_Poperty2)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "Some_Poperty2");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, Some_Poperty2);
        }
    }
}
void Nam_EsService::onEnumPropertyChanged(Enum_With_Under_scoresEnum enum_property)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "enum_property");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, enum_property);
        }
    }
}

