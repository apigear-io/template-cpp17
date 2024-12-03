#pragma once

#include "tb_same2/generated/api/tb_same2.h"
#include "tb_same2/generated/api/common.h"
#include "apigear/nats/natsservice.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

namespace Test {
namespace TbSame2 {
namespace Nats {
class TEST_TB_SAME2_EXPORT SameStruct1InterfaceService : public ISameStruct1InterfaceSubscriber, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<SameStruct1InterfaceService>
{
protected:
    explicit SameStruct1InterfaceService(std::shared_ptr<ISameStruct1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
public:
    static std::shared_ptr<SameStruct1InterfaceService>create(std::shared_ptr<ISameStruct1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~SameStruct1InterfaceService() override;
    void init();

    // ISameStruct1InterfaceSubscriber interface
    void onSig1(const Struct1& param1) override;

private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void onConnected();
    nlohmann::json getState();
    void onProp1Changed(const Struct1& prop1) override;
    /// @brief requests to set the value for the property Prop1 coming from the client
    /// @param fields contains the param of the type Struct1
    void onSetProp1(const std::string& args) const;
    std::string onInvokeFunc1(const std::string& args) const;

    std::shared_ptr<ISameStruct1Interface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

    int32_t m_onReadySubscriptionId = 0;

};
} // namespace Nats
} // namespace TbSame2
} // namespace Test
