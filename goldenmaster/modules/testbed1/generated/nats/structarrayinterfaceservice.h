#pragma once

#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"
#include "apigear/nats/natsservice.h"

namespace Test {
namespace Testbed1 {
namespace Nats {
class TEST_TESTBED1_EXPORT StructArrayInterfaceService : public IStructArrayInterfaceSubscriber
{
public:
    explicit StructArrayInterfaceService(std::shared_ptr<IStructArrayInterface> impl, std::shared_ptr<ApiGear::Nats::Service> service);
    virtual ~StructArrayInterfaceService() override;

    void onConnectionStatusChanged(bool connectionStatus);

    // IStructArrayInterfaceSubscriber interface
    void onSigBool(const std::list<StructBool>& paramBool) override;
    void onSigInt(const std::list<StructInt>& paramInt) override;
    void onSigFloat(const std::list<StructFloat>& paramFloat) override;
    void onSigString(const std::list<StructString>& paramString) override;

private:
    void onPropBoolChanged(const std::list<StructBool>& propBool) override;
    /// @brief requests to set the value for the property PropBool coming from the client
    /// @param fields contains the param of the type std::list<StructBool>
    void onSetPropBool(const std::string& args) const;
    void onPropIntChanged(const std::list<StructInt>& propInt) override;
    /// @brief requests to set the value for the property PropInt coming from the client
    /// @param fields contains the param of the type std::list<StructInt>
    void onSetPropInt(const std::string& args) const;
    void onPropFloatChanged(const std::list<StructFloat>& propFloat) override;
    /// @brief requests to set the value for the property PropFloat coming from the client
    /// @param fields contains the param of the type std::list<StructFloat>
    void onSetPropFloat(const std::string& args) const;
    void onPropStringChanged(const std::list<StructString>& propString) override;
    /// @brief requests to set the value for the property PropString coming from the client
    /// @param fields contains the param of the type std::list<StructString>
    void onSetPropString(const std::string& args) const;

    std::shared_ptr<IStructArrayInterface> m_impl;
    std::shared_ptr<ApiGear::Nats::Service> m_service;

};
} // namespace Nats
} // namespace Testbed1
} // namespace Test
