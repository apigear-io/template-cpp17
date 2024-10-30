#pragma once

#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"
#include "apigear/nats/natsservice.h"

namespace Test {
namespace Testbed2 {
namespace Nats {
class TEST_TESTBED2_EXPORT NestedStruct1InterfaceService : public INestedStruct1InterfaceSubscriber
{
public:
    explicit NestedStruct1InterfaceService(std::shared_ptr<INestedStruct1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~NestedStruct1InterfaceService() override;

    void onConnectionStatusChanged(bool connectionStatus);

    // INestedStruct1InterfaceSubscriber interface
    void onSig1(const NestedStruct1& param1) override;

private:
    void onProp1Changed(const NestedStruct1& prop1) override;
    /// @brief requests to set the value for the property Prop1 coming from the client
    /// @param fields contains the param of the type NestedStruct1
    void onSetProp1(const std::string& args) const;

    std::shared_ptr<INestedStruct1Interface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

};
} // namespace Nats
} // namespace Testbed2
} // namespace Test
