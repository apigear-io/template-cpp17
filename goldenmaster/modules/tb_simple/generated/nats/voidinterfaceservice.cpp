#include "tb_simple/generated/nats/voidinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <iostream>

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

namespace{
const uint32_t  expectedMethodSubscriptions = 1;
const uint32_t  expectedPropertiesSubscriptions = 0;
constexpr uint32_t expectedSubscriptionsCount = expectedMethodSubscriptions + expectedPropertiesSubscriptions;
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
    subscribeRequest("tb.simple.VoidInterface.rpc.funcVoid", [this](const auto& args){  return onInvokeFuncVoid(args); });
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
