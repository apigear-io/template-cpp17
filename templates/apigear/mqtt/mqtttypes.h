#pragma once

#include "mqttcommon.h"
#include "nlohmann/json.hpp"
#include <functional>

namespace ApiGear {
namespace MQTT {

typedef std::function<void(const std::string& args, const std::string& responseTopic, const std::string& correlationData)> CallbackFunction;
typedef std::function<void(bool connectionStatus)> OnConnectionStatusChangedCallBackFunction;

class APIGEAR_MQTT_EXPORT InvokeReplyArg {
public:
    nlohmann::json value;
};

typedef std::function<void(InvokeReplyArg)> InvokeReplyFunc;

class APIGEAR_MQTT_EXPORT Message {
public:
    std::string topic {""};
    std::string content {""}; //optional
    std::string responseTopic {""}; //optional
    std::string correlationData {""}; //optional
};

} // namespace MQTT
} // namespace ApiGear
