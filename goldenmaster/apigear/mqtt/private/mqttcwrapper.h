#pragma once

#include <queue>
#include <set>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <atomic>
#include <thread>
#include <condition_variable>
#include "nlohmann/json.hpp"
#pragma warning (push, 0)
#include "MQTTAsync.h"
#pragma warning(pop)
#include "mqtttypes.h"


namespace ApiGear {
namespace MQTT {

/**
 * @brief This a simple c++ wrapper for the c MQTT implementation
 * 
 * Since in MQTT there are only clients connected to a central broker,
 * the ApiGear service and client side use this class to connect to each other via the broker.
 */
class CWrapper : public std::enable_shared_from_this<CWrapper>
{
public:
    static std::shared_ptr<CWrapper> create(const std::string& clientID)
    {
        return std::shared_ptr<CWrapper>(new CWrapper(clientID));
    };
    virtual ~CWrapper();

    struct MqttClientDeleter
    {
        void operator()(MQTTAsync* cli);
    };
    std::shared_ptr<CWrapper> getPtr()
    {
        return shared_from_this();
    }
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

    void onConnected();
    void onDisconnected();
    void handleTextMessage(const Message& message);

    // subscribe to be notified about connection changes
    int subscribeToConnectionStatus(OnConnectionStatusChangedCallBackFunction callBack);
    // unsubscribe from connection changes
    void unsubscribeToConnectionStatus(int subscriptionID);

    // service interface
    void notifyPropertyChange(const std::string& name, const std::string& value);
    void notifySignal(const std::string& name, const std::string& args);
    void notifyInvokeResponse(const std::string& responseTopic, const std::string& value, const std::string& correlationData);

    // client interface
    void invokeRemote(const std::string& name, const std::string& responseTopic, const std::string& value, int responseId);
    void setRemoteProperty(const std::string& name, const std::string& value);

    void subscribeTopic(const std::string& name, CallbackFunction func);
    void unsubscribeTopic(const std::string& name);

    void onSubscribed(const std::string& name, CallbackFunction func);
    void onUnsubscribed(const std::string& name);

    void run();

    const std::string& getClientId() const { return m_clientID; }
private:
    explicit CWrapper(const std::string& clientID);

    void addNewSubscriptions();
    void removeOldSubscriptions();
    void unsubscribeAllTopics();
    void waitForPendingMessages();

    // after an unintentional disconnect we need to do the subscription again
    void resubscribeAllTopics();

    int sendMessage(const std::string& destinationName, const MQTTAsync_message* msg, MQTTAsync_responseOptions* response);

    /// @brief create an unique id for the connection status subscription
    /// @return unique id in the connection status subscription context
    int createUniqueConnectionStatusId();
private:
    std::condition_variable m_synchronizeSubscriptionChanges;
    std::mutex m_waitForSubscriptionChangesMutex;
    bool m_waitForSubscriptionChanges { true };

    std::unique_ptr<MQTTAsync, MqttClientDeleter> m_client;
    std::mutex m_queueMutex;
    std::string m_serverUrl;
    std::string m_clientID;
    std::thread m_mainMQTTThread;
    std::queue<std::string> m_queue;
    std::atomic<bool> m_disconnectRequested { false };
    std::atomic<bool> m_connected { false };
    std::mutex m_onConnectionStatusChangedCallbacksMutex;
    std::map<int, OnConnectionStatusChangedCallBackFunction> m_onConnectionStatusChangedCallbacks;
    std::mutex m_subscribedTopicsMutex;
    std::multimap<std::string, CallbackFunction> m_subscribedTopics;
    std::mutex m_toBeSubscribedTopicsMutex;
    std::multimap<std::string, CallbackFunction> m_toBeSubscribedTopics;
    std::mutex m_toBeUnsubscribedTopicsMutex;
    std::set<std::string> m_toBeUnsubscribedTopics;
};
} // namespace MQTT
} // namespace ApiGear
