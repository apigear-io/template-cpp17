

#include "tb_simple/generated/olink/simpleinterfaceclient.h"
#include "tb_simple/generated/core/simpleinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::olink;

namespace 
{
const std::string interfaceId = "tb.simple.SimpleInterface";
}

SimpleInterfaceClient::SimpleInterfaceClient()
    : m_publisher(std::make_unique<SimpleInterfacePublisher>())
{}

void SimpleInterfaceClient::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("propBool")) {
        setPropBoolLocal(fields["propBool"].get<bool>());
    }
    if(fields.contains("propInt")) {
        setPropIntLocal(fields["propInt"].get<int>());
    }
    if(fields.contains("propInt32")) {
        setPropInt32Local(fields["propInt32"].get<int32_t>());
    }
    if(fields.contains("propInt64")) {
        setPropInt64Local(fields["propInt64"].get<int64_t>());
    }
    if(fields.contains("propFloat")) {
        setPropFloatLocal(fields["propFloat"].get<float>());
    }
    if(fields.contains("propFloat32")) {
        setPropFloat32Local(fields["propFloat32"].get<float>());
    }
    if(fields.contains("propFloat64")) {
        setPropFloat64Local(fields["propFloat64"].get<double>());
    }
    if(fields.contains("propString")) {
        setPropStringLocal(fields["propString"].get<std::string>());
    }
}

void SimpleInterfaceClient::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
    if ( propertyName == "propBool") {
        setPropBoolLocal(value.get<bool>());
    }
    else if ( propertyName == "propInt") {
        setPropIntLocal(value.get<int>());
    }
    else if ( propertyName == "propInt32") {
        setPropInt32Local(value.get<int32_t>());
    }
    else if ( propertyName == "propInt64") {
        setPropInt64Local(value.get<int64_t>());
    }
    else if ( propertyName == "propFloat") {
        setPropFloatLocal(value.get<float>());
    }
    else if ( propertyName == "propFloat32") {
        setPropFloat32Local(value.get<float>());
    }
    else if ( propertyName == "propFloat64") {
        setPropFloat64Local(value.get<double>());
    }
    else if ( propertyName == "propString") {
        setPropStringLocal(value.get<std::string>());
    }
}

void SimpleInterfaceClient::setPropBool(bool propBool)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propBool");
    m_node->setRemoteProperty(propertyId, propBool);
}

void SimpleInterfaceClient::setPropBoolLocal(bool propBool)
{
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

bool SimpleInterfaceClient::getPropBool() const
{
    return m_data.m_propBool;
}

void SimpleInterfaceClient::setPropInt(int propInt)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt");
    m_node->setRemoteProperty(propertyId, propInt);
}

void SimpleInterfaceClient::setPropIntLocal(int propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

int SimpleInterfaceClient::getPropInt() const
{
    return m_data.m_propInt;
}

void SimpleInterfaceClient::setPropInt32(int32_t propInt32)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt32");
    m_node->setRemoteProperty(propertyId, propInt32);
}

void SimpleInterfaceClient::setPropInt32Local(int32_t propInt32)
{
    if (m_data.m_propInt32 != propInt32) {
        m_data.m_propInt32 = propInt32;
        m_publisher->publishPropInt32Changed(propInt32);
    }
}

int32_t SimpleInterfaceClient::getPropInt32() const
{
    return m_data.m_propInt32;
}

void SimpleInterfaceClient::setPropInt64(int64_t propInt64)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt64");
    m_node->setRemoteProperty(propertyId, propInt64);
}

void SimpleInterfaceClient::setPropInt64Local(int64_t propInt64)
{
    if (m_data.m_propInt64 != propInt64) {
        m_data.m_propInt64 = propInt64;
        m_publisher->publishPropInt64Changed(propInt64);
    }
}

int64_t SimpleInterfaceClient::getPropInt64() const
{
    return m_data.m_propInt64;
}

void SimpleInterfaceClient::setPropFloat(float propFloat)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propFloat");
    m_node->setRemoteProperty(propertyId, propFloat);
}

void SimpleInterfaceClient::setPropFloatLocal(float propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

float SimpleInterfaceClient::getPropFloat() const
{
    return m_data.m_propFloat;
}

void SimpleInterfaceClient::setPropFloat32(float propFloat32)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propFloat32");
    m_node->setRemoteProperty(propertyId, propFloat32);
}

void SimpleInterfaceClient::setPropFloat32Local(float propFloat32)
{
    if (m_data.m_propFloat32 != propFloat32) {
        m_data.m_propFloat32 = propFloat32;
        m_publisher->publishPropFloat32Changed(propFloat32);
    }
}

float SimpleInterfaceClient::getPropFloat32() const
{
    return m_data.m_propFloat32;
}

void SimpleInterfaceClient::setPropFloat64(double propFloat64)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propFloat64");
    m_node->setRemoteProperty(propertyId, propFloat64);
}

void SimpleInterfaceClient::setPropFloat64Local(double propFloat64)
{
    if (m_data.m_propFloat64 != propFloat64) {
        m_data.m_propFloat64 = propFloat64;
        m_publisher->publishPropFloat64Changed(propFloat64);
    }
}

double SimpleInterfaceClient::getPropFloat64() const
{
    return m_data.m_propFloat64;
}

void SimpleInterfaceClient::setPropString(const std::string& propString)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propString");
    m_node->setRemoteProperty(propertyId, propString);
}

void SimpleInterfaceClient::setPropStringLocal(const std::string& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::string& SimpleInterfaceClient::getPropString() const
{
    return m_data.m_propString;
}

void SimpleInterfaceClient::funcNoReturnValue(bool paramBool)
{
    ApiGear::ObjectLink::InvokeReplyFunc func = [this](ApiGear::ObjectLink::InvokeReplyArg arg)
        {
            (void) this;
            (void) arg;
        };
    const nlohmann::json &args = nlohmann::json::array({ paramBool });
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcNoReturnValue");
    m_node->invokeRemote(operationId, args, func);
}

std::future<void> SimpleInterfaceClient::funcNoReturnValueAsync(bool paramBool)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<void>{};
    }
    std::shared_ptr<std::promise<void>> resultPromise = std::make_shared<std::promise<void>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcNoReturnValue");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramBool}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            (void) arg;
            resultPromise->set_value();
        });
    return resultPromise->get_future();
}

bool SimpleInterfaceClient::funcBool(bool paramBool)
{
    bool value(funcBoolAsync(paramBool).get());
    return value;
}

std::future<bool> SimpleInterfaceClient::funcBoolAsync(bool paramBool)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<bool>{};
    }
    std::shared_ptr<std::promise<bool>> resultPromise = std::make_shared<std::promise<bool>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcBool");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramBool}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const bool& value = arg.value.get<bool>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

int SimpleInterfaceClient::funcInt(int paramInt)
{
    int value(funcIntAsync(paramInt).get());
    return value;
}

std::future<int> SimpleInterfaceClient::funcIntAsync(int paramInt)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<int>{};
    }
    std::shared_ptr<std::promise<int>> resultPromise = std::make_shared<std::promise<int>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcInt");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramInt}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const int& value = arg.value.get<int>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

int32_t SimpleInterfaceClient::funcInt32(int32_t paramInt32)
{
    int32_t value(funcInt32Async(paramInt32).get());
    return value;
}

std::future<int32_t> SimpleInterfaceClient::funcInt32Async(int32_t paramInt32)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<int32_t>{};
    }
    std::shared_ptr<std::promise<int32_t>> resultPromise = std::make_shared<std::promise<int32_t>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcInt32");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramInt32}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const int32_t& value = arg.value.get<int32_t>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

int64_t SimpleInterfaceClient::funcInt64(int64_t paramInt64)
{
    int64_t value(funcInt64Async(paramInt64).get());
    return value;
}

std::future<int64_t> SimpleInterfaceClient::funcInt64Async(int64_t paramInt64)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<int64_t>{};
    }
    std::shared_ptr<std::promise<int64_t>> resultPromise = std::make_shared<std::promise<int64_t>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcInt64");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramInt64}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const int64_t& value = arg.value.get<int64_t>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

float SimpleInterfaceClient::funcFloat(float paramFloat)
{
    float value(funcFloatAsync(paramFloat).get());
    return value;
}

std::future<float> SimpleInterfaceClient::funcFloatAsync(float paramFloat)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<float>{};
    }
    std::shared_ptr<std::promise<float>> resultPromise = std::make_shared<std::promise<float>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcFloat");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramFloat}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const float& value = arg.value.get<float>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

float SimpleInterfaceClient::funcFloat32(float paramFloat32)
{
    float value(funcFloat32Async(paramFloat32).get());
    return value;
}

std::future<float> SimpleInterfaceClient::funcFloat32Async(float paramFloat32)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<float>{};
    }
    std::shared_ptr<std::promise<float>> resultPromise = std::make_shared<std::promise<float>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcFloat32");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramFloat32}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const float& value = arg.value.get<float>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

double SimpleInterfaceClient::funcFloat64(double paramFloat)
{
    double value(funcFloat64Async(paramFloat).get());
    return value;
}

std::future<double> SimpleInterfaceClient::funcFloat64Async(double paramFloat)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<double>{};
    }
    std::shared_ptr<std::promise<double>> resultPromise = std::make_shared<std::promise<double>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcFloat64");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramFloat}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const double& value = arg.value.get<double>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::string SimpleInterfaceClient::funcString(const std::string& paramString)
{
    std::string value(funcStringAsync(paramString).get());
    return value;
}

std::future<std::string> SimpleInterfaceClient::funcStringAsync(const std::string& paramString)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<std::string>{};
    }
    std::shared_ptr<std::promise<std::string>> resultPromise = std::make_shared<std::promise<std::string>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcString");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({paramString}), [resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
            const std::string& value = arg.value.get<std::string>();
            resultPromise->set_value(value);
        });
    return resultPromise->get_future();
}

std::string SimpleInterfaceClient::olinkObjectName()
{
    return interfaceId;
}

void SimpleInterfaceClient::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sigBool") {
        m_publisher->publishSigBool(args[0].get<bool>());   
        return;
    }
    if(signalName == "sigInt") {
        m_publisher->publishSigInt(args[0].get<int>());   
        return;
    }
    if(signalName == "sigInt32") {
        m_publisher->publishSigInt32(args[0].get<int32_t>());   
        return;
    }
    if(signalName == "sigInt64") {
        m_publisher->publishSigInt64(args[0].get<int64_t>());   
        return;
    }
    if(signalName == "sigFloat") {
        m_publisher->publishSigFloat(args[0].get<float>());   
        return;
    }
    if(signalName == "sigFloat32") {
        m_publisher->publishSigFloat32(args[0].get<float>());   
        return;
    }
    if(signalName == "sigFloat64") {
        m_publisher->publishSigFloat64(args[0].get<double>());   
        return;
    }
    if(signalName == "sigString") {
        m_publisher->publishSigString(args[0].get<std::string>());   
        return;
    }
}

void SimpleInterfaceClient::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void SimpleInterfaceClient::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void SimpleInterfaceClient::olinkOnRelease()
{
    m_node = nullptr;
}

bool SimpleInterfaceClient::isReady() const
{
    return m_node != nullptr;
}

ISimpleInterfacePublisher& SimpleInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
