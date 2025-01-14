#pragma once

#include "mqttbaseclient.h"
#include "mqtttypes.h"
#include "apigear/utilities/single_pub.hpp"

#include <future>
#include <functional>
#include <unordered_map>
#include <map>
#include <string>
#include <memory>
#include <mutex>

namespace ApiGear {
namespace MQTT {

// This class handles subscriptions for topic given in constructor.
// It subscribes them and tracks their state, notifying all the clients 
// when it has all subscriptions successfully subscribed (use _subscribeForIsReady to get notification) 
// or unsubscribed (use _subscribeForIsUnsubscribed to get notification). 
class APIGEAR_MQTT_EXPORT MqttBaseAdapter
{
public:
    explicit MqttBaseAdapter(std::shared_ptr<MqttBaseClient> client, const std::map<std::string, CallbackFunction> topics);
    virtual ~MqttBaseAdapter();

    unsigned long _subscribeForIsReady(std::function<void(bool)> sub_function);
    void _unsubscribeFromIsReady(unsigned long id);
    bool _is_ready() const;
    unsigned long _subscribeForIsUnsubscribed(std::function<void(bool)> sub_function);
    void _unsubscribeFromIsUnsubscribed(unsigned long id);
    bool _isUnsubscribed() const;

private:
    void subscribeTopic(const std::string& topic, CallbackFunction callback);
    std::shared_ptr<MqttBaseClient> m_client;
    void unsubscribeTopics();
    void onSubscribed(const std::string& topic, bool is_subscribed);
    bool isAlreadyAdded(const std::string& topic);
  
    ApiGear::Utilities::SinglePub<bool> _is_readyChanges;
    ApiGear::Utilities::SinglePub<bool> _is_unsubscribed;
    int onConnectionChangedId;
    std::mutex m_subscribedTopicsMutex;
    std::unordered_map<std::string, SubscriptionStatus> m_subscribedTopics;
};
} // namespace MQTT
} // namespace ApiGear
