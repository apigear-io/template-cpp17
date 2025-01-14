#include "testbed2/generated/mqtt/nestedstruct3interfaceclient.h"
#include "testbed2/generated/core/nestedstruct3interface.publisher.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"
#include <random>

using namespace Test::Testbed2;
using namespace Test::Testbed2::MQTT;

namespace {
    std::mt19937 randomNumberGenerator (std::random_device{}());
}

NestedStruct3InterfaceClient::NestedStruct3InterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client)
    : MqttBaseAdapter(client, createTopicMap(client->getClientId()))
    , m_client(client)
    , m_publisher(std::make_unique<NestedStruct3InterfacePublisher>())
{
}

NestedStruct3InterfaceClient::~NestedStruct3InterfaceClient()
{
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> NestedStruct3InterfaceClient::createTopicMap(const std::string& clientId)
{
    return {
        { std::string("testbed2/NestedStruct3Interface/prop/prop1"), [this](const std::string& args, const std::string&, const std::string&){ this->setProp1Local(args); } },
        { std::string("testbed2/NestedStruct3Interface/prop/prop2"), [this](const std::string& args, const std::string&, const std::string&){ this->setProp2Local(args); } },
        { std::string("testbed2/NestedStruct3Interface/prop/prop3"), [this](const std::string& args, const std::string&, const std::string&){ this->setProp3Local(args); } },
        { std::string("testbed2/NestedStruct3Interface/sig/sig1"), [this](const std::string& args, const std::string&, const std::string&){ this->onSig1(args); } },
        { std::string("testbed2/NestedStruct3Interface/sig/sig2"), [this](const std::string& args, const std::string&, const std::string&){ this->onSig2(args); } },
        { std::string("testbed2/NestedStruct3Interface/sig/sig3"), [this](const std::string& args, const std::string&, const std::string&){ this->onSig3(args); } },
        { std::string("testbed2/NestedStruct3Interface/rpc/func1/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("testbed2/NestedStruct3Interface/rpc/func2/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("testbed2/NestedStruct3Interface/rpc/func3/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
    };
};

void NestedStruct3InterfaceClient::setProp1(const NestedStruct1& prop1)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed2/NestedStruct3Interface/set/prop1");
    m_client->setRemoteProperty(topic, nlohmann::json(prop1).dump());
}

void NestedStruct3InterfaceClient::setProp1Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const NestedStruct1& prop1 = fields.get<NestedStruct1>();
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

const NestedStruct1& NestedStruct3InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

void NestedStruct3InterfaceClient::setProp2(const NestedStruct2& prop2)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed2/NestedStruct3Interface/set/prop2");
    m_client->setRemoteProperty(topic, nlohmann::json(prop2).dump());
}

void NestedStruct3InterfaceClient::setProp2Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const NestedStruct2& prop2 = fields.get<NestedStruct2>();
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

const NestedStruct2& NestedStruct3InterfaceClient::getProp2() const
{
    return m_data.m_prop2;
}

void NestedStruct3InterfaceClient::setProp3(const NestedStruct3& prop3)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed2/NestedStruct3Interface/set/prop3");
    m_client->setRemoteProperty(topic, nlohmann::json(prop3).dump());
}

void NestedStruct3InterfaceClient::setProp3Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const NestedStruct3& prop3 = fields.get<NestedStruct3>();
    if (m_data.m_prop3 != prop3) {
        m_data.m_prop3 = prop3;
        m_publisher->publishProp3Changed(prop3);
    }
}

const NestedStruct3& NestedStruct3InterfaceClient::getProp3() const
{
    return m_data.m_prop3;
}

NestedStruct1 NestedStruct3InterfaceClient::func1(const NestedStruct1& param1)
{
    if(m_client == nullptr) {
        return NestedStruct1();
    }
    NestedStruct1 value(func1Async(param1).get());
    return value;
}

std::future<NestedStruct1> NestedStruct3InterfaceClient::func1Async(const NestedStruct1& param1)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1]()
        {
            std::promise<NestedStruct1> resultPromise;
            static const auto topic = std::string("testbed2/NestedStruct3Interface/rpc/func1");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                const NestedStruct1& value = arg.value.get<NestedStruct1>();
                resultPromise.set_value(value);
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({param1}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}

NestedStruct1 NestedStruct3InterfaceClient::func2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    if(m_client == nullptr) {
        return NestedStruct1();
    }
    NestedStruct1 value(func2Async(param1, param2).get());
    return value;
}

std::future<NestedStruct1> NestedStruct3InterfaceClient::func2Async(const NestedStruct1& param1, const NestedStruct2& param2)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1,
                    param2]()
        {
            std::promise<NestedStruct1> resultPromise;
            static const auto topic = std::string("testbed2/NestedStruct3Interface/rpc/func2");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                const NestedStruct1& value = arg.value.get<NestedStruct1>();
                resultPromise.set_value(value);
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({param1, param2}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}

NestedStruct1 NestedStruct3InterfaceClient::func3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3)
{
    if(m_client == nullptr) {
        return NestedStruct1();
    }
    NestedStruct1 value(func3Async(param1, param2, param3).get());
    return value;
}

std::future<NestedStruct1> NestedStruct3InterfaceClient::func3Async(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1,
                    param2,
                    param3]()
        {
            std::promise<NestedStruct1> resultPromise;
            static const auto topic = std::string("testbed2/NestedStruct3Interface/rpc/func3");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                const NestedStruct1& value = arg.value.get<NestedStruct1>();
                resultPromise.set_value(value);
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({param1, param2, param3}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}
void NestedStruct3InterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<NestedStruct1>());
}
void NestedStruct3InterfaceClient::onSig2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig2(json_args[0].get<NestedStruct1>(),json_args[1].get<NestedStruct2>());
}
void NestedStruct3InterfaceClient::onSig3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig3(json_args[0].get<NestedStruct1>(),json_args[1].get<NestedStruct2>(),json_args[2].get<NestedStruct3>());
}

int NestedStruct3InterfaceClient::registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler)
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

void NestedStruct3InterfaceClient::onInvokeReply(const std::string& args, const std::string& correlationData)
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

bool NestedStruct3InterfaceClient::isReady() const
{
    return m_isReady;
}

INestedStruct3InterfacePublisher& NestedStruct3InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
