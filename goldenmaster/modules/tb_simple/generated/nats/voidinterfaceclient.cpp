#include "tb_simple/generated/nats/voidinterfaceclient.h"
#include "tb_simple/generated/core/voidinterface.publisher.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include "apigear/utilities/logger.h"

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedSingalsSubscriptions = 1;
const uint32_t  initSubscription = 1;
const uint32_t  serviceAvailableSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = serviceAvailableSubscription  + initSubscription
 + expectedSingalsSubscriptions;
}

std::shared_ptr<VoidInterfaceClient> VoidInterfaceClient::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<VoidInterfaceClient> obj(new VoidInterfaceClient(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> VoidInterfaceClient::getSharedFromDerrived()
{
    return shared_from_this();
}

VoidInterfaceClient::VoidInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<VoidInterfacePublisher>())
{}

void VoidInterfaceClient::init()
{
    BaseAdapter::init([this](){onConnected();});
}

VoidInterfaceClient::~VoidInterfaceClient() = default;

void VoidInterfaceClient::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "tb.simple.VoidInterface.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("tb.simple.VoidInterface.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "tb.simple.VoidInterface.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });
    const std::string topic_sigVoid = "tb.simple.VoidInterface.sig.sigVoid";
    subscribeTopic(topic_sigVoid, [this](const auto& args){onSigVoid(args);});
}
void VoidInterfaceClient::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "tb.simple.VoidInterface.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

void VoidInterfaceClient::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
}

void VoidInterfaceClient::funcVoid()
{
    if(m_client == nullptr) {
        return;
    }
    funcVoidAsync();
}

std::future<void> VoidInterfaceClient::funcVoidAsync()
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("tb.simple.VoidInterface.rpc.funcVoid");

    return std::async(std::launch::async, [this]()
    {
        std::promise<void> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            (void) result;
            resultPromise.set_value();
        };

        m_client->request(topic,  nlohmann::json::array({}).dump(), callback);
        return resultPromise.get_future().get();
    });
}
void VoidInterfaceClient::onSigVoid(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigVoid();
}

IVoidInterfacePublisher& VoidInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}

