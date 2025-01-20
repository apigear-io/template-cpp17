#pragma once

#include <future>
#include "testbed2/generated/api/common.h"
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/core/nestedstruct2interface.data.h"
#include "apigear/mqtt/mqttclient.h"

namespace Test {
namespace Testbed2 {
namespace MQTT {
class TEST_TESTBED2_EXPORT NestedStruct2InterfaceClient : public INestedStruct2Interface
{
public:
    explicit NestedStruct2InterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client);
    virtual ~NestedStruct2InterfaceClient() override;
    const NestedStruct1& getProp1() const override;
    void setProp1(const NestedStruct1& prop1) override;
    const NestedStruct2& getProp2() const override;
    void setProp2(const NestedStruct2& prop2) override;
    NestedStruct1 func1(const NestedStruct1& param1) override;
    std::future<NestedStruct1> func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback = nullptr) override;
    NestedStruct1 func2(const NestedStruct1& param1, const NestedStruct2& param2) override;
    std::future<NestedStruct1> func2Async(const NestedStruct1& param1, const NestedStruct2& param2, std::function<void(NestedStruct1)> callback = nullptr) override;
    INestedStruct2InterfacePublisher& _getPublisher() const override;

    bool isReady() const;

    void onInvokeReply(const std::string& args, const std::string& correlationData);

    void onConnectionStatusChanged(bool connectionStatus);
private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap(const std::string&clientId);
    /// @brief sets the value for the property Prop1 coming from the service
    /// @param args contains the param of the type NestedStruct1
    void setProp1Local(const std::string& args);
    /// @brief sets the value for the property Prop2 coming from the service
    /// @param args contains the param of the type NestedStruct2
    void setProp2Local(const std::string& args);
    /// @brief publishes the value for the signal Sig1 coming from the service
    /// @param args contains the param(s) of the type(s) const NestedStruct1& param1
    void onSig1(const std::string& args) const;
    /// @brief publishes the value for the signal Sig2 coming from the service
    /// @param args contains the param(s) of the type(s) const NestedStruct1& param1, const NestedStruct2& param2
    void onSig2(const std::string& args) const;

    bool m_isReady;
    /** Local storage for properties values. */
    NestedStruct2InterfaceData m_data;
    std::shared_ptr<ApiGear::MQTT::Client> m_client;

    /** The publisher for NestedStruct2Interface */
    std::unique_ptr<INestedStruct2InterfacePublisher> m_publisher;

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
