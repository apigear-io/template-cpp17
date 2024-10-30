#pragma once

#include <future>
#include "testbed1/generated/api/common.h"
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/core/structarrayinterface.data.h"
#include "apigear/nats/natsclient.h"

namespace Test {
namespace Testbed1 {
namespace Nats {
class TEST_TESTBED1_EXPORT StructArrayInterfaceClient : public IStructArrayInterface
{
public:
    explicit StructArrayInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~StructArrayInterfaceClient() override;
    const std::list<StructBool>& getPropBool() const override;
    void setPropBool(const std::list<StructBool>& propBool) override;
    const std::list<StructInt>& getPropInt() const override;
    void setPropInt(const std::list<StructInt>& propInt) override;
    const std::list<StructFloat>& getPropFloat() const override;
    void setPropFloat(const std::list<StructFloat>& propFloat) override;
    const std::list<StructString>& getPropString() const override;
    void setPropString(const std::list<StructString>& propString) override;
    StructBool funcBool(const std::list<StructBool>& paramBool) override;
    std::future<StructBool> funcBoolAsync(const std::list<StructBool>& paramBool) override;
    StructBool funcInt(const std::list<StructInt>& paramInt) override;
    std::future<StructBool> funcIntAsync(const std::list<StructInt>& paramInt) override;
    StructBool funcFloat(const std::list<StructFloat>& paramFloat) override;
    std::future<StructBool> funcFloatAsync(const std::list<StructFloat>& paramFloat) override;
    StructBool funcString(const std::list<StructString>& paramString) override;
    std::future<StructBool> funcStringAsync(const std::list<StructString>& paramString) override;
    IStructArrayInterfacePublisher& _getPublisher() const override;
private:
    /// @brief sets the value for the property PropBool coming from the service
    /// @param args contains the param of the type std::list<StructBool>
    void setPropBoolLocal(const std::string& args);
    /// @brief sets the value for the property PropInt coming from the service
    /// @param args contains the param of the type std::list<StructInt>
    void setPropIntLocal(const std::string& args);
    /// @brief sets the value for the property PropFloat coming from the service
    /// @param args contains the param of the type std::list<StructFloat>
    void setPropFloatLocal(const std::string& args);
    /// @brief sets the value for the property PropString coming from the service
    /// @param args contains the param of the type std::list<StructString>
    void setPropStringLocal(const std::string& args);
    /// @brief publishes the value for the signal SigBool coming from the service
    /// @param args contains the param(s) of the type(s) const std::list<StructBool>& paramBool
    void onSigBool(const std::string& args) const;
    /// @brief publishes the value for the signal SigInt coming from the service
    /// @param args contains the param(s) of the type(s) const std::list<StructInt>& paramInt
    void onSigInt(const std::string& args) const;
    /// @brief publishes the value for the signal SigFloat coming from the service
    /// @param args contains the param(s) of the type(s) const std::list<StructFloat>& paramFloat
    void onSigFloat(const std::string& args) const;
    /// @brief publishes the value for the signal SigString coming from the service
    /// @param args contains the param(s) of the type(s) const std::list<StructString>& paramString
    void onSigString(const std::string& args) const;
    /** Local storage for properties values. */
    StructArrayInterfaceData m_data;
    std::shared_ptr<ApiGear::Nats::Client> m_client;

    /** The publisher for StructArrayInterface */
    std::unique_ptr<IStructArrayInterfacePublisher> m_publisher;

};
} // namespace Nats
} // namespace Testbed1
} // namespace Test