#include "testbed2/generated/nats/nestedstruct1interfaceclient.h"
#include "testbed2/generated/core/nestedstruct1interface.publisher.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::Testbed2;
using namespace Test::Testbed2::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 1;
const uint32_t  expectedPropertiesSubscriptions = 1;
const uint32_t  initSubscription = 1;
const uint32_t  serviceAvailableSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = serviceAvailableSubscription + initSubscription + expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<NestedStruct1InterfaceClient> NestedStruct1InterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<NestedStruct1InterfaceClient> obj(new NestedStruct1InterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> NestedStruct1InterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

NestedStruct1InterfaceClient::NestedStruct1InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<NestedStruct1InterfacePublisher>())
{}

void NestedStruct1InterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

NestedStruct1InterfaceClient::~NestedStruct1InterfaceClient() = default;

void NestedStruct1InterfaceClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "testbed2.NestedStruct1Interface.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("testbed2.NestedStruct1Interface.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "testbed2.NestedStruct1Interface.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
    const std::string topic_prop1 =  "testbed2.NestedStruct1Interface.prop.prop1";
    subscribeTopic(topic_prop1, [this](const auto& value){ setProp1Local(_to_Prop1(value)); });
    const std::string topic_sig1 = "testbed2.NestedStruct1Interface.sig.sig1";
    subscribeTopic(topic_sig1, [this](const auto& args){onSig1(args);});
}
void NestedStruct1InterfaceClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "testbed2.NestedStruct1Interface.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void NestedStruct1InterfaceClient::setProp1(const NestedStruct1& prop1)
{
    static const auto topic = std::string("testbed2.NestedStruct1Interface.set.prop1");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop1).dump());
}

NestedStruct1 NestedStruct1InterfaceClient::_to_Prop1(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property prop1");
        return NestedStruct1();
    }
   return fields.get<NestedStruct1>();
}

void NestedStruct1InterfaceClient::setProp1Local(const NestedStruct1& prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

const NestedStruct1& NestedStruct1InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

void NestedStruct1InterfaceClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
    if(fields.contains("prop1")) {
        setProp1Local(fields["prop1"].get<NestedStruct1>());
    }
}

NestedStruct1 NestedStruct1InterfaceClient::func1(const NestedStruct1& param1)
{
    if(m_client == nullptr) {
        return NestedStruct1();
    }
    NestedStruct1 value(func1Async(param1).get());
    return value;
}

std::future<NestedStruct1> NestedStruct1InterfaceClient::func1Async(const NestedStruct1& param1)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed2.NestedStruct1Interface.rpc.func1");

    return std::async(std::launch::async, [this,param1]()
    {
        std::promise<NestedStruct1> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(NestedStruct1());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const NestedStruct1 value = field.get<NestedStruct1>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({param1}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void NestedStruct1InterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<NestedStruct1>());
}

INestedStruct1InterfacePublisher& NestedStruct1InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}

