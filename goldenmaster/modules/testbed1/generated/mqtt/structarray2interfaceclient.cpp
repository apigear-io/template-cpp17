#include "testbed1/generated/mqtt/structarray2interfaceclient.h"
#include "testbed1/generated/core/structarray2interface.publisher.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include <random>

using namespace Test::Testbed1;
using namespace Test::Testbed1::MQTT;

namespace {
    std::mt19937 randomNumberGenerator (std::random_device{}());
}

StructArray2InterfaceClient::StructArray2InterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client)
    : MqttBaseAdapter(client, createTopicMap(client->getClientId()))
    , m_client(client)
    , m_publisher(std::make_unique<StructArray2InterfacePublisher>())
{
}

std::shared_ptr<StructArray2InterfaceClient> StructArray2InterfaceClient::create(std::shared_ptr<ApiGear::MQTT::Client> client)
{
    return std::make_shared<StructArray2InterfaceClient>(client);
}

StructArray2InterfaceClient::~StructArray2InterfaceClient()
{
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> StructArray2InterfaceClient::createTopicMap(const std::string& clientId)
{
    return {
        { std::string("testbed1/StructArray2Interface/prop/propBool"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropBoolLocal(args); } },
        { std::string("testbed1/StructArray2Interface/prop/propInt"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropIntLocal(args); } },
        { std::string("testbed1/StructArray2Interface/prop/propFloat"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropFloatLocal(args); } },
        { std::string("testbed1/StructArray2Interface/prop/propString"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropStringLocal(args); } },
        { std::string("testbed1/StructArray2Interface/prop/propEnum"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropEnumLocal(args); } },
        { std::string("testbed1/StructArray2Interface/sig/sigBool"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigBool(args); } },
        { std::string("testbed1/StructArray2Interface/sig/sigInt"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigInt(args); } },
        { std::string("testbed1/StructArray2Interface/sig/sigFloat"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigFloat(args); } },
        { std::string("testbed1/StructArray2Interface/sig/sigString"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigString(args); } },
        { std::string("testbed1/StructArray2Interface/rpc/funcBool/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("testbed1/StructArray2Interface/rpc/funcInt/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("testbed1/StructArray2Interface/rpc/funcFloat/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("testbed1/StructArray2Interface/rpc/funcString/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("testbed1/StructArray2Interface/rpc/funcEnum/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
    };
};

void StructArray2InterfaceClient::setPropBool(const StructBoolWithArray& propBool)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed1/StructArray2Interface/set/propBool");
    m_client->setRemoteProperty(topic, nlohmann::json(propBool).dump());
}

void StructArray2InterfaceClient::setPropBoolLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const StructBoolWithArray& propBool = fields.get<StructBoolWithArray>();
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

const StructBoolWithArray& StructArray2InterfaceClient::getPropBool() const
{
    return m_data.m_propBool;
}

void StructArray2InterfaceClient::setPropInt(const StructIntWithArray& propInt)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed1/StructArray2Interface/set/propInt");
    m_client->setRemoteProperty(topic, nlohmann::json(propInt).dump());
}

void StructArray2InterfaceClient::setPropIntLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const StructIntWithArray& propInt = fields.get<StructIntWithArray>();
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

const StructIntWithArray& StructArray2InterfaceClient::getPropInt() const
{
    return m_data.m_propInt;
}

void StructArray2InterfaceClient::setPropFloat(const StructFloatWithArray& propFloat)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed1/StructArray2Interface/set/propFloat");
    m_client->setRemoteProperty(topic, nlohmann::json(propFloat).dump());
}

void StructArray2InterfaceClient::setPropFloatLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const StructFloatWithArray& propFloat = fields.get<StructFloatWithArray>();
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

const StructFloatWithArray& StructArray2InterfaceClient::getPropFloat() const
{
    return m_data.m_propFloat;
}

void StructArray2InterfaceClient::setPropString(const StructStringWithArray& propString)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed1/StructArray2Interface/set/propString");
    m_client->setRemoteProperty(topic, nlohmann::json(propString).dump());
}

void StructArray2InterfaceClient::setPropStringLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const StructStringWithArray& propString = fields.get<StructStringWithArray>();
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const StructStringWithArray& StructArray2InterfaceClient::getPropString() const
{
    return m_data.m_propString;
}

void StructArray2InterfaceClient::setPropEnum(const StructEnumWithArray& propEnum)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed1/StructArray2Interface/set/propEnum");
    m_client->setRemoteProperty(topic, nlohmann::json(propEnum).dump());
}

void StructArray2InterfaceClient::setPropEnumLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const StructEnumWithArray& propEnum = fields.get<StructEnumWithArray>();
    if (m_data.m_propEnum != propEnum) {
        m_data.m_propEnum = propEnum;
        m_publisher->publishPropEnumChanged(propEnum);
    }
}

const StructEnumWithArray& StructArray2InterfaceClient::getPropEnum() const
{
    return m_data.m_propEnum;
}

std::list<StructBool> StructArray2InterfaceClient::funcBool(const StructBoolWithArray& paramBool)
{
    if(m_client == nullptr) {
        return std::list<StructBool>();
    }
    std::list<StructBool> value(funcBoolAsync(paramBool).get());
    return value;
}

std::future<std::list<StructBool>> StructArray2InterfaceClient::funcBoolAsync(const StructBoolWithArray& paramBool, std::function<void(std::list<StructBool>)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    paramBool]()
        {
            std::promise<std::list<StructBool>> resultPromise;
            static const auto topic = std::string("testbed1/StructArray2Interface/rpc/funcBool");
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

std::list<StructInt> StructArray2InterfaceClient::funcInt(const StructIntWithArray& paramInt)
{
    if(m_client == nullptr) {
        return std::list<StructInt>();
    }
    std::list<StructInt> value(funcIntAsync(paramInt).get());
    return value;
}

std::future<std::list<StructInt>> StructArray2InterfaceClient::funcIntAsync(const StructIntWithArray& paramInt, std::function<void(std::list<StructInt>)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    paramInt]()
        {
            std::promise<std::list<StructInt>> resultPromise;
            static const auto topic = std::string("testbed1/StructArray2Interface/rpc/funcInt");
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

std::list<StructFloat> StructArray2InterfaceClient::funcFloat(const StructFloatWithArray& paramFloat)
{
    if(m_client == nullptr) {
        return std::list<StructFloat>();
    }
    std::list<StructFloat> value(funcFloatAsync(paramFloat).get());
    return value;
}

std::future<std::list<StructFloat>> StructArray2InterfaceClient::funcFloatAsync(const StructFloatWithArray& paramFloat, std::function<void(std::list<StructFloat>)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    paramFloat]()
        {
            std::promise<std::list<StructFloat>> resultPromise;
            static const auto topic = std::string("testbed1/StructArray2Interface/rpc/funcFloat");
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

std::list<StructString> StructArray2InterfaceClient::funcString(const StructStringWithArray& paramString)
{
    if(m_client == nullptr) {
        return std::list<StructString>();
    }
    std::list<StructString> value(funcStringAsync(paramString).get());
    return value;
}

std::future<std::list<StructString>> StructArray2InterfaceClient::funcStringAsync(const StructStringWithArray& paramString, std::function<void(std::list<StructString>)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    paramString]()
        {
            std::promise<std::list<StructString>> resultPromise;
            static const auto topic = std::string("testbed1/StructArray2Interface/rpc/funcString");
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

std::list<Enum0Enum> StructArray2InterfaceClient::funcEnum(const StructEnumWithArray& paramEnum)
{
    if(m_client == nullptr) {
        return std::list<Enum0Enum>();
    }
    std::list<Enum0Enum> value(funcEnumAsync(paramEnum).get());
    return value;
}

std::future<std::list<Enum0Enum>> StructArray2InterfaceClient::funcEnumAsync(const StructEnumWithArray& paramEnum, std::function<void(std::list<Enum0Enum>)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    paramEnum]()
        {
            std::promise<std::list<Enum0Enum>> resultPromise;
            static const auto topic = std::string("testbed1/StructArray2Interface/rpc/funcEnum");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const std::list<Enum0Enum>& value = arg.value.get<std::list<Enum0Enum>>();
                resultPromise.set_value(value);
                if (callback)
                {
                    callback(value);
                }
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic, nlohmann::json::array({paramEnum}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}
void StructArray2InterfaceClient::onSigBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigBool(json_args[0].get<StructBoolWithArray>());
}
void StructArray2InterfaceClient::onSigInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigInt(json_args[0].get<StructIntWithArray>());
}
void StructArray2InterfaceClient::onSigFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigFloat(json_args[0].get<StructFloatWithArray>());
}
void StructArray2InterfaceClient::onSigString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigString(json_args[0].get<StructStringWithArray>());
}

int StructArray2InterfaceClient::registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler)
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

void StructArray2InterfaceClient::onInvokeReply(const std::string& args, const std::string& correlationData)
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

bool StructArray2InterfaceClient::isReady() const
{
    return m_isReady;
}

IStructArray2InterfacePublisher& StructArray2InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
