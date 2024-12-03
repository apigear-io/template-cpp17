#include "tb_simple/generated/nats/nopropertiesinterfaceclient.h"
#include "tb_simple/generated/core/nopropertiesinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 2;
const uint32_t  initSubscription = 1;
const uint32_t  serviceAvailableSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = serviceAvailableSubscription  + initSubscription
 + expectedSingalsSubscriptions;
}

std::shared_ptr<NoPropertiesInterfaceClient> NoPropertiesInterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<NoPropertiesInterfaceClient> obj(new NoPropertiesInterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> NoPropertiesInterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

NoPropertiesInterfaceClient::NoPropertiesInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<NoPropertiesInterfacePublisher>())
{}

void NoPropertiesInterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

NoPropertiesInterfaceClient::~NoPropertiesInterfaceClient() = default;

void NoPropertiesInterfaceClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "tb.simple.NoPropertiesInterface.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("tb.simple.NoPropertiesInterface.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "tb.simple.NoPropertiesInterface.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
    const std::string topic_sigVoid = "tb.simple.NoPropertiesInterface.sig.sigVoid";
    subscribeTopic(topic_sigVoid, [this](const auto& args){onSigVoid(args);});
    const std::string topic_sigBool = "tb.simple.NoPropertiesInterface.sig.sigBool";
    subscribeTopic(topic_sigBool, [this](const auto& args){onSigBool(args);});
}
void NoPropertiesInterfaceClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "tb.simple.NoPropertiesInterface.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void NoPropertiesInterfaceClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
}

void NoPropertiesInterfaceClient::funcVoid()
{
    if(m_client == nullptr) {
        return;
    }
    funcVoidAsync();
}

std::future<void> NoPropertiesInterfaceClient::funcVoidAsync()
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.NoPropertiesInterface.rpc.funcVoid");

    return std::async(std::launch::async, [this]()
    {
        std::promise<void> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            (void) result;
            resultPromise.set_value();
        };

        m_client->request(topic,  nlohmann::json::array({}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

bool NoPropertiesInterfaceClient::funcBool(bool paramBool)
{
    if(m_client == nullptr) {
        return false;
    }
    bool value(funcBoolAsync(paramBool).get());
    return value;
}

std::future<bool> NoPropertiesInterfaceClient::funcBoolAsync(bool paramBool)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.NoPropertiesInterface.rpc.funcBool");

    return std::async(std::launch::async, [this,paramBool]()
    {
        std::promise<bool> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(false);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const bool value = field.get<bool>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramBool}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void NoPropertiesInterfaceClient::onSigVoid(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigVoid();
}
void NoPropertiesInterfaceClient::onSigBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigBool(json_args[0].get<bool>());
}

INoPropertiesInterfacePublisher& NoPropertiesInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}

