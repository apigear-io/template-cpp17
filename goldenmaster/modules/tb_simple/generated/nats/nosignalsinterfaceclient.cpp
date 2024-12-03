#include "tb_simple/generated/nats/nosignalsinterfaceclient.h"
#include "tb_simple/generated/core/nosignalsinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedPropertiesSubscriptions = 2;
const uint32_t  initSubscription = 1;
const uint32_t  serviceAvailableSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = serviceAvailableSubscription  + initSubscription + expectedPropertiesSubscriptions;
}

std::shared_ptr<NoSignalsInterfaceClient> NoSignalsInterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<NoSignalsInterfaceClient> obj(new NoSignalsInterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> NoSignalsInterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

NoSignalsInterfaceClient::NoSignalsInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<NoSignalsInterfacePublisher>())
{}

void NoSignalsInterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

NoSignalsInterfaceClient::~NoSignalsInterfaceClient() = default;

void NoSignalsInterfaceClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "tb.simple.NoSignalsInterface.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("tb.simple.NoSignalsInterface.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "tb.simple.NoSignalsInterface.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
    const std::string topic_propBool =  "tb.simple.NoSignalsInterface.prop.propBool";
    subscribeTopic(topic_propBool, [this](const auto& value){ setPropBoolLocal(_to_PropBool(value)); });
    const std::string topic_propInt =  "tb.simple.NoSignalsInterface.prop.propInt";
    subscribeTopic(topic_propInt, [this](const auto& value){ setPropIntLocal(_to_PropInt(value)); });
}
void NoSignalsInterfaceClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "tb.simple.NoSignalsInterface.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void NoSignalsInterfaceClient::setPropBool(bool propBool)
{
    static const auto topic = std::string("tb.simple.NoSignalsInterface.set.propBool");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propBool).dump());
}

bool NoSignalsInterfaceClient::_to_PropBool(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propBool");
        return false;
    }
   return fields.get<bool>();
}

void NoSignalsInterfaceClient::setPropBoolLocal(bool propBool)
{
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

bool NoSignalsInterfaceClient::getPropBool() const
{
    return m_data.m_propBool;
}

void NoSignalsInterfaceClient::setPropInt(int propInt)
{
    static const auto topic = std::string("tb.simple.NoSignalsInterface.set.propInt");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propInt).dump());
}

int NoSignalsInterfaceClient::_to_PropInt(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propInt");
        return 0;
    }
   return fields.get<int>();
}

void NoSignalsInterfaceClient::setPropIntLocal(int propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

int NoSignalsInterfaceClient::getPropInt() const
{
    return m_data.m_propInt;
}

void NoSignalsInterfaceClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
    if(fields.contains("propBool")) {
        setPropBoolLocal(fields["propBool"].get<bool>());
    }
    if(fields.contains("propInt")) {
        setPropIntLocal(fields["propInt"].get<int>());
    }
}

void NoSignalsInterfaceClient::funcVoid()
{
    if(m_client == nullptr) {
        return;
    }
    funcVoidAsync();
}

std::future<void> NoSignalsInterfaceClient::funcVoidAsync()
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.NoSignalsInterface.rpc.funcVoid");

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

bool NoSignalsInterfaceClient::funcBool(bool paramBool)
{
    if(m_client == nullptr) {
        return false;
    }
    bool value(funcBoolAsync(paramBool).get());
    return value;
}

std::future<bool> NoSignalsInterfaceClient::funcBoolAsync(bool paramBool)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.NoSignalsInterface.rpc.funcBool");

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

INoSignalsInterfacePublisher& NoSignalsInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}

