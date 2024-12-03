#include "tb_simple/generated/nats/emptyinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <iostream>

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  initRespSubscription = 1;
constexpr uint32_t expectedSubscriptionsCount = initRespSubscription;
}

EmptyInterfaceService::EmptyInterfaceService(std::shared_ptr<IEmptyInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void EmptyInterfaceService::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<EmptyInterfaceService> EmptyInterfaceService::create(std::shared_ptr<IEmptyInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<EmptyInterfaceService> obj(new EmptyInterfaceService(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> EmptyInterfaceService::getSharedFromDerrived()
{
    return shared_from_this();
}


EmptyInterfaceService::~EmptyInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void EmptyInterfaceService::onConnected()
{
    m_onReadySubscriptionId= _subscribeForIsReady([this](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string topic = "tb.simple.EmptyInterface.service.available";
        m_service->publish(topic, "");
        _unsubscribeFromIsReady(m_onReadySubscriptionId);
    });

    const std::string initRequestTopic = "tb.simple.EmptyInterface.init";
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

nlohmann::json EmptyInterfaceService::getState()
{
    return nlohmann::json::object({
    });
}
