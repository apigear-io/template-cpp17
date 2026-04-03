#pragma once

#include <future>
#include "tb_struct_array/generated/api/common.h"
#include "tb_struct_array/generated/api/tb_struct_array.h"
#include "tb_struct_array/generated/core/structarrayfieldinterface.data.h"
#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttbaseadapter.h"

namespace Test {
namespace TbStructArray {
namespace MQTT {
/**
 * @brief MQTT adapter for StructArrayFieldInterface.
 *
 * @note Threading: property-change and signal callbacks arrive on the MQTT transport thread.
 * Subscription management inside the publisher is thread safe, but the callbacks themselves
 * execute without additional locking. Operation calls are not additionally synchronized —
 * callers are responsible for thread safety of concurrent operation invocations.
 * Property storage is not guarded by a mutex; wrap with StructArrayFieldInterfaceThreadSafeDecorator
 * for concurrent access from multiple threads.
 */
class TEST_TB_STRUCT_ARRAY_EXPORT StructArrayFieldInterfaceClient : public IStructArrayFieldInterface, public ApiGear::MQTT::MqttBaseAdapter
{
public:
    explicit StructArrayFieldInterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client);
    static std::shared_ptr<StructArrayFieldInterfaceClient> create(std::shared_ptr<ApiGear::MQTT::Client> client);
    /// Convenience factory. Unlike the NATS adapter, no post-construction init() is needed
    /// because MqttBaseAdapter subscribes topics eagerly in the constructor.
    virtual ~StructArrayFieldInterfaceClient() override;
    const StructWithArrayOfStructs& getPropStructArray() const override;
    void setPropStructArray(const StructWithArrayOfStructs& propStructArray) override;
    const StructWithArrayOfEnums& getPropEnumArray() const override;
    void setPropEnumArray(const StructWithArrayOfEnums& propEnumArray) override;
    const StructWithArrayOfInts& getPropIntArray() const override;
    void setPropIntArray(const StructWithArrayOfInts& propIntArray) override;
    const MixedStruct& getPropMixed() const override;
    void setPropMixed(const MixedStruct& propMixed) override;
    MixedStruct funcMixed(const MixedStruct& paramMixed) override;
    std::future<MixedStruct> funcMixedAsync(const MixedStruct& paramMixed, std::function<void(MixedStruct)> callback = nullptr) override;
    StructWithArrayOfStructs funcStructArray(const StructWithArrayOfStructs& paramPoints) override;
    std::future<StructWithArrayOfStructs> funcStructArrayAsync(const StructWithArrayOfStructs& paramPoints, std::function<void(StructWithArrayOfStructs)> callback = nullptr) override;
    IStructArrayFieldInterfacePublisher& _getPublisher() const override;

    bool isReady() const;

    void onInvokeReply(const std::string& args, const std::string& correlationData);

    void onConnectionStatusChanged(bool connectionStatus);
private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap(const std::string&clientId);
    /// @brief sets the value for the property PropStructArray coming from the service
    /// @param args contains the param of the type StructWithArrayOfStructs
    void setPropStructArrayLocal(const std::string& args);
    /// @brief sets the value for the property PropEnumArray coming from the service
    /// @param args contains the param of the type StructWithArrayOfEnums
    void setPropEnumArrayLocal(const std::string& args);
    /// @brief sets the value for the property PropIntArray coming from the service
    /// @param args contains the param of the type StructWithArrayOfInts
    void setPropIntArrayLocal(const std::string& args);
    /// @brief sets the value for the property PropMixed coming from the service
    /// @param args contains the param of the type MixedStruct
    void setPropMixedLocal(const std::string& args);
    /// @brief publishes the value for the signal SigMixed coming from the service
    /// @param args contains the param(s) of the type(s) const MixedStruct& paramMixed
    void onSigMixed(const std::string& args) const;
    /// @brief publishes the value for the signal SigStructArray coming from the service
    /// @param args contains the param(s) of the type(s) const StructWithArrayOfStructs& paramPoints
    void onSigStructArray(const std::string& args) const;

    bool m_isReady;
    /** Local storage for properties values. */
    StructArrayFieldInterfaceData m_data;
    std::shared_ptr<ApiGear::MQTT::Client> m_client;

    /** The publisher for StructArrayFieldInterface */
    std::unique_ptr<IStructArrayFieldInterfacePublisher> m_publisher;

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
} // namespace TbStructArray
} // namespace Test
