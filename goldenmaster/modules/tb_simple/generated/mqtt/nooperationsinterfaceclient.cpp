#include "tb_simple/generated/mqtt/nooperationsinterfaceclient.h"
#include "tb_simple/generated/core/nooperationsinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <random>

using namespace Test::TbSimple;
using namespace Test::TbSimple::MQTT;

namespace {
    std::mt19937 randomNumberGenerator (std::random_device{}());
}

NoOperationsInterfaceClient::NoOperationsInterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client)
    : MqttBaseAdapter(client, createTopicMap(client->getClientId()))
    , m_client(client)
    , m_publisher(std::make_unique<NoOperationsInterfacePublisher>())
{
}

NoOperationsInterfaceClient::~NoOperationsInterfaceClient()
{
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> NoOperationsInterfaceClient::createTopicMap(const std::string&)
{
    return {
        { std::string("tb.simple/NoOperationsInterface/prop/propBool"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropBoolLocal(args); } },
        { std::string("tb.simple/NoOperationsInterface/prop/propInt"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropIntLocal(args); } },
        { std::string("tb.simple/NoOperationsInterface/sig/sigVoid"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigVoid(args); } },
        { std::string("tb.simple/NoOperationsInterface/sig/sigBool"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigBool(args); } },
    };
};

void NoOperationsInterfaceClient::setPropBool(bool propBool)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.simple/NoOperationsInterface/set/propBool");
    m_client->setRemoteProperty(topic, nlohmann::json(propBool).dump());
}

void NoOperationsInterfaceClient::setPropBoolLocal(const std::string& args)
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

bool NoOperationsInterfaceClient::getPropBool() const
{
    return m_data.m_propBool;
}

void NoOperationsInterfaceClient::setPropInt(int propInt)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.simple/NoOperationsInterface/set/propInt");
    m_client->setRemoteProperty(topic, nlohmann::json(propInt).dump());
}

void NoOperationsInterfaceClient::setPropIntLocal(const std::string& args)
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

int NoOperationsInterfaceClient::getPropInt() const
{
    return m_data.m_propInt;
}
void NoOperationsInterfaceClient::onSigVoid(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigVoid();
}
void NoOperationsInterfaceClient::onSigBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigBool(json_args[0].get<bool>());
}

int NoOperationsInterfaceClient::registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler)
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

void NoOperationsInterfaceClient::onInvokeReply(const std::string& args, const std::string& correlationData)
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

bool NoOperationsInterfaceClient::isReady() const
{
    return m_isReady;
}

INoOperationsInterfacePublisher& NoOperationsInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
