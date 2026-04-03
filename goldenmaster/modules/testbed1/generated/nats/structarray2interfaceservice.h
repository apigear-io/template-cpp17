#pragma once

#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"
#include "apigear/nats/natsservice.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <atomic>

namespace Test {
namespace Testbed1 {
namespace Nats {
class TEST_TESTBED1_EXPORT StructArray2InterfaceService : public IStructArray2InterfaceSubscriber, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<StructArray2InterfaceService>
{
protected:
    explicit StructArray2InterfaceService(std::shared_ptr<IStructArray2Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
public:
    static std::shared_ptr<StructArray2InterfaceService> create(std::shared_ptr<IStructArray2Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~StructArray2InterfaceService() override;
    void init();

    // IStructArray2InterfaceSubscriber interface
    void onSigBool(const StructBoolWithArray& paramBool) override;
    void onSigInt(const StructIntWithArray& paramInt) override;
    void onSigFloat(const StructFloatWithArray& paramFloat) override;
    void onSigString(const StructStringWithArray& paramString) override;

private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void onConnected();
    nlohmann::json getState();
    void onPropBoolChanged(const StructBoolWithArray& propBool) override;
    /// @brief requests to set the value for the property PropBool coming from the client
    /// @param fields contains the param of the type StructBoolWithArray
    void onSetPropBool(const std::string& args) const;
    void onPropIntChanged(const StructIntWithArray& propInt) override;
    /// @brief requests to set the value for the property PropInt coming from the client
    /// @param fields contains the param of the type StructIntWithArray
    void onSetPropInt(const std::string& args) const;
    void onPropFloatChanged(const StructFloatWithArray& propFloat) override;
    /// @brief requests to set the value for the property PropFloat coming from the client
    /// @param fields contains the param of the type StructFloatWithArray
    void onSetPropFloat(const std::string& args) const;
    void onPropStringChanged(const StructStringWithArray& propString) override;
    /// @brief requests to set the value for the property PropString coming from the client
    /// @param fields contains the param of the type StructStringWithArray
    void onSetPropString(const std::string& args) const;
    void onPropEnumChanged(const StructEnumWithArray& propEnum) override;
    /// @brief requests to set the value for the property PropEnum coming from the client
    /// @param fields contains the param of the type StructEnumWithArray
    void onSetPropEnum(const std::string& args) const;
    std::string onInvokeFuncBool(const std::string& args) const;
    std::string onInvokeFuncInt(const std::string& args) const;
    std::string onInvokeFuncFloat(const std::string& args) const;
    std::string onInvokeFuncString(const std::string& args) const;
    std::string onInvokeFuncEnum(const std::string& args) const;

    std::shared_ptr<IStructArray2Interface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

    uint64_t m_onReadySubscriptionId = 0;
    std::atomic<bool> m_initialized{false};

};
} // namespace Nats
} // namespace Testbed1
} // namespace Test
