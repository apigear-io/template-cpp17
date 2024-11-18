#pragma once

#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include "apigear/nats/natsservice.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

namespace Test {
namespace TbSimple {
namespace Nats {
class TEST_TB_SIMPLE_EXPORT EmptyInterfaceService : public IEmptyInterfaceSubscriber, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<EmptyInterfaceService>
{
protected:
    explicit EmptyInterfaceService(std::shared_ptr<IEmptyInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
public:
    static std::shared_ptr<EmptyInterfaceService>create(std::shared_ptr<IEmptyInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~EmptyInterfaceService() override;
    void init();

private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void onConnected();

    std::shared_ptr<IEmptyInterface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
