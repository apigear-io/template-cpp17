#include "tb_simple/generated/mqtt/emptyinterfaceclient.h"
#include "tb_simple/generated/core/emptyinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <random>

using namespace Test::TbSimple;
using namespace Test::TbSimple::MQTT;

namespace {
    std::mt19937 randomNumberGenerator (std::random_device{}());
}

EmptyInterfaceClient::EmptyInterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client)
    : MqttBaseAdapter(client, createTopicMap(client->getClientId()))
    , m_client(client)
    , m_publisher(std::make_unique<EmptyInterfacePublisher>())
{
}

EmptyInterfaceClient::~EmptyInterfaceClient()
{
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> EmptyInterfaceClient::createTopicMap(const std::string&)
{
    return {
    };
};

int EmptyInterfaceClient::registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler)
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

void EmptyInterfaceClient::onInvokeReply(const std::string& args, const std::string& correlationData)
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

bool EmptyInterfaceClient::isReady() const
{
    return m_isReady;
}

IEmptyInterfacePublisher& EmptyInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
