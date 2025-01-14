#include "mqttbaseadapter.h"
#include "utilities/logger.h"

using namespace ApiGear::MQTT;

MqttBaseAdapter::MqttBaseAdapter(std::shared_ptr<MqttBaseClient> client, const std::map<std::string, ApiGear::MQTT::CallbackFunction> topics)
    : m_client(client)
{
    auto onConnectedCallback = [this, topics]()
        {
            for (auto topic : topics)
            {
                subscribeTopic(topic.first, topic.second);
            }
        };

    for (auto topic : topics)
    {
        m_subscribedTopics[topic.first] = ApiGear::MQTT::SubscriptionStatus::unsubscribed;
    }
    
    if (m_client->isConnected())
    {
        onConnectedCallback();
    }

    onConnectionChangedId = m_client->subscribeToConnectionStatus([this, onConnectedCallback](bool is_connected)
        {
            if (is_connected)
            {
                onConnectedCallback();
                if (_is_ready())
                {
                    _is_readyChanges.publishChange(true);
                }
            }
            else
            {
                _is_readyChanges.publishChange(false);
            }
        });
}

MqttBaseAdapter::~MqttBaseAdapter()
{
    unsubscribeTopics();
    m_client->unsubscribeToConnectionStatus(onConnectionChangedId);
}

void MqttBaseAdapter::subscribeTopic(const std::string& topic, CallbackFunction callback)
{
    if (!isAlreadyAdded(topic))
    {
        m_client->subscribeTopic(topic, callback, [this](const std::string& topic, bool is_subscribed) { onSubscribed(topic, is_subscribed); });
    }
}

bool MqttBaseAdapter::isAlreadyAdded(const std::string& topic)
{
    std::unique_lock<std::mutex> lock{ m_subscribedTopicsMutex };
    auto already_added = m_subscribedTopics.find(topic);
    lock.unlock();
    return already_added != m_subscribedTopics.end() &&
        (already_added->second == ApiGear::MQTT::SubscriptionStatus::subscribed ||
            already_added->second == ApiGear::MQTT::SubscriptionStatus::subscribing);
}

void MqttBaseAdapter::unsubscribeTopics()
{
    std::vector<std::string> to_unsubscribe;
    std::unique_lock<std::mutex> lock{ m_subscribedTopicsMutex };
    for (auto topic : m_subscribedTopics)
    {
        if (topic.second == ApiGear::MQTT::SubscriptionStatus::subscribed)
        {
            topic.second = ApiGear::MQTT::SubscriptionStatus::unsubscribing;
            to_unsubscribe.push_back(topic.first);
        }
        else if (topic.second != ApiGear::MQTT::SubscriptionStatus::subscribing)
        {
            topic.second = ApiGear::MQTT::SubscriptionStatus::to_unsubscribe;
        }
    }
    for (auto topic : to_unsubscribe)
    {
        m_client->unsubscribeTopic(topic);
    }
}

void MqttBaseAdapter::onSubscribed(const std::string& topic, bool is_subscribed)
{
    std::unique_lock<std::mutex> lock{ m_subscribedTopicsMutex };
    auto subscription = m_subscribedTopics.find(topic);
    if (is_subscribed)
    {
        if (subscription != m_subscribedTopics.end() && subscription->second == ApiGear::MQTT::SubscriptionStatus::to_unsubscribe)
        {
            m_subscribedTopics[topic] = ApiGear::MQTT::SubscriptionStatus::unsubscribing;
            lock.unlock();
            m_client->unsubscribeTopic(topic);
            return;
        }
        else
        {
            m_subscribedTopics[topic] = ApiGear::MQTT::SubscriptionStatus::subscribed;
        }
        bool isReady = _is_ready();
        lock.unlock();
        if (isReady)
        {
            _is_readyChanges.publishChange(true);
        }
    }
    else
    {
        if (subscription != m_subscribedTopics.end())
        {
            subscription->second = ApiGear::MQTT::SubscriptionStatus::unsubscribed;
        }
        if (_isUnsubscribed())
        {
            _is_unsubscribed.publishChange(true);
        }
    }
}

unsigned long MqttBaseAdapter::_subscribeForIsReady(std::function<void(bool)> sub_function)
{
    auto id = _is_readyChanges.subscribeForChange(sub_function);
    if (_is_ready())
    {
        sub_function(true);
    }
    return id;
}

void MqttBaseAdapter::_unsubscribeFromIsReady(unsigned long id)
{
    _is_readyChanges.unsubscribeFromChange(id);
}

unsigned long MqttBaseAdapter::_subscribeForIsUnsubscribed(std::function<void(bool)> sub_function)
{
    auto id = _is_unsubscribed.subscribeForChange(sub_function);
    if (_isUnsubscribed())
    {
        sub_function(true);
    }
    return id;
}

void MqttBaseAdapter::_unsubscribeFromIsUnsubscribed(unsigned long id)
{
    _is_unsubscribed.unsubscribeFromChange(id);
}

bool MqttBaseAdapter::_isUnsubscribed() const
{
    return std::find_if(m_subscribedTopics.cbegin(),
        m_subscribedTopics.cend(),
        [](const auto& element) {return element.second != ApiGear::MQTT::SubscriptionStatus::unsubscribed; })
        == m_subscribedTopics.end();
}

bool MqttBaseAdapter::_is_ready() const
{
    auto still_not_all_subscribed = std::find_if(m_subscribedTopics.cbegin(),
        m_subscribedTopics.cend(),
        [](const auto& element) {return element.second != ApiGear::MQTT::SubscriptionStatus::subscribed; })
        != m_subscribedTopics.end();
    return m_client->isConnected() &&
        !still_not_all_subscribed;
}
