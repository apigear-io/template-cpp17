#pragma once

#include <memory>
#include "mqttcommon.h"
#include "mqtttypes.h"
#include "mqttbaseclient.h"

namespace ApiGear {
namespace MQTT {

class APIGEAR_MQTT_EXPORT Service : public MqttBaseClient
{
public:
    explicit Service(const std::string& clientID);
    virtual ~Service();

    void notifyPropertyChange(const std::string& name, const std::string& value);
    void notifySignal(const std::string& name, const std::string& args);
    void notifyInvokeResponse(const std::string& responseTopic, const std::string& value, const std::string& correlationData);

private:
    class std::shared_ptr<CWrapper> m_cwrapper;
};
} // namespace MQTT
} // namespace ApiGear
