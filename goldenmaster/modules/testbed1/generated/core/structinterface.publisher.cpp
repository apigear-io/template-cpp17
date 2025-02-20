

#include "testbed1/generated/core/structinterface.publisher.h"
#include <algorithm>


using namespace Test::Testbed1;

void StructInterfacePublisher::subscribeToAllChanges(IStructInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<IStructInterfaceSubscriber>(subscriber));
    }
}

void StructInterfacePublisher::unsubscribeFromAllChanges(IStructInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long StructInterfacePublisher::subscribeToPropBoolChanged(StructInterfacePropBoolPropertyCb callback)
{
    return PropBoolPublisher.subscribeForChange(callback);
}

void StructInterfacePublisher::unsubscribeFromPropBoolChanged(long handleId)
{
    PropBoolPublisher.unsubscribeFromChange(handleId);
}

void StructInterfacePublisher::publishPropBoolChanged(const StructBool& propBool) const
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

long StructInterfacePublisher::subscribeToPropIntChanged(StructInterfacePropIntPropertyCb callback)
{
    return PropIntPublisher.subscribeForChange(callback);
}

void StructInterfacePublisher::unsubscribeFromPropIntChanged(long handleId)
{
    PropIntPublisher.unsubscribeFromChange(handleId);
}

void StructInterfacePublisher::publishPropIntChanged(const StructInt& propInt) const
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

long StructInterfacePublisher::subscribeToPropFloatChanged(StructInterfacePropFloatPropertyCb callback)
{
    return PropFloatPublisher.subscribeForChange(callback);
}

void StructInterfacePublisher::unsubscribeFromPropFloatChanged(long handleId)
{
    PropFloatPublisher.unsubscribeFromChange(handleId);
}

void StructInterfacePublisher::publishPropFloatChanged(const StructFloat& propFloat) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropFloatChanged(propFloat);
    }
    PropFloatPublisher.publishChange(propFloat);
}

long StructInterfacePublisher::subscribeToPropStringChanged(StructInterfacePropStringPropertyCb callback)
{
    return PropStringPublisher.subscribeForChange(callback);
}

void StructInterfacePublisher::unsubscribeFromPropStringChanged(long handleId)
{
    PropStringPublisher.unsubscribeFromChange(handleId);
}

void StructInterfacePublisher::publishPropStringChanged(const StructString& propString) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropStringChanged(propString);
    }
    PropStringPublisher.publishChange(propString);
}

long StructInterfacePublisher::subscribeToSigBool(StructInterfaceSigBoolSignalCb callback)
{
    return SigBoolPublisher.subscribeForChange(callback);
}

void StructInterfacePublisher::unsubscribeFromSigBool(long handleId)
{
    SigBoolPublisher.unsubscribeFromChange(handleId);
}

void StructInterfacePublisher::publishSigBool(const StructBool& paramBool) const
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

long StructInterfacePublisher::subscribeToSigInt(StructInterfaceSigIntSignalCb callback)
{
    return SigIntPublisher.subscribeForChange(callback);
}

void StructInterfacePublisher::unsubscribeFromSigInt(long handleId)
{
    SigIntPublisher.unsubscribeFromChange(handleId);
}

void StructInterfacePublisher::publishSigInt(const StructInt& paramInt) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigInt(paramInt);
    }
    SigIntPublisher.publishChange(paramInt);
}

long StructInterfacePublisher::subscribeToSigFloat(StructInterfaceSigFloatSignalCb callback)
{
    return SigFloatPublisher.subscribeForChange(callback);
}

void StructInterfacePublisher::unsubscribeFromSigFloat(long handleId)
{
    SigFloatPublisher.unsubscribeFromChange(handleId);
}

void StructInterfacePublisher::publishSigFloat(const StructFloat& paramFloat) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigFloat(paramFloat);
    }
    SigFloatPublisher.publishChange(paramFloat);
}

long StructInterfacePublisher::subscribeToSigString(StructInterfaceSigStringSignalCb callback)
{
    return SigStringPublisher.subscribeForChange(callback);
}

void StructInterfacePublisher::unsubscribeFromSigString(long handleId)
{
    SigStringPublisher.unsubscribeFromChange(handleId);
}

void StructInterfacePublisher::publishSigString(const StructString& paramString) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigString(paramString);
    }
    SigStringPublisher.publishChange(paramString);
}

