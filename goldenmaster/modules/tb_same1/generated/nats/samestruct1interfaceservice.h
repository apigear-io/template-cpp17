#pragma once

#include "tb_same1/generated/api/tb_same1.h"
#include "tb_same1/generated/api/common.h"
#include "apigear/nats/natsservice.h"

namespace Test {
namespace TbSame1 {
namespace Nats {
class TEST_TB_SAME1_EXPORT SameStruct1InterfaceService : public ISameStruct1InterfaceSubscriber
{
public:
    explicit SameStruct1InterfaceService(std::shared_ptr<ISameStruct1Interface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~SameStruct1InterfaceService() override;

    void onConnectionStatusChanged(bool connectionStatus);

    // ISameStruct1InterfaceSubscriber interface
    void onSig1(const Struct1& param1) override;

private:
    void onProp1Changed(const Struct1& prop1) override;
    /// @brief requests to set the value for the property Prop1 coming from the client
    /// @param fields contains the param of the type Struct1
    void onSetProp1(const std::string& args) const;

    std::shared_ptr<ISameStruct1Interface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

};
} // namespace Nats
} // namespace TbSame1
} // namespace Test
