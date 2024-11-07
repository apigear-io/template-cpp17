#pragma once

#include <memory>
#include <string>
#include "nlohmann/json.hpp"
#include "natscommon.h"
#include "natstypes.h"
#include <mutex>
#include <condition_variable>

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

    void connect(const std::string& address);
    int64_t subscribe(const std::string& topic, SimpleOnMessageCallback callback);
    int64_t subscribeForRequest(const std::string& topic, MessageCallbackWithResult callback);
    void unsubscribe(int64_t id);
    void publish(const std::string& topic, const std::string& payload);
    void publishRequest(const std::string& topic, const std::string& payload, SimpleOnMessageCallback responseHandler);

    uint32_t addOnConnectedCallback(OnConnectionStatusChangedCallBackFunction callback);
    void removeOnConnectedCallback(uint32_t id);
    bool isConnected() const;
private:
    bool onConnectedChanged();
    std::mutex m_onConnectionStatusChangedCallbacksMutex;
    std::map<uint32_t, OnConnectionStatusChangedCallBackFunction> m_onConnectionStatusChangedCallbacks;

    std::shared_ptr<class CWrapper> m_cwrapper;

    std::map < uint64_t, SimpleMessageCallbackContext> callbacks;
    /** A thread pool*/
    std::unique_ptr<ApiGear::Utilities::ThreadPool> pool;
};
} // namespace Nats
} // namespace ApiGear
