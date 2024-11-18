#pragma once

#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include "apigear/nats/natsservice.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

namespace Test {
namespace TbSimple {
namespace Nats {
class TEST_TB_SIMPLE_EXPORT NoSignalsInterfaceService : public INoSignalsInterfaceSubscriber, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<NoSignalsInterfaceService>
{
protected:
    explicit NoSignalsInterfaceService(std::shared_ptr<INoSignalsInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
public:
    static std::shared_ptr<NoSignalsInterfaceService>create(std::shared_ptr<INoSignalsInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~NoSignalsInterfaceService() override;
    void init();

private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void onConnected();
    void onPropBoolChanged(bool propBool) override;
    /// @brief requests to set the value for the property PropBool coming from the client
    /// @param fields contains the param of the type bool
    void onSetPropBool(const std::string& args) const;
    void onPropIntChanged(int propInt) override;
    /// @brief requests to set the value for the property PropInt coming from the client
    /// @param fields contains the param of the type int
    void onSetPropInt(const std::string& args) const;
    std::string onInvokeFuncVoid(const std::string& args) const;
    std::string onInvokeFuncBool(const std::string& args) const;

    std::shared_ptr<INoSignalsInterface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
