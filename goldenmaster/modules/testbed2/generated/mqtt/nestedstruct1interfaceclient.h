#pragma once

#include <future>
#include "testbed2/generated/api/common.h"
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/core/nestedstruct1interface.data.h"
#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttbaseadapter.h"

namespace Test {
namespace Testbed2 {
namespace MQTT {
/**
 * @brief MQTT adapter for NestedStruct1Interface.
 *
 * @note Threading: property-change and signal callbacks arrive on the MQTT transport thread.
 * Subscription management inside the publisher is thread safe, but the callbacks themselves
 * execute without additional locking. Operation calls are not additionally synchronized —
 * callers are responsible for thread safety of concurrent operation invocations.
 * Property storage is not guarded by a mutex; wrap with NestedStruct1InterfaceThreadSafeDecorator
 * for concurrent access from multiple threads.
 */
class TEST_TESTBED2_EXPORT NestedStruct1InterfaceClient : public INestedStruct1Interface, public ApiGear::MQTT::MqttBaseAdapter
{
public:
    explicit NestedStruct1InterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client);
    static std::shared_ptr<NestedStruct1InterfaceClient> create(std::shared_ptr<ApiGear::MQTT::Client> client);
    /// Convenience factory. Unlike the NATS adapter, no post-construction init() is needed
    /// because MqttBaseAdapter subscribes topics eagerly in the constructor.
    virtual ~NestedStruct1InterfaceClient() override;
    const NestedStruct1& getProp1() const override;
    void setProp1(const NestedStruct1& prop1) override;
    NestedStruct1 func1(const NestedStruct1& param1) override;
    std::future<NestedStruct1> func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback = nullptr) override;
    INestedStruct1InterfacePublisher& _getPublisher() const override;

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
    /// @brief publishes the value for the signal Sig1 coming from the service
    /// @param args contains the param(s) of the type(s) const NestedStruct1& param1
    void onSig1(const std::string& args) const;

    bool m_isReady;
    /** Local storage for properties values. */
    NestedStruct1InterfaceData m_data;
    std::shared_ptr<ApiGear::MQTT::Client> m_client;

    /** The publisher for NestedStruct1Interface */
    std::unique_ptr<INestedStruct1InterfacePublisher> m_publisher;

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
