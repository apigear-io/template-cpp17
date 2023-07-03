#pragma once

#include "tb_same2/generated/api/tb_same2.h"
#include "tb_same2/generated/api/common.h"
#include "apigear/mqtt/mqttservice.h"

namespace Test {
namespace TbSame2 {
namespace MQTT {
class TEST_TB_SAME2_EXPORT SameEnum1InterfaceService : public ISameEnum1InterfaceSubscriber
{
public:
    explicit SameEnum1InterfaceService(std::shared_ptr<ISameEnum1Interface> impl, std::shared_ptr<ApiGear::MQTT::Service> service);
    virtual ~SameEnum1InterfaceService() override;

    void onConnectionStatusChanged(bool connectionStatus);

    void onInvoke(const ApiGear::MQTT::Topic& topic, const std::string& args, const ApiGear::MQTT::Topic& responseTopic, const std::string& correlationData);

    // ISameEnum1InterfaceSubscriber interface
    void onSig1(Enum1Enum param1) override;
    void onProp1Changed(Enum1Enum prop1) override;

private:
    std::shared_ptr<ISameEnum1Interface> m_impl;
    std::shared_ptr<ApiGear::MQTT::Service> m_service;
    // id for connection status registration
    int m_connectionStatusRegistrationID;
};
} // namespace MQTT
} // namespace TbSame2
} // namespace Test