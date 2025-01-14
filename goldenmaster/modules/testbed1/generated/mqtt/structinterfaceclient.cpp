#include "testbed1/generated/mqtt/structinterfaceclient.h"
#include "testbed1/generated/core/structinterface.publisher.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include <random>

using namespace Test::Testbed1;
using namespace Test::Testbed1::MQTT;

namespace {
    std::mt19937 randomNumberGenerator (std::random_device{}());
}

StructInterfaceClient::StructInterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client)
    : MqttBaseAdapter(client, createTopicMap(client->getClientId()))
    , m_client(client)
    , m_publisher(std::make_unique<StructInterfacePublisher>())
{
}

StructInterfaceClient::~StructInterfaceClient()
{
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> StructInterfaceClient::createTopicMap(const std::string& clientId)
{
    return {
        { std::string("testbed1/StructInterface/prop/propBool"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropBoolLocal(args); } },
        { std::string("testbed1/StructInterface/prop/propInt"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropIntLocal(args); } },
        { std::string("testbed1/StructInterface/prop/propFloat"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropFloatLocal(args); } },
        { std::string("testbed1/StructInterface/prop/propString"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropStringLocal(args); } },
        { std::string("testbed1/StructInterface/sig/sigBool"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigBool(args); } },
        { std::string("testbed1/StructInterface/sig/sigInt"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigInt(args); } },
        { std::string("testbed1/StructInterface/sig/sigFloat"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigFloat(args); } },
        { std::string("testbed1/StructInterface/sig/sigString"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigString(args); } },
        { std::string("testbed1/StructInterface/rpc/funcBool/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("testbed1/StructInterface/rpc/funcInt/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("testbed1/StructInterface/rpc/funcFloat/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("testbed1/StructInterface/rpc/funcString/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
    };
};

void StructInterfaceClient::setPropBool(const StructBool& propBool)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed1/StructInterface/set/propBool");
    m_client->setRemoteProperty(topic, nlohmann::json(propBool).dump());
}

void StructInterfaceClient::setPropBoolLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const StructBool& propBool = fields.get<StructBool>();
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
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed1/StructInterface/set/propInt");
    m_client->setRemoteProperty(topic, nlohmann::json(propInt).dump());
}

void StructInterfaceClient::setPropIntLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const StructInt& propInt = fields.get<StructInt>();
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
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed1/StructInterface/set/propFloat");
    m_client->setRemoteProperty(topic, nlohmann::json(propFloat).dump());
}

void StructInterfaceClient::setPropFloatLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const StructFloat& propFloat = fields.get<StructFloat>();
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
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed1/StructInterface/set/propString");
    m_client->setRemoteProperty(topic, nlohmann::json(propString).dump());
}

void StructInterfaceClient::setPropStringLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const StructString& propString = fields.get<StructString>();
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
    if(m_client == nullptr) {
        return StructBool();
    }
    StructBool value(funcBoolAsync(paramBool).get());
    return value;
}

std::future<StructBool> StructInterfaceClient::funcBoolAsync(const StructBool& paramBool, std::function<void(StructBool)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    paramBool]()
        {
            std::promise<StructBool> resultPromise;
            static const auto topic = std::string("testbed1/StructInterface/rpc/funcBool");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const StructBool& value = arg.value.get<StructBool>();
                resultPromise.set_value(value);
                if (callback)
                {
                    callback(value);
                }
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic, nlohmann::json::array({paramBool}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}

StructInt StructInterfaceClient::funcInt(const StructInt& paramInt)
{
    if(m_client == nullptr) {
        return StructInt();
    }
    StructInt value(funcIntAsync(paramInt).get());
    return value;
}

std::future<StructInt> StructInterfaceClient::funcIntAsync(const StructInt& paramInt, std::function<void(StructInt)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    paramInt]()
        {
            std::promise<StructInt> resultPromise;
            static const auto topic = std::string("testbed1/StructInterface/rpc/funcInt");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const StructInt& value = arg.value.get<StructInt>();
                resultPromise.set_value(value);
                if (callback)
                {
                    callback(value);
                }
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic, nlohmann::json::array({paramInt}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}

StructFloat StructInterfaceClient::funcFloat(const StructFloat& paramFloat)
{
    if(m_client == nullptr) {
        return StructFloat();
    }
    StructFloat value(funcFloatAsync(paramFloat).get());
    return value;
}

std::future<StructFloat> StructInterfaceClient::funcFloatAsync(const StructFloat& paramFloat, std::function<void(StructFloat)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    paramFloat]()
        {
            std::promise<StructFloat> resultPromise;
            static const auto topic = std::string("testbed1/StructInterface/rpc/funcFloat");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const StructFloat& value = arg.value.get<StructFloat>();
                resultPromise.set_value(value);
                if (callback)
                {
                    callback(value);
                }
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic, nlohmann::json::array({paramFloat}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}

StructString StructInterfaceClient::funcString(const StructString& paramString)
{
    if(m_client == nullptr) {
        return StructString();
    }
    StructString value(funcStringAsync(paramString).get());
    return value;
}

std::future<StructString> StructInterfaceClient::funcStringAsync(const StructString& paramString, std::function<void(StructString)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    paramString]()
        {
            std::promise<StructString> resultPromise;
            static const auto topic = std::string("testbed1/StructInterface/rpc/funcString");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const StructString& value = arg.value.get<StructString>();
                resultPromise.set_value(value);
                if (callback)
                {
                    callback(value);
                }
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic, nlohmann::json::array({paramString}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}
void StructInterfaceClient::onSigBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigBool(json_args[0].get<StructBool>());
}
void StructInterfaceClient::onSigInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigInt(json_args[0].get<StructInt>());
}
void StructInterfaceClient::onSigFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigFloat(json_args[0].get<StructFloat>());
}
void StructInterfaceClient::onSigString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigString(json_args[0].get<StructString>());
}

int StructInterfaceClient::registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler)
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

void StructInterfaceClient::onInvokeReply(const std::string& args, const std::string& correlationData)
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

bool StructInterfaceClient::isReady() const
{
    return m_isReady;
}

IStructInterfacePublisher& StructInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
