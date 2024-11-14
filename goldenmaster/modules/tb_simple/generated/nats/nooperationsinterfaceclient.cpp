#include "tb_simple/generated/nats/nooperationsinterfaceclient.h"
#include "tb_simple/generated/core/nooperationsinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 2;
const uint32_t  expectedPropertiesSubscriptions = 2;
constexpr uint32_t expectedSubscriptionsCount = expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
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
    const std::string topic_propBool =  "tb.simple.NoOperationsInterface.prop.propBool";
    subscribeTopic(topic_propBool, [this](const auto& value){ setPropBoolLocal(value); });
    const std::string topic_propInt =  "tb.simple.NoOperationsInterface.prop.propInt";
    subscribeTopic(topic_propInt, [this](const auto& value){ setPropIntLocal(value); });
    const std::string topic_sigVoid = "tb.simple.NoOperationsInterface.sig.sigVoid";
    subscribeTopic(topic_sigVoid, [this](const auto& args){onSigVoid(args);});
    const std::string topic_sigBool = "tb.simple.NoOperationsInterface.sig.sigBool";
    subscribeTopic(topic_sigBool, [this](const auto& args){onSigBool(args);});
}

void NoOperationsInterfaceClient::setPropBool(bool propBool)
{
    static const auto topic = std::string("tb.simple.NoOperationsInterface.set.propBool");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propBool).dump());
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
    static const auto topic = std::string("tb.simple.NoOperationsInterface.set.propInt");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propInt).dump());
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


INoOperationsInterfacePublisher& NoOperationsInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
