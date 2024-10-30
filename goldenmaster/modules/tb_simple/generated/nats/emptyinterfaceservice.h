#pragma once

#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include "apigear/nats/natsservice.h"

namespace Test {
namespace TbSimple {
namespace Nats {
class TEST_TB_SIMPLE_EXPORT EmptyInterfaceService : public IEmptyInterfaceSubscriber
{
public:
    explicit EmptyInterfaceService(std::shared_ptr<IEmptyInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~EmptyInterfaceService() override;

    void onConnectionStatusChanged(bool connectionStatus);

private:

    std::shared_ptr<IEmptyInterface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
