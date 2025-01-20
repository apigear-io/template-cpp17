#include "testbed1/generated/nats/structinterfaceclient.h"
#include "testbed1/generated/core/structinterface.publisher.h"
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

std::shared_ptr<StructInterfaceClient> StructInterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<StructInterfaceClient> obj(new StructInterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> StructInterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

StructInterfaceClient::StructInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<StructInterfacePublisher>())
{}

void StructInterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

StructInterfaceClient::~StructInterfaceClient() = default;

void StructInterfaceClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "testbed1.StructInterface.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("testbed1.StructInterface.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "testbed1.StructInterface.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
    const std::string topic_propBool =  "testbed1.StructInterface.prop.propBool";
    subscribeTopic(topic_propBool, [this](const auto& value){ setPropBoolLocal(_to_PropBool(value)); });
    const std::string topic_propInt =  "testbed1.StructInterface.prop.propInt";
    subscribeTopic(topic_propInt, [this](const auto& value){ setPropIntLocal(_to_PropInt(value)); });
    const std::string topic_propFloat =  "testbed1.StructInterface.prop.propFloat";
    subscribeTopic(topic_propFloat, [this](const auto& value){ setPropFloatLocal(_to_PropFloat(value)); });
    const std::string topic_propString =  "testbed1.StructInterface.prop.propString";
    subscribeTopic(topic_propString, [this](const auto& value){ setPropStringLocal(_to_PropString(value)); });
    const std::string topic_sigBool = "testbed1.StructInterface.sig.sigBool";
    subscribeTopic(topic_sigBool, [this](const auto& args){onSigBool(args);});
    const std::string topic_sigInt = "testbed1.StructInterface.sig.sigInt";
    subscribeTopic(topic_sigInt, [this](const auto& args){onSigInt(args);});
    const std::string topic_sigFloat = "testbed1.StructInterface.sig.sigFloat";
    subscribeTopic(topic_sigFloat, [this](const auto& args){onSigFloat(args);});
    const std::string topic_sigString = "testbed1.StructInterface.sig.sigString";
    subscribeTopic(topic_sigString, [this](const auto& args){onSigString(args);});
}
void StructInterfaceClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "testbed1.StructInterface.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void StructInterfaceClient::setPropBool(const StructBool& propBool)
{
    static const auto topic = std::string("testbed1.StructInterface.set.propBool");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propBool).dump());
}

StructBool StructInterfaceClient::_to_PropBool(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propBool");
        return StructBool();
    }
   return fields.get<StructBool>();
}

void StructInterfaceClient::setPropBoolLocal(const StructBool& propBool)
{
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

const StructBool& StructInterfaceClient::getPropBool() const
{
    return m_data.m_propBool;
}

void StructInterfaceClient::setPropInt(const StructInt& propInt)
{
    static const auto topic = std::string("testbed1.StructInterface.set.propInt");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propInt).dump());
}

StructInt StructInterfaceClient::_to_PropInt(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propInt");
        return StructInt();
    }
   return fields.get<StructInt>();
}

void StructInterfaceClient::setPropIntLocal(const StructInt& propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

const StructInt& StructInterfaceClient::getPropInt() const
{
    return m_data.m_propInt;
}

void StructInterfaceClient::setPropFloat(const StructFloat& propFloat)
{
    static const auto topic = std::string("testbed1.StructInterface.set.propFloat");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propFloat).dump());
}

StructFloat StructInterfaceClient::_to_PropFloat(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propFloat");
        return StructFloat();
    }
   return fields.get<StructFloat>();
}

void StructInterfaceClient::setPropFloatLocal(const StructFloat& propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

const StructFloat& StructInterfaceClient::getPropFloat() const
{
    return m_data.m_propFloat;
}

void StructInterfaceClient::setPropString(const StructString& propString)
{
    static const auto topic = std::string("testbed1.StructInterface.set.propString");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propString).dump());
}

StructString StructInterfaceClient::_to_PropString(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propString");
        return StructString();
    }
   return fields.get<StructString>();
}

void StructInterfaceClient::setPropStringLocal(const StructString& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const StructString& StructInterfaceClient::getPropString() const
{
    return m_data.m_propString;
}

void StructInterfaceClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
    if(fields.contains("propBool")) {
        setPropBoolLocal(fields["propBool"].get<StructBool>());
    }
    if(fields.contains("propInt")) {
        setPropIntLocal(fields["propInt"].get<StructInt>());
    }
    if(fields.contains("propFloat")) {
        setPropFloatLocal(fields["propFloat"].get<StructFloat>());
    }
    if(fields.contains("propString")) {
        setPropStringLocal(fields["propString"].get<StructString>());
    }
}

StructBool StructInterfaceClient::funcBool(const StructBool& paramBool)
{
    if(m_client == nullptr) {
        return StructBool();
    }
    StructBool value(funcBoolAsync(paramBool).get());
    return value;
}

std::future<StructBool> StructInterfaceClient::funcBoolAsync(const StructBool& paramBool, std::function<void(StructBool)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructInterface.rpc.funcBool");

    return std::async(std::launch::async, [this, user_callback,paramBool]()
    {
        std::promise<StructBool> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(StructBool());
                if (user_callback)
                {
                    user_callback(StructBool());
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const StructBool value = field.get<StructBool>();
            resultPromise.set_value(value);
            if (user_callback)
            {
                user_callback(value);
            }
        };

        m_client->request(topic,  nlohmann::json::array({paramBool}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

StructInt StructInterfaceClient::funcInt(const StructInt& paramInt)
{
    if(m_client == nullptr) {
        return StructInt();
    }
    StructInt value(funcIntAsync(paramInt).get());
    return value;
}

std::future<StructInt> StructInterfaceClient::funcIntAsync(const StructInt& paramInt, std::function<void(StructInt)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructInterface.rpc.funcInt");

    return std::async(std::launch::async, [this, user_callback,paramInt]()
    {
        std::promise<StructInt> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(StructInt());
                if (user_callback)
                {
                    user_callback(StructInt());
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const StructInt value = field.get<StructInt>();
            resultPromise.set_value(value);
            if (user_callback)
            {
                user_callback(value);
            }
        };

        m_client->request(topic,  nlohmann::json::array({paramInt}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

StructFloat StructInterfaceClient::funcFloat(const StructFloat& paramFloat)
{
    if(m_client == nullptr) {
        return StructFloat();
    }
    StructFloat value(funcFloatAsync(paramFloat).get());
    return value;
}

std::future<StructFloat> StructInterfaceClient::funcFloatAsync(const StructFloat& paramFloat, std::function<void(StructFloat)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructInterface.rpc.funcFloat");

    return std::async(std::launch::async, [this, user_callback,paramFloat]()
    {
        std::promise<StructFloat> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(StructFloat());
                if (user_callback)
                {
                    user_callback(StructFloat());
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const StructFloat value = field.get<StructFloat>();
            resultPromise.set_value(value);
            if (user_callback)
            {
                user_callback(value);
            }
        };

        m_client->request(topic,  nlohmann::json::array({paramFloat}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

StructString StructInterfaceClient::funcString(const StructString& paramString)
{
    if(m_client == nullptr) {
        return StructString();
    }
    StructString value(funcStringAsync(paramString).get());
    return value;
}

std::future<StructString> StructInterfaceClient::funcStringAsync(const StructString& paramString, std::function<void(StructString)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructInterface.rpc.funcString");

    return std::async(std::launch::async, [this, user_callback,paramString]()
    {
        std::promise<StructString> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(StructString());
                if (user_callback)
                {
                    user_callback(StructString());
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const StructString value = field.get<StructString>();
            resultPromise.set_value(value);
            if (user_callback)
            {
                user_callback(value);
            }
        };

        m_client->request(topic,  nlohmann::json::array({paramString}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void StructInterfaceClient::onSigBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigBool(json_args[0].get<StructBool>());
}
void StructInterfaceClient::onSigInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigInt(json_args[0].get<StructInt>());
}
void StructInterfaceClient::onSigFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigFloat(json_args[0].get<StructFloat>());
}
void StructInterfaceClient::onSigString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigString(json_args[0].get<StructString>());
}

IStructInterfacePublisher& StructInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}

