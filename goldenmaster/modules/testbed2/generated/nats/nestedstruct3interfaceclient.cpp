#include "testbed2/generated/nats/nestedstruct3interfaceclient.h"
#include "testbed2/generated/core/nestedstruct3interface.publisher.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::Testbed2;
using namespace Test::Testbed2::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 3;
const uint32_t  expectedPropertiesSubscriptions = 3;
const uint32_t  initSubscription = 1;
const uint32_t  serviceAvailableSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = serviceAvailableSubscription + initSubscription + expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<NestedStruct3InterfaceClient> NestedStruct3InterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<NestedStruct3InterfaceClient> obj(new NestedStruct3InterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> NestedStruct3InterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

NestedStruct3InterfaceClient::NestedStruct3InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<NestedStruct3InterfacePublisher>())
{}

void NestedStruct3InterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

NestedStruct3InterfaceClient::~NestedStruct3InterfaceClient() = default;

void NestedStruct3InterfaceClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "testbed2.NestedStruct3Interface.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("testbed2.NestedStruct3Interface.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "testbed2.NestedStruct3Interface.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
    const std::string topic_prop1 =  "testbed2.NestedStruct3Interface.prop.prop1";
    subscribeTopic(topic_prop1, [this](const auto& value){ setProp1Local(_to_Prop1(value)); });
    const std::string topic_prop2 =  "testbed2.NestedStruct3Interface.prop.prop2";
    subscribeTopic(topic_prop2, [this](const auto& value){ setProp2Local(_to_Prop2(value)); });
    const std::string topic_prop3 =  "testbed2.NestedStruct3Interface.prop.prop3";
    subscribeTopic(topic_prop3, [this](const auto& value){ setProp3Local(_to_Prop3(value)); });
    const std::string topic_sig1 = "testbed2.NestedStruct3Interface.sig.sig1";
    subscribeTopic(topic_sig1, [this](const auto& args){onSig1(args);});
    const std::string topic_sig2 = "testbed2.NestedStruct3Interface.sig.sig2";
    subscribeTopic(topic_sig2, [this](const auto& args){onSig2(args);});
    const std::string topic_sig3 = "testbed2.NestedStruct3Interface.sig.sig3";
    subscribeTopic(topic_sig3, [this](const auto& args){onSig3(args);});
}
void NestedStruct3InterfaceClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "testbed2.NestedStruct3Interface.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void NestedStruct3InterfaceClient::setProp1(const NestedStruct1& prop1)
{
    static const auto topic = std::string("testbed2.NestedStruct3Interface.set.prop1");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop1).dump());
}

NestedStruct1 NestedStruct3InterfaceClient::_to_Prop1(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property prop1");
        return NestedStruct1();
    }
   return fields.get<NestedStruct1>();
}

void NestedStruct3InterfaceClient::setProp1Local(const NestedStruct1& prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

const NestedStruct1& NestedStruct3InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

void NestedStruct3InterfaceClient::setProp2(const NestedStruct2& prop2)
{
    static const auto topic = std::string("testbed2.NestedStruct3Interface.set.prop2");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop2).dump());
}

NestedStruct2 NestedStruct3InterfaceClient::_to_Prop2(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property prop2");
        return NestedStruct2();
    }
   return fields.get<NestedStruct2>();
}

void NestedStruct3InterfaceClient::setProp2Local(const NestedStruct2& prop2)
{
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

const NestedStruct2& NestedStruct3InterfaceClient::getProp2() const
{
    return m_data.m_prop2;
}

void NestedStruct3InterfaceClient::setProp3(const NestedStruct3& prop3)
{
    static const auto topic = std::string("testbed2.NestedStruct3Interface.set.prop3");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop3).dump());
}

NestedStruct3 NestedStruct3InterfaceClient::_to_Prop3(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property prop3");
        return NestedStruct3();
    }
   return fields.get<NestedStruct3>();
}

void NestedStruct3InterfaceClient::setProp3Local(const NestedStruct3& prop3)
{
    if (m_data.m_prop3 != prop3) {
        m_data.m_prop3 = prop3;
        m_publisher->publishProp3Changed(prop3);
    }
}

const NestedStruct3& NestedStruct3InterfaceClient::getProp3() const
{
    return m_data.m_prop3;
}

void NestedStruct3InterfaceClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
    if(fields.contains("prop1")) {
        setProp1Local(fields["prop1"].get<NestedStruct1>());
    }
    if(fields.contains("prop2")) {
        setProp2Local(fields["prop2"].get<NestedStruct2>());
    }
    if(fields.contains("prop3")) {
        setProp3Local(fields["prop3"].get<NestedStruct3>());
    }
}

NestedStruct1 NestedStruct3InterfaceClient::func1(const NestedStruct1& param1)
{
    if(m_client == nullptr) {
        return NestedStruct1();
    }
    NestedStruct1 value(func1Async(param1).get());
    return value;
}

std::future<NestedStruct1> NestedStruct3InterfaceClient::func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed2.NestedStruct3Interface.rpc.func1");

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

NestedStruct1 NestedStruct3InterfaceClient::func2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    if(m_client == nullptr) {
        return NestedStruct1();
    }
    NestedStruct1 value(func2Async(param1, param2).get());
    return value;
}

std::future<NestedStruct1> NestedStruct3InterfaceClient::func2Async(const NestedStruct1& param1, const NestedStruct2& param2, std::function<void(NestedStruct1)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed2.NestedStruct3Interface.rpc.func2");

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

NestedStruct1 NestedStruct3InterfaceClient::func3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3)
{
    if(m_client == nullptr) {
        return NestedStruct1();
    }
    NestedStruct1 value(func3Async(param1, param2, param3).get());
    return value;
}

std::future<NestedStruct1> NestedStruct3InterfaceClient::func3Async(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3, std::function<void(NestedStruct1)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed2.NestedStruct3Interface.rpc.func3");

    return std::async(std::launch::async, [this, user_callback,param1,param2,param3]()
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

        m_client->request(topic,  nlohmann::json::array({param1, param2, param3}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void NestedStruct3InterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<NestedStruct1>());
}
void NestedStruct3InterfaceClient::onSig2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig2(json_args[0].get<NestedStruct1>(),json_args[1].get<NestedStruct2>());
}
void NestedStruct3InterfaceClient::onSig3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig3(json_args[0].get<NestedStruct1>(),json_args[1].get<NestedStruct2>(),json_args[2].get<NestedStruct3>());
}

INestedStruct3InterfacePublisher& NestedStruct3InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}

