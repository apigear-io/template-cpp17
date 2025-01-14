#pragma once

#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"
#include "apigear/mqtt/mqttservice.h"
#include "apigear/mqtt/mqttbaseadapter.h"

namespace Test {
namespace Testbed1 {
namespace MQTT {
class TEST_TESTBED1_EXPORT StructInterfaceService : public IStructInterfaceSubscriber, public ApiGear::MQTT::MqttBaseAdapter
{
public:
    explicit StructInterfaceService(std::shared_ptr<IStructInterface> impl, std::shared_ptr<ApiGear::MQTT::Service> service);
    virtual ~StructInterfaceService() override;

    // IStructInterfaceSubscriber interface
    void onSigBool(const StructBool& paramBool) override;
    void onSigInt(const StructInt& paramInt) override;
    void onSigFloat(const StructFloat& paramFloat) override;
    void onSigString(const StructString& paramString) override;

private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap();

    void onConnectionStatusChanged(bool connectionStatus);
    void onInvokeFuncBool(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncInt(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncFloat(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFuncString(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onPropBoolChanged(const StructBool& propBool) override;
    /// @brief requests to set the value for the property PropBool coming from the client
    /// @param fields contains the param of the type StructBool
    void onSetPropBool(const std::string& args) const;
    void onPropIntChanged(const StructInt& propInt) override;
    /// @brief requests to set the value for the property PropInt coming from the client
    /// @param fields contains the param of the type StructInt
    void onSetPropInt(const std::string& args) const;
    void onPropFloatChanged(const StructFloat& propFloat) override;
    /// @brief requests to set the value for the property PropFloat coming from the client
    /// @param fields contains the param of the type StructFloat
    void onSetPropFloat(const std::string& args) const;
    void onPropStringChanged(const StructString& propString) override;
    /// @brief requests to set the value for the property PropString coming from the client
    /// @param fields contains the param of the type StructString
    void onSetPropString(const std::string& args) const;

    std::shared_ptr<IStructInterface> m_impl;
    std::shared_ptr<ApiGear::MQTT::Service> m_service;
    // id for connection status registration
    int m_connectionStatusId;
};
} // namespace MQTT
} // namespace Testbed1
} // namespace Test
