#include "tb_simple/generated/nats/voidinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <iostream>

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 1;
const uint32_t  initRespSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = initRespSubscription + expectedMethodSubscriptions;
}

VoidInterfaceService::VoidInterfaceService(std::shared_ptr<IVoidInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void VoidInterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<VoidInterfaceService> VoidInterfaceService::create(std::shared_ptr<IVoidInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<VoidInterfaceService> obj(new VoidInterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> VoidInterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


VoidInterfaceService::~VoidInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void VoidInterfaceService::onConnected()
{
    m_onReadySubscriptionId= _subscribeForIsReady([this](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string topic = "tb.simple.VoidInterface.service.available";
        m_service->publish(topic, "");
        _unsubscribeFromIsReady(m_onReadySubscriptionId);
    });
    subscribeRequest("tb.simple.VoidInterface.rpc.funcVoid", [this](const auto& args){  return onInvokeFuncVoid(args); });

    const std::string initRequestTopic = "tb.simple.VoidInterface.init";
    subscribeTopic(initRequestTopic, [this, initRequestTopic](const auto& value){
        nlohmann::json json_id = nlohmann::json::parse(value);
        if (json_id.empty())
        {
            return;
        }
        auto clientId = json_id.get<uint64_t>();
        auto topic = initRequestTopic + ".resp." +  std::to_string(clientId);
        auto properties = getState();
        m_service->publish(topic, properties.dump());
        }
    );

}

nlohmann::json VoidInterfaceService::getState()
{
    return nlohmann::json::object({
    });
}
void VoidInterfaceService::onSigVoid()
{
    static const std::string topic = "tb.simple.VoidInterface.sig.sigVoid";
    nlohmann::json args = {  };
    m_service->publish(topic, nlohmann::json(args).dump());
}
std::string VoidInterfaceService::onInvokeFuncVoid(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_impl->funcVoid();
    return "0";
}
