#pragma once

#include "apigear/nats/natsbase.h"
#include "apigear/nats/natstypes.h"
#include "apigear/utilities/single_pub.hpp"

#include <future>
#include <functional>
#include <unordered_map>
#include <string>
#include <memory>

namespace ApiGear {
namespace Nats {
class APIGEAR_NATS_EXPORT BaseAdapter
{
public:
    explicit BaseAdapter(std::shared_ptr<Base> client);
    virtual ~BaseAdapter();

    unsigned long _subscribeForIsReady(std::function<void(bool)> sub_function);
    void _unsubscribeFromIsReady(unsigned long id);
    bool _is_ready();

protected:
    void subscribeTopic(const std::string& topic, SimpleOnMessageCallback callback);
    void subscribeRequest(const std::string& topic, MessageCallbackWithResult callback);
    void init(std::function<void(void)> onConnectedCallback);

private:
    std::shared_ptr<Base> m_client;
    void unsubscribeTopics();
    void onSubscribed(int64_t id, const std::string& topic, bool is_subscribed);
    bool isAlreadyAdded(const std::string& topic);
  
    ApiGear::Utilities::SinglePub<bool, std::function<void(bool)> > _is_readyChanges;
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
    std::unordered_map<std::string, SubscriptionInfo> m_subscribedTopics;
    std::shared_ptr<bool> m_isAlive;

};
} // namespace Nats
} // namespace ApiGear
