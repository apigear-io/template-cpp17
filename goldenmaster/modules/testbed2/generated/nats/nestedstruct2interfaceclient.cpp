#include "testbed2/generated/nats/nestedstruct2interfaceclient.h"
#include "testbed2/generated/core/nestedstruct2interface.publisher.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::Testbed2;
using namespace Test::Testbed2::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 2;
const uint32_t  expectedPropertiesSubscriptions = 2;
const uint32_t  initSubscription = 1;
const uint32_t  serviceAvailableSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = serviceAvailableSubscription + initSubscription + expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<NestedStruct2InterfaceClient> NestedStruct2InterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<NestedStruct2InterfaceClient> obj(new NestedStruct2InterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> NestedStruct2InterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

NestedStruct2InterfaceClient::NestedStruct2InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<NestedStruct2InterfacePublisher>())
{}

void NestedStruct2InterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

NestedStruct2InterfaceClient::~NestedStruct2InterfaceClient() = default;

void NestedStruct2InterfaceClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "testbed2.NestedStruct2Interface.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("testbed2.NestedStruct2Interface.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "testbed2.NestedStruct2Interface.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
    const std::string topic_prop1 =  "testbed2.NestedStruct2Interface.prop.prop1";
    subscribeTopic(topic_prop1, [this](const auto& value){ setProp1Local(_to_Prop1(value)); });
    const std::string topic_prop2 =  "testbed2.NestedStruct2Interface.prop.prop2";
    subscribeTopic(topic_prop2, [this](const auto& value){ setProp2Local(_to_Prop2(value)); });
    const std::string topic_sig1 = "testbed2.NestedStruct2Interface.sig.sig1";
    subscribeTopic(topic_sig1, [this](const auto& args){onSig1(args);});
    const std::string topic_sig2 = "testbed2.NestedStruct2Interface.sig.sig2";
    subscribeTopic(topic_sig2, [this](const auto& args){onSig2(args);});
}
void NestedStruct2InterfaceClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "testbed2.NestedStruct2Interface.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void NestedStruct2InterfaceClient::setProp1(const NestedStruct1& prop1)
{
    static const auto topic = std::string("testbed2.NestedStruct2Interface.set.prop1");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop1).dump());
}

NestedStruct1 NestedStruct2InterfaceClient::_to_Prop1(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property prop1");
        return NestedStruct1();
    }
   return fields.get<NestedStruct1>();
}

void NestedStruct2InterfaceClient::setProp1Local(const NestedStruct1& prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

const NestedStruct1& NestedStruct2InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

void NestedStruct2InterfaceClient::setProp2(const NestedStruct2& prop2)
{
    static const auto topic = std::string("testbed2.NestedStruct2Interface.set.prop2");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop2).dump());
}

NestedStruct2 NestedStruct2InterfaceClient::_to_Prop2(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property prop2");
        return NestedStruct2();
    }
   return fields.get<NestedStruct2>();
}

void NestedStruct2InterfaceClient::setProp2Local(const NestedStruct2& prop2)
{
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

const NestedStruct2& NestedStruct2InterfaceClient::getProp2() const
{
    return m_data.m_prop2;
}

void NestedStruct2InterfaceClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
    if(fields.contains("prop1")) {
        setProp1Local(fields["prop1"].get<NestedStruct1>());
    }
    if(fields.contains("prop2")) {
        setProp2Local(fields["prop2"].get<NestedStruct2>());
    }
}

NestedStruct1 NestedStruct2InterfaceClient::func1(const NestedStruct1& param1)
{
    if(m_client == nullptr) {
        return NestedStruct1();
    }
    NestedStruct1 value(func1Async(param1).get());
    return value;
}

std::future<NestedStruct1> NestedStruct2InterfaceClient::func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed2.NestedStruct2Interface.rpc.func1");

    return std::async(std::launch::async, [this, user_callback,param1]()
    {
        std::promise<NestedStruct1> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(NestedStruct1());
                if (user_callback)
                {
                    user_callback(NestedStruct1());
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const NestedStruct1 value = field.get<NestedStruct1>();
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

NestedStruct1 NestedStruct2InterfaceClient::func2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    if(m_client == nullptr) {
        return NestedStruct1();
    }
    NestedStruct1 value(func2Async(param1, param2).get());
    return value;
}

std::future<NestedStruct1> NestedStruct2InterfaceClient::func2Async(const NestedStruct1& param1, const NestedStruct2& param2, std::function<void(NestedStruct1)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed2.NestedStruct2Interface.rpc.func2");

    return std::async(std::launch::async, [this, user_callback,param1,param2]()
    {
        std::promise<NestedStruct1> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(NestedStruct1());
                if (user_callback)
                {
                    user_callback(NestedStruct1());
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const NestedStruct1 value = field.get<NestedStruct1>();
            resultPromise.set_value(value);
            if (user_callback)
            {
                user_callback(value);
            }
        };

        m_client->request(topic,  nlohmann::json::array({param1, param2}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void NestedStruct2InterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<NestedStruct1>());
}
void NestedStruct2InterfaceClient::onSig2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig2(json_args[0].get<NestedStruct1>(),json_args[1].get<NestedStruct2>());
}

INestedStruct2InterfacePublisher& NestedStruct2InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}

