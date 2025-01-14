#pragma once

#include "tb_same1/generated/api/tb_same1.h"
#include "tb_same1/generated/api/common.h"
#include "apigear/mqtt/mqttservice.h"
#include "apigear/mqtt/mqttbaseadapter.h"

namespace Test {
namespace TbSame1 {
namespace MQTT {
class TEST_TB_SAME1_EXPORT SameStruct1InterfaceService : public ISameStruct1InterfaceSubscriber, public ApiGear::MQTT::MqttBaseAdapter
{
public:
    explicit SameStruct1InterfaceService(std::shared_ptr<ISameStruct1Interface> impl, std::shared_ptr<ApiGear::MQTT::Service> service);
    virtual ~SameStruct1InterfaceService() override;

    // ISameStruct1InterfaceSubscriber interface
    void onSig1(const Struct1& param1) override;

private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap();

    void onConnectionStatusChanged(bool connectionStatus);
    void onInvokeFunc1(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onProp1Changed(const Struct1& prop1) override;
    /// @brief requests to set the value for the property Prop1 coming from the client
    /// @param fields contains the param of the type Struct1
    void onSetProp1(const std::string& args) const;

    std::shared_ptr<ISameStruct1Interface> m_impl;
    std::shared_ptr<ApiGear::MQTT::Service> m_service;
    // id for connection status registration
    int m_connectionStatusId;
};
} // namespace MQTT
} // namespace TbSame1
} // namespace Test
