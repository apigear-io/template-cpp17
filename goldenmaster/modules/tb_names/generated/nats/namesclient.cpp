#include "tb_names/generated/nats/namesclient.h"
#include "tb_names/generated/core/names.publisher.h"
#include "tb_names/generated/core/tb_names.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbNames;
using namespace Test::TbNames::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 2;
const uint32_t  expectedPropertiesSubscriptions = 4;
constexpr uint32_t expectedSubscriptionsCount = expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<Nam_EsClient> Nam_EsClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<Nam_EsClient> obj(new Nam_EsClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> Nam_EsClient::getSharedFromDerrived()
{
    return shared_from_this();
}

Nam_EsClient::Nam_EsClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<NamEsPublisher>())
{}

void Nam_EsClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

Nam_EsClient::~Nam_EsClient() = default;

void Nam_EsClient::onConnected()
{
    const std::string topic_Switch =  "tb.names.Nam_Es.prop.Switch";
    subscribeTopic(topic_Switch, [this](const auto& value){ setSwitchLocal(value); });
    const std::string topic_SOME_PROPERTY =  "tb.names.Nam_Es.prop.SOME_PROPERTY";
    subscribeTopic(topic_SOME_PROPERTY, [this](const auto& value){ setSomePropertyLocal(value); });
    const std::string topic_Some_Poperty2 =  "tb.names.Nam_Es.prop.Some_Poperty2";
    subscribeTopic(topic_Some_Poperty2, [this](const auto& value){ setSomePoperty2Local(value); });
    const std::string topic_enum_property =  "tb.names.Nam_Es.prop.enum_property";
    subscribeTopic(topic_enum_property, [this](const auto& value){ setEnumPropertyLocal(value); });
    const std::string topic_SOME_SIGNAL = "tb.names.Nam_Es.sig.SOME_SIGNAL";
    subscribeTopic(topic_SOME_SIGNAL, [this](const auto& args){onSomeSignal(args);});
    const std::string topic_Some_Signal2 = "tb.names.Nam_Es.sig.Some_Signal2";
    subscribeTopic(topic_Some_Signal2, [this](const auto& args){onSomeSignal2(args);});
}

void Nam_EsClient::setSwitch(bool Switch)
{
    static const auto topic = std::string("tb.names.Nam_Es.set.Switch");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(Switch).dump());
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
    static const auto topic = std::string("tb.names.Nam_Es.set.SOME_PROPERTY");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(SOME_PROPERTY).dump());
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
    static const auto topic = std::string("tb.names.Nam_Es.set.Some_Poperty2");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(Some_Poperty2).dump());
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

void Nam_EsClient::setEnumProperty(Enum_With_Under_scoresEnum enum_property)
{
    static const auto topic = std::string("tb.names.Nam_Es.set.enum_property");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(enum_property).dump());
}

void Nam_EsClient::setEnumPropertyLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    Enum_With_Under_scoresEnum enum_property = fields.get<Enum_With_Under_scoresEnum>();
    if (m_data.m_enum_property != enum_property) {
        m_data.m_enum_property = enum_property;
        m_publisher->publishEnumPropertyChanged(enum_property);
    }
}

Enum_With_Under_scoresEnum Nam_EsClient::getEnumProperty() const
{
    return m_data.m_enum_property;
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
    static const auto topic = std::string("tb.names.Nam_Es.rpc.SOME_FUNCTION");

    return std::async(std::launch::async, [this,SOME_PARAM]()
    {
        std::promise<void> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            (void) result;
            resultPromise.set_value();
        };

        m_client->request(topic,  nlohmann::json::array({SOME_PARAM}).dump(), callback);
        return resultPromise.get_future().get();
    });
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
    static const auto topic = std::string("tb.names.Nam_Es.rpc.Some_Function2");

    return std::async(std::launch::async, [this,Some_Param]()
    {
        std::promise<void> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            (void) result;
            resultPromise.set_value();
        };

        m_client->request(topic,  nlohmann::json::array({Some_Param}).dump(), callback);
        return resultPromise.get_future().get();
    });
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


INamEsPublisher& Nam_EsClient::_getPublisher() const
{
    return *m_publisher;
}
