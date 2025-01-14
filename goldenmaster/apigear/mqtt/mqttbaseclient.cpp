#include <memory>
#include "mqttcommon.h"
#include "mqtttypes.h"
#include "mqttbaseclient.h"
#include "private/mqttcwrapper.h"

namespace ApiGear {
namespace MQTT {


MqttBaseClient::MqttBaseClient(const std::string& clientID)
{
    m_cwrapper = CWrapper::create(clientID);
}

MqttBaseClient::~MqttBaseClient() = default;

const std::string& MqttBaseClient::getClientId() const
{
    return m_cwrapper->getClientId();
}

int MqttBaseClient::subscribeToConnectionStatus(OnConnectionStatusChangedCallBackFunction callBack)
{
    return m_cwrapper->subscribeToConnectionStatus(callBack);
}

void MqttBaseClient::unsubscribeToConnectionStatus(int subscriptionID)
{
    return m_cwrapper->unsubscribeToConnectionStatus(subscriptionID);
}

void MqttBaseClient::connectToHost(const std::string& brokerURL)
{
    m_cwrapper->connectToHost(brokerURL);
}

void MqttBaseClient::disconnect() {
    m_cwrapper->disconnect();
}

bool MqttBaseClient::isConnected() const
{
    return m_cwrapper->isConnected();
}

void MqttBaseClient::subscribeTopic(const std::string& topic, CallbackFunction func, OnSubscriptionStatusChanged subscriptionCallback)
{
    m_cwrapper->subscribeTopic(topic, func, subscriptionCallback);
}

void MqttBaseClient::unsubscribeTopic(const std::string& topic)
{
    m_cwrapper->unsubscribeTopic(topic);
}

std::shared_ptr<CWrapper> MqttBaseClient::getCwrapper()
{
    return m_cwrapper;
}

}}
