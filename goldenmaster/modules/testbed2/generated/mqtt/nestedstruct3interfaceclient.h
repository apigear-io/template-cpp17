#pragma once

#include <future>
#include "testbed2/generated/api/common.h"
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/core/nestedstruct3interface.data.h"
#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttbaseadapter.h"

namespace Test {
namespace Testbed2 {
namespace MQTT {
class TEST_TESTBED2_EXPORT NestedStruct3InterfaceClient : public INestedStruct3Interface, public ApiGear::MQTT::MqttBaseAdapter
{
public:
    explicit NestedStruct3InterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client);
    virtual ~NestedStruct3InterfaceClient() override;
    const NestedStruct1& getProp1() const override;
    void setProp1(const NestedStruct1& prop1) override;
    const NestedStruct2& getProp2() const override;
    void setProp2(const NestedStruct2& prop2) override;
    const NestedStruct3& getProp3() const override;
    void setProp3(const NestedStruct3& prop3) override;
    NestedStruct1 func1(const NestedStruct1& param1) override;
    std::future<NestedStruct1> func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback = nullptr) override;
    NestedStruct1 func2(const NestedStruct1& param1, const NestedStruct2& param2) override;
    std::future<NestedStruct1> func2Async(const NestedStruct1& param1, const NestedStruct2& param2, std::function<void(NestedStruct1)> callback = nullptr) override;
    NestedStruct1 func3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3) override;
    std::future<NestedStruct1> func3Async(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3, std::function<void(NestedStruct1)> callback = nullptr) override;
    INestedStruct3InterfacePublisher& _getPublisher() const override;

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
    /// @brief sets the value for the property Prop3 coming from the service
    /// @param args contains the param of the type NestedStruct3
    void setProp3Local(const std::string& args);
    /// @brief publishes the value for the signal Sig1 coming from the service
    /// @param args contains the param(s) of the type(s) const NestedStruct1& param1
    void onSig1(const std::string& args) const;
    /// @brief publishes the value for the signal Sig2 coming from the service
    /// @param args contains the param(s) of the type(s) const NestedStruct1& param1, const NestedStruct2& param2
    void onSig2(const std::string& args) const;
    /// @brief publishes the value for the signal Sig3 coming from the service
    /// @param args contains the param(s) of the type(s) const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3
    void onSig3(const std::string& args) const;

    bool m_isReady;
    /** Local storage for properties values. */
    NestedStruct3InterfaceData m_data;
    std::shared_ptr<ApiGear::MQTT::Client> m_client;

    /** The publisher for NestedStruct3Interface */
    std::unique_ptr<INestedStruct3InterfacePublisher> m_publisher;

    /**
     * @brief register a response handler for an operation invocation
     * 
     * @param handler function to be called on return
     * @return int unique id of the call
     */
    int registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler);
    std::mutex m_responseHandlerMutex;
    std::map<int, ApiGear::MQTT::InvokeReplyFunc> m_responseHandlerMap;
};
} // namespace MQTT
} // namespace Testbed2
} // namespace Test
