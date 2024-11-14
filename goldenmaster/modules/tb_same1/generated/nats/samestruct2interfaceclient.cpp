#include "tb_same1/generated/nats/samestruct2interfaceclient.h"
#include "tb_same1/generated/core/samestruct2interface.publisher.h"
#include "tb_same1/generated/core/tb_same1.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSame1;
using namespace Test::TbSame1::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 2;
const uint32_t  expectedPropertiesSubscriptions = 2;
constexpr uint32_t expectedSubscriptionsCount = expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<SameStruct2InterfaceClient> SameStruct2InterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<SameStruct2InterfaceClient> obj(new SameStruct2InterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> SameStruct2InterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

SameStruct2InterfaceClient::SameStruct2InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<SameStruct2InterfacePublisher>())
{}

void SameStruct2InterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

SameStruct2InterfaceClient::~SameStruct2InterfaceClient() = default;

void SameStruct2InterfaceClient::onConnected()
{
    const std::string topic_prop1 =  "tb.same1.SameStruct2Interface.prop.prop1";
    subscribeTopic(topic_prop1, [this](const auto& value){ setProp1Local(value); });
    const std::string topic_prop2 =  "tb.same1.SameStruct2Interface.prop.prop2";
    subscribeTopic(topic_prop2, [this](const auto& value){ setProp2Local(value); });
    const std::string topic_sig1 = "tb.same1.SameStruct2Interface.sig.sig1";
    subscribeTopic(topic_sig1, [this](const auto& args){onSig1(args);});
    const std::string topic_sig2 = "tb.same1.SameStruct2Interface.sig.sig2";
    subscribeTopic(topic_sig2, [this](const auto& args){onSig2(args);});
}

void SameStruct2InterfaceClient::setProp1(const Struct2& prop1)
{
    static const auto topic = std::string("tb.same1.SameStruct2Interface.set.prop1");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop1).dump());
}

void SameStruct2InterfaceClient::setProp1Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const Struct2& prop1 = fields.get<Struct2>();
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

const Struct2& SameStruct2InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

void SameStruct2InterfaceClient::setProp2(const Struct2& prop2)
{
    static const auto topic = std::string("tb.same1.SameStruct2Interface.set.prop2");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop2).dump());
}

void SameStruct2InterfaceClient::setProp2Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const Struct2& prop2 = fields.get<Struct2>();
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

const Struct2& SameStruct2InterfaceClient::getProp2() const
{
    return m_data.m_prop2;
}

Struct1 SameStruct2InterfaceClient::func1(const Struct1& param1)
{
    if(m_client == nullptr) {
        return Struct1();
    }
    Struct1 value(func1Async(param1).get());
    return value;
}

std::future<Struct1> SameStruct2InterfaceClient::func1Async(const Struct1& param1)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.same1.SameStruct2Interface.rpc.func1");

    return std::async(std::launch::async, [this,param1]()
    {
        std::promise<Struct1> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(Struct1());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const Struct1 value = field.get<Struct1>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({param1}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

Struct1 SameStruct2InterfaceClient::func2(const Struct1& param1, const Struct2& param2)
{
    if(m_client == nullptr) {
        return Struct1();
    }
    Struct1 value(func2Async(param1, param2).get());
    return value;
}

std::future<Struct1> SameStruct2InterfaceClient::func2Async(const Struct1& param1, const Struct2& param2)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.same1.SameStruct2Interface.rpc.func2");

    return std::async(std::launch::async, [this,param1,param2]()
    {
        std::promise<Struct1> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(Struct1());
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const Struct1 value = field.get<Struct1>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({param1, param2}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void SameStruct2InterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<Struct1>());
}
void SameStruct2InterfaceClient::onSig2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig2(json_args[0].get<Struct1>(),json_args[1].get<Struct2>());
}


ISameStruct2InterfacePublisher& SameStruct2InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
