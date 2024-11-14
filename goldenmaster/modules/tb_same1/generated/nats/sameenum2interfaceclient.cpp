#include "tb_same1/generated/nats/sameenum2interfaceclient.h"
#include "tb_same1/generated/core/sameenum2interface.publisher.h"
#include "tb_same1/generated/core/tb_same1.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSame1;
using namespace Test::TbSame1::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 2;
const uint32_t  expectedPropertiesSubscriptions = 2;
constexpr uint32_t expectedSubscriptionsCount = expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<SameEnum2InterfaceClient> SameEnum2InterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<SameEnum2InterfaceClient> obj(new SameEnum2InterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> SameEnum2InterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

SameEnum2InterfaceClient::SameEnum2InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<SameEnum2InterfacePublisher>())
{}

void SameEnum2InterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

SameEnum2InterfaceClient::~SameEnum2InterfaceClient() = default;

void SameEnum2InterfaceClient::onConnected()
{
    const std::string topic_prop1 =  "tb.same1.SameEnum2Interface.prop.prop1";
    subscribeTopic(topic_prop1, [this](const auto& value){ setProp1Local(value); });
    const std::string topic_prop2 =  "tb.same1.SameEnum2Interface.prop.prop2";
    subscribeTopic(topic_prop2, [this](const auto& value){ setProp2Local(value); });
    const std::string topic_sig1 = "tb.same1.SameEnum2Interface.sig.sig1";
    subscribeTopic(topic_sig1, [this](const auto& args){onSig1(args);});
    const std::string topic_sig2 = "tb.same1.SameEnum2Interface.sig.sig2";
    subscribeTopic(topic_sig2, [this](const auto& args){onSig2(args);});
}

void SameEnum2InterfaceClient::setProp1(Enum1Enum prop1)
{
    static const auto topic = std::string("tb.same1.SameEnum2Interface.set.prop1");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop1).dump());
}

void SameEnum2InterfaceClient::setProp1Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    Enum1Enum prop1 = fields.get<Enum1Enum>();
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

Enum1Enum SameEnum2InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

void SameEnum2InterfaceClient::setProp2(Enum2Enum prop2)
{
    static const auto topic = std::string("tb.same1.SameEnum2Interface.set.prop2");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop2).dump());
}

void SameEnum2InterfaceClient::setProp2Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    Enum2Enum prop2 = fields.get<Enum2Enum>();
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

Enum2Enum SameEnum2InterfaceClient::getProp2() const
{
    return m_data.m_prop2;
}

Enum1Enum SameEnum2InterfaceClient::func1(Enum1Enum param1)
{
    if(m_client == nullptr) {
        return Enum1Enum::value1;
    }
    Enum1Enum value(func1Async(param1).get());
    return value;
}

std::future<Enum1Enum> SameEnum2InterfaceClient::func1Async(Enum1Enum param1)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.same1.SameEnum2Interface.rpc.func1");

    return std::async(std::launch::async, [this,param1]()
    {
        std::promise<Enum1Enum> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(Enum1Enum::value1);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const Enum1Enum value = field.get<Enum1Enum>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({param1}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

Enum1Enum SameEnum2InterfaceClient::func2(Enum1Enum param1, Enum2Enum param2)
{
    if(m_client == nullptr) {
        return Enum1Enum::value1;
    }
    Enum1Enum value(func2Async(param1, param2).get());
    return value;
}

std::future<Enum1Enum> SameEnum2InterfaceClient::func2Async(Enum1Enum param1, Enum2Enum param2)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.same1.SameEnum2Interface.rpc.func2");

    return std::async(std::launch::async, [this,param1,param2]()
    {
        std::promise<Enum1Enum> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(Enum1Enum::value1);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const Enum1Enum value = field.get<Enum1Enum>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({param1, param2}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void SameEnum2InterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<Enum1Enum>());
}
void SameEnum2InterfaceClient::onSig2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig2(json_args[0].get<Enum1Enum>(),json_args[1].get<Enum2Enum>());
}


ISameEnum2InterfacePublisher& SameEnum2InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
