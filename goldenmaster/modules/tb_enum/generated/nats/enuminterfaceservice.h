#pragma once

#include "tb_enum/generated/api/tb_enum.h"
#include "tb_enum/generated/api/common.h"
#include "apigear/nats/natsservice.h"

namespace Test {
namespace TbEnum {
namespace Nats {
class TEST_TB_ENUM_EXPORT EnumInterfaceService : public IEnumInterfaceSubscriber
{
public:
    explicit EnumInterfaceService(std::shared_ptr<IEnumInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~EnumInterfaceService() override;

    void onConnectionStatusChanged(bool connectionStatus);

    // IEnumInterfaceSubscriber interface
    void onSig0(Enum0Enum param0) override;
    void onSig1(Enum1Enum param1) override;
    void onSig2(Enum2Enum param2) override;
    void onSig3(Enum3Enum param3) override;

private:
    void onProp0Changed(Enum0Enum prop0) override;
    /// @brief requests to set the value for the property Prop0 coming from the client
    /// @param fields contains the param of the type Enum0Enum
    void onSetProp0(const std::string& args) const;
    void onProp1Changed(Enum1Enum prop1) override;
    /// @brief requests to set the value for the property Prop1 coming from the client
    /// @param fields contains the param of the type Enum1Enum
    void onSetProp1(const std::string& args) const;
    void onProp2Changed(Enum2Enum prop2) override;
    /// @brief requests to set the value for the property Prop2 coming from the client
    /// @param fields contains the param of the type Enum2Enum
    void onSetProp2(const std::string& args) const;
    void onProp3Changed(Enum3Enum prop3) override;
    /// @brief requests to set the value for the property Prop3 coming from the client
    /// @param fields contains the param of the type Enum3Enum
    void onSetProp3(const std::string& args) const;

    std::shared_ptr<IEnumInterface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

};
} // namespace Nats
} // namespace TbEnum
} // namespace Test
