#pragma once

#include "natsbase.h"
#include "natstypes.h"
#include "apigear/utilities/single_pub.hpp"

#include <future>
#include <functional>
#include <unordered_map>
#include <string>
#include <memory>
#include <mutex>

namespace ApiGear {
namespace Nats {
class APIGEAR_NATS_EXPORT BaseAdapter
{
public:
    virtual ~BaseAdapter();

    unsigned long _subscribeForIsReady(std::function<void(bool)> sub_function);
    void _unsubscribeFromIsReady(unsigned long id);
    bool _is_ready() const;

protected:
    explicit BaseAdapter(std::shared_ptr<Base> client, uint32_t expectedSubscriptionCount);
    virtual std::shared_ptr<BaseAdapter> getSharedFromDerrived() = 0;
    void subscribeTopic(const std::string& topic, SimpleOnMessageCallback callback);
    void subscribeRequest(const std::string& topic, MessageCallbackWithResult callback);
    void init(std::function<void(void)> onConnectedCallback);

private:
    std::shared_ptr<Base> m_client;
    void unsubscribeTopics();
    void onSubscribed(int64_t id, const std::string& topic, bool is_subscribed);
    bool isAlreadyAdded(const std::string& topic);
  
    ApiGear::Utilities::SinglePub<bool> _is_readyChanges;
    struct SubscriptionInfo
    {
        SubscriptionInfo(){};
        SubscriptionInfo(ApiGear::Nats::SubscriptionStatus in_status)
        :status(in_status)
        {
        }
        SubscriptionInfo(ApiGear::Nats::SubscriptionStatus in_status, int64_t in_id)
        :status(in_status),
        id(in_id)
        {
        }
        ApiGear::Nats::SubscriptionStatus status = ApiGear::Nats::SubscriptionStatus::unsubscribed;
        int64_t id = ApiGear::Nats::Base::InvalidSubscriptionId;
    };

    std::mutex m_subscribedTopicsMutex;
    std::unordered_map<std::string, SubscriptionInfo> m_subscribedTopics;
    const uint32_t m_expectedSubscriptionsCount;
};
} // namespace Nats
} // namespace ApiGear
