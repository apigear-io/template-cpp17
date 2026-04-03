

#include "testbed1/generated/core/structarrayinterface.publisher.h"
#include <algorithm>


using namespace Test::Testbed1;

void StructArrayInterfacePublisher::subscribeToAllChanges(IStructArrayInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<IStructArrayInterfaceSubscriber>(subscriber));
    }
}

void StructArrayInterfacePublisher::unsubscribeFromAllChanges(IStructArrayInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

uint64_t StructArrayInterfacePublisher::subscribeToPropBoolChanged(StructArrayInterfacePropBoolPropertyCb callback)
{
    return PropBoolPublisher.subscribeForChange(callback);
}

void StructArrayInterfacePublisher::unsubscribeFromPropBoolChanged(uint64_t handleId)
{
    PropBoolPublisher.unsubscribeFromChange(handleId);
}

void StructArrayInterfacePublisher::publishPropBoolChanged(const std::list<StructBool>& propBool) const
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

uint64_t StructArrayInterfacePublisher::subscribeToPropIntChanged(StructArrayInterfacePropIntPropertyCb callback)
{
    return PropIntPublisher.subscribeForChange(callback);
}

void StructArrayInterfacePublisher::unsubscribeFromPropIntChanged(uint64_t handleId)
{
    PropIntPublisher.unsubscribeFromChange(handleId);
}

void StructArrayInterfacePublisher::publishPropIntChanged(const std::list<StructInt>& propInt) const
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

uint64_t StructArrayInterfacePublisher::subscribeToPropFloatChanged(StructArrayInterfacePropFloatPropertyCb callback)
{
    return PropFloatPublisher.subscribeForChange(callback);
}

void StructArrayInterfacePublisher::unsubscribeFromPropFloatChanged(uint64_t handleId)
{
    PropFloatPublisher.unsubscribeFromChange(handleId);
}

void StructArrayInterfacePublisher::publishPropFloatChanged(const std::list<StructFloat>& propFloat) const
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

uint64_t StructArrayInterfacePublisher::subscribeToPropStringChanged(StructArrayInterfacePropStringPropertyCb callback)
{
    return PropStringPublisher.subscribeForChange(callback);
}

void StructArrayInterfacePublisher::unsubscribeFromPropStringChanged(uint64_t handleId)
{
    PropStringPublisher.unsubscribeFromChange(handleId);
}

void StructArrayInterfacePublisher::publishPropStringChanged(const std::list<StructString>& propString) const
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

uint64_t StructArrayInterfacePublisher::subscribeToPropEnumChanged(StructArrayInterfacePropEnumPropertyCb callback)
{
    return PropEnumPublisher.subscribeForChange(callback);
}

void StructArrayInterfacePublisher::unsubscribeFromPropEnumChanged(uint64_t handleId)
{
    PropEnumPublisher.unsubscribeFromChange(handleId);
}

void StructArrayInterfacePublisher::publishPropEnumChanged(const std::list<Enum0Enum>& propEnum) const
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

uint64_t StructArrayInterfacePublisher::subscribeToSigBool(StructArrayInterfaceSigBoolSignalCb callback)
{
    return SigBoolPublisher.subscribeForChange(callback);
}

void StructArrayInterfacePublisher::unsubscribeFromSigBool(uint64_t handleId)
{
    SigBoolPublisher.unsubscribeFromChange(handleId);
}

void StructArrayInterfacePublisher::publishSigBool(const std::list<StructBool>& paramBool) const
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

uint64_t StructArrayInterfacePublisher::subscribeToSigInt(StructArrayInterfaceSigIntSignalCb callback)
{
    return SigIntPublisher.subscribeForChange(callback);
}

void StructArrayInterfacePublisher::unsubscribeFromSigInt(uint64_t handleId)
{
    SigIntPublisher.unsubscribeFromChange(handleId);
}

void StructArrayInterfacePublisher::publishSigInt(const std::list<StructInt>& paramInt) const
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

uint64_t StructArrayInterfacePublisher::subscribeToSigFloat(StructArrayInterfaceSigFloatSignalCb callback)
{
    return SigFloatPublisher.subscribeForChange(callback);
}

void StructArrayInterfacePublisher::unsubscribeFromSigFloat(uint64_t handleId)
{
    SigFloatPublisher.unsubscribeFromChange(handleId);
}

void StructArrayInterfacePublisher::publishSigFloat(const std::list<StructFloat>& paramFloat) const
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

uint64_t StructArrayInterfacePublisher::subscribeToSigString(StructArrayInterfaceSigStringSignalCb callback)
{
    return SigStringPublisher.subscribeForChange(callback);
}

void StructArrayInterfacePublisher::unsubscribeFromSigString(uint64_t handleId)
{
    SigStringPublisher.unsubscribeFromChange(handleId);
}

void StructArrayInterfacePublisher::publishSigString(const std::list<StructString>& paramString) const
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

uint64_t StructArrayInterfacePublisher::subscribeToSigEnum(StructArrayInterfaceSigEnumSignalCb callback)
{
    return SigEnumPublisher.subscribeForChange(callback);
}

void StructArrayInterfacePublisher::unsubscribeFromSigEnum(uint64_t handleId)
{
    SigEnumPublisher.unsubscribeFromChange(handleId);
}

void StructArrayInterfacePublisher::publishSigEnum(const std::list<Enum0Enum>& paramEnum) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigEnum(paramEnum);
    }
    SigEnumPublisher.publishChange(paramEnum);
}

