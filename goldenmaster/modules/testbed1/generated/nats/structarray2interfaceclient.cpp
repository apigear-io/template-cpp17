#include "testbed1/generated/nats/structarray2interfaceclient.h"
#include "testbed1/generated/core/structarray2interface.publisher.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::Testbed1;
using namespace Test::Testbed1::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 4;
const uint32_t  expectedPropertiesSubscriptions = 5;
const uint32_t  initSubscription = 1;
const uint32_t  serviceAvailableSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = serviceAvailableSubscription + initSubscription + expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<StructArray2InterfaceClient> StructArray2InterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<StructArray2InterfaceClient> obj(new StructArray2InterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> StructArray2InterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

StructArray2InterfaceClient::StructArray2InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<StructArray2InterfacePublisher>())
{}

void StructArray2InterfaceClient::init()
{
    if (m_initialized.exchange(true)) {
        AG_LOG_WARNING("init() called more than once on " "StructArray2InterfaceClient" ", ignoring");
        return;
    }
    BaseAdapter::init([this](){onConnected();});
}

StructArray2InterfaceClient::~StructArray2InterfaceClient() = default;

void StructArray2InterfaceClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "testbed1.StructArray2Interface.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("testbed1.StructArray2Interface.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "testbed1.StructArray2Interface.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
    const std::string topic_propBool =  "testbed1.StructArray2Interface.prop.propBool";
    subscribeTopic(topic_propBool, [this](const auto& value){ setPropBoolLocal(_to_PropBool(value)); });
    const std::string topic_propInt =  "testbed1.StructArray2Interface.prop.propInt";
    subscribeTopic(topic_propInt, [this](const auto& value){ setPropIntLocal(_to_PropInt(value)); });
    const std::string topic_propFloat =  "testbed1.StructArray2Interface.prop.propFloat";
    subscribeTopic(topic_propFloat, [this](const auto& value){ setPropFloatLocal(_to_PropFloat(value)); });
    const std::string topic_propString =  "testbed1.StructArray2Interface.prop.propString";
    subscribeTopic(topic_propString, [this](const auto& value){ setPropStringLocal(_to_PropString(value)); });
    const std::string topic_propEnum =  "testbed1.StructArray2Interface.prop.propEnum";
    subscribeTopic(topic_propEnum, [this](const auto& value){ setPropEnumLocal(_to_PropEnum(value)); });
    const std::string topic_sigBool = "testbed1.StructArray2Interface.sig.sigBool";
    subscribeTopic(topic_sigBool, [this](const auto& args){onSigBool(args);});
    const std::string topic_sigInt = "testbed1.StructArray2Interface.sig.sigInt";
    subscribeTopic(topic_sigInt, [this](const auto& args){onSigInt(args);});
    const std::string topic_sigFloat = "testbed1.StructArray2Interface.sig.sigFloat";
    subscribeTopic(topic_sigFloat, [this](const auto& args){onSigFloat(args);});
    const std::string topic_sigString = "testbed1.StructArray2Interface.sig.sigString";
    subscribeTopic(topic_sigString, [this](const auto& args){onSigString(args);});
}
void StructArray2InterfaceClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "testbed1.StructArray2Interface.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void StructArray2InterfaceClient::setPropBool(const StructBoolWithArray& propBool)
{
    static const auto topic = std::string("testbed1.StructArray2Interface.set.propBool");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propBool).dump());
}

StructBoolWithArray StructArray2InterfaceClient::_to_PropBool(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propBool");
        return StructBoolWithArray();
    }
   return fields.get<StructBoolWithArray>();
}

void StructArray2InterfaceClient::setPropBoolLocal(const StructBoolWithArray& propBool)
{
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

const StructBoolWithArray& StructArray2InterfaceClient::getPropBool() const
{
    return m_data.m_propBool;
}

void StructArray2InterfaceClient::setPropInt(const StructIntWithArray& propInt)
{
    static const auto topic = std::string("testbed1.StructArray2Interface.set.propInt");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propInt).dump());
}

StructIntWithArray StructArray2InterfaceClient::_to_PropInt(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propInt");
        return StructIntWithArray();
    }
   return fields.get<StructIntWithArray>();
}

void StructArray2InterfaceClient::setPropIntLocal(const StructIntWithArray& propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

const StructIntWithArray& StructArray2InterfaceClient::getPropInt() const
{
    return m_data.m_propInt;
}

void StructArray2InterfaceClient::setPropFloat(const StructFloatWithArray& propFloat)
{
    static const auto topic = std::string("testbed1.StructArray2Interface.set.propFloat");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propFloat).dump());
}

StructFloatWithArray StructArray2InterfaceClient::_to_PropFloat(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propFloat");
        return StructFloatWithArray();
    }
   return fields.get<StructFloatWithArray>();
}

void StructArray2InterfaceClient::setPropFloatLocal(const StructFloatWithArray& propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

const StructFloatWithArray& StructArray2InterfaceClient::getPropFloat() const
{
    return m_data.m_propFloat;
}

void StructArray2InterfaceClient::setPropString(const StructStringWithArray& propString)
{
    static const auto topic = std::string("testbed1.StructArray2Interface.set.propString");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propString).dump());
}

StructStringWithArray StructArray2InterfaceClient::_to_PropString(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propString");
        return StructStringWithArray();
    }
   return fields.get<StructStringWithArray>();
}

void StructArray2InterfaceClient::setPropStringLocal(const StructStringWithArray& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const StructStringWithArray& StructArray2InterfaceClient::getPropString() const
{
    return m_data.m_propString;
}

void StructArray2InterfaceClient::setPropEnum(const StructEnumWithArray& propEnum)
{
    static const auto topic = std::string("testbed1.StructArray2Interface.set.propEnum");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propEnum).dump());
}

StructEnumWithArray StructArray2InterfaceClient::_to_PropEnum(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propEnum");
        return StructEnumWithArray();
    }
   return fields.get<StructEnumWithArray>();
}

void StructArray2InterfaceClient::setPropEnumLocal(const StructEnumWithArray& propEnum)
{
    if (m_data.m_propEnum != propEnum) {
        m_data.m_propEnum = propEnum;
        m_publisher->publishPropEnumChanged(propEnum);
    }
}

const StructEnumWithArray& StructArray2InterfaceClient::getPropEnum() const
{
    return m_data.m_propEnum;
}

void StructArray2InterfaceClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
    if(fields.contains("propBool")) {
        setPropBoolLocal(fields["propBool"].get<StructBoolWithArray>());
    }
    if(fields.contains("propInt")) {
        setPropIntLocal(fields["propInt"].get<StructIntWithArray>());
    }
    if(fields.contains("propFloat")) {
        setPropFloatLocal(fields["propFloat"].get<StructFloatWithArray>());
    }
    if(fields.contains("propString")) {
        setPropStringLocal(fields["propString"].get<StructStringWithArray>());
    }
    if(fields.contains("propEnum")) {
        setPropEnumLocal(fields["propEnum"].get<StructEnumWithArray>());
    }
}

std::list<StructBool> StructArray2InterfaceClient::funcBool(const StructBoolWithArray& paramBool)
{
    if(m_client == nullptr) {
        return std::list<StructBool>();
    }
    std::list<StructBool> value(funcBoolAsync(paramBool).get());
    return value;
}

std::future<std::list<StructBool>> StructArray2InterfaceClient::funcBoolAsync(const StructBoolWithArray& paramBool, std::function<void(std::list<StructBool>)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructArray2Interface.rpc.funcBool");

    return std::async(std::launch::async, [this, user_callback,paramBool]()
    {
        std::promise<std::list<StructBool>> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<StructBool>());
                if (user_callback)
                {
                    user_callback(std::list<StructBool>());
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<StructBool> value = field.get<std::list<StructBool>>();
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

std::list<StructInt> StructArray2InterfaceClient::funcInt(const StructIntWithArray& paramInt)
{
    if(m_client == nullptr) {
        return std::list<StructInt>();
    }
    std::list<StructInt> value(funcIntAsync(paramInt).get());
    return value;
}

std::future<std::list<StructInt>> StructArray2InterfaceClient::funcIntAsync(const StructIntWithArray& paramInt, std::function<void(std::list<StructInt>)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructArray2Interface.rpc.funcInt");

    return std::async(std::launch::async, [this, user_callback,paramInt]()
    {
        std::promise<std::list<StructInt>> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<StructInt>());
                if (user_callback)
                {
                    user_callback(std::list<StructInt>());
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<StructInt> value = field.get<std::list<StructInt>>();
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

std::list<StructFloat> StructArray2InterfaceClient::funcFloat(const StructFloatWithArray& paramFloat)
{
    if(m_client == nullptr) {
        return std::list<StructFloat>();
    }
    std::list<StructFloat> value(funcFloatAsync(paramFloat).get());
    return value;
}

std::future<std::list<StructFloat>> StructArray2InterfaceClient::funcFloatAsync(const StructFloatWithArray& paramFloat, std::function<void(std::list<StructFloat>)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructArray2Interface.rpc.funcFloat");

    return std::async(std::launch::async, [this, user_callback,paramFloat]()
    {
        std::promise<std::list<StructFloat>> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<StructFloat>());
                if (user_callback)
                {
                    user_callback(std::list<StructFloat>());
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<StructFloat> value = field.get<std::list<StructFloat>>();
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

std::list<StructString> StructArray2InterfaceClient::funcString(const StructStringWithArray& paramString)
{
    if(m_client == nullptr) {
        return std::list<StructString>();
    }
    std::list<StructString> value(funcStringAsync(paramString).get());
    return value;
}

std::future<std::list<StructString>> StructArray2InterfaceClient::funcStringAsync(const StructStringWithArray& paramString, std::function<void(std::list<StructString>)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructArray2Interface.rpc.funcString");

    return std::async(std::launch::async, [this, user_callback,paramString]()
    {
        std::promise<std::list<StructString>> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<StructString>());
                if (user_callback)
                {
                    user_callback(std::list<StructString>());
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<StructString> value = field.get<std::list<StructString>>();
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

std::list<Enum0Enum> StructArray2InterfaceClient::funcEnum(const StructEnumWithArray& paramEnum)
{
    if(m_client == nullptr) {
        return std::list<Enum0Enum>();
    }
    std::list<Enum0Enum> value(funcEnumAsync(paramEnum).get());
    return value;
}

std::future<std::list<Enum0Enum>> StructArray2InterfaceClient::funcEnumAsync(const StructEnumWithArray& paramEnum, std::function<void(std::list<Enum0Enum>)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructArray2Interface.rpc.funcEnum");

    return std::async(std::launch::async, [this, user_callback,paramEnum]()
    {
        std::promise<std::list<Enum0Enum>> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(std::list<Enum0Enum>());
                if (user_callback)
                {
                    user_callback(std::list<Enum0Enum>());
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const std::list<Enum0Enum> value = field.get<std::list<Enum0Enum>>();
            resultPromise.set_value(value);
            if (user_callback)
            {
                user_callback(value);
            }
        };

        m_client->request(topic,  nlohmann::json::array({paramEnum}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void StructArray2InterfaceClient::onSigBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigBool(json_args[0].get<StructBoolWithArray>());
}
void StructArray2InterfaceClient::onSigInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigInt(json_args[0].get<StructIntWithArray>());
}
void StructArray2InterfaceClient::onSigFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigFloat(json_args[0].get<StructFloatWithArray>());
}
void StructArray2InterfaceClient::onSigString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigString(json_args[0].get<StructStringWithArray>());
}

IStructArray2InterfacePublisher& StructArray2InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}

