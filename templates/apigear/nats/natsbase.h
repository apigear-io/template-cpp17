#pragma once

#include <memory>
#include <string>
#include "nlohmann/json.hpp"
#include "natscommon.h"
#include "natstypes.h"
#include <mutex>
#include <condition_variable>

namespace ApiGear {
namespace Nats {

class APIGEAR_NATS_EXPORT Base
{
public:
    explicit Base();
    virtual ~Base() = default;

    void connect(const std::string& address);
    int64_t subscribe(const std::string& topic, SimpleOnMessageCallback callback);
    void unsubscribe(int64_t id);
    void publish(const std::string& topic, const std::string& payload);

    uint32_t addOnConnectedCallback(OnConnectionStatusChangedCallBackFunction callback);
    void removeOnConnectedCallback(uint32_t id);
    bool isConnected() const;
private:
    bool onConnectedChanged();
    std::mutex m_onConnectionStatusChangedCallbacksMutex;
    std::map<uint32_t, OnConnectionStatusChangedCallBackFunction> m_onConnectionStatusChangedCallbacks;

    std::shared_ptr<class CWrapper> m_cwrapper;

    std::map < uint64_t, SimpleMessageCallbackContext> callbacks;
};
} // namespace Nats
} // namespace ApiGear
