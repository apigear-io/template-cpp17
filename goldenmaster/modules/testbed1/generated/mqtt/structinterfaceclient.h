#pragma once

#include <future>
#include "testbed1/generated/api/common.h"
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/core/structinterface.data.h"
#include "apigear/mqtt/mqttclient.h"

namespace Test {
namespace Testbed1 {
namespace MQTT {
class TEST_TESTBED1_EXPORT StructInterfaceClient : public IStructInterface
{
public:
    explicit StructInterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client);
    virtual ~StructInterfaceClient() override;
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
    StructInt funcInt(const StructInt& paramInt) override;
    std::future<StructInt> funcIntAsync(const StructInt& paramInt, std::function<void(StructInt)> callback = nullptr) override;
    StructFloat funcFloat(const StructFloat& paramFloat) override;
    std::future<StructFloat> funcFloatAsync(const StructFloat& paramFloat, std::function<void(StructFloat)> callback = nullptr) override;
    StructString funcString(const StructString& paramString) override;
    std::future<StructString> funcStringAsync(const StructString& paramString, std::function<void(StructString)> callback = nullptr) override;
    IStructInterfacePublisher& _getPublisher() const override;

    bool isReady() const;

    void onInvokeReply(const std::string& args, const std::string& correlationData);

    void onConnectionStatusChanged(bool connectionStatus);
private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap(const std::string&clientId);
    /// @brief sets the value for the property PropBool coming from the service
    /// @param args contains the param of the type StructBool
    void setPropBoolLocal(const std::string& args);
    /// @brief sets the value for the property PropInt coming from the service
    /// @param args contains the param of the type StructInt
    void setPropIntLocal(const std::string& args);
    /// @brief sets the value for the property PropFloat coming from the service
    /// @param args contains the param of the type StructFloat
    void setPropFloatLocal(const std::string& args);
    /// @brief sets the value for the property PropString coming from the service
    /// @param args contains the param of the type StructString
    void setPropStringLocal(const std::string& args);
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

    bool m_isReady;
    /** Local storage for properties values. */
    StructInterfaceData m_data;
    std::shared_ptr<ApiGear::MQTT::Client> m_client;

    /** The publisher for StructInterface */
    std::unique_ptr<IStructInterfacePublisher> m_publisher;

    /**
     * @brief register a response handler for an operation invocation
     * 
     * @param handler function to be called on return
     * @return int unique id of the call
     */
    int registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler);
    std::mutex m_responseHandlerMutex;
    std::map<int, ApiGear::MQTT::InvokeReplyFunc> m_responseHandlerMap;

    /// @brief has all the topics of this client and the corresponding function callbacks
    const std::map<std::string, ApiGear::MQTT::CallbackFunction> m_topics;
    // id for connection status registration
    int m_connectionStatusRegistrationID;
};
} // namespace MQTT
} // namespace Testbed1
} // namespace Test
