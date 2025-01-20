#include "tb_same1/generated/nats/sameenum1interfaceclient.h"
#include "tb_same1/generated/core/sameenum1interface.publisher.h"
#include "tb_same1/generated/core/tb_same1.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSame1;
using namespace Test::TbSame1::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 1;
const uint32_t  expectedPropertiesSubscriptions = 1;
const uint32_t  initSubscription = 1;
const uint32_t  serviceAvailableSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = serviceAvailableSubscription + initSubscription + expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<SameEnum1InterfaceClient> SameEnum1InterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<SameEnum1InterfaceClient> obj(new SameEnum1InterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> SameEnum1InterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

SameEnum1InterfaceClient::SameEnum1InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<SameEnum1InterfacePublisher>())
{}

void SameEnum1InterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

SameEnum1InterfaceClient::~SameEnum1InterfaceClient() = default;

void SameEnum1InterfaceClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "tb.same1.SameEnum1Interface.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("tb.same1.SameEnum1Interface.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "tb.same1.SameEnum1Interface.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
    const std::string topic_prop1 =  "tb.same1.SameEnum1Interface.prop.prop1";
    subscribeTopic(topic_prop1, [this](const auto& value){ setProp1Local(_to_Prop1(value)); });
    const std::string topic_sig1 = "tb.same1.SameEnum1Interface.sig.sig1";
    subscribeTopic(topic_sig1, [this](const auto& args){onSig1(args);});
}
void SameEnum1InterfaceClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "tb.same1.SameEnum1Interface.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void SameEnum1InterfaceClient::setProp1(Enum1Enum prop1)
{
    static const auto topic = std::string("tb.same1.SameEnum1Interface.set.prop1");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop1).dump());
}

Enum1Enum SameEnum1InterfaceClient::_to_Prop1(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property prop1");
        return Enum1Enum::value1;
    }
   return fields.get<Enum1Enum>();
}

void SameEnum1InterfaceClient::setProp1Local(Enum1Enum prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

Enum1Enum SameEnum1InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

void SameEnum1InterfaceClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
    if(fields.contains("prop1")) {
        setProp1Local(fields["prop1"].get<Enum1Enum>());
    }
}

Enum1Enum SameEnum1InterfaceClient::func1(Enum1Enum param1)
{
    if(m_client == nullptr) {
        return Enum1Enum::value1;
    }
    Enum1Enum value(func1Async(param1).get());
    return value;
}

std::future<Enum1Enum> SameEnum1InterfaceClient::func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.same1.SameEnum1Interface.rpc.func1");

    return std::async(std::launch::async, [this, user_callback,param1]()
    {
        std::promise<Enum1Enum> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(Enum1Enum::value1);
                if (user_callback)
                {
                    user_callback(Enum1Enum::value1);
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const Enum1Enum value = field.get<Enum1Enum>();
            resultPromise.set_value(value);
            if (user_callback)
            {
                user_callback(value);
            }
        };

        m_client->request(topic,  nlohmann::json::array({param1}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void SameEnum1InterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<Enum1Enum>());
}

ISameEnum1InterfacePublisher& SameEnum1InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}

