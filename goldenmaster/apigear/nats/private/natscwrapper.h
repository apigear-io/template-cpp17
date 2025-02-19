#pragma once

#include <queue>
#include <set>
#include <unordered_map>
#include <memory>
#include <mutex>
#include <string>
#include <atomic>
#include <list>
#include <thread>
#include <condition_variable>
#include "natstypes.h"
#include "nlohmann/json.hpp"
#pragma warning (push, 0)
#include <nats/nats.h>
#pragma warning(pop)


namespace ApiGear {
namespace Nats {

/**
 * @brief This a simple c++ wrapper for the c Nats implementation
 * 
 * Since in Nats there are only clients connected to a central broker,
 * the ApiGear service and client side use this class to connect to each other via the broker.
 */
class CWrapper : public std::enable_shared_from_this<CWrapper>
{
public:
    static std::shared_ptr<CWrapper> create()
    {
        return std::shared_ptr<CWrapper>(new CWrapper());
    };
    virtual ~CWrapper();

    std::shared_ptr<CWrapper> getPtr()
    {
        return shared_from_this();
    }

    void connect(const std::string& address, std::function<void(void)> connectionStateChangedCallback);
    uint64_t getId() const;
    void disconnect();
    int64_t subscribe(const std::string& topic, SimpleOnMessageCallback callback, SubscriptionClosedCallback onSubscriptionClosedCallback);
    int64_t subscribeWithResponse(const std::string& topic, MessageCallbackWithResult callback, SubscriptionClosedCallback onSubscriptionClosedCallback);
    void unsubscribe(int64_t id);
    void publish(const std::string& topic, const std::string& payload);
    std::string request(const std::string& topic, const std::string& payload);
    void flush();
    ConnectionStatus getStatus();

    struct SimpleCallbackWrapper
    {
        SimpleCallbackWrapper(SimpleOnMessageCallback cb)
            :callback(cb)
        {
        }
        int64_t id = -1;
        SimpleOnMessageCallback callback;
    };

    struct MessageCallbackWithResultWrapper
    {
        MessageCallbackWithResultWrapper(MessageCallbackWithResult cb)
            :callback(cb)
        {
        }
        int64_t id = -1;
        MessageCallbackWithResult callback;
    };
    struct ConnectionCallbackContext
    {
        std::weak_ptr<CWrapper> object;
        std::function<void(uint64_t)> function;
    };

    struct SubscriptionErrorContext {
        std::weak_ptr<CWrapper> object;
        std::function<void(uint64_t, int64_t, int)> function;
    };

private:
    struct NatsConnectionDeleter
    {
        void operator()(natsConnection* connection);
    };

    void handleConnectionStateChanged(uint64_t connection_id);
    void cleanSubscription(int64_t id);
    void handleSubscriptionError(uint64_t connection_id, int64_t subscription_id, int status);

    std::mutex m_simpleCallbacksMutex;
    std::mutex m_requestCallbacksMutex;
    // Container that does not reallocate.
    std::list<std::shared_ptr<SimpleCallbackWrapper>> m_simpleCallbacks;
    std::list<std::shared_ptr<MessageCallbackWithResultWrapper>> m_requestCallbacks;
    std::unique_ptr<natsConnection, NatsConnectionDeleter> m_connection;

    // Container that does not reallocate.
    std::unordered_map<uint64_t, std::shared_ptr<natsSubscription>> m_subscriptions;
    std::mutex m_subscriptionsMutex;

    ConnectionCallbackContext m_connectionHandlerContext;
    std::function<void(void)> m_connectionStateChangedCallback;
    SubscriptionErrorContext m_subscriptionErrorContext;

    explicit CWrapper();
};
} // namespace Nats
} // namespace ApiGear
