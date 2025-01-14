#pragma once

#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"
#include "apigear/mqtt/mqttservice.h"
#include "apigear/mqtt/mqttbaseadapter.h"

namespace Test {
namespace Testbed2 {
namespace MQTT {
class TEST_TESTBED2_EXPORT NestedStruct3InterfaceService : public INestedStruct3InterfaceSubscriber, public ApiGear::MQTT::MqttBaseAdapter
{
public:
    explicit NestedStruct3InterfaceService(std::shared_ptr<INestedStruct3Interface> impl, std::shared_ptr<ApiGear::MQTT::Service> service);
    virtual ~NestedStruct3InterfaceService() override;

    // INestedStruct3InterfaceSubscriber interface
    void onSig1(const NestedStruct1& param1) override;
    void onSig2(const NestedStruct1& param1, const NestedStruct2& param2) override;
    void onSig3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3) override;

private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap();

    void onConnectionStatusChanged(bool connectionStatus);
    void onInvokeFunc1(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFunc2(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeFunc3(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onProp1Changed(const NestedStruct1& prop1) override;
    /// @brief requests to set the value for the property Prop1 coming from the client
    /// @param fields contains the param of the type NestedStruct1
    void onSetProp1(const std::string& args) const;
    void onProp2Changed(const NestedStruct2& prop2) override;
    /// @brief requests to set the value for the property Prop2 coming from the client
    /// @param fields contains the param of the type NestedStruct2
    void onSetProp2(const std::string& args) const;
    void onProp3Changed(const NestedStruct3& prop3) override;
    /// @brief requests to set the value for the property Prop3 coming from the client
    /// @param fields contains the param of the type NestedStruct3
    void onSetProp3(const std::string& args) const;

    std::shared_ptr<INestedStruct3Interface> m_impl;
    std::shared_ptr<ApiGear::MQTT::Service> m_service;
    // id for connection status registration
    int m_connectionStatusId;
};
} // namespace MQTT
} // namespace Testbed2
} // namespace Test
