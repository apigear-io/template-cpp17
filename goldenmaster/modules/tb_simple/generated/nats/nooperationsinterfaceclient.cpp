#include "tb_simple/generated/nats/nooperationsinterfaceclient.h"
#include "tb_simple/generated/core/nooperationsinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 2;
const uint32_t  expectedPropertiesSubscriptions = 2;
const uint32_t  initSubscription = 1;
const uint32_t  serviceAvailableSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = serviceAvailableSubscription  + initSubscription
 + expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<NoOperationsInterfaceClient> NoOperationsInterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<NoOperationsInterfaceClient> obj(new NoOperationsInterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> NoOperationsInterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

NoOperationsInterfaceClient::NoOperationsInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<NoOperationsInterfacePublisher>())
{}

void NoOperationsInterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

NoOperationsInterfaceClient::~NoOperationsInterfaceClient() = default;

void NoOperationsInterfaceClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "tb.simple.NoOperationsInterface.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("tb.simple.NoOperationsInterface.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "tb.simple.NoOperationsInterface.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
    const std::string topic_propBool =  "tb.simple.NoOperationsInterface.prop.propBool";
    subscribeTopic(topic_propBool, [this](const auto& value){ setPropBoolLocal(_to_PropBool(value)); });
    const std::string topic_propInt =  "tb.simple.NoOperationsInterface.prop.propInt";
    subscribeTopic(topic_propInt, [this](const auto& value){ setPropIntLocal(_to_PropInt(value)); });
    const std::string topic_sigVoid = "tb.simple.NoOperationsInterface.sig.sigVoid";
    subscribeTopic(topic_sigVoid, [this](const auto& args){onSigVoid(args);});
    const std::string topic_sigBool = "tb.simple.NoOperationsInterface.sig.sigBool";
    subscribeTopic(topic_sigBool, [this](const auto& args){onSigBool(args);});
}
void NoOperationsInterfaceClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "tb.simple.NoOperationsInterface.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void NoOperationsInterfaceClient::setPropBool(bool propBool)
{
    static const auto topic = std::string("tb.simple.NoOperationsInterface.set.propBool");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propBool).dump());
}

bool NoOperationsInterfaceClient::_to_PropBool(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propBool");
        return false;
    }
   return fields.get<bool>();
}

void NoOperationsInterfaceClient::setPropBoolLocal(bool propBool)
{
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
    static const auto topic = std::string("tb.simple.NoOperationsInterface.set.propInt");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propInt).dump());
}

int NoOperationsInterfaceClient::_to_PropInt(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propInt");
        return 0;
    }
   return fields.get<int>();
}

void NoOperationsInterfaceClient::setPropIntLocal(int propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

int NoOperationsInterfaceClient::getPropInt() const
{
    return m_data.m_propInt;
}

void NoOperationsInterfaceClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
    if(fields.contains("propBool")) {
        setPropBoolLocal(fields["propBool"].get<bool>());
    }
    if(fields.contains("propInt")) {
        setPropIntLocal(fields["propInt"].get<int>());
    }
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

INoOperationsInterfacePublisher& NoOperationsInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}

