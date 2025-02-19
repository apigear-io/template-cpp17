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

    void connect(std::string address, std::function<void(void)> connectionStateChangedCallback);

    void subscribe(std::string topic);
    void unsubscribe(std::string topic);
    void publish(std::string topic, std::string payload);
    ConnectionStatus getStatus();

    struct ConnectionCallbackContext
    {
        std::weak_ptr<CWrapper> object;
        std::function<void(uint64_t)> function;
    };

    void cleanSubscription(int64_t id);
private:
    struct NatsConnectionDeleter
    {
        void operator()(natsConnection* connection);
    };
    void handleConnectionStateChanged(uint64_t connection_id);

    std::unique_ptr<natsConnection, NatsConnectionDeleter> m_connection;
    natsSubscription* m_subscription = nullptr;
    ConnectionCallbackContext m_connectionHandlerContext;
    std::function<void(void)> m_connectionStateChangedCallback;

    explicit CWrapper();
};
} // namespace Nats
} // namespace ApiGear
