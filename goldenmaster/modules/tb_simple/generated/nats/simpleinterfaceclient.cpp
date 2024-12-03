#include "tb_simple/generated/nats/simpleinterfaceclient.h"
#include "tb_simple/generated/core/simpleinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 8;
const uint32_t  expectedPropertiesSubscriptions = 8;
const uint32_t  initSubscription = 1;
const uint32_t  serviceAvailableSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = serviceAvailableSubscription  + initSubscription
 + expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<SimpleInterfaceClient> SimpleInterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<SimpleInterfaceClient> obj(new SimpleInterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> SimpleInterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

SimpleInterfaceClient::SimpleInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<SimpleInterfacePublisher>())
{}

void SimpleInterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

SimpleInterfaceClient::~SimpleInterfaceClient() = default;

void SimpleInterfaceClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "tb.simple.SimpleInterface.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("tb.simple.SimpleInterface.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "tb.simple.SimpleInterface.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
    const std::string topic_propBool =  "tb.simple.SimpleInterface.prop.propBool";
    subscribeTopic(topic_propBool, [this](const auto& value){ setPropBoolLocal(_to_PropBool(value)); });
    const std::string topic_propInt =  "tb.simple.SimpleInterface.prop.propInt";
    subscribeTopic(topic_propInt, [this](const auto& value){ setPropIntLocal(_to_PropInt(value)); });
    const std::string topic_propInt32 =  "tb.simple.SimpleInterface.prop.propInt32";
    subscribeTopic(topic_propInt32, [this](const auto& value){ setPropInt32Local(_to_PropInt32(value)); });
    const std::string topic_propInt64 =  "tb.simple.SimpleInterface.prop.propInt64";
    subscribeTopic(topic_propInt64, [this](const auto& value){ setPropInt64Local(_to_PropInt64(value)); });
    const std::string topic_propFloat =  "tb.simple.SimpleInterface.prop.propFloat";
    subscribeTopic(topic_propFloat, [this](const auto& value){ setPropFloatLocal(_to_PropFloat(value)); });
    const std::string topic_propFloat32 =  "tb.simple.SimpleInterface.prop.propFloat32";
    subscribeTopic(topic_propFloat32, [this](const auto& value){ setPropFloat32Local(_to_PropFloat32(value)); });
    const std::string topic_propFloat64 =  "tb.simple.SimpleInterface.prop.propFloat64";
    subscribeTopic(topic_propFloat64, [this](const auto& value){ setPropFloat64Local(_to_PropFloat64(value)); });
    const std::string topic_propString =  "tb.simple.SimpleInterface.prop.propString";
    subscribeTopic(topic_propString, [this](const auto& value){ setPropStringLocal(_to_PropString(value)); });
    const std::string topic_sigBool = "tb.simple.SimpleInterface.sig.sigBool";
    subscribeTopic(topic_sigBool, [this](const auto& args){onSigBool(args);});
    const std::string topic_sigInt = "tb.simple.SimpleInterface.sig.sigInt";
    subscribeTopic(topic_sigInt, [this](const auto& args){onSigInt(args);});
    const std::string topic_sigInt32 = "tb.simple.SimpleInterface.sig.sigInt32";
    subscribeTopic(topic_sigInt32, [this](const auto& args){onSigInt32(args);});
    const std::string topic_sigInt64 = "tb.simple.SimpleInterface.sig.sigInt64";
    subscribeTopic(topic_sigInt64, [this](const auto& args){onSigInt64(args);});
    const std::string topic_sigFloat = "tb.simple.SimpleInterface.sig.sigFloat";
    subscribeTopic(topic_sigFloat, [this](const auto& args){onSigFloat(args);});
    const std::string topic_sigFloat32 = "tb.simple.SimpleInterface.sig.sigFloat32";
    subscribeTopic(topic_sigFloat32, [this](const auto& args){onSigFloat32(args);});
    const std::string topic_sigFloat64 = "tb.simple.SimpleInterface.sig.sigFloat64";
    subscribeTopic(topic_sigFloat64, [this](const auto& args){onSigFloat64(args);});
    const std::string topic_sigString = "tb.simple.SimpleInterface.sig.sigString";
    subscribeTopic(topic_sigString, [this](const auto& args){onSigString(args);});
}
void SimpleInterfaceClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "tb.simple.SimpleInterface.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void SimpleInterfaceClient::setPropBool(bool propBool)
{
    static const auto topic = std::string("tb.simple.SimpleInterface.set.propBool");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propBool).dump());
}

bool SimpleInterfaceClient::_to_PropBool(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propBool");
        return false;
    }
   return fields.get<bool>();
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
    static const auto topic = std::string("tb.simple.SimpleInterface.set.propInt");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propInt).dump());
}

int SimpleInterfaceClient::_to_PropInt(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propInt");
        return 0;
    }
   return fields.get<int>();
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
    static const auto topic = std::string("tb.simple.SimpleInterface.set.propInt32");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propInt32).dump());
}

int32_t SimpleInterfaceClient::_to_PropInt32(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propInt32");
        return 0;
    }
   return fields.get<int32_t>();
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
    static const auto topic = std::string("tb.simple.SimpleInterface.set.propInt64");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propInt64).dump());
}

int64_t SimpleInterfaceClient::_to_PropInt64(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propInt64");
        return 0LL;
    }
   return fields.get<int64_t>();
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
    static const auto topic = std::string("tb.simple.SimpleInterface.set.propFloat");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propFloat).dump());
}

float SimpleInterfaceClient::_to_PropFloat(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propFloat");
        return 0.0f;
    }
   return fields.get<float>();
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
    static const auto topic = std::string("tb.simple.SimpleInterface.set.propFloat32");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propFloat32).dump());
}

float SimpleInterfaceClient::_to_PropFloat32(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propFloat32");
        return 0.0f;
    }
   return fields.get<float>();
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
    static const auto topic = std::string("tb.simple.SimpleInterface.set.propFloat64");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propFloat64).dump());
}

double SimpleInterfaceClient::_to_PropFloat64(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propFloat64");
        return 0.0;
    }
   return fields.get<double>();
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
    static const auto topic = std::string("tb.simple.SimpleInterface.set.propString");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propString).dump());
}

std::string SimpleInterfaceClient::_to_PropString(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propString");
        return std::string();
    }
   return fields.get<std::string>();
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

void SimpleInterfaceClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
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

void SimpleInterfaceClient::funcNoReturnValue(bool paramBool)
{
    if(m_client == nullptr) {
        return;
    }
    funcNoReturnValueAsync(paramBool);
}

std::future<void> SimpleInterfaceClient::funcNoReturnValueAsync(bool paramBool)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleInterface.rpc.funcNoReturnValue");

    return std::async(std::launch::async, [this,paramBool]()
    {
        std::promise<void> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            (void) result;
            resultPromise.set_value();
        };

        m_client->request(topic,  nlohmann::json::array({paramBool}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

bool SimpleInterfaceClient::funcBool(bool paramBool)
{
    if(m_client == nullptr) {
        return false;
    }
    bool value(funcBoolAsync(paramBool).get());
    return value;
}

std::future<bool> SimpleInterfaceClient::funcBoolAsync(bool paramBool)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleInterface.rpc.funcBool");

    return std::async(std::launch::async, [this,paramBool]()
    {
        std::promise<bool> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(false);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const bool value = field.get<bool>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramBool}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

int SimpleInterfaceClient::funcInt(int paramInt)
{
    if(m_client == nullptr) {
        return 0;
    }
    int value(funcIntAsync(paramInt).get());
    return value;
}

std::future<int> SimpleInterfaceClient::funcIntAsync(int paramInt)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleInterface.rpc.funcInt");

    return std::async(std::launch::async, [this,paramInt]()
    {
        std::promise<int> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(0);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const int value = field.get<int>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramInt}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

int32_t SimpleInterfaceClient::funcInt32(int32_t paramInt32)
{
    if(m_client == nullptr) {
        return 0;
    }
    int32_t value(funcInt32Async(paramInt32).get());
    return value;
}

std::future<int32_t> SimpleInterfaceClient::funcInt32Async(int32_t paramInt32)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleInterface.rpc.funcInt32");

    return std::async(std::launch::async, [this,paramInt32]()
    {
        std::promise<int32_t> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(0);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const int32_t value = field.get<int32_t>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramInt32}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

int64_t SimpleInterfaceClient::funcInt64(int64_t paramInt64)
{
    if(m_client == nullptr) {
        return 0LL;
    }
    int64_t value(funcInt64Async(paramInt64).get());
    return value;
}

std::future<int64_t> SimpleInterfaceClient::funcInt64Async(int64_t paramInt64)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleInterface.rpc.funcInt64");

    return std::async(std::launch::async, [this,paramInt64]()
    {
        std::promise<int64_t> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(0LL);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const int64_t value = field.get<int64_t>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramInt64}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

float SimpleInterfaceClient::funcFloat(float paramFloat)
{
    if(m_client == nullptr) {
        return 0.0f;
    }
    float value(funcFloatAsync(paramFloat).get());
    return value;
}

std::future<float> SimpleInterfaceClient::funcFloatAsync(float paramFloat)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleInterface.rpc.funcFloat");

    return std::async(std::launch::async, [this,paramFloat]()
    {
        std::promise<float> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(0.0f);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const float value = field.get<float>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramFloat}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

float SimpleInterfaceClient::funcFloat32(float paramFloat32)
{
    if(m_client == nullptr) {
        return 0.0f;
    }
    float value(funcFloat32Async(paramFloat32).get());
    return value;
}

std::future<float> SimpleInterfaceClient::funcFloat32Async(float paramFloat32)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleInterface.rpc.funcFloat32");

    return std::async(std::launch::async, [this,paramFloat32]()
    {
        std::promise<float> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(0.0f);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const float value = field.get<float>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramFloat32}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

double SimpleInterfaceClient::funcFloat64(double paramFloat)
{
    if(m_client == nullptr) {
        return 0.0;
    }
    double value(funcFloat64Async(paramFloat).get());
    return value;
}

std::future<double> SimpleInterfaceClient::funcFloat64Async(double paramFloat)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleInterface.rpc.funcFloat64");

    return std::async(std::launch::async, [this,paramFloat]()
    {
        std::promise<double> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(0.0);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const double value = field.get<double>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramFloat}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

std::string SimpleInterfaceClient::funcString(const std::string& paramString)
{
    if(m_client == nullptr) {
        return std::string();
    }
    std::string value(funcStringAsync(paramString).get());
    return value;
}

std::future<std::string> SimpleInterfaceClient::funcStringAsync(const std::string& paramString)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleInterface.rpc.funcString");

    return std::async(std::launch::async, [this,paramString]()
    {
        std::promise<std::string> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::string());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::string value = field.get<std::string>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramString}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void SimpleInterfaceClient::onSigBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigBool(json_args[0].get<bool>());
}
void SimpleInterfaceClient::onSigInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigInt(json_args[0].get<int>());
}
void SimpleInterfaceClient::onSigInt32(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigInt32(json_args[0].get<int32_t>());
}
void SimpleInterfaceClient::onSigInt64(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigInt64(json_args[0].get<int64_t>());
}
void SimpleInterfaceClient::onSigFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigFloat(json_args[0].get<float>());
}
void SimpleInterfaceClient::onSigFloat32(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigFloat32(json_args[0].get<float>());
}
void SimpleInterfaceClient::onSigFloat64(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigFloat64(json_args[0].get<double>());
}
void SimpleInterfaceClient::onSigString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigString(json_args[0].get<std::string>());
}

ISimpleInterfacePublisher& SimpleInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}

