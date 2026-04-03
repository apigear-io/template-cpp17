#pragma once

#include "tb_struct_array/generated/api/tb_struct_array.h"
#include "tb_struct_array/generated/api/common.h"
#include "apigear/nats/natsservice.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <atomic>

namespace Test {
namespace TbStructArray {
namespace Nats {
class TEST_TB_STRUCT_ARRAY_EXPORT StructArrayFieldInterfaceService : public IStructArrayFieldInterfaceSubscriber, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<StructArrayFieldInterfaceService>
{
protected:
    explicit StructArrayFieldInterfaceService(std::shared_ptr<IStructArrayFieldInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
public:
    static std::shared_ptr<StructArrayFieldInterfaceService> create(std::shared_ptr<IStructArrayFieldInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~StructArrayFieldInterfaceService() override;
    void init();

    // IStructArrayFieldInterfaceSubscriber interface
    void onSigMixed(const MixedStruct& paramMixed) override;
    void onSigStructArray(const StructWithArrayOfStructs& paramPoints) override;

private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void onConnected();
    nlohmann::json getState();
    void onPropStructArrayChanged(const StructWithArrayOfStructs& propStructArray) override;
    /// @brief requests to set the value for the property PropStructArray coming from the client
    /// @param fields contains the param of the type StructWithArrayOfStructs
    void onSetPropStructArray(const std::string& args) const;
    void onPropEnumArrayChanged(const StructWithArrayOfEnums& propEnumArray) override;
    /// @brief requests to set the value for the property PropEnumArray coming from the client
    /// @param fields contains the param of the type StructWithArrayOfEnums
    void onSetPropEnumArray(const std::string& args) const;
    void onPropIntArrayChanged(const StructWithArrayOfInts& propIntArray) override;
    /// @brief requests to set the value for the property PropIntArray coming from the client
    /// @param fields contains the param of the type StructWithArrayOfInts
    void onSetPropIntArray(const std::string& args) const;
    void onPropMixedChanged(const MixedStruct& propMixed) override;
    /// @brief requests to set the value for the property PropMixed coming from the client
    /// @param fields contains the param of the type MixedStruct
    void onSetPropMixed(const std::string& args) const;
    std::string onInvokeFuncMixed(const std::string& args) const;
    std::string onInvokeFuncStructArray(const std::string& args) const;

    std::shared_ptr<IStructArrayFieldInterface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

    uint64_t m_onReadySubscriptionId = 0;
    std::atomic<bool> m_initialized{false};

};
} // namespace Nats
} // namespace TbStructArray
} // namespace Test
