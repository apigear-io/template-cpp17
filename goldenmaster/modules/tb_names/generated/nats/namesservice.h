#pragma once

#include "tb_names/generated/api/tb_names.h"
#include "tb_names/generated/api/common.h"
#include "apigear/nats/natsservice.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

namespace Test {
namespace TbNames {
namespace Nats {
class TEST_TB_NAMES_EXPORT Nam_EsService : public INamEsSubscriber, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<Nam_EsService>
{
protected:
    explicit Nam_EsService(std::shared_ptr<INamEs> impl, std::shared_ptr<ApiGear::Nats::Service> service);
public:
    static std::shared_ptr<Nam_EsService>create(std::shared_ptr<INamEs> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~Nam_EsService() override;
    void init();

    // INamEsSubscriber interface
    void onSomeSignal(bool SOME_PARAM) override;
    void onSomeSignal2(bool Some_Param) override;

private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void onConnected();
    nlohmann::json getState();
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
    std::string onInvokeSomeFunction(const std::string& args) const;
    std::string onInvokeSomeFunction2(const std::string& args) const;

    std::shared_ptr<INamEs> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

    int32_t m_onReadySubscriptionId = 0;

};
} // namespace Nats
} // namespace TbNames
} // namespace Test
