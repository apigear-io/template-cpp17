#pragma once

#include <future>
#include "testbed1/generated/api/common.h"
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/core/structarrayinterface.data.h"
#include "apigear/mqtt/mqttclient.h"

namespace Test {
namespace Testbed1 {
namespace MQTT {
class TEST_TESTBED1_EXPORT StructArrayInterfaceClient : public IStructArrayInterface
{
public:
    explicit StructArrayInterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client);
    virtual ~StructArrayInterfaceClient() override;
    const std::list<StructBool>& getPropBool() const override;
    void setPropBool(const std::list<StructBool>& propBool) override;
    const std::list<StructInt>& getPropInt() const override;
    void setPropInt(const std::list<StructInt>& propInt) override;
    const std::list<StructFloat>& getPropFloat() const override;
    void setPropFloat(const std::list<StructFloat>& propFloat) override;
    const std::list<StructString>& getPropString() const override;
    void setPropString(const std::list<StructString>& propString) override;
    std::list<StructBool> funcBool(const std::list<StructBool>& paramBool) override;
    std::future<std::list<StructBool>> funcBoolAsync(const std::list<StructBool>& paramBool, std::function<void(std::list<StructBool>)> callback = nullptr) override;
    std::list<StructInt> funcInt(const std::list<StructInt>& paramInt) override;
    std::future<std::list<StructInt>> funcIntAsync(const std::list<StructInt>& paramInt, std::function<void(std::list<StructInt>)> callback = nullptr) override;
    std::list<StructFloat> funcFloat(const std::list<StructFloat>& paramFloat) override;
    std::future<std::list<StructFloat>> funcFloatAsync(const std::list<StructFloat>& paramFloat, std::function<void(std::list<StructFloat>)> callback = nullptr) override;
    std::list<StructString> funcString(const std::list<StructString>& paramString) override;
    std::future<std::list<StructString>> funcStringAsync(const std::list<StructString>& paramString, std::function<void(std::list<StructString>)> callback = nullptr) override;
    IStructArrayInterfacePublisher& _getPublisher() const override;

    bool isReady() const;

    void onInvokeReply(const std::string& args, const std::string& correlationData);

    void onConnectionStatusChanged(bool connectionStatus);
private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap(const std::string&clientId);
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

    bool m_isReady;
    /** Local storage for properties values. */
    StructArrayInterfaceData m_data;
    std::shared_ptr<ApiGear::MQTT::Client> m_client;

    /** The publisher for StructArrayInterface */
    std::unique_ptr<IStructArrayInterfacePublisher> m_publisher;

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
