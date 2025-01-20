#include "tb_same1/generated/mqtt/sameenum1interfaceclient.h"
#include "tb_same1/generated/core/sameenum1interface.publisher.h"
#include "tb_same1/generated/core/tb_same1.json.adapter.h"
#include <random>

using namespace Test::TbSame1;
using namespace Test::TbSame1::MQTT;

namespace {
    std::mt19937 randomNumberGenerator (std::random_device{}());
}

SameEnum1InterfaceClient::SameEnum1InterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client)
    : m_isReady(false)
    , m_client(client)
    , m_publisher(std::make_unique<SameEnum1InterfacePublisher>())
    , m_topics(createTopicMap(m_client->getClientId()))
{
    m_connectionStatusRegistrationID = m_client->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

SameEnum1InterfaceClient::~SameEnum1InterfaceClient()
{
    for (const auto& topic: m_topics)
    {
        m_client->unsubscribeTopic(topic. first);
    }
    m_client->unsubscribeToConnectionStatus(m_connectionStatusRegistrationID);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> SameEnum1InterfaceClient::createTopicMap(const std::string& clientId)
{
    return {
        { std::string("tb.same1/SameEnum1Interface/prop/prop1"), [this](const std::string& args, const std::string&, const std::string&){ this->setProp1Local(args); } },
        { std::string("tb.same1/SameEnum1Interface/sig/sig1"), [this](const std::string& args, const std::string&, const std::string&){ this->onSig1(args); } },
        { std::string("tb.same1/SameEnum1Interface/rpc/func1/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
    };
};

void SameEnum1InterfaceClient::onConnectionStatusChanged(bool connectionStatus)
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

void SameEnum1InterfaceClient::setProp1(Enum1Enum prop1)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.same1/SameEnum1Interface/set/prop1");
    m_client->setRemoteProperty(topic, nlohmann::json(prop1).dump());
}

void SameEnum1InterfaceClient::setProp1Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    Enum1Enum prop1 = fields.get<Enum1Enum>();
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

Enum1Enum SameEnum1InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

Enum1Enum SameEnum1InterfaceClient::func1(Enum1Enum param1)
{
    if(m_client == nullptr) {
        return Enum1Enum::value1;
    }
    Enum1Enum value(func1Async(param1).get());
    return value;
}

std::future<Enum1Enum> SameEnum1InterfaceClient::func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    param1]()
        {
            std::promise<Enum1Enum> resultPromise;
            static const auto topic = std::string("tb.same1/SameEnum1Interface/rpc/func1");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                const Enum1Enum& value = arg.value.get<Enum1Enum>();
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
void SameEnum1InterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<Enum1Enum>());
}

int SameEnum1InterfaceClient::registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler)
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

void SameEnum1InterfaceClient::onInvokeReply(const std::string& args, const std::string& correlationData)
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

bool SameEnum1InterfaceClient::isReady() const
{
    return m_isReady;
}

ISameEnum1InterfacePublisher& SameEnum1InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
