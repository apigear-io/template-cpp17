#pragma once

#include <atomic>
#include <map>
#include <shared_mutex>

namespace ApiGear {
namespace Utilities {

template<typename... Arguments>
class SinglePub
{
public:
    unsigned long subscribeForChange(std::function<void(Arguments...)> callback)
    {
        // this is a short term workaround - we need a better solution for unique handle identifiers
        auto handleId = m_nextId++;
        std::unique_lock<std::shared_timed_mutex> lock(m_callbacksMutex);
        m_callbacks[handleId] = callback;
        return handleId;
    }
    void unsubscribeFromChange(unsigned long handleId)
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_callbacksMutex);
        m_callbacks.erase(handleId);
    }
    void publishChange(Arguments... params) const
    {
        std::shared_lock<std::shared_timed_mutex> lock(m_callbacksMutex);
        const auto callbacks = m_callbacks;
        lock.unlock();
        for (const auto& callbackEntry : callbacks)
        {
            if (callbackEntry.second)
            {
                callbackEntry.second(params...);
            }
        }
    }
private:
    std::atomic<unsigned long> m_nextId{ 0 };
    std::map<unsigned long, std::function<void(Arguments...)> > m_callbacks;
    mutable std::shared_timed_mutex m_callbacksMutex;

};
}} //namespace ApiGear::Utilities
