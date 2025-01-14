#include "tb_names/generated/mqtt/namesclient.h"
#include "tb_names/generated/core/names.publisher.h"
#include "tb_names/generated/core/tb_names.json.adapter.h"
#include <random>

using namespace Test::TbNames;
using namespace Test::TbNames::MQTT;

namespace {
    std::mt19937 randomNumberGenerator (std::random_device{}());
}

Nam_EsClient::Nam_EsClient(std::shared_ptr<ApiGear::MQTT::Client> client)
    : m_isReady(false)
    , m_client(client)
    , m_publisher(std::make_unique<NamEsPublisher>())
    , m_topics(createTopicMap(m_client->getClientId()))
{
    m_connectionStatusRegistrationID = m_client->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

Nam_EsClient::~Nam_EsClient()
{
    for (const auto& topic: m_topics)
    {
        m_client->unsubscribeTopic(topic. first);
    }
    m_client->unsubscribeToConnectionStatus(m_connectionStatusRegistrationID);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> Nam_EsClient::createTopicMap(const std::string& clientId)
{
    return {
        { std::string("tb.names/Nam_Es/prop/Switch"), [this](const std::string& args, const std::string&, const std::string&){ this->setSwitchLocal(args); } },
        { std::string("tb.names/Nam_Es/prop/SOME_PROPERTY"), [this](const std::string& args, const std::string&, const std::string&){ this->setSomePropertyLocal(args); } },
        { std::string("tb.names/Nam_Es/prop/Some_Poperty2"), [this](const std::string& args, const std::string&, const std::string&){ this->setSomePoperty2Local(args); } },
        { std::string("tb.names/Nam_Es/sig/SOME_SIGNAL"), [this](const std::string& args, const std::string&, const std::string&){ this->onSomeSignal(args); } },
        { std::string("tb.names/Nam_Es/sig/Some_Signal2"), [this](const std::string& args, const std::string&, const std::string&){ this->onSomeSignal2(args); } },
        { std::string("tb.names/Nam_Es/rpc/SOME_FUNCTION/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("tb.names/Nam_Es/rpc/Some_Function2/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
    };
};

void Nam_EsClient::onConnectionStatusChanged(bool connectionStatus)
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

void Nam_EsClient::setSwitch(bool Switch)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.names/Nam_Es/set/Switch");
    m_client->setRemoteProperty(topic, nlohmann::json(Switch).dump());
}

void Nam_EsClient::setSwitchLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    bool Switch = fields.get<bool>();
    if (m_data.m_Switch != Switch) {
        m_data.m_Switch = Switch;
        m_publisher->publishSwitchChanged(Switch);
    }
}

bool Nam_EsClient::getSwitch() const
{
    return m_data.m_Switch;
}

void Nam_EsClient::setSomeProperty(int SOME_PROPERTY)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.names/Nam_Es/set/SOME_PROPERTY");
    m_client->setRemoteProperty(topic, nlohmann::json(SOME_PROPERTY).dump());
}

void Nam_EsClient::setSomePropertyLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    int SOME_PROPERTY = fields.get<int>();
    if (m_data.m_SOME_PROPERTY != SOME_PROPERTY) {
        m_data.m_SOME_PROPERTY = SOME_PROPERTY;
        m_publisher->publishSomePropertyChanged(SOME_PROPERTY);
    }
}

int Nam_EsClient::getSomeProperty() const
{
    return m_data.m_SOME_PROPERTY;
}

void Nam_EsClient::setSomePoperty2(int Some_Poperty2)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.names/Nam_Es/set/Some_Poperty2");
    m_client->setRemoteProperty(topic, nlohmann::json(Some_Poperty2).dump());
}

void Nam_EsClient::setSomePoperty2Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    int Some_Poperty2 = fields.get<int>();
    if (m_data.m_Some_Poperty2 != Some_Poperty2) {
        m_data.m_Some_Poperty2 = Some_Poperty2;
        m_publisher->publishSomePoperty2Changed(Some_Poperty2);
    }
}

int Nam_EsClient::getSomePoperty2() const
{
    return m_data.m_Some_Poperty2;
}

void Nam_EsClient::sOME_FUNCTION(bool SOME_PARAM)
{
    if(m_client == nullptr) {
        return;
    }
    sOME_FUNCTIONAsync(SOME_PARAM);
}

std::future<void> Nam_EsClient::sOME_FUNCTIONAsync(bool SOME_PARAM)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    SOME_PARAM]()
        {
            std::promise<void> resultPromise;
            static const auto topic = std::string("tb.names/Nam_Es/rpc/SOME_FUNCTION");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                (void) arg;
                resultPromise.set_value();
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({SOME_PARAM}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}

void Nam_EsClient::some_Function2(bool Some_Param)
{
    if(m_client == nullptr) {
        return;
    }
    some_Function2Async(Some_Param);
}

std::future<void> Nam_EsClient::some_Function2Async(bool Some_Param)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    Some_Param]()
        {
            std::promise<void> resultPromise;
            static const auto topic = std::string("tb.names/Nam_Es/rpc/Some_Function2");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                (void) arg;
                resultPromise.set_value();
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({Some_Param}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}
void Nam_EsClient::onSomeSignal(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSomeSignal(json_args[0].get<bool>());
}
void Nam_EsClient::onSomeSignal2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSomeSignal2(json_args[0].get<bool>());
}

int Nam_EsClient::registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler)
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

void Nam_EsClient::onInvokeReply(const std::string& args, const std::string& correlationData)
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

bool Nam_EsClient::isReady() const
{
    return m_isReady;
}

INamEsPublisher& Nam_EsClient::_getPublisher() const
{
    return *m_publisher;
}
