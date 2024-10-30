#pragma once

#include "tb_same2/generated/api/tb_same2.h"
#include "tb_same2/generated/api/common.h"
#include "apigear/nats/natsservice.h"

namespace Test {
namespace TbSame2 {
namespace Nats {
class TEST_TB_SAME2_EXPORT SameEnum1InterfaceService : public ISameEnum1InterfaceSubscriber
{
public:
    explicit SameEnum1InterfaceService(std::shared_ptr<ISameEnum1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~SameEnum1InterfaceService() override;

    void onConnectionStatusChanged(bool connectionStatus);

    // ISameEnum1InterfaceSubscriber interface
    void onSig1(Enum1Enum param1) override;

private:
    void onProp1Changed(Enum1Enum prop1) override;
    /// @brief requests to set the value for the property Prop1 coming from the client
    /// @param fields contains the param of the type Enum1Enum
    void onSetProp1(const std::string& args) const;

    std::shared_ptr<ISameEnum1Interface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

};
} // namespace Nats
} // namespace TbSame2
} // namespace Test
