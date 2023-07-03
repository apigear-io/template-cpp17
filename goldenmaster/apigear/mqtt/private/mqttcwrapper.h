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
#include "mqtttopic.h"
#include "mqtttypes.h"


namespace ApiGear {
namespace MQTT {

class ISink;

/**
 * @brief Describes incoming part of messages of the protocol for client side.
 * 
 * Since in MQTT there are only clients connected to a central broker,
 * the service and client side use this class to connect to each other via the broker.
 */
class CWrapper
{
public:
    explicit CWrapper(const std::string& clientID);
    virtual ~CWrapper();
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
    void notifyPropertyChange(const Topic& name, const std::string& value);
    void notifySignal(const Topic& name, const std::string& args);
    void notifyInvokeResponse(const Topic& responseTopic, const std::string& value, const std::string& correlationData);

    // client interface
    void invokeRemote(const Topic& name, const std::string& value, InvokeReplyFunc func=nullptr);
    void setRemoteProperty(const Topic& name, const std::string& value);
    void subscribeTopic(const Topic& name, CallbackFunction func);
    void unsubscribeTopic(const Topic& name, CallbackFunction func);

    void confirmSubscription(const Topic& name, CallbackFunction func);
    void removeSubscription(const Topic& name);
    
    void run();

    const std::string& getClientId() const { return m_clientID; }
private:
    void checkForNewSubscriptions();
    void checkForOldSubscriptions();
    void unsubscribeAllTopics();
    void waitForPendingMessages();

    int sendMessage(const std::string& destinationName, const MQTTAsync_message* msg, MQTTAsync_responseOptions* response);

private:
    std::condition_variable m_conditionVariable;
    std::mutex m_waitForWorkMutex;
    bool m_waitForWork { true };

    std::unique_ptr<MQTTAsync> m_client;
    std::mutex m_queueMutex;
    std::string m_serverUrl;
    std::string m_clientID;
    std::thread m_thread;
    std::queue<std::string> m_queue;
    std::atomic<bool> m_disconnectRequested { false };
    std::atomic<bool> m_connected { false };
    std::mutex m_onConnectionStatusChangedCallbacksMutex;
    std::map<int, OnConnectionStatusChangedCallBackFunction> m_onConnectionStatusChangedCallbacks;
    std::mutex m_invokeResultsMutex;
    std::map<int, InvokeReplyFunc> m_invokeResults;
    std::mutex m_subscribedTopicsMutex;
    std::multimap<Topic, CallbackFunction, Topic> m_subscribedTopics;
    std::mutex m_toBeSubscribedTopicsMutex;
    std::multimap<Topic, CallbackFunction, Topic> m_toBeSubscribedTopics;
    std::mutex m_toBeUnsubscribedTopicsMutex;
    std::multimap<Topic, CallbackFunction, Topic> m_toBeUnsubscribedTopics;
};
} // namespace MQTT
} // namespace ApiGear