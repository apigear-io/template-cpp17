#pragma once

#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"
#include "apigear/nats/natsservice.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

namespace Test {
namespace Testbed2 {
namespace Nats {
class TEST_TESTBED2_EXPORT NestedStruct2InterfaceService : public INestedStruct2InterfaceSubscriber, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<NestedStruct2InterfaceService>
{
protected:
    explicit NestedStruct2InterfaceService(std::shared_ptr<INestedStruct2Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
public:
    static std::shared_ptr<NestedStruct2InterfaceService>create(std::shared_ptr<INestedStruct2Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~NestedStruct2InterfaceService() override;
    void init();

    // INestedStruct2InterfaceSubscriber interface
    void onSig1(const NestedStruct1& param1) override;
    void onSig2(const NestedStruct1& param1, const NestedStruct2& param2) override;

private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void onConnected();
    nlohmann::json getState();
    void onProp1Changed(const NestedStruct1& prop1) override;
    /// @brief requests to set the value for the property Prop1 coming from the client
    /// @param fields contains the param of the type NestedStruct1
    void onSetProp1(const std::string& args) const;
    void onProp2Changed(const NestedStruct2& prop2) override;
    /// @brief requests to set the value for the property Prop2 coming from the client
    /// @param fields contains the param of the type NestedStruct2
    void onSetProp2(const std::string& args) const;
    std::string onInvokeFunc1(const std::string& args) const;
    std::string onInvokeFunc2(const std::string& args) const;

    std::shared_ptr<INestedStruct2Interface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

    int32_t m_onReadySubscriptionId = 0;

};
} // namespace Nats
} // namespace Testbed2
} // namespace Test
