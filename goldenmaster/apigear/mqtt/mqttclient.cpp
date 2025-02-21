#include "mqttclient.h"
#include "private/mqttcwrapper.h"

using namespace ApiGear::MQTT;

Client::Client(const std::string& clientID)
    :MqttBaseClient(clientID),
     m_cwrapper(getCwrapper())
{
}

Client::~Client() = default;

void Client::invokeRemote(const std::string& topic, const std::string& responseTopic, const std::string& value, int responseId)
{
    m_cwrapper->invokeRemote(topic, responseTopic, value, responseId);
}

void Client::setRemoteProperty(const std::string& topic, const std::string& value)
{
	m_cwrapper->setRemoteProperty(topic, value);
}
