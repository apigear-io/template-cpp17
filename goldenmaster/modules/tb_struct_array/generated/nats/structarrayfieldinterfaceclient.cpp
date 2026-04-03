#include "tb_struct_array/generated/nats/structarrayfieldinterfaceclient.h"
#include "tb_struct_array/generated/core/structarrayfieldinterface.publisher.h"
#include "tb_struct_array/generated/core/tb_struct_array.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbStructArray;
using namespace Test::TbStructArray::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 2;
const uint32_t  expectedPropertiesSubscriptions = 4;
const uint32_t  initSubscription = 1;
const uint32_t  serviceAvailableSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = serviceAvailableSubscription + initSubscription + expectedSingalsSubscriptions + expectedPropertiesSubscriptions;
}

std::shared_ptr<StructArrayFieldInterfaceClient> StructArrayFieldInterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<StructArrayFieldInterfaceClient> obj(new StructArrayFieldInterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> StructArrayFieldInterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

StructArrayFieldInterfaceClient::StructArrayFieldInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<StructArrayFieldInterfacePublisher>())
{}

void StructArrayFieldInterfaceClient::init()
{
    if (m_initialized.exchange(true)) {
        AG_LOG_WARNING("init() called more than once on " "StructArrayFieldInterfaceClient" ", ignoring");
        return;
    }
    std::weak_ptr<StructArrayFieldInterfaceClient> weak_self = shared_from_this();
    BaseAdapter::init([weak_self](){
        if (auto self = weak_self.lock()) {
            self->onConnected();
        }
    });
}

StructArrayFieldInterfaceClient::~StructArrayFieldInterfaceClient() = default;

void StructArrayFieldInterfaceClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "tb.struct.array.StructArrayFieldInterface.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("tb.struct.array.StructArrayFieldInterface.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "tb.struct.array.StructArrayFieldInterface.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
    const std::string topic_propStructArray =  "tb.struct.array.StructArrayFieldInterface.prop.propStructArray";
    subscribeTopic(topic_propStructArray, [this](const auto& value){ setPropStructArrayLocal(_to_PropStructArray(value)); });
    const std::string topic_propEnumArray =  "tb.struct.array.StructArrayFieldInterface.prop.propEnumArray";
    subscribeTopic(topic_propEnumArray, [this](const auto& value){ setPropEnumArrayLocal(_to_PropEnumArray(value)); });
    const std::string topic_propIntArray =  "tb.struct.array.StructArrayFieldInterface.prop.propIntArray";
    subscribeTopic(topic_propIntArray, [this](const auto& value){ setPropIntArrayLocal(_to_PropIntArray(value)); });
    const std::string topic_propMixed =  "tb.struct.array.StructArrayFieldInterface.prop.propMixed";
    subscribeTopic(topic_propMixed, [this](const auto& value){ setPropMixedLocal(_to_PropMixed(value)); });
    const std::string topic_sigMixed = "tb.struct.array.StructArrayFieldInterface.sig.sigMixed";
    subscribeTopic(topic_sigMixed, [this](const auto& args){onSigMixed(args);});
    const std::string topic_sigStructArray = "tb.struct.array.StructArrayFieldInterface.sig.sigStructArray";
    subscribeTopic(topic_sigStructArray, [this](const auto& args){onSigStructArray(args);});
}
void StructArrayFieldInterfaceClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "tb.struct.array.StructArrayFieldInterface.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void StructArrayFieldInterfaceClient::setPropStructArray(const StructWithArrayOfStructs& propStructArray)
{
    static const auto topic = std::string("tb.struct.array.StructArrayFieldInterface.set.propStructArray");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propStructArray).dump());
}

StructWithArrayOfStructs StructArrayFieldInterfaceClient::_to_PropStructArray(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propStructArray");
        return StructWithArrayOfStructs();
    }
   return fields.get<StructWithArrayOfStructs>();
}

void StructArrayFieldInterfaceClient::setPropStructArrayLocal(const StructWithArrayOfStructs& propStructArray)
{
    if (m_data.m_propStructArray != propStructArray) {
        m_data.m_propStructArray = propStructArray;
        m_publisher->publishPropStructArrayChanged(propStructArray);
    }
}

const StructWithArrayOfStructs& StructArrayFieldInterfaceClient::getPropStructArray() const
{
    return m_data.m_propStructArray;
}

void StructArrayFieldInterfaceClient::setPropEnumArray(const StructWithArrayOfEnums& propEnumArray)
{
    static const auto topic = std::string("tb.struct.array.StructArrayFieldInterface.set.propEnumArray");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propEnumArray).dump());
}

StructWithArrayOfEnums StructArrayFieldInterfaceClient::_to_PropEnumArray(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propEnumArray");
        return StructWithArrayOfEnums();
    }
   return fields.get<StructWithArrayOfEnums>();
}

void StructArrayFieldInterfaceClient::setPropEnumArrayLocal(const StructWithArrayOfEnums& propEnumArray)
{
    if (m_data.m_propEnumArray != propEnumArray) {
        m_data.m_propEnumArray = propEnumArray;
        m_publisher->publishPropEnumArrayChanged(propEnumArray);
    }
}

const StructWithArrayOfEnums& StructArrayFieldInterfaceClient::getPropEnumArray() const
{
    return m_data.m_propEnumArray;
}

void StructArrayFieldInterfaceClient::setPropIntArray(const StructWithArrayOfInts& propIntArray)
{
    static const auto topic = std::string("tb.struct.array.StructArrayFieldInterface.set.propIntArray");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propIntArray).dump());
}

StructWithArrayOfInts StructArrayFieldInterfaceClient::_to_PropIntArray(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propIntArray");
        return StructWithArrayOfInts();
    }
   return fields.get<StructWithArrayOfInts>();
}

void StructArrayFieldInterfaceClient::setPropIntArrayLocal(const StructWithArrayOfInts& propIntArray)
{
    if (m_data.m_propIntArray != propIntArray) {
        m_data.m_propIntArray = propIntArray;
        m_publisher->publishPropIntArrayChanged(propIntArray);
    }
}

const StructWithArrayOfInts& StructArrayFieldInterfaceClient::getPropIntArray() const
{
    return m_data.m_propIntArray;
}

void StructArrayFieldInterfaceClient::setPropMixed(const MixedStruct& propMixed)
{
    static const auto topic = std::string("tb.struct.array.StructArrayFieldInterface.set.propMixed");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(propMixed).dump());
}

MixedStruct StructArrayFieldInterfaceClient::_to_PropMixed(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property propMixed");
        return MixedStruct();
    }
   return fields.get<MixedStruct>();
}

void StructArrayFieldInterfaceClient::setPropMixedLocal(const MixedStruct& propMixed)
{
    if (m_data.m_propMixed != propMixed) {
        m_data.m_propMixed = propMixed;
        m_publisher->publishPropMixedChanged(propMixed);
    }
}

const MixedStruct& StructArrayFieldInterfaceClient::getPropMixed() const
{
    return m_data.m_propMixed;
}

void StructArrayFieldInterfaceClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
    if(fields.contains("propStructArray")) {
        setPropStructArrayLocal(fields["propStructArray"].get<StructWithArrayOfStructs>());
    }
    if(fields.contains("propEnumArray")) {
        setPropEnumArrayLocal(fields["propEnumArray"].get<StructWithArrayOfEnums>());
    }
    if(fields.contains("propIntArray")) {
        setPropIntArrayLocal(fields["propIntArray"].get<StructWithArrayOfInts>());
    }
    if(fields.contains("propMixed")) {
        setPropMixedLocal(fields["propMixed"].get<MixedStruct>());
    }
}

MixedStruct StructArrayFieldInterfaceClient::funcMixed(const MixedStruct& paramMixed)
{
    if(m_client == nullptr) {
        return MixedStruct();
    }
    MixedStruct value(funcMixedAsync(paramMixed).get());
    return value;
}

std::future<MixedStruct> StructArrayFieldInterfaceClient::funcMixedAsync(const MixedStruct& paramMixed, std::function<void(MixedStruct)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.struct.array.StructArrayFieldInterface.rpc.funcMixed");

    return std::async(std::launch::async, [this, user_callback,paramMixed]()
    {
        std::promise<MixedStruct> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(MixedStruct());
                if (user_callback)
                {
                    user_callback(MixedStruct());
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const MixedStruct value = field.get<MixedStruct>();
            resultPromise.set_value(value);
            if (user_callback)
            {
                user_callback(value);
            }
        };

        m_client->request(topic,  nlohmann::json::array({paramMixed}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

StructWithArrayOfStructs StructArrayFieldInterfaceClient::funcStructArray(const StructWithArrayOfStructs& paramPoints)
{
    if(m_client == nullptr) {
        return StructWithArrayOfStructs();
    }
    StructWithArrayOfStructs value(funcStructArrayAsync(paramPoints).get());
    return value;
}

std::future<StructWithArrayOfStructs> StructArrayFieldInterfaceClient::funcStructArrayAsync(const StructWithArrayOfStructs& paramPoints, std::function<void(StructWithArrayOfStructs)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.struct.array.StructArrayFieldInterface.rpc.funcStructArray");

    return std::async(std::launch::async, [this, user_callback,paramPoints]()
    {
        std::promise<StructWithArrayOfStructs> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(StructWithArrayOfStructs());
                if (user_callback)
                {
                    user_callback(StructWithArrayOfStructs());
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const StructWithArrayOfStructs value = field.get<StructWithArrayOfStructs>();
            resultPromise.set_value(value);
            if (user_callback)
            {
                user_callback(value);
            }
        };

        m_client->request(topic,  nlohmann::json::array({paramPoints}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void StructArrayFieldInterfaceClient::onSigMixed(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigMixed(json_args[0].get<MixedStruct>());
}
void StructArrayFieldInterfaceClient::onSigStructArray(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigStructArray(json_args[0].get<StructWithArrayOfStructs>());
}

IStructArrayFieldInterfacePublisher& StructArrayFieldInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}

