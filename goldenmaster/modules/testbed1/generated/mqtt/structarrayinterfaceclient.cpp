#include "testbed1/generated/mqtt/structarrayinterfaceclient.h"
#include "testbed1/generated/core/structarrayinterface.publisher.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include <random>

using namespace Test::Testbed1;
using namespace Test::Testbed1::MQTT;

namespace {
    std::mt19937 randomNumberGenerator (std::random_device{}());
}

StructArrayInterfaceClient::StructArrayInterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client)
    : MqttBaseAdapter(client, createTopicMap(client->getClientId()))
    , m_client(client)
    , m_publisher(std::make_unique<StructArrayInterfacePublisher>())
{
}

StructArrayInterfaceClient::~StructArrayInterfaceClient()
{
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> StructArrayInterfaceClient::createTopicMap(const std::string& clientId)
{
    return {
        { std::string("testbed1/StructArrayInterface/prop/propBool"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropBoolLocal(args); } },
        { std::string("testbed1/StructArrayInterface/prop/propInt"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropIntLocal(args); } },
        { std::string("testbed1/StructArrayInterface/prop/propFloat"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropFloatLocal(args); } },
        { std::string("testbed1/StructArrayInterface/prop/propString"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropStringLocal(args); } },
        { std::string("testbed1/StructArrayInterface/sig/sigBool"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigBool(args); } },
        { std::string("testbed1/StructArrayInterface/sig/sigInt"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigInt(args); } },
        { std::string("testbed1/StructArrayInterface/sig/sigFloat"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigFloat(args); } },
        { std::string("testbed1/StructArrayInterface/sig/sigString"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigString(args); } },
        { std::string("testbed1/StructArrayInterface/rpc/funcBool/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("testbed1/StructArrayInterface/rpc/funcInt/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("testbed1/StructArrayInterface/rpc/funcFloat/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("testbed1/StructArrayInterface/rpc/funcString/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
    };
};

void StructArrayInterfaceClient::setPropBool(const std::list<StructBool>& propBool)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed1/StructArrayInterface/set/propBool");
    m_client->setRemoteProperty(topic, nlohmann::json(propBool).dump());
}

void StructArrayInterfaceClient::setPropBoolLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<StructBool>& propBool = fields.get<std::list<StructBool>>();
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
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed1/StructArrayInterface/set/propInt");
    m_client->setRemoteProperty(topic, nlohmann::json(propInt).dump());
}

void StructArrayInterfaceClient::setPropIntLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<StructInt>& propInt = fields.get<std::list<StructInt>>();
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
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed1/StructArrayInterface/set/propFloat");
    m_client->setRemoteProperty(topic, nlohmann::json(propFloat).dump());
}

void StructArrayInterfaceClient::setPropFloatLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<StructFloat>& propFloat = fields.get<std::list<StructFloat>>();
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
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed1/StructArrayInterface/set/propString");
    m_client->setRemoteProperty(topic, nlohmann::json(propString).dump());
}

void StructArrayInterfaceClient::setPropStringLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<StructString>& propString = fields.get<std::list<StructString>>();
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::list<StructString>& StructArrayInterfaceClient::getPropString() const
{
    return m_data.m_propString;
}

std::list<StructBool> StructArrayInterfaceClient::funcBool(const std::list<StructBool>& paramBool)
{
    if(m_client == nullptr) {
        return std::list<StructBool>();
    }
    std::list<StructBool> value(funcBoolAsync(paramBool).get());
    return value;
}

std::future<std::list<StructBool>> StructArrayInterfaceClient::funcBoolAsync(const std::list<StructBool>& paramBool, std::function<void(std::list<StructBool>)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    paramBool]()
        {
            std::promise<std::list<StructBool>> resultPromise;
            static const auto topic = std::string("testbed1/StructArrayInterface/rpc/funcBool");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const std::list<StructBool>& value = arg.value.get<std::list<StructBool>>();
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

std::list<StructInt> StructArrayInterfaceClient::funcInt(const std::list<StructInt>& paramInt)
{
    if(m_client == nullptr) {
        return std::list<StructInt>();
    }
    std::list<StructInt> value(funcIntAsync(paramInt).get());
    return value;
}

std::future<std::list<StructInt>> StructArrayInterfaceClient::funcIntAsync(const std::list<StructInt>& paramInt, std::function<void(std::list<StructInt>)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    paramInt]()
        {
            std::promise<std::list<StructInt>> resultPromise;
            static const auto topic = std::string("testbed1/StructArrayInterface/rpc/funcInt");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const std::list<StructInt>& value = arg.value.get<std::list<StructInt>>();
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

std::list<StructFloat> StructArrayInterfaceClient::funcFloat(const std::list<StructFloat>& paramFloat)
{
    if(m_client == nullptr) {
        return std::list<StructFloat>();
    }
    std::list<StructFloat> value(funcFloatAsync(paramFloat).get());
    return value;
}

std::future<std::list<StructFloat>> StructArrayInterfaceClient::funcFloatAsync(const std::list<StructFloat>& paramFloat, std::function<void(std::list<StructFloat>)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    paramFloat]()
        {
            std::promise<std::list<StructFloat>> resultPromise;
            static const auto topic = std::string("testbed1/StructArrayInterface/rpc/funcFloat");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const std::list<StructFloat>& value = arg.value.get<std::list<StructFloat>>();
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

std::list<StructString> StructArrayInterfaceClient::funcString(const std::list<StructString>& paramString)
{
    if(m_client == nullptr) {
        return std::list<StructString>();
    }
    std::list<StructString> value(funcStringAsync(paramString).get());
    return value;
}

std::future<std::list<StructString>> StructArrayInterfaceClient::funcStringAsync(const std::list<StructString>& paramString, std::function<void(std::list<StructString>)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    paramString]()
        {
            std::promise<std::list<StructString>> resultPromise;
            static const auto topic = std::string("testbed1/StructArrayInterface/rpc/funcString");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const std::list<StructString>& value = arg.value.get<std::list<StructString>>();
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
void StructArrayInterfaceClient::onSigBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigBool(json_args[0].get<std::list<StructBool>>());
}
void StructArrayInterfaceClient::onSigInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigInt(json_args[0].get<std::list<StructInt>>());
}
void StructArrayInterfaceClient::onSigFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigFloat(json_args[0].get<std::list<StructFloat>>());
}
void StructArrayInterfaceClient::onSigString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigString(json_args[0].get<std::list<StructString>>());
}

int StructArrayInterfaceClient::registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler)
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

void StructArrayInterfaceClient::onInvokeReply(const std::string& args, const std::string& correlationData)
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

bool StructArrayInterfaceClient::isReady() const
{
    return m_isReady;
}

IStructArrayInterfacePublisher& StructArrayInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
