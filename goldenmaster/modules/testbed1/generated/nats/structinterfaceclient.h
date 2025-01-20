#pragma once

#include "testbed1/generated/api/common.h"
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/core/structinterface.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace Testbed1 {
namespace Nats {
class TEST_TESTBED1_EXPORT StructInterfaceClient : public IStructInterface, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<StructInterfaceClient>
{
protected:
    explicit StructInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<StructInterfaceClient>create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~StructInterfaceClient() override;
    void init();
    const StructBool& getPropBool() const override;
    void setPropBool(const StructBool& propBool) override;
    const StructInt& getPropInt() const override;
    void setPropInt(const StructInt& propInt) override;
    const StructFloat& getPropFloat() const override;
    void setPropFloat(const StructFloat& propFloat) override;
    const StructString& getPropString() const override;
    void setPropString(const StructString& propString) override;
    StructBool funcBool(const StructBool& paramBool) override;
    std::future<StructBool> funcBoolAsync(const StructBool& paramBool, std::function<void(StructBool)> callback = nullptr) override;
    StructBool funcInt(const StructInt& paramInt) override;
    std::future<StructBool> funcIntAsync(const StructInt& paramInt, std::function<void(StructBool)> callback = nullptr) override;
    StructFloat funcFloat(const StructFloat& paramFloat) override;
    std::future<StructFloat> funcFloatAsync(const StructFloat& paramFloat, std::function<void(StructFloat)> callback = nullptr) override;
    StructString funcString(const StructString& paramString) override;
    std::future<StructString> funcStringAsync(const StructString& paramString, std::function<void(StructString)> callback = nullptr) override;
    IStructInterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void handleAvailable(const std::string& payload);
    void handleInit(const std::string& value);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type StructBool
    StructBool _to_PropBool(const std::string& args);
    /// @brief sets the value for the property PropBool coming from the service
    void setPropBoolLocal(const StructBool& propBool);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type StructInt
    StructInt _to_PropInt(const std::string& args);
    /// @brief sets the value for the property PropInt coming from the service
    void setPropIntLocal(const StructInt& propInt);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type StructFloat
    StructFloat _to_PropFloat(const std::string& args);
    /// @brief sets the value for the property PropFloat coming from the service
    void setPropFloatLocal(const StructFloat& propFloat);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type StructString
    StructString _to_PropString(const std::string& args);
    /// @brief sets the value for the property PropString coming from the service
    void setPropStringLocal(const StructString& propString);
    /// @brief publishes the value for the signal SigBool coming from the service
    /// @param args contains the param(s) of the type(s) const StructBool& paramBool
    void onSigBool(const std::string& args) const;
    /// @brief publishes the value for the signal SigInt coming from the service
    /// @param args contains the param(s) of the type(s) const StructInt& paramInt
    void onSigInt(const std::string& args) const;
    /// @brief publishes the value for the signal SigFloat coming from the service
    /// @param args contains the param(s) of the type(s) const StructFloat& paramFloat
    void onSigFloat(const std::string& args) const;
    /// @brief publishes the value for the signal SigString coming from the service
    /// @param args contains the param(s) of the type(s) const StructString& paramString
    void onSigString(const std::string& args) const;
    /** Local storage for properties values. */
    StructInterfaceData m_data;
    int32_t m_requestInitCallId = 0;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for StructInterface */
    std::unique_ptr<IStructInterfacePublisher> m_publisher;
    void onConnected();

};
} // namespace Nats
} // namespace Testbed1
} // namespace Test
