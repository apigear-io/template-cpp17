

#include "testbed1/generated/olink/structinterfaceclient.h"
#include "testbed1/generated/core/structinterface.publisher.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::Testbed1;
using namespace Test::Testbed1::olink;

namespace 
{
const std::string interfaceId = "testbed1.StructInterface";
}

StructInterfaceClient::StructInterfaceClient()
    : m_publisher(std::make_unique<StructInterfacePublisher>())
{}

void StructInterfaceClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("propBool")) {
        setPropBoolLocal(fields["propBool"].get<StructBool>());
    }
    if(fields.contains("propInt")) {
        setPropIntLocal(fields["propInt"].get<StructInt>());
    }
    if(fields.contains("propFloat")) {
        setPropFloatLocal(fields["propFloat"].get<StructFloat>());
    }
    if(fields.contains("propString")) {
        setPropStringLocal(fields["propString"].get<StructString>());
    }
}

void StructInterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "propBool") {
        setPropBoolLocal(value.get<StructBool>());
    }
    else if ( propertyName == "propInt") {
        setPropIntLocal(value.get<StructInt>());
    }
    else if ( propertyName == "propFloat") {
        setPropFloatLocal(value.get<StructFloat>());
    }
    else if ( propertyName == "propString") {
        setPropStringLocal(value.get<StructString>());
    }
}

void StructInterfaceClient::setPropBool(const StructBool& propBool)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propBool");
    m_node->setRemoteProperty(propertyId, propBool);
}

void StructInterfaceClient::setPropBoolLocal(const StructBool& propBool)
{
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

const StructBool& StructInterfaceClient::getPropBool() const
{
    return m_data.m_propBool;
}

void StructInterfaceClient::setPropInt(const StructInt& propInt)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt");
    m_node->setRemoteProperty(propertyId, propInt);
}

void StructInterfaceClient::setPropIntLocal(const StructInt& propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

const StructInt& StructInterfaceClient::getPropInt() const
{
    return m_data.m_propInt;
}

void StructInterfaceClient::setPropFloat(const StructFloat& propFloat)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propFloat");
    m_node->setRemoteProperty(propertyId, propFloat);
}

void StructInterfaceClient::setPropFloatLocal(const StructFloat& propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

const StructFloat& StructInterfaceClient::getPropFloat() const
{
    return m_data.m_propFloat;
}

void StructInterfaceClient::setPropString(const StructString& propString)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propString");
    m_node->setRemoteProperty(propertyId, propString);
}

void StructInterfaceClient::setPropStringLocal(const StructString& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const StructString& StructInterfaceClient::getPropString() const
{
    return m_data.m_propString;
}

StructBool StructInterfaceClient::funcBool(const StructBool& paramBool)
{
    return funcBoolAsync(paramBool).get();
}

std::future<StructBool> StructInterfaceClient::funcBoolAsync(const StructBool& paramBool)
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

StructBool StructInterfaceClient::funcInt(const StructInt& paramInt)
{
    return funcIntAsync(paramInt).get();
}

std::future<StructBool> StructInterfaceClient::funcIntAsync(const StructInt& paramInt)
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

StructFloat StructInterfaceClient::funcFloat(const StructFloat& paramFloat)
{
    return funcFloatAsync(paramFloat).get();
}

std::future<StructFloat> StructInterfaceClient::funcFloatAsync(const StructFloat& paramFloat)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<StructFloat>{};
    }
    std::shared_ptr<std::promise<StructFloat>> resultPromise = std::make_shared<std::promise<StructFloat>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcFloat");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramFloat}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const StructFloat& value = arg.value.get<StructFloat>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

StructString StructInterfaceClient::funcString(const StructString& paramString)
{
    return funcStringAsync(paramString).get();
}

std::future<StructString> StructInterfaceClient::funcStringAsync(const StructString& paramString)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<StructString>{};
    }
    std::shared_ptr<std::promise<StructString>> resultPromise = std::make_shared<std::promise<StructString>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcString");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramString}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const StructString& value = arg.value.get<StructString>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::string StructInterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void StructInterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sigBool") {
        m_publisher->publishSigBool(args[0].get<StructBool>());   
        return;
    }
    if(signalName == "sigInt") {
        m_publisher->publishSigInt(args[0].get<StructInt>());   
        return;
    }
    if(signalName == "sigFloat") {
        m_publisher->publishSigFloat(args[0].get<StructFloat>());   
        return;
    }
    if(signalName == "sigString") {
        m_publisher->publishSigString(args[0].get<StructString>());   
        return;
    }
}

void StructInterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void StructInterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void StructInterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool StructInterfaceClient::isReady() const
{
    return m_node != nullptr;
}

IStructInterfacePublisher& StructInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
