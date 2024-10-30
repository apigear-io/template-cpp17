#include "tb_simple/generated/nats/voidinterfaceservice.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include <iostream>

using namespace Test::TbSimple;
using namespace Test::TbSimple::Nats;

VoidInterfaceService::VoidInterfaceService(std::shared_ptr<IVoidInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    : m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

VoidInterfaceService::~VoidInterfaceService()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void VoidInterfaceService::onConnectionStatusChanged(bool connectionStatus)
{
    if(!connectionStatus)
    {
        return;
    }
    // TODO send current values through service
}
void VoidInterfaceService::onSigVoid()
{
//TODO use service to notify clients
}
