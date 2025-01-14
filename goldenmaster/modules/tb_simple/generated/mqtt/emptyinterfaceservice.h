#pragma once

#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include "apigear/mqtt/mqttservice.h"
#include "apigear/mqtt/mqttbaseadapter.h"

namespace Test {
namespace TbSimple {
namespace MQTT {
class TEST_TB_SIMPLE_EXPORT EmptyInterfaceService : public IEmptyInterfaceSubscriber, public ApiGear::MQTT::MqttBaseAdapter
{
public:
    explicit EmptyInterfaceService(std::shared_ptr<IEmptyInterface> impl, std::shared_ptr<ApiGear::MQTT::Service> service);
    virtual ~EmptyInterfaceService() override;

private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap();

    void onConnectionStatusChanged(bool connectionStatus);

    std::shared_ptr<IEmptyInterface> m_impl;
    std::shared_ptr<ApiGear::MQTT::Service> m_service;
    // id for connection status registration
    int m_connectionStatusId;
};
} // namespace MQTT
} // namespace TbSimple
} // namespace Test
