#pragma once

#include <atomic>
#include <cstdint>
#include <functional>
#include <map>
#include <mutex>
#include <shared_mutex>

namespace ApiGear {
namespace Utilities {

template<typename... Arguments>
class SinglePub
{
public:
    uint64_t subscribeForChange(std::function<void(Arguments...)> callback)
    {
        auto handleId = m_nextId++;
        std::unique_lock<std::shared_timed_mutex> lock(m_callbacksMutex);
        m_callbacks[handleId] = callback;
        return handleId;
    }
    void unsubscribeFromChange(uint64_t handleId)
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_callbacksMutex);
        m_callbacks.erase(handleId);
    }
    void publishChange(Arguments... params) const
    {
        decltype(m_callbacks) callbacksCopy;
        {
            std::shared_lock<std::shared_timed_mutex> lock(m_callbacksMutex);
            callbacksCopy = m_callbacks;
        }
        for (const auto& callbackEntry : callbacksCopy)
        {
            if (callbackEntry.second)
            {
                callbackEntry.second(params...);
            }
        }
    }
private:
    std::atomic<uint64_t> m_nextId{ 0 };
    std::map<uint64_t, std::function<void(Arguments...)> > m_callbacks;
    mutable std::shared_timed_mutex m_callbacksMutex;

};
}} //namespace ApiGear::Utilities
