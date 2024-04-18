

#include "tb_simple/generated/olink/simplearrayinterfaceclient.h"
#include "tb_simple/generated/core/simplearrayinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::olink;

namespace 
{
const std::string interfaceId = "tb.simple.SimpleArrayInterface";
}

SimpleArrayInterfaceClient::SimpleArrayInterfaceClient()
    : m_publisher(std::make_unique<SimpleArrayInterfacePublisher>())
{}

void SimpleArrayInterfaceClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("propBool")) {
        setPropBoolLocal(fields["propBool"].get<std::list<bool>>());
    }
    if(fields.contains("propInt")) {
        setPropIntLocal(fields["propInt"].get<std::list<int>>());
    }
    if(fields.contains("propInt32")) {
        setPropInt32Local(fields["propInt32"].get<std::list<int32_t>>());
    }
    if(fields.contains("propInt64")) {
        setPropInt64Local(fields["propInt64"].get<std::list<int64_t>>());
    }
    if(fields.contains("propFloat")) {
        setPropFloatLocal(fields["propFloat"].get<std::list<float>>());
    }
    if(fields.contains("propFloat32")) {
        setPropFloat32Local(fields["propFloat32"].get<std::list<float>>());
    }
    if(fields.contains("propFloat64")) {
        setPropFloat64Local(fields["propFloat64"].get<std::list<double>>());
    }
    if(fields.contains("propString")) {
        setPropStringLocal(fields["propString"].get<std::list<std::string>>());
    }
}

void SimpleArrayInterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "propBool") {
        setPropBoolLocal(value.get<std::list<bool>>());
    }
    else if ( propertyName == "propInt") {
        setPropIntLocal(value.get<std::list<int>>());
    }
    else if ( propertyName == "propInt32") {
        setPropInt32Local(value.get<std::list<int32_t>>());
    }
    else if ( propertyName == "propInt64") {
        setPropInt64Local(value.get<std::list<int64_t>>());
    }
    else if ( propertyName == "propFloat") {
        setPropFloatLocal(value.get<std::list<float>>());
    }
    else if ( propertyName == "propFloat32") {
        setPropFloat32Local(value.get<std::list<float>>());
    }
    else if ( propertyName == "propFloat64") {
        setPropFloat64Local(value.get<std::list<double>>());
    }
    else if ( propertyName == "propString") {
        setPropStringLocal(value.get<std::list<std::string>>());
    }
}

void SimpleArrayInterfaceClient::setPropBool(const std::list<bool>& propBool)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propBool");
    m_node->setRemoteProperty(propertyId, propBool);
}

void SimpleArrayInterfaceClient::setPropBoolLocal(const std::list<bool>& propBool)
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

const std::list<bool>& SimpleArrayInterfaceClient::getPropBool() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propBoolMutex);
    return m_data.m_propBool;
}

void SimpleArrayInterfaceClient::setPropInt(const std::list<int>& propInt)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt");
    m_node->setRemoteProperty(propertyId, propInt);
}

void SimpleArrayInterfaceClient::setPropIntLocal(const std::list<int>& propInt)
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

const std::list<int>& SimpleArrayInterfaceClient::getPropInt() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    return m_data.m_propInt;
}

void SimpleArrayInterfaceClient::setPropInt32(const std::list<int32_t>& propInt32)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt32");
    m_node->setRemoteProperty(propertyId, propInt32);
}

void SimpleArrayInterfaceClient::setPropInt32Local(const std::list<int32_t>& propInt32)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_propInt32Mutex);
        if (m_data.m_propInt32 == propInt32) {
            return;
        }
        m_data.m_propInt32 = propInt32;
    }

    m_publisher->publishPropInt32Changed(propInt32);
}

const std::list<int32_t>& SimpleArrayInterfaceClient::getPropInt32() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propInt32Mutex);
    return m_data.m_propInt32;
}

void SimpleArrayInterfaceClient::setPropInt64(const std::list<int64_t>& propInt64)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt64");
    m_node->setRemoteProperty(propertyId, propInt64);
}

void SimpleArrayInterfaceClient::setPropInt64Local(const std::list<int64_t>& propInt64)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_propInt64Mutex);
        if (m_data.m_propInt64 == propInt64) {
            return;
        }
        m_data.m_propInt64 = propInt64;
    }

    m_publisher->publishPropInt64Changed(propInt64);
}

const std::list<int64_t>& SimpleArrayInterfaceClient::getPropInt64() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propInt64Mutex);
    return m_data.m_propInt64;
}

void SimpleArrayInterfaceClient::setPropFloat(const std::list<float>& propFloat)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propFloat");
    m_node->setRemoteProperty(propertyId, propFloat);
}

void SimpleArrayInterfaceClient::setPropFloatLocal(const std::list<float>& propFloat)
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

const std::list<float>& SimpleArrayInterfaceClient::getPropFloat() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    return m_data.m_propFloat;
}

void SimpleArrayInterfaceClient::setPropFloat32(const std::list<float>& propFloat32)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propFloat32");
    m_node->setRemoteProperty(propertyId, propFloat32);
}

void SimpleArrayInterfaceClient::setPropFloat32Local(const std::list<float>& propFloat32)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_propFloat32Mutex);
        if (m_data.m_propFloat32 == propFloat32) {
            return;
        }
        m_data.m_propFloat32 = propFloat32;
    }

    m_publisher->publishPropFloat32Changed(propFloat32);
}

const std::list<float>& SimpleArrayInterfaceClient::getPropFloat32() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloat32Mutex);
    return m_data.m_propFloat32;
}

void SimpleArrayInterfaceClient::setPropFloat64(const std::list<double>& propFloat64)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propFloat64");
    m_node->setRemoteProperty(propertyId, propFloat64);
}

void SimpleArrayInterfaceClient::setPropFloat64Local(const std::list<double>& propFloat64)
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_propFloat64Mutex);
        if (m_data.m_propFloat64 == propFloat64) {
            return;
        }
        m_data.m_propFloat64 = propFloat64;
    }

    m_publisher->publishPropFloat64Changed(propFloat64);
}

const std::list<double>& SimpleArrayInterfaceClient::getPropFloat64() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloat64Mutex);
    return m_data.m_propFloat64;
}

void SimpleArrayInterfaceClient::setPropString(const std::list<std::string>& propString)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propString");
    m_node->setRemoteProperty(propertyId, propString);
}

void SimpleArrayInterfaceClient::setPropStringLocal(const std::list<std::string>& propString)
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

const std::list<std::string>& SimpleArrayInterfaceClient::getPropString() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    return m_data.m_propString;
}

const std::string& SimpleArrayInterfaceClient::getPropReadOnlyString() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propReadOnlyStringMutex);
    return m_data.m_propReadOnlyString;
}

std::list<bool> SimpleArrayInterfaceClient::funcBool(const std::list<bool>& paramBool)
{
    return funcBoolAsync(paramBool).get();
}

std::future<std::list<bool>> SimpleArrayInterfaceClient::funcBoolAsync(const std::list<bool>& paramBool)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<std::list<bool>>{};
    }
    std::shared_ptr<std::promise<std::list<bool>>> resultPromise = std::make_shared<std::promise<std::list<bool>>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcBool");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramBool}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const std::list<bool>& value = arg.value.get<std::list<bool>>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::list<int> SimpleArrayInterfaceClient::funcInt(const std::list<int>& paramInt)
{
    return funcIntAsync(paramInt).get();
}

std::future<std::list<int>> SimpleArrayInterfaceClient::funcIntAsync(const std::list<int>& paramInt)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<std::list<int>>{};
    }
    std::shared_ptr<std::promise<std::list<int>>> resultPromise = std::make_shared<std::promise<std::list<int>>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcInt");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramInt}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const std::list<int>& value = arg.value.get<std::list<int>>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::list<int32_t> SimpleArrayInterfaceClient::funcInt32(const std::list<int32_t>& paramInt32)
{
    return funcInt32Async(paramInt32).get();
}

std::future<std::list<int32_t>> SimpleArrayInterfaceClient::funcInt32Async(const std::list<int32_t>& paramInt32)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<std::list<int32_t>>{};
    }
    std::shared_ptr<std::promise<std::list<int32_t>>> resultPromise = std::make_shared<std::promise<std::list<int32_t>>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcInt32");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramInt32}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const std::list<int32_t>& value = arg.value.get<std::list<int32_t>>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::list<int64_t> SimpleArrayInterfaceClient::funcInt64(const std::list<int64_t>& paramInt64)
{
    return funcInt64Async(paramInt64).get();
}

std::future<std::list<int64_t>> SimpleArrayInterfaceClient::funcInt64Async(const std::list<int64_t>& paramInt64)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<std::list<int64_t>>{};
    }
    std::shared_ptr<std::promise<std::list<int64_t>>> resultPromise = std::make_shared<std::promise<std::list<int64_t>>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcInt64");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramInt64}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const std::list<int64_t>& value = arg.value.get<std::list<int64_t>>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::list<float> SimpleArrayInterfaceClient::funcFloat(const std::list<float>& paramFloat)
{
    return funcFloatAsync(paramFloat).get();
}

std::future<std::list<float>> SimpleArrayInterfaceClient::funcFloatAsync(const std::list<float>& paramFloat)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<std::list<float>>{};
    }
    std::shared_ptr<std::promise<std::list<float>>> resultPromise = std::make_shared<std::promise<std::list<float>>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcFloat");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramFloat}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const std::list<float>& value = arg.value.get<std::list<float>>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::list<float> SimpleArrayInterfaceClient::funcFloat32(const std::list<float>& paramFloat32)
{
    return funcFloat32Async(paramFloat32).get();
}

std::future<std::list<float>> SimpleArrayInterfaceClient::funcFloat32Async(const std::list<float>& paramFloat32)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<std::list<float>>{};
    }
    std::shared_ptr<std::promise<std::list<float>>> resultPromise = std::make_shared<std::promise<std::list<float>>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcFloat32");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramFloat32}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const std::list<float>& value = arg.value.get<std::list<float>>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::list<double> SimpleArrayInterfaceClient::funcFloat64(const std::list<double>& paramFloat)
{
    return funcFloat64Async(paramFloat).get();
}

std::future<std::list<double>> SimpleArrayInterfaceClient::funcFloat64Async(const std::list<double>& paramFloat)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<std::list<double>>{};
    }
    std::shared_ptr<std::promise<std::list<double>>> resultPromise = std::make_shared<std::promise<std::list<double>>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcFloat64");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramFloat}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const std::list<double>& value = arg.value.get<std::list<double>>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::list<std::string> SimpleArrayInterfaceClient::funcString(const std::list<std::string>& paramString)
{
    return funcStringAsync(paramString).get();
}

std::future<std::list<std::string>> SimpleArrayInterfaceClient::funcStringAsync(const std::list<std::string>& paramString)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<std::list<std::string>>{};
    }
    std::shared_ptr<std::promise<std::list<std::string>>> resultPromise = std::make_shared<std::promise<std::list<std::string>>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcString");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramString}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const std::list<std::string>& value = arg.value.get<std::list<std::string>>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::string SimpleArrayInterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void SimpleArrayInterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sigBool") {
        m_publisher->publishSigBool(args[0].get<std::list<bool>>());   
        return;
    }
    if(signalName == "sigInt") {
        m_publisher->publishSigInt(args[0].get<std::list<int>>());   
        return;
    }
    if(signalName == "sigInt32") {
        m_publisher->publishSigInt32(args[0].get<std::list<int32_t>>());   
        return;
    }
    if(signalName == "sigInt64") {
        m_publisher->publishSigInt64(args[0].get<std::list<int64_t>>());   
        return;
    }
    if(signalName == "sigFloat") {
        m_publisher->publishSigFloat(args[0].get<std::list<float>>());   
        return;
    }
    if(signalName == "sigFloat32") {
        m_publisher->publishSigFloat32(args[0].get<std::list<float>>());   
        return;
    }
    if(signalName == "sigFloat64") {
        m_publisher->publishSigFloat64(args[0].get<std::list<double>>());   
        return;
    }
    if(signalName == "sigString") {
        m_publisher->publishSigString(args[0].get<std::list<std::string>>());   
        return;
    }
}

void SimpleArrayInterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void SimpleArrayInterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void SimpleArrayInterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool SimpleArrayInterfaceClient::isReady() const
{
    return m_node != nullptr;
}

ISimpleArrayInterfacePublisher& SimpleArrayInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
