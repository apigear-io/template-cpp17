#include "testbed2/generated/nats/manyparaminterfaceclient.h"
#include "testbed2/generated/core/manyparaminterface.publisher.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::Testbed2;
using namespace Test::Testbed2::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 4;
const uint32_t  expectedPropertiesSubscriptions = 4;
const uint32_t  initSubscription = 1;
const uint32_t  serviceAvailableSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = serviceAvailableSubscription  + initSubscription
 + expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<ManyParamInterfaceClient> ManyParamInterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<ManyParamInterfaceClient> obj(new ManyParamInterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> ManyParamInterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

ManyParamInterfaceClient::ManyParamInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<ManyParamInterfacePublisher>())
{}

void ManyParamInterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

ManyParamInterfaceClient::~ManyParamInterfaceClient() = default;

void ManyParamInterfaceClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "testbed2.ManyParamInterface.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("testbed2.ManyParamInterface.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "testbed2.ManyParamInterface.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
    const std::string topic_prop1 =  "testbed2.ManyParamInterface.prop.prop1";
    subscribeTopic(topic_prop1, [this](const auto& value){ setProp1Local(_to_Prop1(value)); });
    const std::string topic_prop2 =  "testbed2.ManyParamInterface.prop.prop2";
    subscribeTopic(topic_prop2, [this](const auto& value){ setProp2Local(_to_Prop2(value)); });
    const std::string topic_prop3 =  "testbed2.ManyParamInterface.prop.prop3";
    subscribeTopic(topic_prop3, [this](const auto& value){ setProp3Local(_to_Prop3(value)); });
    const std::string topic_prop4 =  "testbed2.ManyParamInterface.prop.prop4";
    subscribeTopic(topic_prop4, [this](const auto& value){ setProp4Local(_to_Prop4(value)); });
    const std::string topic_sig1 = "testbed2.ManyParamInterface.sig.sig1";
    subscribeTopic(topic_sig1, [this](const auto& args){onSig1(args);});
    const std::string topic_sig2 = "testbed2.ManyParamInterface.sig.sig2";
    subscribeTopic(topic_sig2, [this](const auto& args){onSig2(args);});
    const std::string topic_sig3 = "testbed2.ManyParamInterface.sig.sig3";
    subscribeTopic(topic_sig3, [this](const auto& args){onSig3(args);});
    const std::string topic_sig4 = "testbed2.ManyParamInterface.sig.sig4";
    subscribeTopic(topic_sig4, [this](const auto& args){onSig4(args);});
}
void ManyParamInterfaceClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "testbed2.ManyParamInterface.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void ManyParamInterfaceClient::setProp1(int prop1)
{
    static const auto topic = std::string("testbed2.ManyParamInterface.set.prop1");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop1).dump());
}

int ManyParamInterfaceClient::_to_Prop1(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property prop1");
        return 0;
    }
   return fields.get<int>();
}

void ManyParamInterfaceClient::setProp1Local(int prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

int ManyParamInterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

void ManyParamInterfaceClient::setProp2(int prop2)
{
    static const auto topic = std::string("testbed2.ManyParamInterface.set.prop2");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop2).dump());
}

int ManyParamInterfaceClient::_to_Prop2(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property prop2");
        return 0;
    }
   return fields.get<int>();
}

void ManyParamInterfaceClient::setProp2Local(int prop2)
{
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

int ManyParamInterfaceClient::getProp2() const
{
    return m_data.m_prop2;
}

void ManyParamInterfaceClient::setProp3(int prop3)
{
    static const auto topic = std::string("testbed2.ManyParamInterface.set.prop3");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop3).dump());
}

int ManyParamInterfaceClient::_to_Prop3(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property prop3");
        return 0;
    }
   return fields.get<int>();
}

void ManyParamInterfaceClient::setProp3Local(int prop3)
{
    if (m_data.m_prop3 != prop3) {
        m_data.m_prop3 = prop3;
        m_publisher->publishProp3Changed(prop3);
    }
}

int ManyParamInterfaceClient::getProp3() const
{
    return m_data.m_prop3;
}

void ManyParamInterfaceClient::setProp4(int prop4)
{
    static const auto topic = std::string("testbed2.ManyParamInterface.set.prop4");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop4).dump());
}

int ManyParamInterfaceClient::_to_Prop4(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property prop4");
        return 0;
    }
   return fields.get<int>();
}

void ManyParamInterfaceClient::setProp4Local(int prop4)
{
    if (m_data.m_prop4 != prop4) {
        m_data.m_prop4 = prop4;
        m_publisher->publishProp4Changed(prop4);
    }
}

int ManyParamInterfaceClient::getProp4() const
{
    return m_data.m_prop4;
}

void ManyParamInterfaceClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
    if(fields.contains("prop1")) {
        setProp1Local(fields["prop1"].get<int>());
    }
    if(fields.contains("prop2")) {
        setProp2Local(fields["prop2"].get<int>());
    }
    if(fields.contains("prop3")) {
        setProp3Local(fields["prop3"].get<int>());
    }
    if(fields.contains("prop4")) {
        setProp4Local(fields["prop4"].get<int>());
    }
}

int ManyParamInterfaceClient::func1(int param1)
{
    if(m_client == nullptr) {
        return 0;
    }
    int value(func1Async(param1).get());
    return value;
}

std::future<int> ManyParamInterfaceClient::func1Async(int param1)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed2.ManyParamInterface.rpc.func1");

    return std::async(std::launch::async, [this,param1]()
    {
        std::promise<int> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(0);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const int value = field.get<int>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({param1}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

int ManyParamInterfaceClient::func2(int param1, int param2)
{
    if(m_client == nullptr) {
        return 0;
    }
    int value(func2Async(param1, param2).get());
    return value;
}

std::future<int> ManyParamInterfaceClient::func2Async(int param1, int param2)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed2.ManyParamInterface.rpc.func2");

    return std::async(std::launch::async, [this,param1,param2]()
    {
        std::promise<int> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(0);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const int value = field.get<int>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({param1, param2}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

int ManyParamInterfaceClient::func3(int param1, int param2, int param3)
{
    if(m_client == nullptr) {
        return 0;
    }
    int value(func3Async(param1, param2, param3).get());
    return value;
}

std::future<int> ManyParamInterfaceClient::func3Async(int param1, int param2, int param3)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed2.ManyParamInterface.rpc.func3");

    return std::async(std::launch::async, [this,param1,param2,param3]()
    {
        std::promise<int> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(0);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const int value = field.get<int>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({param1, param2, param3}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

int ManyParamInterfaceClient::func4(int param1, int param2, int param3, int param4)
{
    if(m_client == nullptr) {
        return 0;
    }
    int value(func4Async(param1, param2, param3, param4).get());
    return value;
}

std::future<int> ManyParamInterfaceClient::func4Async(int param1, int param2, int param3, int param4)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("testbed2.ManyParamInterface.rpc.func4");

    return std::async(std::launch::async, [this,param1,param2,param3,param4]()
    {
        std::promise<int> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(0);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const int value = field.get<int>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({param1, param2, param3, param4}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void ManyParamInterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<int>());
}
void ManyParamInterfaceClient::onSig2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig2(json_args[0].get<int>(),json_args[1].get<int>());
}
void ManyParamInterfaceClient::onSig3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig3(json_args[0].get<int>(),json_args[1].get<int>(),json_args[2].get<int>());
}
void ManyParamInterfaceClient::onSig4(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig4(json_args[0].get<int>(),json_args[1].get<int>(),json_args[2].get<int>(),json_args[3].get<int>());
}

IManyParamInterfacePublisher& ManyParamInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}

