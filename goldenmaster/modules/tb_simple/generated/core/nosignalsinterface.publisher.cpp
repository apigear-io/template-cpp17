

#include "tb_simple/generated/core/nosignalsinterface.publisher.h"
#include <algorithm>


using namespace Test::TbSimple;

void NoSignalsInterfacePublisher::subscribeToAllChanges(INoSignalsInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<INoSignalsInterfaceSubscriber>(subscriber));
    }
}

void NoSignalsInterfacePublisher::unsubscribeFromAllChanges(INoSignalsInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long NoSignalsInterfacePublisher::subscribeToPropBoolChanged(NoSignalsInterfacePropBoolPropertyCb callback)
{
    return PropBoolPublisher.subscribeForChange(callback);
}

void NoSignalsInterfacePublisher::unsubscribeFromPropBoolChanged(long handleId)
{
    PropBoolPublisher.unsubscribeFromChange(handleId);
}

void NoSignalsInterfacePublisher::publishPropBoolChanged(bool propBool) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropBoolChanged(propBool);
    }
    PropBoolPublisher.publishChange(propBool);
}

long NoSignalsInterfacePublisher::subscribeToPropIntChanged(NoSignalsInterfacePropIntPropertyCb callback)
{
    return PropIntPublisher.subscribeForChange(callback);
}

void NoSignalsInterfacePublisher::unsubscribeFromPropIntChanged(long handleId)
{
    PropIntPublisher.unsubscribeFromChange(handleId);
}

void NoSignalsInterfacePublisher::publishPropIntChanged(int propInt) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropIntChanged(propInt);
    }
    PropIntPublisher.publishChange(propInt);
}

