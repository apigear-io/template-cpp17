

#include "testbed1/generated/olink/structarrayinterfaceclient.h"
#include "testbed1/generated/core/structarrayinterface.publisher.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::Testbed1;
using namespace Test::Testbed1::olink;

namespace 
{
const std::string interfaceId = "testbed1.StructArrayInterface";
}

StructArrayInterfaceClient::StructArrayInterfaceClient()
    : m_publisher(std::make_unique<StructArrayInterfacePublisher>())
{}

void StructArrayInterfaceClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("propBool")) {
        setPropBoolLocal(fields["propBool"].get<std::list<StructBool>>());
    }
    if(fields.contains("propInt")) {
        setPropIntLocal(fields["propInt"].get<std::list<StructInt>>());
    }
    if(fields.contains("propFloat")) {
        setPropFloatLocal(fields["propFloat"].get<std::list<StructFloat>>());
    }
    if(fields.contains("propString")) {
        setPropStringLocal(fields["propString"].get<std::list<StructString>>());
    }
}

void StructArrayInterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "propBool") {
        setPropBoolLocal(value.get<std::list<StructBool>>());
    }
    else if ( propertyName == "propInt") {
        setPropIntLocal(value.get<std::list<StructInt>>());
    }
    else if ( propertyName == "propFloat") {
        setPropFloatLocal(value.get<std::list<StructFloat>>());
    }
    else if ( propertyName == "propString") {
        setPropStringLocal(value.get<std::list<StructString>>());
    }
}

void StructArrayInterfaceClient::setPropBool(const std::list<StructBool>& propBool)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propBool");
    m_node->setRemoteProperty(propertyId, propBool);
}

void StructArrayInterfaceClient::setPropBoolLocal(const std::list<StructBool>& propBool)
{
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

const std::list<StructBool>& StructArrayInterfaceClient::getPropBool() const
{
    return m_data.m_propBool;
}

void StructArrayInterfaceClient::setPropInt(const std::list<StructInt>& propInt)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt");
    m_node->setRemoteProperty(propertyId, propInt);
}

void StructArrayInterfaceClient::setPropIntLocal(const std::list<StructInt>& propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

const std::list<StructInt>& StructArrayInterfaceClient::getPropInt() const
{
    return m_data.m_propInt;
}

void StructArrayInterfaceClient::setPropFloat(const std::list<StructFloat>& propFloat)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propFloat");
    m_node->setRemoteProperty(propertyId, propFloat);
}

void StructArrayInterfaceClient::setPropFloatLocal(const std::list<StructFloat>& propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

const std::list<StructFloat>& StructArrayInterfaceClient::getPropFloat() const
{
    return m_data.m_propFloat;
}

void StructArrayInterfaceClient::setPropString(const std::list<StructString>& propString)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propString");
    m_node->setRemoteProperty(propertyId, propString);
}

void StructArrayInterfaceClient::setPropStringLocal(const std::list<StructString>& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::list<StructString>& StructArrayInterfaceClient::getPropString() const
{
    return m_data.m_propString;
}

StructBool StructArrayInterfaceClient::funcBool(const std::list<StructBool>& paramBool)
{
    StructBool value(funcBoolAsync(paramBool).get());
    return value;
}

std::future<StructBool> StructArrayInterfaceClient::funcBoolAsync(const std::list<StructBool>& paramBool)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<StructBool>{};
    }
    std::shared_ptr<std::promise<StructBool>> resultPromise = std::make_shared<std::promise<StructBool>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcBool");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramBool}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const StructBool& value = arg.value.get<StructBool>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

StructBool StructArrayInterfaceClient::funcInt(const std::list<StructInt>& paramInt)
{
    StructBool value(funcIntAsync(paramInt).get());
    return value;
}

std::future<StructBool> StructArrayInterfaceClient::funcIntAsync(const std::list<StructInt>& paramInt)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<StructBool>{};
    }
    std::shared_ptr<std::promise<StructBool>> resultPromise = std::make_shared<std::promise<StructBool>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcInt");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramInt}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const StructBool& value = arg.value.get<StructBool>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

StructBool StructArrayInterfaceClient::funcFloat(const std::list<StructFloat>& paramFloat)
{
    StructBool value(funcFloatAsync(paramFloat).get());
    return value;
}

std::future<StructBool> StructArrayInterfaceClient::funcFloatAsync(const std::list<StructFloat>& paramFloat)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<StructBool>{};
    }
    std::shared_ptr<std::promise<StructBool>> resultPromise = std::make_shared<std::promise<StructBool>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcFloat");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramFloat}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const StructBool& value = arg.value.get<StructBool>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

StructBool StructArrayInterfaceClient::funcString(const std::list<StructString>& paramString)
{
    StructBool value(funcStringAsync(paramString).get());
    return value;
}

std::future<StructBool> StructArrayInterfaceClient::funcStringAsync(const std::list<StructString>& paramString)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<StructBool>{};
    }
    std::shared_ptr<std::promise<StructBool>> resultPromise = std::make_shared<std::promise<StructBool>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcString");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramString}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const StructBool& value = arg.value.get<StructBool>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::string StructArrayInterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void StructArrayInterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sigBool") {
        m_publisher->publishSigBool(args[0].get<std::list<StructBool>>());   
        return;
    }
    if(signalName == "sigInt") {
        m_publisher->publishSigInt(args[0].get<std::list<StructInt>>());   
        return;
    }
    if(signalName == "sigFloat") {
        m_publisher->publishSigFloat(args[0].get<std::list<StructFloat>>());   
        return;
    }
    if(signalName == "sigString") {
        m_publisher->publishSigString(args[0].get<std::list<StructString>>());   
        return;
    }
}

void StructArrayInterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void StructArrayInterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void StructArrayInterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool StructArrayInterfaceClient::isReady() const
{
    return m_node != nullptr;
}

IStructArrayInterfacePublisher& StructArrayInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
