#include "testbed1/generated/nats/structarrayinterfaceclient.h"
#include "testbed1/generated/core/structarrayinterface.publisher.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::Testbed1;
using namespace Test::Testbed1::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 4;
const uint32_t  expectedPropertiesSubscriptions = 4;
constexpr uint32_t expectedSubscriptionsCount = expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
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
    const std::string topic_propBool =  "testbed1.StructArrayInterface.prop.propBool";
    subscribeTopic(topic_propBool, [this](const auto& value){ setPropBoolLocal(value); });
    const std::string topic_propInt =  "testbed1.StructArrayInterface.prop.propInt";
    subscribeTopic(topic_propInt, [this](const auto& value){ setPropIntLocal(value); });
    const std::string topic_propFloat =  "testbed1.StructArrayInterface.prop.propFloat";
    subscribeTopic(topic_propFloat, [this](const auto& value){ setPropFloatLocal(value); });
    const std::string topic_propString =  "testbed1.StructArrayInterface.prop.propString";
    subscribeTopic(topic_propString, [this](const auto& value){ setPropStringLocal(value); });
    const std::string topic_sigBool = "testbed1.StructArrayInterface.sig.sigBool";
    subscribeTopic(topic_sigBool, [this](const auto& args){onSigBool(args);});
    const std::string topic_sigInt = "testbed1.StructArrayInterface.sig.sigInt";
    subscribeTopic(topic_sigInt, [this](const auto& args){onSigInt(args);});
    const std::string topic_sigFloat = "testbed1.StructArrayInterface.sig.sigFloat";
    subscribeTopic(topic_sigFloat, [this](const auto& args){onSigFloat(args);});
    const std::string topic_sigString = "testbed1.StructArrayInterface.sig.sigString";
    subscribeTopic(topic_sigString, [this](const auto& args){onSigString(args);});
}

void StructArrayInterfaceClient::setPropBool(const std::list<StructBool>& propBool)
{
    static const auto topic = std::string("testbed1.StructArrayInterface.set.propBool");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propBool).dump());
}

void StructArrayInterfaceClient::setPropBoolLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<StructBool>& propBool = fields.get<std::list<StructBool>>();
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

void StructArrayInterfaceClient::setPropIntLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<StructInt>& propInt = fields.get<std::list<StructInt>>();
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

void StructArrayInterfaceClient::setPropFloatLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<StructFloat>& propFloat = fields.get<std::list<StructFloat>>();
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

void StructArrayInterfaceClient::setPropStringLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<StructString>& propString = fields.get<std::list<StructString>>();
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::list<StructString>& StructArrayInterfaceClient::getPropString() const
{
    return m_data.m_propString;
}

StructBool StructArrayInterfaceClient::funcBool(const std::list<StructBool>& paramBool)
{
    if(m_client == nullptr) {
        return StructBool();
    }
    StructBool value(funcBoolAsync(paramBool).get());
    return value;
}

std::future<StructBool> StructArrayInterfaceClient::funcBoolAsync(const std::list<StructBool>& paramBool)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructArrayInterface.rpc.funcBool");

    return std::async(std::launch::async, [this,paramBool]()
    {
        std::promise<StructBool> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(StructBool());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const StructBool value = field.get<StructBool>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramBool}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

StructBool StructArrayInterfaceClient::funcInt(const std::list<StructInt>& paramInt)
{
    if(m_client == nullptr) {
        return StructBool();
    }
    StructBool value(funcIntAsync(paramInt).get());
    return value;
}

std::future<StructBool> StructArrayInterfaceClient::funcIntAsync(const std::list<StructInt>& paramInt)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructArrayInterface.rpc.funcInt");

    return std::async(std::launch::async, [this,paramInt]()
    {
        std::promise<StructBool> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(StructBool());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const StructBool value = field.get<StructBool>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramInt}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

StructBool StructArrayInterfaceClient::funcFloat(const std::list<StructFloat>& paramFloat)
{
    if(m_client == nullptr) {
        return StructBool();
    }
    StructBool value(funcFloatAsync(paramFloat).get());
    return value;
}

std::future<StructBool> StructArrayInterfaceClient::funcFloatAsync(const std::list<StructFloat>& paramFloat)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructArrayInterface.rpc.funcFloat");

    return std::async(std::launch::async, [this,paramFloat]()
    {
        std::promise<StructBool> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(StructBool());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const StructBool value = field.get<StructBool>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({paramFloat}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

StructBool StructArrayInterfaceClient::funcString(const std::list<StructString>& paramString)
{
    if(m_client == nullptr) {
        return StructBool();
    }
    StructBool value(funcStringAsync(paramString).get());
    return value;
}

std::future<StructBool> StructArrayInterfaceClient::funcStringAsync(const std::list<StructString>& paramString)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed1.StructArrayInterface.rpc.funcString");

    return std::async(std::launch::async, [this,paramString]()
    {
        std::promise<StructBool> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(StructBool());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const StructBool value = field.get<StructBool>();
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
