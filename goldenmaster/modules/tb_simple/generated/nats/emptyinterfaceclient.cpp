#include "tb_simple/generated/nats/emptyinterfaceclient.h"
#include "tb_simple/generated/core/emptyinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
// no singals and properties to subscribe for
constexpr uint32_t expectedSubscriptionsCount = 0;
}

std::shared_ptr<EmptyInterfaceClient> EmptyInterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<EmptyInterfaceClient> obj(new EmptyInterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> EmptyInterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

EmptyInterfaceClient::EmptyInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<EmptyInterfacePublisher>())
{}

void EmptyInterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

EmptyInterfaceClient::~EmptyInterfaceClient() = default;

void EmptyInterfaceClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "tb.simple.EmptyInterface.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("tb.simple.EmptyInterface.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "tb.simple.EmptyInterface.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
}
void EmptyInterfaceClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "tb.simple.EmptyInterface.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void EmptyInterfaceClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
}

IEmptyInterfacePublisher& EmptyInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}

