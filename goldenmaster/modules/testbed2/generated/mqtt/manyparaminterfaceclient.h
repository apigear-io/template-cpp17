#pragma once

#include <future>
#include "testbed2/generated/api/common.h"
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/core/manyparaminterface.data.h"
#include "apigear/mqtt/mqttclient.h"

namespace Test {
namespace Testbed2 {
namespace MQTT {
class TEST_TESTBED2_EXPORT ManyParamInterfaceClient : public IManyParamInterface
{
public:
    explicit ManyParamInterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client);
    virtual ~ManyParamInterfaceClient() override;
    int getProp1() const override;
    void setProp1(int prop1) override;
    int getProp2() const override;
    void setProp2(int prop2) override;
    int getProp3() const override;
    void setProp3(int prop3) override;
    int getProp4() const override;
    void setProp4(int prop4) override;
    int func1(int param1) override;
    std::future<int> func1Async(int param1, std::function<void(int)> callback = nullptr) override;
    int func2(int param1, int param2) override;
    std::future<int> func2Async(int param1, int param2, std::function<void(int)> callback = nullptr) override;
    int func3(int param1, int param2, int param3) override;
    std::future<int> func3Async(int param1, int param2, int param3, std::function<void(int)> callback = nullptr) override;
    int func4(int param1, int param2, int param3, int param4) override;
    std::future<int> func4Async(int param1, int param2, int param3, int param4, std::function<void(int)> callback = nullptr) override;
    IManyParamInterfacePublisher& _getPublisher() const override;

    bool isReady() const;

    void onInvokeReply(const std::string& args, const std::string& correlationData);

    void onConnectionStatusChanged(bool connectionStatus);
private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap(const std::string&clientId);
    /// @brief sets the value for the property Prop1 coming from the service
    /// @param args contains the param of the type int
    void setProp1Local(const std::string& args);
    /// @brief sets the value for the property Prop2 coming from the service
    /// @param args contains the param of the type int
    void setProp2Local(const std::string& args);
    /// @brief sets the value for the property Prop3 coming from the service
    /// @param args contains the param of the type int
    void setProp3Local(const std::string& args);
    /// @brief sets the value for the property Prop4 coming from the service
    /// @param args contains the param of the type int
    void setProp4Local(const std::string& args);
    /// @brief publishes the value for the signal Sig1 coming from the service
    /// @param args contains the param(s) of the type(s) int param1
    void onSig1(const std::string& args) const;
    /// @brief publishes the value for the signal Sig2 coming from the service
    /// @param args contains the param(s) of the type(s) int param1, int param2
    void onSig2(const std::string& args) const;
    /// @brief publishes the value for the signal Sig3 coming from the service
    /// @param args contains the param(s) of the type(s) int param1, int param2, int param3
    void onSig3(const std::string& args) const;
    /// @brief publishes the value for the signal Sig4 coming from the service
    /// @param args contains the param(s) of the type(s) int param1, int param2, int param3, int param4
    void onSig4(const std::string& args) const;

    bool m_isReady;
    /** Local storage for properties values. */
    ManyParamInterfaceData m_data;
    std::shared_ptr<ApiGear::MQTT::Client> m_client;

    /** The publisher for ManyParamInterface */
    std::unique_ptr<IManyParamInterfacePublisher> m_publisher;

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
} // namespace Testbed2
} // namespace Test
