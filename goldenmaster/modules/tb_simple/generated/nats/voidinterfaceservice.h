#pragma once

#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include "apigear/nats/natsservice.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

namespace Test {
namespace TbSimple {
namespace Nats {
class TEST_TB_SIMPLE_EXPORT VoidInterfaceService : public IVoidInterfaceSubscriber, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<VoidInterfaceService>
{
protected:
    explicit VoidInterfaceService(std::shared_ptr<IVoidInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
public:
    static std::shared_ptr<VoidInterfaceService>create(std::shared_ptr<IVoidInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~VoidInterfaceService() override;
    void init();

    // IVoidInterfaceSubscriber interface
    void onSigVoid() override;

private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void onConnected();
    std::string onInvokeFuncVoid(const std::string& args) const;

    std::shared_ptr<IVoidInterface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
