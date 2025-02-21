#include "tb_simple/generated/mqtt/voidinterfaceclient.h"
#include "tb_simple/generated/core/voidinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <random>

using namespace Test::TbSimple;
using namespace Test::TbSimple::MQTT;

namespace {
    std::mt19937 randomNumberGenerator (std::random_device{}());
}

VoidInterfaceClient::VoidInterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client)
    : MqttBaseAdapter(client, createTopicMap(client->getClientId()))
    , m_client(client)
    , m_publisher(std::make_unique<VoidInterfacePublisher>())
{
}

VoidInterfaceClient::~VoidInterfaceClient()
{
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> VoidInterfaceClient::createTopicMap(const std::string& clientId)
{
    return {
        { std::string("tb.simple/VoidInterface/sig/sigVoid"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigVoid(args); } },
        { std::string("tb.simple/VoidInterface/rpc/funcVoid/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
    };
};

void VoidInterfaceClient::funcVoid()
{
    if(m_client == nullptr) {
        return;
    }
    funcVoidAsync();
}

std::future<void> VoidInterfaceClient::funcVoidAsync( std::function<void(void)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback]()
        {
            std::promise<void> resultPromise;
            static const auto topic = std::string("tb.simple/VoidInterface/rpc/funcVoid");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            auto responseId = 0; //Not used, the service won't respond, no handler is added for response.
            m_client->invokeRemote(topic, responseTopic, nlohmann::json::array({}).dump(), responseId);
            resultPromise.set_value();
            if (callback)
            {
                callback();
            }
            return resultPromise.get_future().get();
        }
    );
}
void VoidInterfaceClient::onSigVoid(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigVoid();
}

int VoidInterfaceClient::registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler)
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

void VoidInterfaceClient::onInvokeReply(const std::string& args, const std::string& correlationData)
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

bool VoidInterfaceClient::isReady() const
{
    return m_isReady;
}

IVoidInterfacePublisher& VoidInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
