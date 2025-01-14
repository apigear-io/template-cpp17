#pragma once

#include <memory>
#include "mqttcommon.h"
#include "mqtttypes.h"

namespace ApiGear {
namespace MQTT {

class CWrapper;

// Provides common functionality for  MQTT Client.
// This is base class for the client and service side network endpoint layer adapters.
class APIGEAR_MQTT_EXPORT MqttBaseClient
{
public:
    explicit MqttBaseClient(const std::string& clientID);
    virtual ~MqttBaseClient();

public:
    /**
    * Connects to the specified broker brokerURL
    * @param brokerURL The address of the broker
    */
    void connectToHost(const std::string& brokerURL);
    /**
    * Disconnects from the broker
    */
    void disconnect();
    /** Returns true if connected, false otherwise. */
    bool isConnected() const;

    // subscribe to be notified about connection changes
    int subscribeToConnectionStatus(OnConnectionStatusChangedCallBackFunction callBack);
    // unsubscribe from connection changes
    void unsubscribeToConnectionStatus(int subscriptionID);

    void subscribeTopic(const std::string& name, CallbackFunction func, OnSubscriptionStatusChanged subscriptionCallback);
    void unsubscribeTopic(const std::string& name);

    const std::string& getClientId() const;

protected:
    std::shared_ptr<CWrapper> getCwrapper();
private:
    std::shared_ptr<CWrapper> m_cwrapper;
};
} // namespace MQTT
} // namespace ApiGear
