#pragma once

#include "tb_same1/generated/api/tb_same1.h"
#include "tb_same1/generated/api/common.h"
#include "apigear/nats/natsservice.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

namespace Test {
namespace TbSame1 {
namespace Nats {
class TEST_TB_SAME1_EXPORT SameEnum1InterfaceService : public ISameEnum1InterfaceSubscriber, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<SameEnum1InterfaceService>
{
protected:
    explicit SameEnum1InterfaceService(std::shared_ptr<ISameEnum1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
public:
    static std::shared_ptr<SameEnum1InterfaceService>create(std::shared_ptr<ISameEnum1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~SameEnum1InterfaceService() override;
    void init();

    // ISameEnum1InterfaceSubscriber interface
    void onSig1(Enum1Enum param1) override;

private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void onConnected();
    nlohmann::json getState();
    void onProp1Changed(Enum1Enum prop1) override;
    /// @brief requests to set the value for the property Prop1 coming from the client
    /// @param fields contains the param of the type Enum1Enum
    void onSetProp1(const std::string& args) const;
    std::string onInvokeFunc1(const std::string& args) const;

    std::shared_ptr<ISameEnum1Interface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

    int32_t m_onReadySubscriptionId = 0;

};
} // namespace Nats
} // namespace TbSame1
} // namespace Test
