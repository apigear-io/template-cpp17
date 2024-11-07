#include "natsbase.h"
#include "private/natscwrapper.h"
#include "apigear/utilities/logger.h"
#include "apigear/utilities/threadpool.h"
#include <random>

using namespace ApiGear::Nats;

namespace
{

int64_t nats_invalid_subscription_id = 0;
std::mt19937 randomNumberGenerator(std::random_device{}());
std::uniform_int_distribution<uint32_t> distribution(0, 0xFFFFFFFF);

const size_t workerThreadsPerConnection = 10;

template<typename StoredItem>
uint32_t createUniqueMapId(const std::map<uint32_t, StoredItem>& existing_map, std::mutex& map_mutex)
{
    uint32_t uniqueId = 0;
    std::unique_lock<std::mutex> lock(map_mutex);
    do {
        uniqueId = distribution(randomNumberGenerator);
    } while (existing_map.find(uniqueId) != existing_map.end());

    return uniqueId;
}

}

Base::Base()
{
    m_cwrapper = CWrapper::create();
    m_subscriptions_pool = std::make_unique<ApiGear::Utilities::ThreadPool>(workerThreadsPerConnection);
}

void Base::connect(const std::string& address)
{
    auto status = m_cwrapper->getStatus();
    if (status == ConnectionStatus::reconnecting ||
        status == ConnectionStatus::connected ||
        status == ConnectionStatus::connecting)
    {
        return;
    }
    m_cwrapper->connect(address, [this]() { onConnectedChanged(); });
    if (m_cwrapper->getStatus() == ConnectionStatus::connected)
    {
        AG_LOG_DEBUG("nats client connected");
        handleConnectionState(true);
    }
}

void Base::handleConnectionState(bool state)
{
    m_onConnectionStatusChangedCallbacksMutex.lock();
    auto onConnectionStatusChangedCallbacks{ m_onConnectionStatusChangedCallbacks };
    m_onConnectionStatusChangedCallbacksMutex.unlock();
    for (auto& callback : onConnectionStatusChangedCallbacks)
    {
        callback.second(state);
    }
}

bool Base::onConnectedChanged()
{
    auto status = m_cwrapper->getStatus();
    if (status == ConnectionStatus::connected)
    {
        AG_LOG_DEBUG("nats client connected");
        handleConnectionState(true);
    }
    else if (status == ConnectionStatus::disconnected || status == ConnectionStatus::closed)
    {
        AG_LOG_DEBUG("nats client disconnected");
        handleConnectionState(false);
    }
    return false;
}

bool Base::isConnected() const
{
    return m_cwrapper->getStatus() == ConnectionStatus::connected;
}

void Base::subscribe(const std::string& topic, SimpleOnMessageCallback callback, std::function<void(int64_t, std::string, bool)> subscribe_callback)
{
    m_subscriptions_pool->enqueue([this, topic, callback, subscribe_callback]()
        {
            auto id = m_cwrapper->subscribe(topic, callback);
            subscribe_callback(id, topic, id != nats_invalid_subscription_id);
        });
}

void Base::unsubscribe(int64_t id)
{
    m_cwrapper->unsubscribe(id);
}
void Base::publish(const std::string& topic, const std::string& payload)
{
    m_cwrapper->publish(topic, payload);
}

uint32_t Base::addOnConnectedCallback(OnConnectionStatusChangedCallBackFunction callBack)
{
    auto callbackId = createUniqueMapId(m_onConnectionStatusChangedCallbacks, m_onConnectionStatusChangedCallbacksMutex);
    std::unique_lock<std::mutex> lock(m_onConnectionStatusChangedCallbacksMutex);
    m_onConnectionStatusChangedCallbacks[callbackId] = callBack;
    lock.unlock();

    return callbackId;
}

void Base::removeOnConnectedCallback(uint32_t callbackId)
{
    std::unique_lock<std::mutex> lock(m_onConnectionStatusChangedCallbacksMutex);
    if ((m_onConnectionStatusChangedCallbacks.find(callbackId) != m_onConnectionStatusChangedCallbacks.end()))
    {
        m_onConnectionStatusChangedCallbacks.erase(callbackId);
    }
    lock.unlock();
}
