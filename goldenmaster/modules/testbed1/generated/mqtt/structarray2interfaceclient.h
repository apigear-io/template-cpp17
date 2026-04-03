#pragma once

#include <future>
#include "testbed1/generated/api/common.h"
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/core/structarray2interface.data.h"
#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttbaseadapter.h"

namespace Test {
namespace Testbed1 {
namespace MQTT {
/**
 * @brief MQTT adapter for StructArray2Interface.
 *
 * @note Threading: property-change and signal callbacks arrive on the MQTT transport thread.
 * Subscription management inside the publisher is thread safe, but the callbacks themselves
 * execute without additional locking. Operation calls are not additionally synchronized —
 * callers are responsible for thread safety of concurrent operation invocations.
 * Property storage is not guarded by a mutex; wrap with StructArray2InterfaceThreadSafeDecorator
 * for concurrent access from multiple threads.
 */
class TEST_TESTBED1_EXPORT StructArray2InterfaceClient : public IStructArray2Interface, public ApiGear::MQTT::MqttBaseAdapter
{
public:
    explicit StructArray2InterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client);
    static std::shared_ptr<StructArray2InterfaceClient> create(std::shared_ptr<ApiGear::MQTT::Client> client);
    /// Convenience factory. Unlike the NATS adapter, no post-construction init() is needed
    /// because MqttBaseAdapter subscribes topics eagerly in the constructor.
    virtual ~StructArray2InterfaceClient() override;
    const StructBoolWithArray& getPropBool() const override;
    void setPropBool(const StructBoolWithArray& propBool) override;
    const StructIntWithArray& getPropInt() const override;
    void setPropInt(const StructIntWithArray& propInt) override;
    const StructFloatWithArray& getPropFloat() const override;
    void setPropFloat(const StructFloatWithArray& propFloat) override;
    const StructStringWithArray& getPropString() const override;
    void setPropString(const StructStringWithArray& propString) override;
    const StructEnumWithArray& getPropEnum() const override;
    void setPropEnum(const StructEnumWithArray& propEnum) override;
    std::list<StructBool> funcBool(const StructBoolWithArray& paramBool) override;
    std::future<std::list<StructBool>> funcBoolAsync(const StructBoolWithArray& paramBool, std::function<void(std::list<StructBool>)> callback = nullptr) override;
    std::list<StructInt> funcInt(const StructIntWithArray& paramInt) override;
    std::future<std::list<StructInt>> funcIntAsync(const StructIntWithArray& paramInt, std::function<void(std::list<StructInt>)> callback = nullptr) override;
    std::list<StructFloat> funcFloat(const StructFloatWithArray& paramFloat) override;
    std::future<std::list<StructFloat>> funcFloatAsync(const StructFloatWithArray& paramFloat, std::function<void(std::list<StructFloat>)> callback = nullptr) override;
    std::list<StructString> funcString(const StructStringWithArray& paramString) override;
    std::future<std::list<StructString>> funcStringAsync(const StructStringWithArray& paramString, std::function<void(std::list<StructString>)> callback = nullptr) override;
    std::list<Enum0Enum> funcEnum(const StructEnumWithArray& paramEnum) override;
    std::future<std::list<Enum0Enum>> funcEnumAsync(const StructEnumWithArray& paramEnum, std::function<void(std::list<Enum0Enum>)> callback = nullptr) override;
    IStructArray2InterfacePublisher& _getPublisher() const override;

    bool isReady() const;

    void onInvokeReply(const std::string& args, const std::string& correlationData);

    void onConnectionStatusChanged(bool connectionStatus);
private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap(const std::string&clientId);
    /// @brief sets the value for the property PropBool coming from the service
    /// @param args contains the param of the type StructBoolWithArray
    void setPropBoolLocal(const std::string& args);
    /// @brief sets the value for the property PropInt coming from the service
    /// @param args contains the param of the type StructIntWithArray
    void setPropIntLocal(const std::string& args);
    /// @brief sets the value for the property PropFloat coming from the service
    /// @param args contains the param of the type StructFloatWithArray
    void setPropFloatLocal(const std::string& args);
    /// @brief sets the value for the property PropString coming from the service
    /// @param args contains the param of the type StructStringWithArray
    void setPropStringLocal(const std::string& args);
    /// @brief sets the value for the property PropEnum coming from the service
    /// @param args contains the param of the type StructEnumWithArray
    void setPropEnumLocal(const std::string& args);
    /// @brief publishes the value for the signal SigBool coming from the service
    /// @param args contains the param(s) of the type(s) const StructBoolWithArray& paramBool
    void onSigBool(const std::string& args) const;
    /// @brief publishes the value for the signal SigInt coming from the service
    /// @param args contains the param(s) of the type(s) const StructIntWithArray& paramInt
    void onSigInt(const std::string& args) const;
    /// @brief publishes the value for the signal SigFloat coming from the service
    /// @param args contains the param(s) of the type(s) const StructFloatWithArray& paramFloat
    void onSigFloat(const std::string& args) const;
    /// @brief publishes the value for the signal SigString coming from the service
    /// @param args contains the param(s) of the type(s) const StructStringWithArray& paramString
    void onSigString(const std::string& args) const;

    bool m_isReady;
    /** Local storage for properties values. */
    StructArray2InterfaceData m_data;
    std::shared_ptr<ApiGear::MQTT::Client> m_client;

    /** The publisher for StructArray2Interface */
    std::unique_ptr<IStructArray2InterfacePublisher> m_publisher;

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
} // namespace Testbed1
} // namespace Test
