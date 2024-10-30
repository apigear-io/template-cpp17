#pragma once

#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"
#include "apigear/nats/natsservice.h"

namespace Test {
namespace Testbed1 {
namespace Nats {
class TEST_TESTBED1_EXPORT StructInterfaceService : public IStructInterfaceSubscriber
{
public:
    explicit StructInterfaceService(std::shared_ptr<IStructInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~StructInterfaceService() override;

    void onConnectionStatusChanged(bool connectionStatus);

    // IStructInterfaceSubscriber interface
    void onSigBool(const StructBool& paramBool) override;
    void onSigInt(const StructInt& paramInt) override;
    void onSigFloat(const StructFloat& paramFloat) override;
    void onSigString(const StructString& paramString) override;

private:
    void onPropBoolChanged(const StructBool& propBool) override;
    /// @brief requests to set the value for the property PropBool coming from the client
    /// @param fields contains the param of the type StructBool
    void onSetPropBool(const std::string& args) const;
    void onPropIntChanged(const StructInt& propInt) override;
    /// @brief requests to set the value for the property PropInt coming from the client
    /// @param fields contains the param of the type StructInt
    void onSetPropInt(const std::string& args) const;
    void onPropFloatChanged(const StructFloat& propFloat) override;
    /// @brief requests to set the value for the property PropFloat coming from the client
    /// @param fields contains the param of the type StructFloat
    void onSetPropFloat(const std::string& args) const;
    void onPropStringChanged(const StructString& propString) override;
    /// @brief requests to set the value for the property PropString coming from the client
    /// @param fields contains the param of the type StructString
    void onSetPropString(const std::string& args) const;

    std::shared_ptr<IStructInterface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

};
} // namespace Nats
} // namespace Testbed1
} // namespace Test
