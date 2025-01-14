#pragma once

#include "tb_names/generated/api/tb_names.h"
#include "tb_names/generated/api/common.h"
#include "apigear/mqtt/mqttservice.h"
#include "apigear/mqtt/mqttbaseadapter.h"

namespace Test {
namespace TbNames {
namespace MQTT {
class TEST_TB_NAMES_EXPORT Nam_EsService : public INamEsSubscriber, public ApiGear::MQTT::MqttBaseAdapter
{
public:
    explicit Nam_EsService(std::shared_ptr<INamEs> impl, std::shared_ptr<ApiGear::MQTT::Service> service);
    virtual ~Nam_EsService() override;

    // INamEsSubscriber interface
    void onSomeSignal(bool SOME_PARAM) override;
    void onSomeSignal2(bool Some_Param) override;

private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap();

    void onConnectionStatusChanged(bool connectionStatus);
    void onInvokeSomeFunction(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeSomeFunction2(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onSwitchChanged(bool Switch) override;
    /// @brief requests to set the value for the property Switch coming from the client
    /// @param fields contains the param of the type bool
    void onSetSwitch(const std::string& args) const;
    void onSomePropertyChanged(int SOME_PROPERTY) override;
    /// @brief requests to set the value for the property SomeProperty coming from the client
    /// @param fields contains the param of the type int
    void onSetSomeProperty(const std::string& args) const;
    void onSomePoperty2Changed(int Some_Poperty2) override;
    /// @brief requests to set the value for the property SomePoperty2 coming from the client
    /// @param fields contains the param of the type int
    void onSetSomePoperty2(const std::string& args) const;

    std::shared_ptr<INamEs> m_impl;
    std::shared_ptr<ApiGear::MQTT::Service> m_service;
    // id for connection status registration
    int m_connectionStatusId;
};
} // namespace MQTT
} // namespace TbNames
} // namespace Test
