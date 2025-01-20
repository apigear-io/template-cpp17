#include "counter/generated/nats/counterclient.h"
#include "counter/generated/core/counter.publisher.h"
#include "counter/generated/core/counter.json.adapter.h"
#include "custom_types/generated/core/custom_types.json.adapter.h"
#include "extern_types/generated/core/extern_types.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::Counter;
using namespace Test::Counter::Nats;

namespace{
const uint32_t  expectedPropertiesSubscriptions = 2;
const uint32_t  initSubscription = 1;
const uint32_t  serviceAvailableSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = serviceAvailableSubscription  + initSubscription + expectedPropertiesSubscriptions;
}

std::shared_ptr<CounterClient> CounterClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<CounterClient> obj(new CounterClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> CounterClient::getSharedFromDerrived()
{
    return shared_from_this();
}

CounterClient::CounterClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<CounterPublisher>())
{}

void CounterClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

CounterClient::~CounterClient() = default;

void CounterClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "counter.Counter.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("counter.Counter.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "counter.Counter.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
    const std::string topic_vector =  "counter.Counter.prop.vector";
    subscribeTopic(topic_vector, [this](const auto& value){ setVectorLocal(_to_Vector(value)); });
    const std::string topic_extern_vector =  "counter.Counter.prop.extern_vector";
    subscribeTopic(topic_extern_vector, [this](const auto& value){ setExternVectorLocal(_to_ExternVector(value)); });
}
void CounterClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "counter.Counter.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void CounterClient::setVector(const Test::CustomTypes::Vector3D& vector)
{
    static const auto topic = std::string("counter.Counter.set.vector");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(vector).dump());
}

Test::CustomTypes::Vector3D CounterClient::_to_Vector(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property vector");
        return Test::CustomTypes::Vector3D();
    }
   return fields.get<Test::CustomTypes::Vector3D>();
}

void CounterClient::setVectorLocal(const Test::CustomTypes::Vector3D& vector)
{
    if (m_data.m_vector != vector) {
        m_data.m_vector = vector;
        m_publisher->publishVectorChanged(vector);
    }
}

const Test::CustomTypes::Vector3D& CounterClient::getVector() const
{
    return m_data.m_vector;
}

void CounterClient::setExternVector(const Eigen::Vector3f& extern_vector)
{
    static const auto topic = std::string("counter.Counter.set.extern_vector");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json(extern_vector).dump());
}

Eigen::Vector3f CounterClient::_to_ExternVector(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property extern_vector");
        return Eigen::Vector3f(0,0,0);
    }
   return fields.get<Eigen::Vector3f>();
}

void CounterClient::setExternVectorLocal(const Eigen::Vector3f& extern_vector)
{
    if (m_data.m_extern_vector != extern_vector) {
        m_data.m_extern_vector = extern_vector;
        m_publisher->publishExternVectorChanged(extern_vector);
    }
}

const Eigen::Vector3f& CounterClient::getExternVector() const
{
    return m_data.m_extern_vector;
}

void CounterClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
    if(fields.contains("vector")) {
        setVectorLocal(fields["vector"].get<Test::CustomTypes::Vector3D>());
    }
    if(fields.contains("extern_vector")) {
        setExternVectorLocal(fields["extern_vector"].get<Eigen::Vector3f>());
    }
}

Eigen::Vector3f CounterClient::increment(const Eigen::Vector3f& vec)
{
    if(m_client == nullptr) {
        return Eigen::Vector3f(0,0,0);
    }
    Eigen::Vector3f value(incrementAsync(vec).get());
    return value;
}

std::future<Eigen::Vector3f> CounterClient::incrementAsync(const Eigen::Vector3f& vec, std::function<void(Eigen::Vector3f)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("counter.Counter.rpc.increment");

    return std::async(std::launch::async, [this, user_callback,vec]()
    {
        std::promise<Eigen::Vector3f> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(Eigen::Vector3f(0,0,0));
                if (user_callback)
                {
                    user_callback(Eigen::Vector3f(0,0,0));
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const Eigen::Vector3f value = field.get<Eigen::Vector3f>();
            resultPromise.set_value(value);
            if (user_callback)
            {
                user_callback(value);
            }
        };

        m_client->request(topic,  nlohmann::json::array({vec}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

Test::CustomTypes::Vector3D CounterClient::decrement(const Test::CustomTypes::Vector3D& vec)
{
    if(m_client == nullptr) {
        return Test::CustomTypes::Vector3D();
    }
    Test::CustomTypes::Vector3D value(decrementAsync(vec).get());
    return value;
}

std::future<Test::CustomTypes::Vector3D> CounterClient::decrementAsync(const Test::CustomTypes::Vector3D& vec, std::function<void(Test::CustomTypes::Vector3D)> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("counter.Counter.rpc.decrement");

    return std::async(std::launch::async, [this, user_callback,vec]()
    {
        std::promise<Test::CustomTypes::Vector3D> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            if (result.empty())
            {
                resultPromise.set_value(Test::CustomTypes::Vector3D());
                if (user_callback)
                {
                    user_callback(Test::CustomTypes::Vector3D());
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const Test::CustomTypes::Vector3D value = field.get<Test::CustomTypes::Vector3D>();
            resultPromise.set_value(value);
            if (user_callback)
            {
                user_callback(value);
            }
        };

        m_client->request(topic,  nlohmann::json::array({vec}).dump(), callback);
        return resultPromise.get_future().get();
    });
}

ICounterPublisher& CounterClient::_getPublisher() const
{
    return *m_publisher;
}

