#include "counter/generated/mqtt/counterclient.h"
#include "counter/generated/core/counter.publisher.h"
#include "counter/generated/core/counter.json.adapter.h"
#include "custom_types/generated/core/custom_types.json.adapter.h"
#include "extern_types/generated/core/extern_types.json.adapter.h"
#include <random>

using namespace Test::Counter;
using namespace Test::Counter::MQTT;

namespace {
    std::mt19937 randomNumberGenerator (std::random_device{}());
}

CounterClient::CounterClient(std::shared_ptr<ApiGear::MQTT::Client> client)
    : m_isReady(false)
    , m_client(client)
    , m_publisher(std::make_unique<CounterPublisher>())
    , m_topics(createTopicMap(m_client->getClientId()))
{
    m_connectionStatusRegistrationID = m_client->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

CounterClient::~CounterClient()
{
    for (const auto& topic: m_topics)
    {
        m_client->unsubscribeTopic(topic. first);
    }
    m_client->unsubscribeToConnectionStatus(m_connectionStatusRegistrationID);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> CounterClient::createTopicMap(const std::string& clientId)
{
    return {
        { std::string("counter/Counter/prop/vector"), [this](const std::string& args, const std::string&, const std::string&){ this->setVectorLocal(args); } },
        { std::string("counter/Counter/prop/extern_vector"), [this](const std::string& args, const std::string&, const std::string&){ this->setExternVectorLocal(args); } },
        { std::string("counter/Counter/prop/vectorArray"), [this](const std::string& args, const std::string&, const std::string&){ this->setVectorArrayLocal(args); } },
        { std::string("counter/Counter/prop/extern_vectorArray"), [this](const std::string& args, const std::string&, const std::string&){ this->setExternVectorArrayLocal(args); } },
        { std::string("counter/Counter/sig/valueChanged"), [this](const std::string& args, const std::string&, const std::string&){ this->onValueChanged(args); } },
        { std::string("counter/Counter/rpc/increment/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("counter/Counter/rpc/incrementArray/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("counter/Counter/rpc/decrement/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("counter/Counter/rpc/decrementArray/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
    };
};

void CounterClient::onConnectionStatusChanged(bool connectionStatus)
{
    m_isReady = connectionStatus;
    if(!connectionStatus)
    {
        return;
    }

    for (const auto& topic: m_topics)
    {
        m_client->subscribeTopic(topic. first, topic.second);
    }
}

void CounterClient::setVector(const Test::CustomTypes::Vector3D& vector)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("counter/Counter/set/vector");
    m_client->setRemoteProperty(topic, nlohmann::json(vector).dump());
}

void CounterClient::setVectorLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const Test::CustomTypes::Vector3D& vector = fields.get<Test::CustomTypes::Vector3D>();
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
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("counter/Counter/set/extern_vector");
    m_client->setRemoteProperty(topic, nlohmann::json(extern_vector).dump());
}

void CounterClient::setExternVectorLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const Eigen::Vector3f& extern_vector = fields.get<Eigen::Vector3f>();
    if (m_data.m_extern_vector != extern_vector) {
        m_data.m_extern_vector = extern_vector;
        m_publisher->publishExternVectorChanged(extern_vector);
    }
}

const Eigen::Vector3f& CounterClient::getExternVector() const
{
    return m_data.m_extern_vector;
}

void CounterClient::setVectorArray(const std::list<Test::CustomTypes::Vector3D>& vectorArray)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("counter/Counter/set/vectorArray");
    m_client->setRemoteProperty(topic, nlohmann::json(vectorArray).dump());
}

void CounterClient::setVectorArrayLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<Test::CustomTypes::Vector3D>& vectorArray = fields.get<std::list<Test::CustomTypes::Vector3D>>();
    if (m_data.m_vectorArray != vectorArray) {
        m_data.m_vectorArray = vectorArray;
        m_publisher->publishVectorArrayChanged(vectorArray);
    }
}

const std::list<Test::CustomTypes::Vector3D>& CounterClient::getVectorArray() const
{
    return m_data.m_vectorArray;
}

void CounterClient::setExternVectorArray(const std::list<Eigen::Vector3f>& extern_vectorArray)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("counter/Counter/set/extern_vectorArray");
    m_client->setRemoteProperty(topic, nlohmann::json(extern_vectorArray).dump());
}

void CounterClient::setExternVectorArrayLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<Eigen::Vector3f>& extern_vectorArray = fields.get<std::list<Eigen::Vector3f>>();
    if (m_data.m_extern_vectorArray != extern_vectorArray) {
        m_data.m_extern_vectorArray = extern_vectorArray;
        m_publisher->publishExternVectorArrayChanged(extern_vectorArray);
    }
}

const std::list<Eigen::Vector3f>& CounterClient::getExternVectorArray() const
{
    return m_data.m_extern_vectorArray;
}

Eigen::Vector3f CounterClient::increment(const Eigen::Vector3f& vec)
{
    if(m_client == nullptr) {
        return Eigen::Vector3f(0,0,0);
    }
    Eigen::Vector3f value(incrementAsync(vec).get());
    return value;
}

std::future<Eigen::Vector3f> CounterClient::incrementAsync(const Eigen::Vector3f& vec)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    vec]()
        {
            std::promise<Eigen::Vector3f> resultPromise;
            static const auto topic = std::string("counter/Counter/rpc/increment");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                const Eigen::Vector3f& value = arg.value.get<Eigen::Vector3f>();
                resultPromise.set_value(value);
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({vec}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}

std::list<Eigen::Vector3f> CounterClient::incrementArray(const std::list<Eigen::Vector3f>& vec)
{
    if(m_client == nullptr) {
        return std::list<Eigen::Vector3f>();
    }
    std::list<Eigen::Vector3f> value(incrementArrayAsync(vec).get());
    return value;
}

std::future<std::list<Eigen::Vector3f>> CounterClient::incrementArrayAsync(const std::list<Eigen::Vector3f>& vec)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    vec]()
        {
            std::promise<std::list<Eigen::Vector3f>> resultPromise;
            static const auto topic = std::string("counter/Counter/rpc/incrementArray");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                const std::list<Eigen::Vector3f>& value = arg.value.get<std::list<Eigen::Vector3f>>();
                resultPromise.set_value(value);
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({vec}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}

Test::CustomTypes::Vector3D CounterClient::decrement(const Test::CustomTypes::Vector3D& vec)
{
    if(m_client == nullptr) {
        return Test::CustomTypes::Vector3D();
    }
    Test::CustomTypes::Vector3D value(decrementAsync(vec).get());
    return value;
}

std::future<Test::CustomTypes::Vector3D> CounterClient::decrementAsync(const Test::CustomTypes::Vector3D& vec)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    vec]()
        {
            std::promise<Test::CustomTypes::Vector3D> resultPromise;
            static const auto topic = std::string("counter/Counter/rpc/decrement");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                const Test::CustomTypes::Vector3D& value = arg.value.get<Test::CustomTypes::Vector3D>();
                resultPromise.set_value(value);
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({vec}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}

std::list<Test::CustomTypes::Vector3D> CounterClient::decrementArray(const std::list<Test::CustomTypes::Vector3D>& vec)
{
    if(m_client == nullptr) {
        return std::list<Test::CustomTypes::Vector3D>();
    }
    std::list<Test::CustomTypes::Vector3D> value(decrementArrayAsync(vec).get());
    return value;
}

std::future<std::list<Test::CustomTypes::Vector3D>> CounterClient::decrementArrayAsync(const std::list<Test::CustomTypes::Vector3D>& vec)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    vec]()
        {
            std::promise<std::list<Test::CustomTypes::Vector3D>> resultPromise;
            static const auto topic = std::string("counter/Counter/rpc/decrementArray");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                const std::list<Test::CustomTypes::Vector3D>& value = arg.value.get<std::list<Test::CustomTypes::Vector3D>>();
                resultPromise.set_value(value);
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({vec}).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
}
void CounterClient::onValueChanged(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishValueChanged(json_args[0].get<Test::CustomTypes::Vector3D>(),json_args[1].get<Eigen::Vector3f>(),json_args[2].get<std::list<Test::CustomTypes::Vector3D>>(),json_args[3].get<std::list<Eigen::Vector3f>>());
}

int CounterClient::registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler)
{
    auto responseId = 0;
    std::uniform_int_distribution<> distribution (0, 100000);
    m_responseHandlerMutex.lock();
    do {
        responseId = distribution(randomNumberGenerator);
    } while (m_responseHandlerMap.find(responseId) != m_responseHandlerMap.end());
    m_responseHandlerMap.insert(std::pair<int, ApiGear::MQTT::InvokeReplyFunc>(responseId, handler));
    m_responseHandlerMutex.unlock();

    return responseId;
}

void CounterClient::onInvokeReply(const std::string& args, const std::string& correlationData)
{
    const int randomId = std::stoi(correlationData);
    ApiGear::MQTT::InvokeReplyFunc responseHandler {};
    m_responseHandlerMutex.lock();
    if((m_responseHandlerMap.find(randomId) != m_responseHandlerMap.end()))
    {
        responseHandler = m_responseHandlerMap[randomId];
        m_responseHandlerMap.erase(randomId);
    }
    m_responseHandlerMutex.unlock();
    if(responseHandler) {
        const ApiGear::MQTT::InvokeReplyArg response{nlohmann::json::parse(args)};
        responseHandler(response);
    }
}

bool CounterClient::isReady() const
{
    return m_isReady;
}

ICounterPublisher& CounterClient::_getPublisher() const
{
    return *m_publisher;
}
