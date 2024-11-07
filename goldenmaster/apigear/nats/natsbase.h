#pragma once

#include <memory>
#include <string>
#include "natscommon.h"
#include "natstypes.h"
#include <mutex>
#include <atomic>
#include <future>
#include "apigear/utilities/threadpool.h"

namespace ApiGear {
namespace Nats {

class APIGEAR_NATS_EXPORT Base
{
public:
    explicit Base();
    virtual ~Base() = default;

    // WARNING this is blocking call, but calling with std::async causes error with state NATS_NO_SERVER_SUPPORT 
    void connect(const std::string& address);
    void subscribe(const std::string& topic, SimpleOnMessageCallback callback, std::function<void(int64_t, std::string, bool)> subscribe_callback);
    void unsubscribe(int64_t id);
    void publish(const std::string& topic, const std::string& payload);

    uint32_t addOnConnectedCallback(OnConnectionStatusChangedCallBackFunction callback);
    void removeOnConnectedCallback(uint32_t id);
    bool isConnected() const;
private:
    bool onConnectedChanged();
    void handleConnectionState(bool state);
    std::mutex m_onConnectionStatusChangedCallbacksMutex;
    std::map<uint32_t, OnConnectionStatusChangedCallBackFunction> m_onConnectionStatusChangedCallbacks;

    std::shared_ptr<class CWrapper> m_cwrapper;

    /** subscriptions pool*/
    std::unique_ptr<ApiGear::Utilities::ThreadPool> m_subscriptions_pool;
};
} // namespace Nats
} // namespace ApiGear
