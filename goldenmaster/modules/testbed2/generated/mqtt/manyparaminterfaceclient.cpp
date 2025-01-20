#include "testbed2/generated/mqtt/manyparaminterfaceclient.h"
#include "testbed2/generated/core/manyparaminterface.publisher.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"
#include <random>

using namespace Test::Testbed2;
using namespace Test::Testbed2::MQTT;

namespace {
    std::mt19937 randomNumberGenerator (std::random_device{}());
}

ManyParamInterfaceClient::ManyParamInterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client)
    : m_isReady(false)
    , m_client(client)
    , m_publisher(std::make_unique<ManyParamInterfacePublisher>())
    , m_topics(createTopicMap(m_client->getClientId()))
{
    m_connectionStatusRegistrationID = m_client->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

ManyParamInterfaceClient::~ManyParamInterfaceClient()
{
    for (const auto& topic: m_topics)
    {
        m_client->unsubscribeTopic(topic. first);
    }
    m_client->unsubscribeToConnectionStatus(m_connectionStatusRegistrationID);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> ManyParamInterfaceClient::createTopicMap(const std::string& clientId)
{
    return {
        { std::string("testbed2/ManyParamInterface/prop/prop1"), [this](const std::string& args, const std::string&, const std::string&){ this->setProp1Local(args); } },
        { std::string("testbed2/ManyParamInterface/prop/prop2"), [this](const std::string& args, const std::string&, const std::string&){ this->setProp2Local(args); } },
        { std::string("testbed2/ManyParamInterface/prop/prop3"), [this](const std::string& args, const std::string&, const std::string&){ this->setProp3Local(args); } },
        { std::string("testbed2/ManyParamInterface/prop/prop4"), [this](const std::string& args, const std::string&, const std::string&){ this->setProp4Local(args); } },
        { std::string("testbed2/ManyParamInterface/sig/sig1"), [this](const std::string& args, const std::string&, const std::string&){ this->onSig1(args); } },
        { std::string("testbed2/ManyParamInterface/sig/sig2"), [this](const std::string& args, const std::string&, const std::string&){ this->onSig2(args); } },
        { std::string("testbed2/ManyParamInterface/sig/sig3"), [this](const std::string& args, const std::string&, const std::string&){ this->onSig3(args); } },
        { std::string("testbed2/ManyParamInterface/sig/sig4"), [this](const std::string& args, const std::string&, const std::string&){ this->onSig4(args); } },
        { std::string("testbed2/ManyParamInterface/rpc/func1/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("testbed2/ManyParamInterface/rpc/func2/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("testbed2/ManyParamInterface/rpc/func3/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("testbed2/ManyParamInterface/rpc/func4/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
    };
};

void ManyParamInterfaceClient::onConnectionStatusChanged(bool connectionStatus)
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

void ManyParamInterfaceClient::setProp1(int prop1)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed2/ManyParamInterface/set/prop1");
    m_client->setRemoteProperty(topic, nlohmann::json(prop1).dump());
}

void ManyParamInterfaceClient::setProp1Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    int prop1 = fields.get<int>();
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

int ManyParamInterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

void ManyParamInterfaceClient::setProp2(int prop2)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed2/ManyParamInterface/set/prop2");
    m_client->setRemoteProperty(topic, nlohmann::json(prop2).dump());
}

void ManyParamInterfaceClient::setProp2Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    int prop2 = fields.get<int>();
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

int ManyParamInterfaceClient::getProp2() const
{
    return m_data.m_prop2;
}

void ManyParamInterfaceClient::setProp3(int prop3)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed2/ManyParamInterface/set/prop3");
    m_client->setRemoteProperty(topic, nlohmann::json(prop3).dump());
}

void ManyParamInterfaceClient::setProp3Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    int prop3 = fields.get<int>();
    if (m_data.m_prop3 != prop3) {
        m_data.m_prop3 = prop3;
        m_publisher->publishProp3Changed(prop3);
    }
}

int ManyParamInterfaceClient::getProp3() const
{
    return m_data.m_prop3;
}

void ManyParamInterfaceClient::setProp4(int prop4)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("testbed2/ManyParamInterface/set/prop4");
    m_client->setRemoteProperty(topic, nlohmann::json(prop4).dump());
}

void ManyParamInterfaceClient::setProp4Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    int prop4 = fields.get<int>();
    if (m_data.m_prop4 != prop4) {
        m_data.m_prop4 = prop4;
        m_publisher->publishProp4Changed(prop4);
    }
}

int ManyParamInterfaceClient::getProp4() const
{
    return m_data.m_prop4;
}

int ManyParamInterfaceClient::func1(int param1)
{
    if(m_client == nullptr) {
        return 0;
    }
    int value(func1Async(param1).get());
    return value;
}

std::future<int> ManyParamInterfaceClient::func1Async(int param1, std::function<void(int)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    param1]()
        {
            std::promise<int> resultPromise;
            static const auto topic = std::string("testbed2/ManyParamInterface/rpc/func1");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const int& value = arg.value.get<int>();
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

int ManyParamInterfaceClient::func2(int param1, int param2)
{
    if(m_client == nullptr) {
        return 0;
    }
    int value(func2Async(param1, param2).get());
    return value;
}

std::future<int> ManyParamInterfaceClient::func2Async(int param1, int param2, std::function<void(int)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    param1,
                    param2]()
        {
            std::promise<int> resultPromise;
            static const auto topic = std::string("testbed2/ManyParamInterface/rpc/func2");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const int& value = arg.value.get<int>();
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

int ManyParamInterfaceClient::func3(int param1, int param2, int param3)
{
    if(m_client == nullptr) {
        return 0;
    }
    int value(func3Async(param1, param2, param3).get());
    return value;
}

std::future<int> ManyParamInterfaceClient::func3Async(int param1, int param2, int param3, std::function<void(int)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    param1,
                    param2,
                    param3]()
        {
            std::promise<int> resultPromise;
            static const auto topic = std::string("testbed2/ManyParamInterface/rpc/func3");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const int& value = arg.value.get<int>();
                resultPromise.set_value(value);
                if (callback)
                {
                    callback(value);
                }
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic, nlohmann::json::array({param1, param2, param3}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}

int ManyParamInterfaceClient::func4(int param1, int param2, int param3, int param4)
{
    if(m_client == nullptr) {
        return 0;
    }
    int value(func4Async(param1, param2, param3, param4).get());
    return value;
}

std::future<int> ManyParamInterfaceClient::func4Async(int param1, int param2, int param3, int param4, std::function<void(int)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    param1,
                    param2,
                    param3,
                    param4]()
        {
            std::promise<int> resultPromise;
            static const auto topic = std::string("testbed2/ManyParamInterface/rpc/func4");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const int& value = arg.value.get<int>();
                resultPromise.set_value(value);
                if (callback)
                {
                    callback(value);
                }
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic, nlohmann::json::array({param1, param2, param3, param4}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}
void ManyParamInterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<int>());
}
void ManyParamInterfaceClient::onSig2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig2(json_args[0].get<int>(),json_args[1].get<int>());
}
void ManyParamInterfaceClient::onSig3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig3(json_args[0].get<int>(),json_args[1].get<int>(),json_args[2].get<int>());
}
void ManyParamInterfaceClient::onSig4(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig4(json_args[0].get<int>(),json_args[1].get<int>(),json_args[2].get<int>(),json_args[3].get<int>());
}

int ManyParamInterfaceClient::registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler)
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

void ManyParamInterfaceClient::onInvokeReply(const std::string& args, const std::string& correlationData)
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

bool ManyParamInterfaceClient::isReady() const
{
    return m_isReady;
}

IManyParamInterfacePublisher& ManyParamInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
