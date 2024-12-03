#pragma once

#include <memory>
#include <string>
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
    void subscribe(std::string topic);
    void unsubscribe(std::string topic);
    void publish(std::string topic, std::string payload);

    uint32_t addOnConnectedCallback(OnConnectionStatusChangedCallBackFunction callback);
    void removeOnConnectedCallback(uint32_t id);
    bool isConnected() const;
private:
    bool onConnectedChanged();
    void handleConnectionState(bool state);
    std::mutex m_onConnectionStatusChangedCallbacksMutex;
    std::map<uint32_t, OnConnectionStatusChangedCallBackFunction> m_onConnectionStatusChangedCallbacks;

    std::shared_ptr<class CWrapper> m_cwrapper;
};
} // namespace Nats
} // namespace ApiGear
