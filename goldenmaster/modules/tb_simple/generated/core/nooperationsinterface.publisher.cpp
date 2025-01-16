

#include "tb_simple/generated/core/nooperationsinterface.publisher.h"
#include <algorithm>


using namespace Test::TbSimple;

void NoOperationsInterfacePublisher::subscribeToAllChanges(INoOperationsInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<INoOperationsInterfaceSubscriber>(subscriber));
    }
}

void NoOperationsInterfacePublisher::unsubscribeFromAllChanges(INoOperationsInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long NoOperationsInterfacePublisher::subscribeToPropBoolChanged(NoOperationsInterfacePropBoolPropertyCb callback)
{
    return PropBoolPublisher.subscribeForChange(callback);
}

void NoOperationsInterfacePublisher::unsubscribeFromPropBoolChanged(long handleId)
{
    PropBoolPublisher.unsubscribeFromChange(handleId);
}

void NoOperationsInterfacePublisher::publishPropBoolChanged(bool propBool) const
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

long NoOperationsInterfacePublisher::subscribeToPropIntChanged(NoOperationsInterfacePropIntPropertyCb callback)
{
    return PropIntPublisher.subscribeForChange(callback);
}

void NoOperationsInterfacePublisher::unsubscribeFromPropIntChanged(long handleId)
{
    PropIntPublisher.unsubscribeFromChange(handleId);
}

void NoOperationsInterfacePublisher::publishPropIntChanged(int propInt) const
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

long NoOperationsInterfacePublisher::subscribeToSigVoid(NoOperationsInterfaceSigVoidSignalCb callback)
{
    return SigVoidPublisher.subscribeForChange(callback);
}

void NoOperationsInterfacePublisher::unsubscribeFromSigVoid(long handleId)
{
    SigVoidPublisher.unsubscribeFromChange(handleId);
}

void NoOperationsInterfacePublisher::publishSigVoid() const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigVoid();
    }
    SigVoidPublisher.publishChange();
}

long NoOperationsInterfacePublisher::subscribeToSigBool(NoOperationsInterfaceSigBoolSignalCb callback)
{
    return SigBoolPublisher.subscribeForChange(callback);
}

void NoOperationsInterfacePublisher::unsubscribeFromSigBool(long handleId)
{
    SigBoolPublisher.unsubscribeFromChange(handleId);
}

void NoOperationsInterfacePublisher::publishSigBool(bool paramBool) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigBool(paramBool);
    }
    SigBoolPublisher.publishChange(paramBool);
}

