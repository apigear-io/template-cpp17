#include "tb_simple/generated/mqtt/simplearrayinterfaceclient.h"
#include "tb_simple/generated/core/simplearrayinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <random>

using namespace Test::TbSimple;
using namespace Test::TbSimple::MQTT;

namespace {
    std::mt19937 randomNumberGenerator (std::random_device{}());
}

SimpleArrayInterfaceClient::SimpleArrayInterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client)
    : m_isReady(false)
    , m_client(client)
    , m_publisher(std::make_unique<SimpleArrayInterfacePublisher>())
    , m_topics(createTopicMap(m_client->getClientId()))
{
    m_connectionStatusRegistrationID = m_client->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

SimpleArrayInterfaceClient::~SimpleArrayInterfaceClient()
{
    for (const auto& topic: m_topics)
    {
        m_client->unsubscribeTopic(topic. first);
    }
    m_client->unsubscribeToConnectionStatus(m_connectionStatusRegistrationID);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> SimpleArrayInterfaceClient::createTopicMap(const std::string& clientId)
{
    return {
        { std::string("tb.simple/SimpleArrayInterface/prop/propBool"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropBoolLocal(args); } },
        { std::string("tb.simple/SimpleArrayInterface/prop/propInt"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropIntLocal(args); } },
        { std::string("tb.simple/SimpleArrayInterface/prop/propInt32"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropInt32Local(args); } },
        { std::string("tb.simple/SimpleArrayInterface/prop/propInt64"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropInt64Local(args); } },
        { std::string("tb.simple/SimpleArrayInterface/prop/propFloat"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropFloatLocal(args); } },
        { std::string("tb.simple/SimpleArrayInterface/prop/propFloat32"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropFloat32Local(args); } },
        { std::string("tb.simple/SimpleArrayInterface/prop/propFloat64"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropFloat64Local(args); } },
        { std::string("tb.simple/SimpleArrayInterface/prop/propString"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropStringLocal(args); } },
        { std::string("tb.simple/SimpleArrayInterface/sig/sigBool"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigBool(args); } },
        { std::string("tb.simple/SimpleArrayInterface/sig/sigInt"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigInt(args); } },
        { std::string("tb.simple/SimpleArrayInterface/sig/sigInt32"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigInt32(args); } },
        { std::string("tb.simple/SimpleArrayInterface/sig/sigInt64"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigInt64(args); } },
        { std::string("tb.simple/SimpleArrayInterface/sig/sigFloat"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigFloat(args); } },
        { std::string("tb.simple/SimpleArrayInterface/sig/sigFloat32"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigFloat32(args); } },
        { std::string("tb.simple/SimpleArrayInterface/sig/sigFloat64"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigFloat64(args); } },
        { std::string("tb.simple/SimpleArrayInterface/sig/sigString"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigString(args); } },
        { std::string("tb.simple/SimpleArrayInterface/rpc/funcBool/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("tb.simple/SimpleArrayInterface/rpc/funcInt/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("tb.simple/SimpleArrayInterface/rpc/funcInt32/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("tb.simple/SimpleArrayInterface/rpc/funcInt64/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("tb.simple/SimpleArrayInterface/rpc/funcFloat/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("tb.simple/SimpleArrayInterface/rpc/funcFloat32/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("tb.simple/SimpleArrayInterface/rpc/funcFloat64/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("tb.simple/SimpleArrayInterface/rpc/funcString/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
    };
};

void SimpleArrayInterfaceClient::onConnectionStatusChanged(bool connectionStatus)
{
    m_isReady = connectionStatus;
    if(!connectionStatus)
    {
        return;
    }

    for (const auto& topic: m_topics)
    {
        m_client->subscribeTopic(topic. first, topic.second);
    }
}

void SimpleArrayInterfaceClient::setPropBool(const std::list<bool>& propBool)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.simple/SimpleArrayInterface/set/propBool");
    m_client->setRemoteProperty(topic, nlohmann::json(propBool).dump());
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
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.simple/SimpleArrayInterface/set/propInt");
    m_client->setRemoteProperty(topic, nlohmann::json(propInt).dump());
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
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.simple/SimpleArrayInterface/set/propInt32");
    m_client->setRemoteProperty(topic, nlohmann::json(propInt32).dump());
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
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.simple/SimpleArrayInterface/set/propInt64");
    m_client->setRemoteProperty(topic, nlohmann::json(propInt64).dump());
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
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.simple/SimpleArrayInterface/set/propFloat");
    m_client->setRemoteProperty(topic, nlohmann::json(propFloat).dump());
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
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.simple/SimpleArrayInterface/set/propFloat32");
    m_client->setRemoteProperty(topic, nlohmann::json(propFloat32).dump());
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
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.simple/SimpleArrayInterface/set/propFloat64");
    m_client->setRemoteProperty(topic, nlohmann::json(propFloat64).dump());
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
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.simple/SimpleArrayInterface/set/propString");
    m_client->setRemoteProperty(topic, nlohmann::json(propString).dump());
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
    return std::async(std::launch::async, [this,
                    paramBool]()
        {
            std::promise<std::list<bool>> resultPromise;
            static const auto topic = std::string("tb.simple/SimpleArrayInterface/rpc/funcBool");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                const std::list<bool>& value = arg.value.get<std::list<bool>>();
                resultPromise.set_value(value);
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({paramBool}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
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
    return std::async(std::launch::async, [this,
                    paramInt]()
        {
            std::promise<std::list<int>> resultPromise;
            static const auto topic = std::string("tb.simple/SimpleArrayInterface/rpc/funcInt");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                const std::list<int>& value = arg.value.get<std::list<int>>();
                resultPromise.set_value(value);
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({paramInt}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
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
    return std::async(std::launch::async, [this,
                    paramInt32]()
        {
            std::promise<std::list<int32_t>> resultPromise;
            static const auto topic = std::string("tb.simple/SimpleArrayInterface/rpc/funcInt32");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                const std::list<int32_t>& value = arg.value.get<std::list<int32_t>>();
                resultPromise.set_value(value);
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({paramInt32}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
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
    return std::async(std::launch::async, [this,
                    paramInt64]()
        {
            std::promise<std::list<int64_t>> resultPromise;
            static const auto topic = std::string("tb.simple/SimpleArrayInterface/rpc/funcInt64");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                const std::list<int64_t>& value = arg.value.get<std::list<int64_t>>();
                resultPromise.set_value(value);
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({paramInt64}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
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
    return std::async(std::launch::async, [this,
                    paramFloat]()
        {
            std::promise<std::list<float>> resultPromise;
            static const auto topic = std::string("tb.simple/SimpleArrayInterface/rpc/funcFloat");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                const std::list<float>& value = arg.value.get<std::list<float>>();
                resultPromise.set_value(value);
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({paramFloat}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
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
    return std::async(std::launch::async, [this,
                    paramFloat32]()
        {
            std::promise<std::list<float>> resultPromise;
            static const auto topic = std::string("tb.simple/SimpleArrayInterface/rpc/funcFloat32");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                const std::list<float>& value = arg.value.get<std::list<float>>();
                resultPromise.set_value(value);
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({paramFloat32}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
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
    return std::async(std::launch::async, [this,
                    paramFloat]()
        {
            std::promise<std::list<double>> resultPromise;
            static const auto topic = std::string("tb.simple/SimpleArrayInterface/rpc/funcFloat64");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                const std::list<double>& value = arg.value.get<std::list<double>>();
                resultPromise.set_value(value);
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({paramFloat}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
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
    return std::async(std::launch::async, [this,
                    paramString]()
        {
            std::promise<std::list<std::string>> resultPromise;
            static const auto topic = std::string("tb.simple/SimpleArrayInterface/rpc/funcString");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                const std::list<std::string>& value = arg.value.get<std::list<std::string>>();
                resultPromise.set_value(value);
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({paramString}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
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

int SimpleArrayInterfaceClient::registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler)
{
    auto responseId = 0;
    std::uniform_int_distribution<> distribution (0, 100000);
    m_responseHandlerMutex.lock();
    do {
        responseId = distribution(randomNumberGenerator);
    } while (m_responseHandlerMap.find(responseId) != m_responseHandlerMap.end());
    m_responseHandlerMap.insert(std::pair<int, ApiGear::MQTT::InvokeReplyFunc>(responseId, handler));
    m_responseHandlerMutex.unlock();

    return responseId;
}

void SimpleArrayInterfaceClient::onInvokeReply(const std::string& args, const std::string& correlationData)
{
    const int randomId = std::stoi(correlationData);
    ApiGear::MQTT::InvokeReplyFunc responseHandler {};
    m_responseHandlerMutex.lock();
    if((m_responseHandlerMap.find(randomId) != m_responseHandlerMap.end()))
    {
        responseHandler = m_responseHandlerMap[randomId];
        m_responseHandlerMap.erase(randomId);
    }
    m_responseHandlerMutex.unlock();
    if(responseHandler) {
        const ApiGear::MQTT::InvokeReplyArg response{nlohmann::json::parse(args)};
        responseHandler(response);
    }
}

bool SimpleArrayInterfaceClient::isReady() const
{
    return m_isReady;
}

ISimpleArrayInterfacePublisher& SimpleArrayInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
