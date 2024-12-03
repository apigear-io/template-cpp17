#pragma once

#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"
#include "apigear/nats/natsservice.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

namespace Test {
namespace Testbed2 {
namespace Nats {
class TEST_TESTBED2_EXPORT ManyParamInterfaceService : public IManyParamInterfaceSubscriber, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<ManyParamInterfaceService>
{
protected:
    explicit ManyParamInterfaceService(std::shared_ptr<IManyParamInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
public:
    static std::shared_ptr<ManyParamInterfaceService>create(std::shared_ptr<IManyParamInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~ManyParamInterfaceService() override;
    void init();

    // IManyParamInterfaceSubscriber interface
    void onSig1(int param1) override;
    void onSig2(int param1, int param2) override;
    void onSig3(int param1, int param2, int param3) override;
    void onSig4(int param1, int param2, int param3, int param4) override;

private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void onConnected();
    nlohmann::json getState();
    void onProp1Changed(int prop1) override;
    /// @brief requests to set the value for the property Prop1 coming from the client
    /// @param fields contains the param of the type int
    void onSetProp1(const std::string& args) const;
    void onProp2Changed(int prop2) override;
    /// @brief requests to set the value for the property Prop2 coming from the client
    /// @param fields contains the param of the type int
    void onSetProp2(const std::string& args) const;
    void onProp3Changed(int prop3) override;
    /// @brief requests to set the value for the property Prop3 coming from the client
    /// @param fields contains the param of the type int
    void onSetProp3(const std::string& args) const;
    void onProp4Changed(int prop4) override;
    /// @brief requests to set the value for the property Prop4 coming from the client
    /// @param fields contains the param of the type int
    void onSetProp4(const std::string& args) const;
    std::string onInvokeFunc1(const std::string& args) const;
    std::string onInvokeFunc2(const std::string& args) const;
    std::string onInvokeFunc3(const std::string& args) const;
    std::string onInvokeFunc4(const std::string& args) const;

    std::shared_ptr<IManyParamInterface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

    int32_t m_onReadySubscriptionId = 0;

};
} // namespace Nats
} // namespace Testbed2
} // namespace Test
