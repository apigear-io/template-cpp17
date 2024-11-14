#pragma once

#include <memory>
#include <string>
#include "nlohmann/json.hpp"
#include "natscommon.h"
#include "natstypes.h"
#include <mutex>
#include <atomic>
#include <future>

namespace ApiGear {

namespace Utilities {
    class ThreadPool;
}

namespace Nats {


class APIGEAR_NATS_EXPORT Base
{
public:

    explicit Base();
    virtual ~Base();

    static const int64_t InvalidSubscriptionId = 0;

    void connect(const std::string& address);
    void disconnect();
    void subscribe(const std::string& topic, SimpleOnMessageCallback callback, std::function<void(int64_t, std::string, bool)> subscribe_callback);
    void subscribeForRequest(const std::string& topic, MessageCallbackWithResult callback, std::function<void(int64_t, std::string, bool)> subscribe_callback);
    void unsubscribe(int64_t id);
    void publish(const std::string& topic, const std::string& payload);
    void request(const std::string& topic, const std::string& payload, SimpleOnMessageCallback responseHandler);

    uint32_t addOnConnectedCallback(OnConnectionStatusChangedCallBackFunction callback);
    void removeOnConnectedCallback(uint32_t id);
    bool isConnected() const;
private:
    bool onConnectedChanged();
    void handleConnectionState(bool state);
    std::mutex m_onConnectionStatusChangedCallbacksMutex;
    std::map<uint32_t, OnConnectionStatusChangedCallBackFunction> m_onConnectionStatusChangedCallbacks;

    std::shared_ptr<class CWrapper> m_cwrapper;

    std::map < uint64_t, SimpleMessageCallbackContext> callbacks;
    /** A thread pool*/
    std::unique_ptr<ApiGear::Utilities::ThreadPool> m_requests_pool;
    /** subscriptions pool*/
    std::unique_ptr<ApiGear::Utilities::ThreadPool> m_subscriptions_pool;

    std::atomic<bool> m_connecting{ false };
    std::future<void> m_connectionAwait;
};
} // namespace Nats
} // namespace ApiGear
