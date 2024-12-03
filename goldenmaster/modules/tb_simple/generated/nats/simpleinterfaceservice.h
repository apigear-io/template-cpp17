#pragma once

#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include "apigear/nats/natsservice.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

namespace Test {
namespace TbSimple {
namespace Nats {
class TEST_TB_SIMPLE_EXPORT SimpleInterfaceService : public ISimpleInterfaceSubscriber, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<SimpleInterfaceService>
{
protected:
    explicit SimpleInterfaceService(std::shared_ptr<ISimpleInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
public:
    static std::shared_ptr<SimpleInterfaceService>create(std::shared_ptr<ISimpleInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~SimpleInterfaceService() override;
    void init();

    // ISimpleInterfaceSubscriber interface
    void onSigBool(bool paramBool) override;
    void onSigInt(int paramInt) override;
    void onSigInt32(int32_t paramInt32) override;
    void onSigInt64(int64_t paramInt64) override;
    void onSigFloat(float paramFloat) override;
    void onSigFloat32(float paramFloat32) override;
    void onSigFloat64(double paramFloat64) override;
    void onSigString(const std::string& paramString) override;

private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void onConnected();
    nlohmann::json getState();
    void onPropBoolChanged(bool propBool) override;
    /// @brief requests to set the value for the property PropBool coming from the client
    /// @param fields contains the param of the type bool
    void onSetPropBool(const std::string& args) const;
    void onPropIntChanged(int propInt) override;
    /// @brief requests to set the value for the property PropInt coming from the client
    /// @param fields contains the param of the type int
    void onSetPropInt(const std::string& args) const;
    void onPropInt32Changed(int32_t propInt32) override;
    /// @brief requests to set the value for the property PropInt32 coming from the client
    /// @param fields contains the param of the type int32_t
    void onSetPropInt32(const std::string& args) const;
    void onPropInt64Changed(int64_t propInt64) override;
    /// @brief requests to set the value for the property PropInt64 coming from the client
    /// @param fields contains the param of the type int64_t
    void onSetPropInt64(const std::string& args) const;
    void onPropFloatChanged(float propFloat) override;
    /// @brief requests to set the value for the property PropFloat coming from the client
    /// @param fields contains the param of the type float
    void onSetPropFloat(const std::string& args) const;
    void onPropFloat32Changed(float propFloat32) override;
    /// @brief requests to set the value for the property PropFloat32 coming from the client
    /// @param fields contains the param of the type float
    void onSetPropFloat32(const std::string& args) const;
    void onPropFloat64Changed(double propFloat64) override;
    /// @brief requests to set the value for the property PropFloat64 coming from the client
    /// @param fields contains the param of the type double
    void onSetPropFloat64(const std::string& args) const;
    void onPropStringChanged(const std::string& propString) override;
    /// @brief requests to set the value for the property PropString coming from the client
    /// @param fields contains the param of the type std::string
    void onSetPropString(const std::string& args) const;
    std::string onInvokeFuncNoReturnValue(const std::string& args) const;
    std::string onInvokeFuncBool(const std::string& args) const;
    std::string onInvokeFuncInt(const std::string& args) const;
    std::string onInvokeFuncInt32(const std::string& args) const;
    std::string onInvokeFuncInt64(const std::string& args) const;
    std::string onInvokeFuncFloat(const std::string& args) const;
    std::string onInvokeFuncFloat32(const std::string& args) const;
    std::string onInvokeFuncFloat64(const std::string& args) const;
    std::string onInvokeFuncString(const std::string& args) const;

    std::shared_ptr<ISimpleInterface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

    int32_t m_onReadySubscriptionId = 0;

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
