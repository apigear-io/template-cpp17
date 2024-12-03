#pragma once

#include "testbed1/generated/api/common.h"
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/core/structarrayinterface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace Testbed1 {
namespace Nats {
class TEST_TESTBED1_EXPORT StructArrayInterfaceClient : public IStructArrayInterface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<StructArrayInterfaceClient>
{
protected:
    explicit StructArrayInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<StructArrayInterfaceClient>create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~StructArrayInterfaceClient() override;
    void init();
    const std::list<StructBool>& getPropBool() const override;
    void setPropBool(const std::list<StructBool>& propBool) override;
    const std::list<StructInt>& getPropInt() const override;
    void setPropInt(const std::list<StructInt>& propInt) override;
    const std::list<StructFloat>& getPropFloat() const override;
    void setPropFloat(const std::list<StructFloat>& propFloat) override;
    const std::list<StructString>& getPropString() const override;
    void setPropString(const std::list<StructString>& propString) override;
    std::list<StructBool> funcBool(const std::list<StructBool>& paramBool) override;
    std::future<std::list<StructBool>> funcBoolAsync(const std::list<StructBool>& paramBool) override;
    std::list<StructInt> funcInt(const std::list<StructInt>& paramInt) override;
    std::future<std::list<StructInt>> funcIntAsync(const std::list<StructInt>& paramInt) override;
    std::list<StructFloat> funcFloat(const std::list<StructFloat>& paramFloat) override;
    std::future<std::list<StructFloat>> funcFloatAsync(const std::list<StructFloat>& paramFloat) override;
    std::list<StructString> funcString(const std::list<StructString>& paramString) override;
    std::future<std::list<StructString>> funcStringAsync(const std::list<StructString>& paramString) override;
    IStructArrayInterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void handleAvailable(const std::string& payload);
    void handleInit(const std::string& value);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::list<StructBool>
    std::list<StructBool> _to_PropBool(const std::string& args);
    /// @brief sets the value for the property PropBool coming from the service
    void setPropBoolLocal(const std::list<StructBool>& propBool);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::list<StructInt>
    std::list<StructInt> _to_PropInt(const std::string& args);
    /// @brief sets the value for the property PropInt coming from the service
    void setPropIntLocal(const std::list<StructInt>& propInt);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::list<StructFloat>
    std::list<StructFloat> _to_PropFloat(const std::string& args);
    /// @brief sets the value for the property PropFloat coming from the service
    void setPropFloatLocal(const std::list<StructFloat>& propFloat);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::list<StructString>
    std::list<StructString> _to_PropString(const std::string& args);
    /// @brief sets the value for the property PropString coming from the service
    void setPropStringLocal(const std::list<StructString>& propString);
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
    int32_t m_requestInitCallId = 0;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for StructArrayInterface */
    std::unique_ptr<IStructArrayInterfacePublisher> m_publisher;
    void onConnected();

};
} // namespace Nats
} // namespace Testbed1
} // namespace Test
