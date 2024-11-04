#pragma once

#include <queue>
#include <set>
#include <map>
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
#include <nats.h>
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
    struct ConnectionCallbackContext
    {
        std::function<void(void)> function;
    };

    static std::shared_ptr<CWrapper> create()
    {
        return std::shared_ptr<CWrapper>(new CWrapper());
    };
    virtual ~CWrapper();


    std::shared_ptr<CWrapper> getPtr()
    {
        return shared_from_this();
    }

    void connect(std::string address, std::function<void(void)> connectionStateChangedCallback);

    int64_t subscribe(std::string topic, SimpleOnMessageCallback callback);
    void unsubscribe(int64_t id);
    void publish(std::string topic, std::string payload);
    ConnectionStatus getStatus();

private:
    struct NatsConnectionDeleter
    {
        void operator()(natsConnection* connection);
    };

    std::unique_ptr<natsConnection, NatsConnectionDeleter> m_connection;
    std::list<std::shared_ptr<natsSubscription>> m_subscriptions;
    std::mutex m_subscriptionsMutex;
    ConnectionCallbackContext m_connectionStateChangedCallback;

    explicit CWrapper();
};
} // namespace Nats
} // namespace ApiGear
