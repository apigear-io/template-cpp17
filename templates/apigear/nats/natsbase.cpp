#include "natsclient.h"
#include "private/natscwrapper.h"
#include <random>
#include <iostream>

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
    // TODO this possibly should be called with std::async, 
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

// MAKE SURE TO UNSUBSCRIBE BEFORE THE onMsg gets invalidated
// TODO probably should by void Base::subscribe(std::string topic,
//                                              std::function<void>(uint64_t, std::string, bool?) onSubscribed,
//                                              SimpleOnMessageCallback onMsg)
// so subscribe will be called from different threads - and subscriptions stored in CWrapper have to be guarded with mutex
int64_t Base::subscribe(std::string topic, SimpleOnMessageCallback callback)
{
    // TODO this possibly should be called with std::async, and have a callback to inform when subscription ready
    return m_cwrapper->subscribe(topic, callback);

    //This object needs to store the futures - but it needs a handle with which the future will be destroyed - does it have to be unique id?
    //WHAT WITH THREAD POOL - will using it be thread safe , threads are chosen on subscribe?
}

void Base::unsubscribe(int64_t id)
{
    m_cwrapper->unsubscribe(id);
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