#pragma once

#include <memory>
#include "nlohmann/json.hpp"
#include "mqttcommon.h"
#include "mqtttypes.h"
#include "mqttbaseclient.h"

namespace ApiGear {
namespace MQTT {

class APIGEAR_MQTT_EXPORT Client : public MqttBaseClient
{
public:
    explicit Client(const std::string& clientID);
    virtual ~Client();

    void invokeRemote(const std::string& name, const std::string& responseTopic, const std::string& value, int responseId);
    void setRemoteProperty(const std::string& name, const std::string& value);

private:
    class std::shared_ptr<CWrapper> m_cwrapper;
};
} // namespace MQTT
} // namespace ApiGear
