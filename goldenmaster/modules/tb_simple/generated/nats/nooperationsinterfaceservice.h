#pragma once

#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include "apigear/nats/natsservice.h"

namespace Test {
namespace TbSimple {
namespace Nats {
class TEST_TB_SIMPLE_EXPORT NoOperationsInterfaceService : public INoOperationsInterfaceSubscriber
{
public:
    explicit NoOperationsInterfaceService(std::shared_ptr<INoOperationsInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~NoOperationsInterfaceService() override;

    void onConnectionStatusChanged(bool connectionStatus);

    // INoOperationsInterfaceSubscriber interface
    void onSigVoid() override;
    void onSigBool(bool paramBool) override;

private:
    void onPropBoolChanged(bool propBool) override;
    /// @brief requests to set the value for the property PropBool coming from the client
    /// @param fields contains the param of the type bool
    void onSetPropBool(const std::string& args) const;
    void onPropIntChanged(int propInt) override;
    /// @brief requests to set the value for the property PropInt coming from the client
    /// @param fields contains the param of the type int
    void onSetPropInt(const std::string& args) const;

    std::shared_ptr<INoOperationsInterface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
