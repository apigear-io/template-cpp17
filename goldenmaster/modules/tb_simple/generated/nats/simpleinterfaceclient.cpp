#include "tb_simple/generated/nats/simpleinterfaceclient.h"
#include "tb_simple/generated/core/simpleinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 8;
const uint32_t  expectedPropertiesSubscriptions = 8;
constexpr uint32_t expectedSubscriptionsCount = expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
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
    const std::string topic_propBool =  "tb.simple.SimpleInterface.prop.propBool";
    subscribeTopic(topic_propBool, [this](const auto& value){ setPropBoolLocal(value); });
    const std::string topic_propInt =  "tb.simple.SimpleInterface.prop.propInt";
    subscribeTopic(topic_propInt, [this](const auto& value){ setPropIntLocal(value); });
    const std::string topic_propInt32 =  "tb.simple.SimpleInterface.prop.propInt32";
    subscribeTopic(topic_propInt32, [this](const auto& value){ setPropInt32Local(value); });
    const std::string topic_propInt64 =  "tb.simple.SimpleInterface.prop.propInt64";
    subscribeTopic(topic_propInt64, [this](const auto& value){ setPropInt64Local(value); });
    const std::string topic_propFloat =  "tb.simple.SimpleInterface.prop.propFloat";
    subscribeTopic(topic_propFloat, [this](const auto& value){ setPropFloatLocal(value); });
    const std::string topic_propFloat32 =  "tb.simple.SimpleInterface.prop.propFloat32";
    subscribeTopic(topic_propFloat32, [this](const auto& value){ setPropFloat32Local(value); });
    const std::string topic_propFloat64 =  "tb.simple.SimpleInterface.prop.propFloat64";
    subscribeTopic(topic_propFloat64, [this](const auto& value){ setPropFloat64Local(value); });
    const std::string topic_propString =  "tb.simple.SimpleInterface.prop.propString";
    subscribeTopic(topic_propString, [this](const auto& value){ setPropStringLocal(value); });
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

void SimpleInterfaceClient::setPropBool(bool propBool)
{
    static const auto topic = std::string("tb.simple.SimpleInterface.set.propBool");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propBool).dump());
}

void SimpleInterfaceClient::setPropBoolLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    bool propBool = fields.get<bool>();
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

void SimpleInterfaceClient::setPropIntLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    int propInt = fields.get<int>();
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

void SimpleInterfaceClient::setPropInt32Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    int32_t propInt32 = fields.get<int32_t>();
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

void SimpleInterfaceClient::setPropInt64Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    int64_t propInt64 = fields.get<int64_t>();
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

void SimpleInterfaceClient::setPropFloatLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    float propFloat = fields.get<float>();
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

void SimpleInterfaceClient::setPropFloat32Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    float propFloat32 = fields.get<float>();
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

void SimpleInterfaceClient::setPropFloat64Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    double propFloat64 = fields.get<double>();
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

void SimpleInterfaceClient::setPropStringLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::string& propString = fields.get<std::string>();
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
