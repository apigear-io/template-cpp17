#include "mqttservice.h"
#include "private/mqttcwrapper.h"

using namespace ApiGear::MQTT;

Service::Service(const std::string& clientID)
    :MqttBaseClient(clientID),
    m_cwrapper(getCwrapper())
{
}

Service::~Service() = default;

void Service::notifyPropertyChange(const std::string& topic, const std::string& value)
{
    m_cwrapper->notifyPropertyChange(topic, value);
}

void Service::notifySignal(const std::string& topic, const std::string& args)
{
    m_cwrapper->notifySignal(topic, args);
}

void Service::notifyInvokeResponse(const std::string& responseTopic, const std::string& value, const std::string& correlationData)
{
    m_cwrapper->notifyInvokeResponse(responseTopic, value, correlationData);
}
