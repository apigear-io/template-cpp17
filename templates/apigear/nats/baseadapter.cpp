#include "baseadapter.h"
#include "utilities/logger.h"

using namespace ApiGear::Nats;

BaseAdapter::BaseAdapter(std::shared_ptr<Base> client, uint32_t expectedSubscriptionsCount)
    : m_client(client)
    , m_expectedSubscriptionsCount(expectedSubscriptionsCount)
{
}

void BaseAdapter::init(std::function<void(void)> onConnectedCallback)
{
    if (m_client->isConnected())
    {
        onConnectedCallback();
    }
    else
    {
        std::weak_ptr<BaseAdapter> weak_adapter = getSharedFromDerrived();
        m_client->addOnConnectedCallback([this, onConnectedCallback, weak_adapter](bool is_connected)
            {
                if (weak_adapter.expired())
                {
                    return;
                }
                auto locked = weak_adapter.lock();
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
                    // In this case the nats client will clean up all the subscriptions.
                    _is_readyChanges.publishChange(false);
                    std::unique_lock<std::mutex> lock{ m_subscribedTopicsMutex };
                    for (auto topic : m_subscribedTopics)
                    {
                        topic.second.status = ApiGear::Nats::SubscriptionStatus::unsubscribed;
                    }
                    lock.unlock();
                }
            });
    }
}

BaseAdapter::~BaseAdapter()
{
    unsubscribeTopics();
}

void BaseAdapter::subscribeTopic(const std::string& topic, SimpleOnMessageCallback callback)
{
    std::weak_ptr<BaseAdapter> weak_adapter = getSharedFromDerrived();
    std::shared_ptr<Base> client = m_client;
    auto safeOnSubscribed = [weak_adapter, client, this](int64_t id, const std::string& topic, bool is_subscribed)
        {
            if (!weak_adapter.expired())
            {
                auto adapter = weak_adapter.lock();
                onSubscribed(id, topic, is_subscribed);
            }
            else if (is_subscribed)
            {
                client->unsubscribe(id);
            }
        };
    if (!isAlreadyAdded(topic))
    {
        m_client->subscribe(topic, callback, safeOnSubscribed);
    }
}

void BaseAdapter::subscribeRequest(const std::string& topic, MessageCallbackWithResult callback)
{
    std::weak_ptr<BaseAdapter> weak_adapter = getSharedFromDerrived();
    std::shared_ptr<Base> client = m_client;
    auto safeOnSubscribed = [weak_adapter, client, this](int64_t id, const std::string& topic, bool is_subscribed)
        {
            if (!weak_adapter.expired())
            {
                auto adapter = weak_adapter.lock();
                onSubscribed(id, topic, is_subscribed);
            }
            else if (is_subscribed)
            {
                client->unsubscribe(id);
            }
        };
    if (!isAlreadyAdded(topic))
    {
        m_client->subscribeForRequest(topic, callback, safeOnSubscribed);
    }
}

bool BaseAdapter::isAlreadyAdded(const std::string& topic)
{
    std::unique_lock<std::mutex> lock{m_subscribedTopicsMutex};
    auto already_added = m_subscribedTopics.find(topic);
    lock.unlock();
    return already_added != m_subscribedTopics.end() &&
        (already_added->second.status == ApiGear::Nats::SubscriptionStatus::subscribed ||
            already_added->second.status == ApiGear::Nats::SubscriptionStatus::subscribing);
}

void BaseAdapter::unsubscribeTopics()
{
    std::vector<int64_t> ids_to_unsubscribe;
    std::unique_lock<std::mutex> lock{ m_subscribedTopicsMutex };
    for (auto topic : m_subscribedTopics)
    {
        if (topic.second.status == ApiGear::Nats::SubscriptionStatus::subscribed)
        {
            topic.second.status = ApiGear::Nats::SubscriptionStatus::unsubscribing;
            ids_to_unsubscribe.push_back(topic.second.id);
        }
        else if (topic.second.status != ApiGear::Nats::SubscriptionStatus::subscribing)
        {
            topic.second.status = ApiGear::Nats::SubscriptionStatus::to_unsubscribe;
        }
    }
    for (auto id : ids_to_unsubscribe)
    {
        m_client->unsubscribe(id);
    }
}

void BaseAdapter::onSubscribed(int64_t id, const std::string& topic, bool is_subscribed)
{
    std::unique_lock<std::mutex> lock{ m_subscribedTopicsMutex };
    auto subscription = m_subscribedTopics.find(topic);
    if (is_subscribed)
    {
        if (subscription != m_subscribedTopics.end() && subscription->second.status == ApiGear::Nats::SubscriptionStatus::to_unsubscribe)
        {
            m_subscribedTopics[topic] = SubscriptionInfo(ApiGear::Nats::SubscriptionStatus::unsubscribing);
            lock.unlock();
            m_client->unsubscribe(id);
            return;
        }
        else
        {
            m_subscribedTopics[topic] = SubscriptionInfo(ApiGear::Nats::SubscriptionStatus::subscribed, id);
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
        if (id == ApiGear::Nats::Base::InvalidSubscriptionId)
        {
            AG_LOG_ERROR("failed to unsubscribe " + topic);
        }
        if (subscription != m_subscribedTopics.end())
        {
            subscription->second.status = ApiGear::Nats::SubscriptionStatus::unsubscribed;
            subscription->second.id = ApiGear::Nats::Base::InvalidSubscriptionId;
        }
    }
}

unsigned long BaseAdapter::_subscribeForIsReady(std::function<void(bool)> sub_function)
{
    return _is_readyChanges.subscribeForChange(sub_function);
}

void BaseAdapter::_unsubscribeFromIsReady(unsigned long id)
{
    _is_readyChanges.unsubscribeFromChange(id);
}

bool BaseAdapter::_is_ready() const
{
    auto still_not_all_subscribed = std::find_if(m_subscribedTopics.cbegin(),
        m_subscribedTopics.cend(),
        [](const auto& element) {return element.second.status != ApiGear::Nats::SubscriptionStatus::subscribed; })
        != m_subscribedTopics.end();
    return m_client->isConnected() &&
        m_expectedSubscriptionsCount == m_subscribedTopics.size() &&
        !still_not_all_subscribed;
}
