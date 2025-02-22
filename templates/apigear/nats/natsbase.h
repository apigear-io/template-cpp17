#pragma once

#include <memory>
#include <string>
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

/**
Base class for Apigear Client and Apigear Service general (interface independent) adapters for NATS Client.
It provides common functionality for them like managing the subscriptions and connection state and provides an access 
to common methods implemented in a wrapper of CNATS library.
*/
class APIGEAR_NATS_EXPORT Base
{
public:

    explicit Base();
    virtual ~Base();

    static const int64_t InvalidSubscriptionId = 0;

    // WARNING this is blocking call, but calling with std::async causes error with state NATS_NO_SERVER_SUPPORT 
    void connect(const std::string& address, bool sendAsap = true);
    uint64_t getId() const;
    void disconnect();
    void flush();
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

    /* thread pools for c_wrapper thread blocking events*/
    std::unique_ptr<ApiGear::Utilities::ThreadPool> m_subscriptions_pool;
    std::unique_ptr<ApiGear::Utilities::ThreadPool> m_requests_pool;
};
} // namespace Nats
} // namespace ApiGear
