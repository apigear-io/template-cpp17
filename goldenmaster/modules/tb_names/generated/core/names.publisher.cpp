

#include "tb_names/generated/core/names.publisher.h"
#include <algorithm>


using namespace Test::TbNames;

void NamEsPublisher::subscribeToAllChanges(INamEsSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<INamEsSubscriber>(subscriber));
    }
}

void NamEsPublisher::unsubscribeFromAllChanges(INamEsSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long NamEsPublisher::subscribeToSwitchChanged(NamEsSwitchPropertyCb callback)
{
    auto handleId = m_switchChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_switchCallbacksMutex);
    m_switchCallbacks[handleId] = callback;
    return handleId;
}

void NamEsPublisher::unsubscribeFromSwitchChanged(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_switchCallbacksMutex);
    m_switchCallbacks.erase(handleId);
}

void NamEsPublisher::publishSwitchChanged(bool Switch) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSwitchChanged(Switch);
    }
    std::shared_lock<std::shared_timed_mutex> switchCallbacksLock(m_switchCallbacksMutex);
    const auto switchCallbacks = m_switchCallbacks;
    switchCallbacksLock.unlock();
    for(const auto& callbackEntry: switchCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(Switch);
        }
    }
}

long NamEsPublisher::subscribeToSomePropertyChanged(NamEsSomePropertyPropertyCb callback)
{
    auto handleId = m_somePropertyChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_somePropertyCallbacksMutex);
    m_somePropertyCallbacks[handleId] = callback;
    return handleId;
}

void NamEsPublisher::unsubscribeFromSomePropertyChanged(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_somePropertyCallbacksMutex);
    m_somePropertyCallbacks.erase(handleId);
}

void NamEsPublisher::publishSomePropertyChanged(int SOME_PROPERTY) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSomePropertyChanged(SOME_PROPERTY);
    }
    std::shared_lock<std::shared_timed_mutex> somePropertyCallbacksLock(m_somePropertyCallbacksMutex);
    const auto somePropertyCallbacks = m_somePropertyCallbacks;
    somePropertyCallbacksLock.unlock();
    for(const auto& callbackEntry: somePropertyCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(SOME_PROPERTY);
        }
    }
}

long NamEsPublisher::subscribeToSomePoperty2Changed(NamEsSomePoperty2PropertyCb callback)
{
    auto handleId = m_somePoperty2ChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_somePoperty2CallbacksMutex);
    m_somePoperty2Callbacks[handleId] = callback;
    return handleId;
}

void NamEsPublisher::unsubscribeFromSomePoperty2Changed(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_somePoperty2CallbacksMutex);
    m_somePoperty2Callbacks.erase(handleId);
}

void NamEsPublisher::publishSomePoperty2Changed(int Some_Poperty2) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSomePoperty2Changed(Some_Poperty2);
    }
    std::shared_lock<std::shared_timed_mutex> somePoperty2CallbacksLock(m_somePoperty2CallbacksMutex);
    const auto somePoperty2Callbacks = m_somePoperty2Callbacks;
    somePoperty2CallbacksLock.unlock();
    for(const auto& callbackEntry: somePoperty2Callbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(Some_Poperty2);
        }
    }
}

long NamEsPublisher::subscribeToEnumPropertyChanged(NamEsEnumPropertyPropertyCb callback)
{
    auto handleId = m_enumPropertyChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_enumPropertyCallbacksMutex);
    m_enumPropertyCallbacks[handleId] = callback;
    return handleId;
}

void NamEsPublisher::unsubscribeFromEnumPropertyChanged(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_enumPropertyCallbacksMutex);
    m_enumPropertyCallbacks.erase(handleId);
}

void NamEsPublisher::publishEnumPropertyChanged(Enum_With_Under_scoresEnum enum_property) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onEnumPropertyChanged(enum_property);
    }
    std::shared_lock<std::shared_timed_mutex> enumPropertyCallbacksLock(m_enumPropertyCallbacksMutex);
    const auto enumPropertyCallbacks = m_enumPropertyCallbacks;
    enumPropertyCallbacksLock.unlock();
    for(const auto& callbackEntry: enumPropertyCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(enum_property);
        }
    }
}

long NamEsPublisher::subscribeToSomeSignal(NamEsSomeSignalSignalCb callback)
{
    // this is a short term workaround - we need a better solution for unique handle identifiers
    auto handleId = m_someSignalSignalCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_someSignalCallbacksMutex);
    m_someSignalCallbacks[handleId] = callback;
    return handleId;
}

void NamEsPublisher::unsubscribeFromSomeSignal(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_someSignalCallbacksMutex);
    m_someSignalCallbacks.erase(handleId);
}

void NamEsPublisher::publishSomeSignal(bool SOME_PARAM) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSomeSignal(SOME_PARAM);
    }
    std::shared_lock<std::shared_timed_mutex> someSignalCallbacksLock(m_someSignalCallbacksMutex);
    const auto someSignalCallbacks = m_someSignalCallbacks;
    someSignalCallbacksLock.unlock();
    for(const auto& callbackEntry: someSignalCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(SOME_PARAM);
        }
    }
}

long NamEsPublisher::subscribeToSomeSignal2(NamEsSomeSignal2SignalCb callback)
{
    // this is a short term workaround - we need a better solution for unique handle identifiers
    auto handleId = m_someSignal2SignalCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_someSignal2CallbacksMutex);
    m_someSignal2Callbacks[handleId] = callback;
    return handleId;
}

void NamEsPublisher::unsubscribeFromSomeSignal2(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_someSignal2CallbacksMutex);
    m_someSignal2Callbacks.erase(handleId);
}

void NamEsPublisher::publishSomeSignal2(bool Some_Param) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSomeSignal2(Some_Param);
    }
    std::shared_lock<std::shared_timed_mutex> someSignal2CallbacksLock(m_someSignal2CallbacksMutex);
    const auto someSignal2Callbacks = m_someSignal2Callbacks;
    someSignal2CallbacksLock.unlock();
    for(const auto& callbackEntry: someSignal2Callbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(Some_Param);
        }
    }
}

