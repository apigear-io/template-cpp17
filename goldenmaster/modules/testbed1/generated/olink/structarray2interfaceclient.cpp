

#include "testbed1/generated/olink/structarray2interfaceclient.h"
#include "testbed1/generated/core/structarray2interface.publisher.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"

THIRD_PARTY_INCLUDES_START
#include "olink/iclientnode.h"
THIRD_PARTY_INCLUDES_END
#include "apigear/utilities/logger.h"

using namespace Test::Testbed1;
using namespace Test::Testbed1::olink;

namespace 
{
const std::string interfaceId = "testbed1.StructArray2Interface";
}

StructArray2InterfaceClient::StructArray2InterfaceClient()
    : m_publisher(std::make_unique<StructArray2InterfacePublisher>())
{}

void StructArray2InterfaceClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("propBool")) {
        setPropBoolLocal(fields["propBool"].get<StructBoolWithArray>());
    }
    if(fields.contains("propInt")) {
        setPropIntLocal(fields["propInt"].get<StructIntWithArray>());
    }
    if(fields.contains("propFloat")) {
        setPropFloatLocal(fields["propFloat"].get<StructFloatWithArray>());
    }
    if(fields.contains("propString")) {
        setPropStringLocal(fields["propString"].get<StructStringWithArray>());
    }
    if(fields.contains("propEnum")) {
        setPropEnumLocal(fields["propEnum"].get<StructEnumWithArray>());
    }
}

void StructArray2InterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "propBool") {
        setPropBoolLocal(value.get<StructBoolWithArray>());
    }
    else if ( propertyName == "propInt") {
        setPropIntLocal(value.get<StructIntWithArray>());
    }
    else if ( propertyName == "propFloat") {
        setPropFloatLocal(value.get<StructFloatWithArray>());
    }
    else if ( propertyName == "propString") {
        setPropStringLocal(value.get<StructStringWithArray>());
    }
    else if ( propertyName == "propEnum") {
        setPropEnumLocal(value.get<StructEnumWithArray>());
    }
}

void StructArray2InterfaceClient::setPropBool(const StructBoolWithArray& propBool)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propBool");
    m_node->setRemoteProperty(propertyId, propBool);
}

void StructArray2InterfaceClient::setPropBoolLocal(const StructBoolWithArray& propBool)
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

const StructBoolWithArray& StructArray2InterfaceClient::getPropBool() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propBoolMutex);
    return m_data.m_propBool;
}

void StructArray2InterfaceClient::setPropInt(const StructIntWithArray& propInt)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt");
    m_node->setRemoteProperty(propertyId, propInt);
}

void StructArray2InterfaceClient::setPropIntLocal(const StructIntWithArray& propInt)
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

const StructIntWithArray& StructArray2InterfaceClient::getPropInt() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    return m_data.m_propInt;
}

void StructArray2InterfaceClient::setPropFloat(const StructFloatWithArray& propFloat)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propFloat");
    m_node->setRemoteProperty(propertyId, propFloat);
}

void StructArray2InterfaceClient::setPropFloatLocal(const StructFloatWithArray& propFloat)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
        if (m_data.m_propFloat == propFloat) {
            return;
        }
        m_data.m_propFloat = propFloat;
    }

    m_publisher->publishPropFloatChanged(propFloat);
}

const StructFloatWithArray& StructArray2InterfaceClient::getPropFloat() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    return m_data.m_propFloat;
}

void StructArray2InterfaceClient::setPropString(const StructStringWithArray& propString)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propString");
    m_node->setRemoteProperty(propertyId, propString);
}

void StructArray2InterfaceClient::setPropStringLocal(const StructStringWithArray& propString)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_propStringMutex);
        if (m_data.m_propString == propString) {
            return;
        }
        m_data.m_propString = propString;
    }

    m_publisher->publishPropStringChanged(propString);
}

const StructStringWithArray& StructArray2InterfaceClient::getPropString() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    return m_data.m_propString;
}

void StructArray2InterfaceClient::setPropEnum(const StructEnumWithArray& propEnum)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propEnum");
    m_node->setRemoteProperty(propertyId, propEnum);
}

void StructArray2InterfaceClient::setPropEnumLocal(const StructEnumWithArray& propEnum)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_propEnumMutex);
        if (m_data.m_propEnum == propEnum) {
            return;
        }
        m_data.m_propEnum = propEnum;
    }

    m_publisher->publishPropEnumChanged(propEnum);
}

const StructEnumWithArray& StructArray2InterfaceClient::getPropEnum() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propEnumMutex);
    return m_data.m_propEnum;
}

std::list<StructBool> StructArray2InterfaceClient::funcBool(const StructBoolWithArray& paramBool)
{
    return funcBoolAsync(paramBool).get();
}

std::future<std::list<StructBool>> StructArray2InterfaceClient::funcBoolAsync(const StructBoolWithArray& paramBool, std::function<void(std::list<StructBool>)> callback)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<std::list<StructBool>>{};
    }
    std::shared_ptr<std::promise<std::list<StructBool>>> resultPromise = std::make_shared<std::promise<std::list<StructBool>>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcBool");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramBool}), [resultPromise, callback](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const std::list<StructBool>& value = arg.value.get<std::list<StructBool>>();
            resultPromise->set_value(value);
            if (callback)
            {
                callback(value);
            }
        });
    return resultPromise->get_future();
}

std::list<StructInt> StructArray2InterfaceClient::funcInt(const StructIntWithArray& paramInt)
{
    return funcIntAsync(paramInt).get();
}

std::future<std::list<StructInt>> StructArray2InterfaceClient::funcIntAsync(const StructIntWithArray& paramInt, std::function<void(std::list<StructInt>)> callback)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<std::list<StructInt>>{};
    }
    std::shared_ptr<std::promise<std::list<StructInt>>> resultPromise = std::make_shared<std::promise<std::list<StructInt>>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcInt");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramInt}), [resultPromise, callback](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const std::list<StructInt>& value = arg.value.get<std::list<StructInt>>();
            resultPromise->set_value(value);
            if (callback)
            {
                callback(value);
            }
        });
    return resultPromise->get_future();
}

std::list<StructFloat> StructArray2InterfaceClient::funcFloat(const StructFloatWithArray& paramFloat)
{
    return funcFloatAsync(paramFloat).get();
}

std::future<std::list<StructFloat>> StructArray2InterfaceClient::funcFloatAsync(const StructFloatWithArray& paramFloat, std::function<void(std::list<StructFloat>)> callback)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<std::list<StructFloat>>{};
    }
    std::shared_ptr<std::promise<std::list<StructFloat>>> resultPromise = std::make_shared<std::promise<std::list<StructFloat>>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcFloat");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramFloat}), [resultPromise, callback](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const std::list<StructFloat>& value = arg.value.get<std::list<StructFloat>>();
            resultPromise->set_value(value);
            if (callback)
            {
                callback(value);
            }
        });
    return resultPromise->get_future();
}

std::list<StructString> StructArray2InterfaceClient::funcString(const StructStringWithArray& paramString)
{
    return funcStringAsync(paramString).get();
}

std::future<std::list<StructString>> StructArray2InterfaceClient::funcStringAsync(const StructStringWithArray& paramString, std::function<void(std::list<StructString>)> callback)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<std::list<StructString>>{};
    }
    std::shared_ptr<std::promise<std::list<StructString>>> resultPromise = std::make_shared<std::promise<std::list<StructString>>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcString");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramString}), [resultPromise, callback](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const std::list<StructString>& value = arg.value.get<std::list<StructString>>();
            resultPromise->set_value(value);
            if (callback)
            {
                callback(value);
            }
        });
    return resultPromise->get_future();
}

std::list<Enum0Enum> StructArray2InterfaceClient::funcEnum(const StructEnumWithArray& paramEnum)
{
    return funcEnumAsync(paramEnum).get();
}

std::future<std::list<Enum0Enum>> StructArray2InterfaceClient::funcEnumAsync(const StructEnumWithArray& paramEnum, std::function<void(std::list<Enum0Enum>)> callback)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<std::list<Enum0Enum>>{};
    }
    std::shared_ptr<std::promise<std::list<Enum0Enum>>> resultPromise = std::make_shared<std::promise<std::list<Enum0Enum>>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcEnum");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramEnum}), [resultPromise, callback](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const std::list<Enum0Enum>& value = arg.value.get<std::list<Enum0Enum>>();
            resultPromise->set_value(value);
            if (callback)
            {
                callback(value);
            }
        });
    return resultPromise->get_future();
}

std::string StructArray2InterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void StructArray2InterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sigBool") {
        m_publisher->publishSigBool(args[0].get<StructBoolWithArray>());   
        return;
    }
    if(signalName == "sigInt") {
        m_publisher->publishSigInt(args[0].get<StructIntWithArray>());   
        return;
    }
    if(signalName == "sigFloat") {
        m_publisher->publishSigFloat(args[0].get<StructFloatWithArray>());   
        return;
    }
    if(signalName == "sigString") {
        m_publisher->publishSigString(args[0].get<StructStringWithArray>());   
        return;
    }
}

void StructArray2InterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void StructArray2InterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void StructArray2InterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool StructArray2InterfaceClient::isReady() const
{
    return m_node != nullptr;
}

IStructArray2InterfacePublisher& StructArray2InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
