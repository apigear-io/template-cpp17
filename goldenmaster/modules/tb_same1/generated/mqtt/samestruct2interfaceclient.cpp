#include "tb_same1/generated/mqtt/samestruct2interfaceclient.h"
#include "tb_same1/generated/core/samestruct2interface.publisher.h"
#include "tb_same1/generated/core/tb_same1.json.adapter.h"
#include <random>

using namespace Test::TbSame1;
using namespace Test::TbSame1::MQTT;

namespace {
    std::mt19937 randomNumberGenerator (std::random_device{}());
}

SameStruct2InterfaceClient::SameStruct2InterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client)
    : m_isReady(false)
    , m_client(client)
    , m_publisher(std::make_unique<SameStruct2InterfacePublisher>())
    , m_topics(createTopicMap(m_client->getClientId()))
{
    m_connectionStatusRegistrationID = m_client->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

SameStruct2InterfaceClient::~SameStruct2InterfaceClient()
{
    for (const auto& topic: m_topics)
    {
        m_client->unsubscribeTopic(topic. first);
    }
    m_client->unsubscribeToConnectionStatus(m_connectionStatusRegistrationID);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> SameStruct2InterfaceClient::createTopicMap(const std::string& clientId)
{
    return {
        { std::string("tb.same1/SameStruct2Interface/prop/prop1"), [this](const std::string& args, const std::string&, const std::string&){ this->setProp1Local(args); } },
        { std::string("tb.same1/SameStruct2Interface/prop/prop2"), [this](const std::string& args, const std::string&, const std::string&){ this->setProp2Local(args); } },
        { std::string("tb.same1/SameStruct2Interface/sig/sig1"), [this](const std::string& args, const std::string&, const std::string&){ this->onSig1(args); } },
        { std::string("tb.same1/SameStruct2Interface/sig/sig2"), [this](const std::string& args, const std::string&, const std::string&){ this->onSig2(args); } },
        { std::string("tb.same1/SameStruct2Interface/rpc/func1/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("tb.same1/SameStruct2Interface/rpc/func2/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
    };
};

void SameStruct2InterfaceClient::onConnectionStatusChanged(bool connectionStatus)
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

void SameStruct2InterfaceClient::setProp1(const Struct2& prop1)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.same1/SameStruct2Interface/set/prop1");
    m_client->setRemoteProperty(topic, nlohmann::json(prop1).dump());
}

void SameStruct2InterfaceClient::setProp1Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const Struct2& prop1 = fields.get<Struct2>();
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

const Struct2& SameStruct2InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

void SameStruct2InterfaceClient::setProp2(const Struct2& prop2)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.same1/SameStruct2Interface/set/prop2");
    m_client->setRemoteProperty(topic, nlohmann::json(prop2).dump());
}

void SameStruct2InterfaceClient::setProp2Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const Struct2& prop2 = fields.get<Struct2>();
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

const Struct2& SameStruct2InterfaceClient::getProp2() const
{
    return m_data.m_prop2;
}

Struct1 SameStruct2InterfaceClient::func1(const Struct1& param1)
{
    if(m_client == nullptr) {
        return Struct1();
    }
    Struct1 value(func1Async(param1).get());
    return value;
}

std::future<Struct1> SameStruct2InterfaceClient::func1Async(const Struct1& param1, std::function<void(Struct1)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    param1]()
        {
            std::promise<Struct1> resultPromise;
            static const auto topic = std::string("tb.same1/SameStruct2Interface/rpc/func1");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const Struct1& value = arg.value.get<Struct1>();
                resultPromise.set_value(value);
                if (callback)
                {
                    callback(value);
                }
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic, nlohmann::json::array({param1}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}

Struct1 SameStruct2InterfaceClient::func2(const Struct1& param1, const Struct2& param2)
{
    if(m_client == nullptr) {
        return Struct1();
    }
    Struct1 value(func2Async(param1, param2).get());
    return value;
}

std::future<Struct1> SameStruct2InterfaceClient::func2Async(const Struct1& param1, const Struct2& param2, std::function<void(Struct1)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    param1,
                    param2]()
        {
            std::promise<Struct1> resultPromise;
            static const auto topic = std::string("tb.same1/SameStruct2Interface/rpc/func2");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const Struct1& value = arg.value.get<Struct1>();
                resultPromise.set_value(value);
                if (callback)
                {
                    callback(value);
                }
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic, nlohmann::json::array({param1, param2}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}
void SameStruct2InterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<Struct1>());
}
void SameStruct2InterfaceClient::onSig2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig2(json_args[0].get<Struct1>(),json_args[1].get<Struct2>());
}

int SameStruct2InterfaceClient::registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler)
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

void SameStruct2InterfaceClient::onInvokeReply(const std::string& args, const std::string& correlationData)
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

bool SameStruct2InterfaceClient::isReady() const
{
    return m_isReady;
}

ISameStruct2InterfacePublisher& SameStruct2InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
