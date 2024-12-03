#include "testbed1/generated/nats/structarrayinterfaceclient.h"
#include "testbed1/generated/core/structarrayinterface.publisher.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::Testbed1;
using namespace Test::Testbed1::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 4;
const uint32_t  expectedPropertiesSubscriptions = 4;
const uint32_t  initSubscription = 1;
const uint32_t  serviceAvailableSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = serviceAvailableSubscription + initSubscription + expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<StructArrayInterfaceClient> StructArrayInterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<StructArrayInterfaceClient> obj(new StructArrayInterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> StructArrayInterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

StructArrayInterfaceClient::StructArrayInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<StructArrayInterfacePublisher>())
{}

void StructArrayInterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

StructArrayInterfaceClient::~StructArrayInterfaceClient() = default;

void StructArrayInterfaceClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "testbed1.StructArrayInterface.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("testbed1.StructArrayInterface.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "testbed1.StructArrayInterface.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
    const std::string topic_propBool =  "testbed1.StructArrayInterface.prop.propBool";
    subscribeTopic(topic_propBool, [this](const auto& value){ setPropBoolLocal(_to_PropBool(value)); });
    const std::string topic_propInt =  "testbed1.StructArrayInterface.prop.propInt";
    subscribeTopic(topic_propInt, [this](const auto& value){ setPropIntLocal(_to_PropInt(value)); });
    const std::string topic_propFloat =  "testbed1.StructArrayInterface.prop.propFloat";
    subscribeTopic(topic_propFloat, [this](const auto& value){ setPropFloatLocal(_to_PropFloat(value)); });
    const std::string topic_propString =  "testbed1.StructArrayInterface.prop.propString";
    subscribeTopic(topic_propString, [this](const auto& value){ setPropStringLocal(_to_PropString(value)); });
    const std::string topic_sigBool = "testbed1.StructArrayInterface.sig.sigBool";
    subscribeTopic(topic_sigBool, [this](const auto& args){onSigBool(args);});
    const std::string topic_sigInt = "testbed1.StructArrayInterface.sig.sigInt";
    subscribeTopic(topic_sigInt, [this](const auto& args){onSigInt(args);});
    const std::string topic_sigFloat = "testbed1.StructArrayInterface.sig.sigFloat";
    subscribeTopic(topic_sigFloat, [this](const auto& args){onSigFloat(args);});
    const std::string topic_sigString = "testbed1.StructArrayInterface.sig.sigString";
    subscribeTopic(topic_sigString, [this](const auto& args){onSigString(args);});
}
void StructArrayInterfaceClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "testbed1.StructArrayInterface.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void StructArrayInterfaceClient::setPropBool(const std::list<StructBool>& propBool)
{
    static const auto topic = std::string("testbed1.StructArrayInterface.set.propBool");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propBool).dump());
}

std::list<StructBool> StructArrayInterfaceClient::_to_PropBool(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propBool");
        return std::list<StructBool>();
    }
   return fields.get<std::list<StructBool>>();
}

void StructArrayInterfaceClient::setPropBoolLocal(const std::list<StructBool>& propBool)
{
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

const std::list<StructBool>& StructArrayInterfaceClient::getPropBool() const
{
    return m_data.m_propBool;
}

void StructArrayInterfaceClient::setPropInt(const std::list<StructInt>& propInt)
{
    static const auto topic = std::string("testbed1.StructArrayInterface.set.propInt");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propInt).dump());
}

std::list<StructInt> StructArrayInterfaceClient::_to_PropInt(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propInt");
        return std::list<StructInt>();
    }
   return fields.get<std::list<StructInt>>();
}

void StructArrayInterfaceClient::setPropIntLocal(const std::list<StructInt>& propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

const std::list<StructInt>& StructArrayInterfaceClient::getPropInt() const
{
    return m_data.m_propInt;
}

void StructArrayInterfaceClient::setPropFloat(const std::list<StructFloat>& propFloat)
{
    static const auto topic = std::string("testbed1.StructArrayInterface.set.propFloat");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propFloat).dump());
}

std::list<StructFloat> StructArrayInterfaceClient::_to_PropFloat(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propFloat");
        return std::list<StructFloat>();
    }
   return fields.get<std::list<StructFloat>>();
}

void StructArrayInterfaceClient::setPropFloatLocal(const std::list<StructFloat>& propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

const std::list<StructFloat>& StructArrayInterfaceClient::getPropFloat() const
{
    return m_data.m_propFloat;
}

void StructArrayInterfaceClient::setPropString(const std::list<StructString>& propString)
{
    static const auto topic = std::string("testbed1.StructArrayInterface.set.propString");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propString).dump());
}

std::list<StructString> StructArrayInterfaceClient::_to_PropString(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propString");
        return std::list<StructString>();
    }
   return fields.get<std::list<StructString>>();
}

void StructArrayInterfaceClient::setPropStringLocal(const std::list<StructString>& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::list<StructString>& StructArrayInterfaceClient::getPropString() const
{
    return m_data.m_propString;
}

void StructArrayInterfaceClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
    if(fields.contains("propBool")) {
        setPropBoolLocal(fields["propBool"].get<std::list<StructBool>>());
    }
    if(fields.contains("propInt")) {
        setPropIntLocal(fields["propInt"].get<std::list<StructInt>>());
    }
    if(fields.contains("propFloat")) {
        setPropFloatLocal(fields["propFloat"].get<std::list<StructFloat>>());
    }
    if(fields.contains("propString")) {
        setPropStringLocal(fields["propString"].get<std::list<StructString>>());
    }
}

std::list<StructBool> StructArrayInterfaceClient::funcBool(const std::list<StructBool>& paramBool)
{
    if(m_client == nullptr) {
        return std::list<StructBool>();
    }
    std::list<StructBool> value(funcBoolAsync(paramBool).get());
    return value;
}

std::future<std::list<StructBool>> StructArrayInterfaceClient::funcBoolAsync(const std::list<StructBool>& paramBool)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructArrayInterface.rpc.funcBool");

    return std::async(std::launch::async, [this,paramBool]()
    {
        std::promise<std::list<StructBool>> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<StructBool>());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<StructBool> value = field.get<std::list<StructBool>>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramBool}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

std::list<StructInt> StructArrayInterfaceClient::funcInt(const std::list<StructInt>& paramInt)
{
    if(m_client == nullptr) {
        return std::list<StructInt>();
    }
    std::list<StructInt> value(funcIntAsync(paramInt).get());
    return value;
}

std::future<std::list<StructInt>> StructArrayInterfaceClient::funcIntAsync(const std::list<StructInt>& paramInt)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructArrayInterface.rpc.funcInt");

    return std::async(std::launch::async, [this,paramInt]()
    {
        std::promise<std::list<StructInt>> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<StructInt>());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<StructInt> value = field.get<std::list<StructInt>>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramInt}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

std::list<StructFloat> StructArrayInterfaceClient::funcFloat(const std::list<StructFloat>& paramFloat)
{
    if(m_client == nullptr) {
        return std::list<StructFloat>();
    }
    std::list<StructFloat> value(funcFloatAsync(paramFloat).get());
    return value;
}

std::future<std::list<StructFloat>> StructArrayInterfaceClient::funcFloatAsync(const std::list<StructFloat>& paramFloat)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructArrayInterface.rpc.funcFloat");

    return std::async(std::launch::async, [this,paramFloat]()
    {
        std::promise<std::list<StructFloat>> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<StructFloat>());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<StructFloat> value = field.get<std::list<StructFloat>>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramFloat}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

std::list<StructString> StructArrayInterfaceClient::funcString(const std::list<StructString>& paramString)
{
    if(m_client == nullptr) {
        return std::list<StructString>();
    }
    std::list<StructString> value(funcStringAsync(paramString).get());
    return value;
}

std::future<std::list<StructString>> StructArrayInterfaceClient::funcStringAsync(const std::list<StructString>& paramString)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructArrayInterface.rpc.funcString");

    return std::async(std::launch::async, [this,paramString]()
    {
        std::promise<std::list<StructString>> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<StructString>());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<StructString> value = field.get<std::list<StructString>>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramString}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void StructArrayInterfaceClient::onSigBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigBool(json_args[0].get<std::list<StructBool>>());
}
void StructArrayInterfaceClient::onSigInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigInt(json_args[0].get<std::list<StructInt>>());
}
void StructArrayInterfaceClient::onSigFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigFloat(json_args[0].get<std::list<StructFloat>>());
}
void StructArrayInterfaceClient::onSigString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigString(json_args[0].get<std::list<StructString>>());
}

IStructArrayInterfacePublisher& StructArrayInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}

