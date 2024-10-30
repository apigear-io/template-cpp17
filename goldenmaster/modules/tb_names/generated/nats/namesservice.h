#pragma once

#include "tb_names/generated/api/tb_names.h"
#include "tb_names/generated/api/common.h"
#include "apigear/nats/natsservice.h"

namespace Test {
namespace TbNames {
namespace Nats {
class TEST_TB_NAMES_EXPORT Nam_EsService : public INamEsSubscriber
{
public:
    explicit Nam_EsService(std::shared_ptr<INamEs> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~Nam_EsService() override;

    void onConnectionStatusChanged(bool connectionStatus);

    // INamEsSubscriber interface
    void onSomeSignal(bool SOME_PARAM) override;
    void onSomeSignal2(bool Some_Param) override;

private:
    void onSwitchChanged(bool Switch) override;
    /// @brief requests to set the value for the property Switch coming from the client
    /// @param fields contains the param of the type bool
    void onSetSwitch(const std::string& args) const;
    void onSomePropertyChanged(int SOME_PROPERTY) override;
    /// @brief requests to set the value for the property SomeProperty coming from the client
    /// @param fields contains the param of the type int
    void onSetSomeProperty(const std::string& args) const;
    void onSomePoperty2Changed(int Some_Poperty2) override;
    /// @brief requests to set the value for the property SomePoperty2 coming from the client
    /// @param fields contains the param of the type int
    void onSetSomePoperty2(const std::string& args) const;
    void onEnumPropertyChanged(Enum_With_Under_scoresEnum enum_property) override;
    /// @brief requests to set the value for the property EnumProperty coming from the client
    /// @param fields contains the param of the type Enum_With_Under_scoresEnum
    void onSetEnumProperty(const std::string& args) const;

    std::shared_ptr<INamEs> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

};
} // namespace Nats
} // namespace TbNames
} // namespace Test
