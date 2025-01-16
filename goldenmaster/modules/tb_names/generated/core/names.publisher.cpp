

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
    return SwitchPublisher.subscribeForChange(callback);
}

void NamEsPublisher::unsubscribeFromSwitchChanged(long handleId)
{
    SwitchPublisher.unsubscribeFromChange(handleId);
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
    SwitchPublisher.publishChange(Switch);
}

long NamEsPublisher::subscribeToSomePropertyChanged(NamEsSomePropertyPropertyCb callback)
{
    return SomePropertyPublisher.subscribeForChange(callback);
}

void NamEsPublisher::unsubscribeFromSomePropertyChanged(long handleId)
{
    SomePropertyPublisher.unsubscribeFromChange(handleId);
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
    SomePropertyPublisher.publishChange(SOME_PROPERTY);
}

long NamEsPublisher::subscribeToSomePoperty2Changed(NamEsSomePoperty2PropertyCb callback)
{
    return SomePoperty2Publisher.subscribeForChange(callback);
}

void NamEsPublisher::unsubscribeFromSomePoperty2Changed(long handleId)
{
    SomePoperty2Publisher.unsubscribeFromChange(handleId);
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
    SomePoperty2Publisher.publishChange(Some_Poperty2);
}

long NamEsPublisher::subscribeToSomeSignal(NamEsSomeSignalSignalCb callback)
{
    return SomeSignalPublisher.subscribeForChange(callback);
}

void NamEsPublisher::unsubscribeFromSomeSignal(long handleId)
{
    SomeSignalPublisher.unsubscribeFromChange(handleId);
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
    SomeSignalPublisher.publishChange(SOME_PARAM);
}

long NamEsPublisher::subscribeToSomeSignal2(NamEsSomeSignal2SignalCb callback)
{
    return SomeSignal2Publisher.subscribeForChange(callback);
}

void NamEsPublisher::unsubscribeFromSomeSignal2(long handleId)
{
    SomeSignal2Publisher.unsubscribeFromChange(handleId);
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
    SomeSignal2Publisher.publishChange(Some_Param);
}

