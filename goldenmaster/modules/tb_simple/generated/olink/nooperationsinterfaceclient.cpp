

#include "tb_simple/generated/olink/nooperationsinterfaceclient.h"
#include "tb_simple/generated/core/nooperationsinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::olink;

namespace 
{
const std::string interfaceId = "tb.simple.NoOperationsInterface";
}

NoOperationsInterfaceClient::NoOperationsInterfaceClient()
    : m_publisher(std::make_unique<NoOperationsInterfacePublisher>())
{}

void NoOperationsInterfaceClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("propBool")) {
        setPropBoolLocal(fields["propBool"].get<bool>());
    }
    if(fields.contains("propInt")) {
        setPropIntLocal(fields["propInt"].get<int>());
    }
}

void NoOperationsInterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "propBool") {
        setPropBoolLocal(value.get<bool>());
    }
    else if ( propertyName == "propInt") {
        setPropIntLocal(value.get<int>());
    }
}

void NoOperationsInterfaceClient::setPropBool(bool propBool)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propBool");
    m_node->setRemoteProperty(propertyId, propBool);
}

void NoOperationsInterfaceClient::setPropBoolLocal(bool propBool)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_propBoolMutex);
        if (m_data.m_propBool == propBool) {
            return;
        }
        m_data.m_propBool = propBool;
    }

    m_publisher->publishPropBoolChanged(propBool);
}

bool NoOperationsInterfaceClient::getPropBool() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propBoolMutex);
    return m_data.m_propBool;
}

void NoOperationsInterfaceClient::setPropInt(int propInt)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt");
    m_node->setRemoteProperty(propertyId, propInt);
}

void NoOperationsInterfaceClient::setPropIntLocal(int propInt)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_propIntMutex);
        if (m_data.m_propInt == propInt) {
            return;
        }
        m_data.m_propInt = propInt;
    }

    m_publisher->publishPropIntChanged(propInt);
}

int NoOperationsInterfaceClient::getPropInt() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    return m_data.m_propInt;
}

std::string NoOperationsInterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void NoOperationsInterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sigVoid") {
        m_publisher->publishSigVoid();   
        return;
    }
    if(signalName == "sigBool") {
        m_publisher->publishSigBool(args[0].get<bool>());   
        return;
    }
}

void NoOperationsInterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void NoOperationsInterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void NoOperationsInterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool NoOperationsInterfaceClient::isReady() const
{
    return m_node != nullptr;
}

INoOperationsInterfacePublisher& NoOperationsInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
