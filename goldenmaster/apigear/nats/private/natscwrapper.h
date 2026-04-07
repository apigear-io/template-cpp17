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

    void connect(const std::string& address, std::function<void(void)> connectionStateChangedCallback, bool sendAsap);
    uint64_t getId() const;
    void disconnect(bool graceful = true);
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

    struct CallbackContext
    {
        std::mutex mutex;
        std::weak_ptr<CWrapper> owner;
        std::function<void(void)> connectionStateChangedCallback;
        bool closed = false;
        std::condition_variable closedCV;
    };

private:
    struct NatsConnectionDeleter
    {
        void operator()(natsConnection* connection);
    };

    void cleanSubscription(int64_t id);

    std::mutex m_simpleCallbacksMutex;
    std::mutex m_requestCallbacksMutex;
    // Container that does not reallocate.
    std::list<std::shared_ptr<SimpleCallbackWrapper>> m_simpleCallbacks;
    std::list<std::shared_ptr<MessageCallbackWithResultWrapper>> m_requestCallbacks;
    std::unique_ptr<natsConnection, NatsConnectionDeleter> m_connection;
    mutable std::mutex m_connectionMutex;

    // Container that does not reallocate.
    std::unordered_map<uint64_t, std::shared_ptr<natsSubscription>> m_subscriptions;
    std::mutex m_subscriptionsMutex;

    std::shared_ptr<CallbackContext> m_callbackContext;

    explicit CWrapper();
};
} // namespace Nats
} // namespace ApiGear
