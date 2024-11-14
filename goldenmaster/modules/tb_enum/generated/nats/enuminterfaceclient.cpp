#include "tb_enum/generated/nats/enuminterfaceclient.h"
#include "tb_enum/generated/core/enuminterface.publisher.h"
#include "tb_enum/generated/core/tb_enum.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbEnum;
using namespace Test::TbEnum::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 4;
const uint32_t  expectedPropertiesSubscriptions = 4;
constexpr uint32_t expectedSubscriptionsCount = expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<EnumInterfaceClient> EnumInterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<EnumInterfaceClient> obj(new EnumInterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> EnumInterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

EnumInterfaceClient::EnumInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<EnumInterfacePublisher>())
{}

void EnumInterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

EnumInterfaceClient::~EnumInterfaceClient() = default;

void EnumInterfaceClient::onConnected()
{
    const std::string topic_prop0 =  "tb.enum.EnumInterface.prop.prop0";
    subscribeTopic(topic_prop0, [this](const auto& value){ setProp0Local(value); });
    const std::string topic_prop1 =  "tb.enum.EnumInterface.prop.prop1";
    subscribeTopic(topic_prop1, [this](const auto& value){ setProp1Local(value); });
    const std::string topic_prop2 =  "tb.enum.EnumInterface.prop.prop2";
    subscribeTopic(topic_prop2, [this](const auto& value){ setProp2Local(value); });
    const std::string topic_prop3 =  "tb.enum.EnumInterface.prop.prop3";
    subscribeTopic(topic_prop3, [this](const auto& value){ setProp3Local(value); });
    const std::string topic_sig0 = "tb.enum.EnumInterface.sig.sig0";
    subscribeTopic(topic_sig0, [this](const auto& args){onSig0(args);});
    const std::string topic_sig1 = "tb.enum.EnumInterface.sig.sig1";
    subscribeTopic(topic_sig1, [this](const auto& args){onSig1(args);});
    const std::string topic_sig2 = "tb.enum.EnumInterface.sig.sig2";
    subscribeTopic(topic_sig2, [this](const auto& args){onSig2(args);});
    const std::string topic_sig3 = "tb.enum.EnumInterface.sig.sig3";
    subscribeTopic(topic_sig3, [this](const auto& args){onSig3(args);});
}

void EnumInterfaceClient::setProp0(Enum0Enum prop0)
{
    static const auto topic = std::string("tb.enum.EnumInterface.set.prop0");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop0).dump());
}

void EnumInterfaceClient::setProp0Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    Enum0Enum prop0 = fields.get<Enum0Enum>();
    if (m_data.m_prop0 != prop0) {
        m_data.m_prop0 = prop0;
        m_publisher->publishProp0Changed(prop0);
    }
}

Enum0Enum EnumInterfaceClient::getProp0() const
{
    return m_data.m_prop0;
}

void EnumInterfaceClient::setProp1(Enum1Enum prop1)
{
    static const auto topic = std::string("tb.enum.EnumInterface.set.prop1");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop1).dump());
}

void EnumInterfaceClient::setProp1Local(const std::string& args)
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

Enum1Enum EnumInterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

void EnumInterfaceClient::setProp2(Enum2Enum prop2)
{
    static const auto topic = std::string("tb.enum.EnumInterface.set.prop2");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop2).dump());
}

void EnumInterfaceClient::setProp2Local(const std::string& args)
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

Enum2Enum EnumInterfaceClient::getProp2() const
{
    return m_data.m_prop2;
}

void EnumInterfaceClient::setProp3(Enum3Enum prop3)
{
    static const auto topic = std::string("tb.enum.EnumInterface.set.prop3");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(prop3).dump());
}

void EnumInterfaceClient::setProp3Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    Enum3Enum prop3 = fields.get<Enum3Enum>();
    if (m_data.m_prop3 != prop3) {
        m_data.m_prop3 = prop3;
        m_publisher->publishProp3Changed(prop3);
    }
}

Enum3Enum EnumInterfaceClient::getProp3() const
{
    return m_data.m_prop3;
}

Enum0Enum EnumInterfaceClient::func0(Enum0Enum param0)
{
    if(m_client == nullptr) {
        return Enum0Enum::value0;
    }
    Enum0Enum value(func0Async(param0).get());
    return value;
}

std::future<Enum0Enum> EnumInterfaceClient::func0Async(Enum0Enum param0)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.enum.EnumInterface.rpc.func0");

    return std::async(std::launch::async, [this,param0]()
    {
        std::promise<Enum0Enum> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(Enum0Enum::value0);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const Enum0Enum value = field.get<Enum0Enum>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({param0}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

Enum1Enum EnumInterfaceClient::func1(Enum1Enum param1)
{
    if(m_client == nullptr) {
        return Enum1Enum::value1;
    }
    Enum1Enum value(func1Async(param1).get());
    return value;
}

std::future<Enum1Enum> EnumInterfaceClient::func1Async(Enum1Enum param1)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.enum.EnumInterface.rpc.func1");

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

Enum2Enum EnumInterfaceClient::func2(Enum2Enum param2)
{
    if(m_client == nullptr) {
        return Enum2Enum::value2;
    }
    Enum2Enum value(func2Async(param2).get());
    return value;
}

std::future<Enum2Enum> EnumInterfaceClient::func2Async(Enum2Enum param2)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.enum.EnumInterface.rpc.func2");

    return std::async(std::launch::async, [this,param2]()
    {
        std::promise<Enum2Enum> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(Enum2Enum::value2);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const Enum2Enum value = field.get<Enum2Enum>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({param2}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

Enum3Enum EnumInterfaceClient::func3(Enum3Enum param3)
{
    if(m_client == nullptr) {
        return Enum3Enum::value3;
    }
    Enum3Enum value(func3Async(param3).get());
    return value;
}

std::future<Enum3Enum> EnumInterfaceClient::func3Async(Enum3Enum param3)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.enum.EnumInterface.rpc.func3");

    return std::async(std::launch::async, [this,param3]()
    {
        std::promise<Enum3Enum> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(Enum3Enum::value3);
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const Enum3Enum value = field.get<Enum3Enum>();
            resultPromise.set_value(value);
        };

        m_client->request(topic,  nlohmann::json::array({param3}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void EnumInterfaceClient::onSig0(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig0(json_args[0].get<Enum0Enum>());
}
void EnumInterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<Enum1Enum>());
}
void EnumInterfaceClient::onSig2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig2(json_args[0].get<Enum2Enum>());
}
void EnumInterfaceClient::onSig3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig3(json_args[0].get<Enum3Enum>());
}


IEnumInterfacePublisher& EnumInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
