#pragma once

#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"
#include "apigear/mqtt/mqttservice.h"
#include "apigear/mqtt/mqttbaseadapter.h"

namespace Test {
namespace Testbed2 {
namespace MQTT {
class TEST_TESTBED2_EXPORT ManyParamInterfaceService : public IManyParamInterfaceSubscriber, public ApiGear::MQTT::MqttBaseAdapter
{
public:
    explicit ManyParamInterfaceService(std::shared_ptr<IManyParamInterface> impl, std::shared_ptr<ApiGear::MQTT::Service> service);
    virtual ~ManyParamInterfaceService() override;

    // IManyParamInterfaceSubscriber interface
    void onSig1(int param1) override;
    void onSig2(int param1, int param2) override;
    void onSig3(int param1, int param2, int param3) override;
    void onSig4(int param1, int param2, int param3, int param4) override;

private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap();

    void onConnectionStatusChanged(bool connectionStatus);
    void onInvokeFunc1(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFunc2(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFunc3(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFunc4(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onProp1Changed(int prop1) override;
    /// @brief requests to set the value for the property Prop1 coming from the client
    /// @param fields contains the param of the type int
    void onSetProp1(const std::string& args) const;
    void onProp2Changed(int prop2) override;
    /// @brief requests to set the value for the property Prop2 coming from the client
    /// @param fields contains the param of the type int
    void onSetProp2(const std::string& args) const;
    void onProp3Changed(int prop3) override;
    /// @brief requests to set the value for the property Prop3 coming from the client
    /// @param fields contains the param of the type int
    void onSetProp3(const std::string& args) const;
    void onProp4Changed(int prop4) override;
    /// @brief requests to set the value for the property Prop4 coming from the client
    /// @param fields contains the param of the type int
    void onSetProp4(const std::string& args) const;

    std::shared_ptr<IManyParamInterface> m_impl;
    std::shared_ptr<ApiGear::MQTT::Service> m_service;
    // id for connection status registration
    int m_connectionStatusId;
};
} // namespace MQTT
} // namespace Testbed2
} // namespace Test
