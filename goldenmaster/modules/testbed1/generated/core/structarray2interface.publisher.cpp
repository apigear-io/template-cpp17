

#include "testbed1/generated/core/structarray2interface.publisher.h"
#include <algorithm>


using namespace Test::Testbed1;

void StructArray2InterfacePublisher::subscribeToAllChanges(IStructArray2InterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<IStructArray2InterfaceSubscriber>(subscriber));
    }
}

void StructArray2InterfacePublisher::unsubscribeFromAllChanges(IStructArray2InterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

uint64_t StructArray2InterfacePublisher::subscribeToPropBoolChanged(StructArray2InterfacePropBoolPropertyCb callback)
{
    return PropBoolPublisher.subscribeForChange(callback);
}

void StructArray2InterfacePublisher::unsubscribeFromPropBoolChanged(uint64_t handleId)
{
    PropBoolPublisher.unsubscribeFromChange(handleId);
}

void StructArray2InterfacePublisher::publishPropBoolChanged(const StructBoolWithArray& propBool) const
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

uint64_t StructArray2InterfacePublisher::subscribeToPropIntChanged(StructArray2InterfacePropIntPropertyCb callback)
{
    return PropIntPublisher.subscribeForChange(callback);
}

void StructArray2InterfacePublisher::unsubscribeFromPropIntChanged(uint64_t handleId)
{
    PropIntPublisher.unsubscribeFromChange(handleId);
}

void StructArray2InterfacePublisher::publishPropIntChanged(const StructIntWithArray& propInt) const
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

uint64_t StructArray2InterfacePublisher::subscribeToPropFloatChanged(StructArray2InterfacePropFloatPropertyCb callback)
{
    return PropFloatPublisher.subscribeForChange(callback);
}

void StructArray2InterfacePublisher::unsubscribeFromPropFloatChanged(uint64_t handleId)
{
    PropFloatPublisher.unsubscribeFromChange(handleId);
}

void StructArray2InterfacePublisher::publishPropFloatChanged(const StructFloatWithArray& propFloat) const
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

uint64_t StructArray2InterfacePublisher::subscribeToPropStringChanged(StructArray2InterfacePropStringPropertyCb callback)
{
    return PropStringPublisher.subscribeForChange(callback);
}

void StructArray2InterfacePublisher::unsubscribeFromPropStringChanged(uint64_t handleId)
{
    PropStringPublisher.unsubscribeFromChange(handleId);
}

void StructArray2InterfacePublisher::publishPropStringChanged(const StructStringWithArray& propString) const
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

uint64_t StructArray2InterfacePublisher::subscribeToPropEnumChanged(StructArray2InterfacePropEnumPropertyCb callback)
{
    return PropEnumPublisher.subscribeForChange(callback);
}

void StructArray2InterfacePublisher::unsubscribeFromPropEnumChanged(uint64_t handleId)
{
    PropEnumPublisher.unsubscribeFromChange(handleId);
}

void StructArray2InterfacePublisher::publishPropEnumChanged(const StructEnumWithArray& propEnum) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropEnumChanged(propEnum);
    }
    PropEnumPublisher.publishChange(propEnum);
}

uint64_t StructArray2InterfacePublisher::subscribeToSigBool(StructArray2InterfaceSigBoolSignalCb callback)
{
    return SigBoolPublisher.subscribeForChange(callback);
}

void StructArray2InterfacePublisher::unsubscribeFromSigBool(uint64_t handleId)
{
    SigBoolPublisher.unsubscribeFromChange(handleId);
}

void StructArray2InterfacePublisher::publishSigBool(const StructBoolWithArray& paramBool) const
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

uint64_t StructArray2InterfacePublisher::subscribeToSigInt(StructArray2InterfaceSigIntSignalCb callback)
{
    return SigIntPublisher.subscribeForChange(callback);
}

void StructArray2InterfacePublisher::unsubscribeFromSigInt(uint64_t handleId)
{
    SigIntPublisher.unsubscribeFromChange(handleId);
}

void StructArray2InterfacePublisher::publishSigInt(const StructIntWithArray& paramInt) const
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

uint64_t StructArray2InterfacePublisher::subscribeToSigFloat(StructArray2InterfaceSigFloatSignalCb callback)
{
    return SigFloatPublisher.subscribeForChange(callback);
}

void StructArray2InterfacePublisher::unsubscribeFromSigFloat(uint64_t handleId)
{
    SigFloatPublisher.unsubscribeFromChange(handleId);
}

void StructArray2InterfacePublisher::publishSigFloat(const StructFloatWithArray& paramFloat) const
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

uint64_t StructArray2InterfacePublisher::subscribeToSigString(StructArray2InterfaceSigStringSignalCb callback)
{
    return SigStringPublisher.subscribeForChange(callback);
}

void StructArray2InterfacePublisher::unsubscribeFromSigString(uint64_t handleId)
{
    SigStringPublisher.unsubscribeFromChange(handleId);
}

void StructArray2InterfacePublisher::publishSigString(const StructStringWithArray& paramString) const
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

