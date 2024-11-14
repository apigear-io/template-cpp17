#include "tb_simple/generated/nats/simplearrayinterfaceclient.h"
#include "tb_simple/generated/core/simplearrayinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 8;
const uint32_t  expectedPropertiesSubscriptions = 9;
constexpr uint32_t expectedSubscriptionsCount = expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<SimpleArrayInterfaceClient> SimpleArrayInterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<SimpleArrayInterfaceClient> obj(new SimpleArrayInterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> SimpleArrayInterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

SimpleArrayInterfaceClient::SimpleArrayInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<SimpleArrayInterfacePublisher>())
{}

void SimpleArrayInterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

SimpleArrayInterfaceClient::~SimpleArrayInterfaceClient() = default;

void SimpleArrayInterfaceClient::onConnected()
{
    const std::string topic_propBool =  "tb.simple.SimpleArrayInterface.prop.propBool";
    subscribeTopic(topic_propBool, [this](const auto& value){ setPropBoolLocal(value); });
    const std::string topic_propInt =  "tb.simple.SimpleArrayInterface.prop.propInt";
    subscribeTopic(topic_propInt, [this](const auto& value){ setPropIntLocal(value); });
    const std::string topic_propInt32 =  "tb.simple.SimpleArrayInterface.prop.propInt32";
    subscribeTopic(topic_propInt32, [this](const auto& value){ setPropInt32Local(value); });
    const std::string topic_propInt64 =  "tb.simple.SimpleArrayInterface.prop.propInt64";
    subscribeTopic(topic_propInt64, [this](const auto& value){ setPropInt64Local(value); });
    const std::string topic_propFloat =  "tb.simple.SimpleArrayInterface.prop.propFloat";
    subscribeTopic(topic_propFloat, [this](const auto& value){ setPropFloatLocal(value); });
    const std::string topic_propFloat32 =  "tb.simple.SimpleArrayInterface.prop.propFloat32";
    subscribeTopic(topic_propFloat32, [this](const auto& value){ setPropFloat32Local(value); });
    const std::string topic_propFloat64 =  "tb.simple.SimpleArrayInterface.prop.propFloat64";
    subscribeTopic(topic_propFloat64, [this](const auto& value){ setPropFloat64Local(value); });
    const std::string topic_propString =  "tb.simple.SimpleArrayInterface.prop.propString";
    subscribeTopic(topic_propString, [this](const auto& value){ setPropStringLocal(value); });
    const std::string topic_propReadOnlyString =  "tb.simple.SimpleArrayInterface.prop.propReadOnlyString";
    subscribeTopic(topic_propReadOnlyString, [this](const auto& value){ setPropReadOnlyStringLocal(value); });
    const std::string topic_sigBool = "tb.simple.SimpleArrayInterface.sig.sigBool";
    subscribeTopic(topic_sigBool, [this](const auto& args){onSigBool(args);});
    const std::string topic_sigInt = "tb.simple.SimpleArrayInterface.sig.sigInt";
    subscribeTopic(topic_sigInt, [this](const auto& args){onSigInt(args);});
    const std::string topic_sigInt32 = "tb.simple.SimpleArrayInterface.sig.sigInt32";
    subscribeTopic(topic_sigInt32, [this](const auto& args){onSigInt32(args);});
    const std::string topic_sigInt64 = "tb.simple.SimpleArrayInterface.sig.sigInt64";
    subscribeTopic(topic_sigInt64, [this](const auto& args){onSigInt64(args);});
    const std::string topic_sigFloat = "tb.simple.SimpleArrayInterface.sig.sigFloat";
    subscribeTopic(topic_sigFloat, [this](const auto& args){onSigFloat(args);});
    const std::string topic_sigFloat32 = "tb.simple.SimpleArrayInterface.sig.sigFloat32";
    subscribeTopic(topic_sigFloat32, [this](const auto& args){onSigFloat32(args);});
    const std::string topic_sigFloat64 = "tb.simple.SimpleArrayInterface.sig.sigFloat64";
    subscribeTopic(topic_sigFloat64, [this](const auto& args){onSigFloat64(args);});
    const std::string topic_sigString = "tb.simple.SimpleArrayInterface.sig.sigString";
    subscribeTopic(topic_sigString, [this](const auto& args){onSigString(args);});
}

void SimpleArrayInterfaceClient::setPropBool(const std::list<bool>& propBool)
{
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.set.propBool");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propBool).dump());
}

void SimpleArrayInterfaceClient::setPropBoolLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<bool>& propBool = fields.get<std::list<bool>>();
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

const std::list<bool>& SimpleArrayInterfaceClient::getPropBool() const
{
    return m_data.m_propBool;
}

void SimpleArrayInterfaceClient::setPropInt(const std::list<int>& propInt)
{
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.set.propInt");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propInt).dump());
}

void SimpleArrayInterfaceClient::setPropIntLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<int>& propInt = fields.get<std::list<int>>();
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

const std::list<int>& SimpleArrayInterfaceClient::getPropInt() const
{
    return m_data.m_propInt;
}

void SimpleArrayInterfaceClient::setPropInt32(const std::list<int32_t>& propInt32)
{
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.set.propInt32");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propInt32).dump());
}

void SimpleArrayInterfaceClient::setPropInt32Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<int32_t>& propInt32 = fields.get<std::list<int32_t>>();
    if (m_data.m_propInt32 != propInt32) {
        m_data.m_propInt32 = propInt32;
        m_publisher->publishPropInt32Changed(propInt32);
    }
}

const std::list<int32_t>& SimpleArrayInterfaceClient::getPropInt32() const
{
    return m_data.m_propInt32;
}

void SimpleArrayInterfaceClient::setPropInt64(const std::list<int64_t>& propInt64)
{
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.set.propInt64");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propInt64).dump());
}

void SimpleArrayInterfaceClient::setPropInt64Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<int64_t>& propInt64 = fields.get<std::list<int64_t>>();
    if (m_data.m_propInt64 != propInt64) {
        m_data.m_propInt64 = propInt64;
        m_publisher->publishPropInt64Changed(propInt64);
    }
}

const std::list<int64_t>& SimpleArrayInterfaceClient::getPropInt64() const
{
    return m_data.m_propInt64;
}

void SimpleArrayInterfaceClient::setPropFloat(const std::list<float>& propFloat)
{
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.set.propFloat");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propFloat).dump());
}

void SimpleArrayInterfaceClient::setPropFloatLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<float>& propFloat = fields.get<std::list<float>>();
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

const std::list<float>& SimpleArrayInterfaceClient::getPropFloat() const
{
    return m_data.m_propFloat;
}

void SimpleArrayInterfaceClient::setPropFloat32(const std::list<float>& propFloat32)
{
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.set.propFloat32");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propFloat32).dump());
}

void SimpleArrayInterfaceClient::setPropFloat32Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<float>& propFloat32 = fields.get<std::list<float>>();
    if (m_data.m_propFloat32 != propFloat32) {
        m_data.m_propFloat32 = propFloat32;
        m_publisher->publishPropFloat32Changed(propFloat32);
    }
}

const std::list<float>& SimpleArrayInterfaceClient::getPropFloat32() const
{
    return m_data.m_propFloat32;
}

void SimpleArrayInterfaceClient::setPropFloat64(const std::list<double>& propFloat64)
{
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.set.propFloat64");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propFloat64).dump());
}

void SimpleArrayInterfaceClient::setPropFloat64Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<double>& propFloat64 = fields.get<std::list<double>>();
    if (m_data.m_propFloat64 != propFloat64) {
        m_data.m_propFloat64 = propFloat64;
        m_publisher->publishPropFloat64Changed(propFloat64);
    }
}

const std::list<double>& SimpleArrayInterfaceClient::getPropFloat64() const
{
    return m_data.m_propFloat64;
}

void SimpleArrayInterfaceClient::setPropString(const std::list<std::string>& propString)
{
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.set.propString");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propString).dump());
}

void SimpleArrayInterfaceClient::setPropStringLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<std::string>& propString = fields.get<std::list<std::string>>();
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::list<std::string>& SimpleArrayInterfaceClient::getPropString() const
{
    return m_data.m_propString;
}

void SimpleArrayInterfaceClient::setPropReadOnlyStringLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::string& propReadOnlyString = fields.get<std::string>();
    if (m_data.m_propReadOnlyString != propReadOnlyString) {
        m_data.m_propReadOnlyString = propReadOnlyString;
        m_publisher->publishPropReadOnlyStringChanged(propReadOnlyString);
    }
}

const std::string& SimpleArrayInterfaceClient::getPropReadOnlyString() const
{
    return m_data.m_propReadOnlyString;
}

std::list<bool> SimpleArrayInterfaceClient::funcBool(const std::list<bool>& paramBool)
{
    if(m_client == nullptr) {
        return std::list<bool>();
    }
    std::list<bool> value(funcBoolAsync(paramBool).get());
    return value;
}

std::future<std::list<bool>> SimpleArrayInterfaceClient::funcBoolAsync(const std::list<bool>& paramBool)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.rpc.funcBool");

    return std::async(std::launch::async, [this,paramBool]()
    {
        std::promise<std::list<bool>> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<bool>());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<bool> value = field.get<std::list<bool>>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramBool}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

std::list<int> SimpleArrayInterfaceClient::funcInt(const std::list<int>& paramInt)
{
    if(m_client == nullptr) {
        return std::list<int>();
    }
    std::list<int> value(funcIntAsync(paramInt).get());
    return value;
}

std::future<std::list<int>> SimpleArrayInterfaceClient::funcIntAsync(const std::list<int>& paramInt)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.rpc.funcInt");

    return std::async(std::launch::async, [this,paramInt]()
    {
        std::promise<std::list<int>> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<int>());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<int> value = field.get<std::list<int>>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramInt}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

std::list<int32_t> SimpleArrayInterfaceClient::funcInt32(const std::list<int32_t>& paramInt32)
{
    if(m_client == nullptr) {
        return std::list<int32_t>();
    }
    std::list<int32_t> value(funcInt32Async(paramInt32).get());
    return value;
}

std::future<std::list<int32_t>> SimpleArrayInterfaceClient::funcInt32Async(const std::list<int32_t>& paramInt32)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.rpc.funcInt32");

    return std::async(std::launch::async, [this,paramInt32]()
    {
        std::promise<std::list<int32_t>> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<int32_t>());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<int32_t> value = field.get<std::list<int32_t>>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramInt32}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

std::list<int64_t> SimpleArrayInterfaceClient::funcInt64(const std::list<int64_t>& paramInt64)
{
    if(m_client == nullptr) {
        return std::list<int64_t>();
    }
    std::list<int64_t> value(funcInt64Async(paramInt64).get());
    return value;
}

std::future<std::list<int64_t>> SimpleArrayInterfaceClient::funcInt64Async(const std::list<int64_t>& paramInt64)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.rpc.funcInt64");

    return std::async(std::launch::async, [this,paramInt64]()
    {
        std::promise<std::list<int64_t>> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<int64_t>());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<int64_t> value = field.get<std::list<int64_t>>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramInt64}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

std::list<float> SimpleArrayInterfaceClient::funcFloat(const std::list<float>& paramFloat)
{
    if(m_client == nullptr) {
        return std::list<float>();
    }
    std::list<float> value(funcFloatAsync(paramFloat).get());
    return value;
}

std::future<std::list<float>> SimpleArrayInterfaceClient::funcFloatAsync(const std::list<float>& paramFloat)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.rpc.funcFloat");

    return std::async(std::launch::async, [this,paramFloat]()
    {
        std::promise<std::list<float>> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<float>());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<float> value = field.get<std::list<float>>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramFloat}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

std::list<float> SimpleArrayInterfaceClient::funcFloat32(const std::list<float>& paramFloat32)
{
    if(m_client == nullptr) {
        return std::list<float>();
    }
    std::list<float> value(funcFloat32Async(paramFloat32).get());
    return value;
}

std::future<std::list<float>> SimpleArrayInterfaceClient::funcFloat32Async(const std::list<float>& paramFloat32)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.rpc.funcFloat32");

    return std::async(std::launch::async, [this,paramFloat32]()
    {
        std::promise<std::list<float>> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<float>());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<float> value = field.get<std::list<float>>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramFloat32}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

std::list<double> SimpleArrayInterfaceClient::funcFloat64(const std::list<double>& paramFloat)
{
    if(m_client == nullptr) {
        return std::list<double>();
    }
    std::list<double> value(funcFloat64Async(paramFloat).get());
    return value;
}

std::future<std::list<double>> SimpleArrayInterfaceClient::funcFloat64Async(const std::list<double>& paramFloat)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.rpc.funcFloat64");

    return std::async(std::launch::async, [this,paramFloat]()
    {
        std::promise<std::list<double>> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<double>());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<double> value = field.get<std::list<double>>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramFloat}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

std::list<std::string> SimpleArrayInterfaceClient::funcString(const std::list<std::string>& paramString)
{
    if(m_client == nullptr) {
        return std::list<std::string>();
    }
    std::list<std::string> value(funcStringAsync(paramString).get());
    return value;
}

std::future<std::list<std::string>> SimpleArrayInterfaceClient::funcStringAsync(const std::list<std::string>& paramString)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.SimpleArrayInterface.rpc.funcString");

    return std::async(std::launch::async, [this,paramString]()
    {
        std::promise<std::list<std::string>> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<std::string>());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<std::string> value = field.get<std::list<std::string>>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramString}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void SimpleArrayInterfaceClient::onSigBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigBool(json_args[0].get<std::list<bool>>());
}
void SimpleArrayInterfaceClient::onSigInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigInt(json_args[0].get<std::list<int>>());
}
void SimpleArrayInterfaceClient::onSigInt32(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigInt32(json_args[0].get<std::list<int32_t>>());
}
void SimpleArrayInterfaceClient::onSigInt64(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigInt64(json_args[0].get<std::list<int64_t>>());
}
void SimpleArrayInterfaceClient::onSigFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigFloat(json_args[0].get<std::list<float>>());
}
void SimpleArrayInterfaceClient::onSigFloat32(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigFloat32(json_args[0].get<std::list<float>>());
}
void SimpleArrayInterfaceClient::onSigFloat64(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigFloat64(json_args[0].get<std::list<double>>());
}
void SimpleArrayInterfaceClient::onSigString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigString(json_args[0].get<std::list<std::string>>());
}


ISimpleArrayInterfacePublisher& SimpleArrayInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
