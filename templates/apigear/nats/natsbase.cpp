#include "natsclient.h"
#include "private/natscwrapper.h"
#include <random>

using namespace ApiGear::Nats;

std::mt19937 randomNumberGenerator(std::random_device{}());
std::uniform_int_distribution<uint32_t> distribution(0, 0xFFFFFFFF);

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


Base::Base()
{
    m_cwrapper = CWrapper::create();
}

void Base::connect(std::string address)
{
    m_cwrapper->connect(address, [this]() {onConnectedChanged(); });
    auto status = m_cwrapper->getStatus();
    if (status == ConnectionStatus::connected)
    {
        //TODO LOG AG_LOG_DEBUG("nats client connected");
        m_onConnectionStatusChangedCallbacksMutex.lock();
        auto onConnectionStatusChangedCallbacks{ m_onConnectionStatusChangedCallbacks };
        m_onConnectionStatusChangedCallbacksMutex.unlock();
        for (auto& callback : onConnectionStatusChangedCallbacks) {
            callback.second(true);
        }
    }
}

bool Base::onConnectedChanged()
{
    auto status = m_cwrapper->getStatus();
    if (status == ConnectionStatus::connected)
    {
        //TODO LOG AG_LOG_DEBUG("nats client connected");
        m_onConnectionStatusChangedCallbacksMutex.lock();
        auto onConnectionStatusChangedCallbacks{ m_onConnectionStatusChangedCallbacks };
        m_onConnectionStatusChangedCallbacksMutex.unlock();
        for (auto& callback : onConnectionStatusChangedCallbacks) {
            callback.second(true);
        }
    }
    else if (status == ConnectionStatus::disconnected || status == ConnectionStatus::closed)
    {
        //TODO LOG AG_LOG_DEBUG("nats client disconnected");
        m_onConnectionStatusChangedCallbacksMutex.lock();
        auto onConnectionStatusChangedCallbacks{ m_onConnectionStatusChangedCallbacks };
        m_onConnectionStatusChangedCallbacksMutex.unlock();
        for (auto& callback : onConnectionStatusChangedCallbacks) {
            callback.second(false);
        }
    }
    return false;
}

bool Base::isConnected() const
{
    return m_cwrapper->getStatus() == ConnectionStatus::connected;
}

uint32_t Base::subscribe(std::string topic)
{
    m_cwrapper->subscribe(topic);
    return 0;
}
void Base::unsubscribe(std::string topic)
{
    m_cwrapper->unsubscribe(topic);
}
void Base::publish(std::string topic, std::string payload)
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