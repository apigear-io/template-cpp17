#include "mqttcppclient.h"
#include "private/mqttcwrapper.h"

using namespace ApiGear::MQTT;

Client::Client(const std::string& clientID)
{
    m_cwrapper = std::make_unique<CWrapper>(clientID);
}

Client::~Client() = default;

const std::string& Client::getClientId() const
{
    return m_cwrapper->getClientId();
}

int Client::subscribeToConnectionStatus(OnConnectionStatusChangedCallBackFunction callBack)
{
    return m_cwrapper->subscribeToConnectionStatus(callBack);
}

void Client::unsubscribeToConnectionStatus(int subscriptionID)
{
    return m_cwrapper->unsubscribeToConnectionStatus(subscriptionID);
}

void Client::connectToHost(const std::string& brokerURL)
{
    m_cwrapper->connectToHost(brokerURL);
}

void Client::disconnect() {
    m_cwrapper->disconnect();
}

void Client::invokeRemote(const Topic& topic, const std::string& value, InvokeReplyFunc func)
{
    m_cwrapper->invokeRemote(topic, value, func);
}

void Client::notifyPropertyChange(const Topic& topic, const std::string& value)
{
    m_cwrapper->notifyPropertyChange(topic, value);
}

void Client::notifySignal(const Topic& topic, const std::string& args)
{
    m_cwrapper->notifySignal(topic, args);
}

void Client::notifyInvokeResponse(const Topic& responseTopic, const std::string& value, const std::string& correlationData)
{
    m_cwrapper->notifyInvokeResponse(responseTopic, value, correlationData);
}

void Client::setRemoteProperty(const Topic& topic, const std::string& value)
{
	m_cwrapper->setRemoteProperty(topic, value);
}

void Client::subscribeTopic(const Topic& topic, ISink* sink)
{
    m_cwrapper->subscribeTopic(topic, sink);
}

void Client::confirmSubscription(const Topic& topic, ISink& sink)
{
    m_cwrapper->confirmSubscription(topic, sink);
}

void Client::removeSubscription(const Topic& topic)
{
    m_cwrapper->removeSubscription(topic);
}

void Client::unsubscribeTopic(const Topic& topic, ISink* sink)
{
    m_cwrapper->unsubscribeTopic(topic, sink);
}
