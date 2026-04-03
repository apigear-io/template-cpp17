#pragma once

#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"
#include "apigear/mqtt/mqttservice.h"
#include "apigear/mqtt/mqttbaseadapter.h"

namespace Test {
namespace Testbed1 {
namespace MQTT {
class TEST_TESTBED1_EXPORT StructArray2InterfaceService : public IStructArray2InterfaceSubscriber, public ApiGear::MQTT::MqttBaseAdapter
{
public:
    explicit StructArray2InterfaceService(std::shared_ptr<IStructArray2Interface> impl, std::shared_ptr<ApiGear::MQTT::Service> service);
    virtual ~StructArray2InterfaceService() override;

    // IStructArray2InterfaceSubscriber interface
    void onSigBool(const StructBoolWithArray& paramBool) override;
    void onSigInt(const StructIntWithArray& paramInt) override;
    void onSigFloat(const StructFloatWithArray& paramFloat) override;
    void onSigString(const StructStringWithArray& paramString) override;

private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap();

    void onConnectionStatusChanged(bool connectionStatus);
    void onInvokeFuncBool(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncInt(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncFloat(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncString(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncEnum(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onPropBoolChanged(const StructBoolWithArray& propBool) override;
    /// @brief requests to set the value for the property PropBool coming from the client
    /// @param fields contains the param of the type StructBoolWithArray
    void onSetPropBool(const std::string& args) const;
    void onPropIntChanged(const StructIntWithArray& propInt) override;
    /// @brief requests to set the value for the property PropInt coming from the client
    /// @param fields contains the param of the type StructIntWithArray
    void onSetPropInt(const std::string& args) const;
    void onPropFloatChanged(const StructFloatWithArray& propFloat) override;
    /// @brief requests to set the value for the property PropFloat coming from the client
    /// @param fields contains the param of the type StructFloatWithArray
    void onSetPropFloat(const std::string& args) const;
    void onPropStringChanged(const StructStringWithArray& propString) override;
    /// @brief requests to set the value for the property PropString coming from the client
    /// @param fields contains the param of the type StructStringWithArray
    void onSetPropString(const std::string& args) const;
    void onPropEnumChanged(const StructEnumWithArray& propEnum) override;
    /// @brief requests to set the value for the property PropEnum coming from the client
    /// @param fields contains the param of the type StructEnumWithArray
    void onSetPropEnum(const std::string& args) const;

    std::shared_ptr<IStructArray2Interface> m_impl;
    std::shared_ptr<ApiGear::MQTT::Service> m_service;
    // id for connection status registration
    int m_connectionStatusId;
};
} // namespace MQTT
} // namespace Testbed1
} // namespace Test
