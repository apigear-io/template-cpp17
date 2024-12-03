#pragma once

#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"
#include "apigear/nats/natsservice.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

namespace Test {
namespace Testbed2 {
namespace Nats {
class TEST_TESTBED2_EXPORT NestedStruct1InterfaceService : public INestedStruct1InterfaceSubscriber, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<NestedStruct1InterfaceService>
{
protected:
    explicit NestedStruct1InterfaceService(std::shared_ptr<INestedStruct1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
public:
    static std::shared_ptr<NestedStruct1InterfaceService>create(std::shared_ptr<INestedStruct1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~NestedStruct1InterfaceService() override;
    void init();

    // INestedStruct1InterfaceSubscriber interface
    void onSig1(const NestedStruct1& param1) override;

private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void onConnected();
    nlohmann::json getState();
    void onProp1Changed(const NestedStruct1& prop1) override;
    /// @brief requests to set the value for the property Prop1 coming from the client
    /// @param fields contains the param of the type NestedStruct1
    void onSetProp1(const std::string& args) const;
    std::string onInvokeFunc1(const std::string& args) const;

    std::shared_ptr<INestedStruct1Interface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

    int32_t m_onReadySubscriptionId = 0;

};
} // namespace Nats
} // namespace Testbed2
} // namespace Test
