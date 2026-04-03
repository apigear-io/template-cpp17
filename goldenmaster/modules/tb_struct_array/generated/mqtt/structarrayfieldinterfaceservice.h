#pragma once

#include "tb_struct_array/generated/api/tb_struct_array.h"
#include "tb_struct_array/generated/api/common.h"
#include "apigear/mqtt/mqttservice.h"
#include "apigear/mqtt/mqttbaseadapter.h"

namespace Test {
namespace TbStructArray {
namespace MQTT {
class TEST_TB_STRUCT_ARRAY_EXPORT StructArrayFieldInterfaceService : public IStructArrayFieldInterfaceSubscriber, public ApiGear::MQTT::MqttBaseAdapter
{
public:
    explicit StructArrayFieldInterfaceService(std::shared_ptr<IStructArrayFieldInterface> impl, std::shared_ptr<ApiGear::MQTT::Service> service);
    virtual ~StructArrayFieldInterfaceService() override;

    // IStructArrayFieldInterfaceSubscriber interface
    void onSigMixed(const MixedStruct& paramMixed) override;
    void onSigStructArray(const StructWithArrayOfStructs& paramPoints) override;

private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap();

    void onConnectionStatusChanged(bool connectionStatus);
    void onInvokeFuncMixed(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncStructArray(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onPropStructArrayChanged(const StructWithArrayOfStructs& propStructArray) override;
    /// @brief requests to set the value for the property PropStructArray coming from the client
    /// @param fields contains the param of the type StructWithArrayOfStructs
    void onSetPropStructArray(const std::string& args) const;
    void onPropEnumArrayChanged(const StructWithArrayOfEnums& propEnumArray) override;
    /// @brief requests to set the value for the property PropEnumArray coming from the client
    /// @param fields contains the param of the type StructWithArrayOfEnums
    void onSetPropEnumArray(const std::string& args) const;
    void onPropIntArrayChanged(const StructWithArrayOfInts& propIntArray) override;
    /// @brief requests to set the value for the property PropIntArray coming from the client
    /// @param fields contains the param of the type StructWithArrayOfInts
    void onSetPropIntArray(const std::string& args) const;
    void onPropMixedChanged(const MixedStruct& propMixed) override;
    /// @brief requests to set the value for the property PropMixed coming from the client
    /// @param fields contains the param of the type MixedStruct
    void onSetPropMixed(const std::string& args) const;

    std::shared_ptr<IStructArrayFieldInterface> m_impl;
    std::shared_ptr<ApiGear::MQTT::Service> m_service;
    // id for connection status registration
    int m_connectionStatusId;
};
} // namespace MQTT
} // namespace TbStructArray
} // namespace Test
