

#include "tb_simple/generated/core/simplearrayinterface.publisher.h"
#include <algorithm>


using namespace Test::TbSimple;

void SimpleArrayInterfacePublisher::subscribeToAllChanges(ISimpleArrayInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<ISimpleArrayInterfaceSubscriber>(subscriber));
    }
}

void SimpleArrayInterfacePublisher::unsubscribeFromAllChanges(ISimpleArrayInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long SimpleArrayInterfacePublisher::subscribeToPropBoolChanged(SimpleArrayInterfacePropBoolPropertyCb callback)
{
    return PropBoolPublisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropBoolChanged(long handleId)
{
    PropBoolPublisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishPropBoolChanged(const std::list<bool>& propBool) const
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

long SimpleArrayInterfacePublisher::subscribeToPropIntChanged(SimpleArrayInterfacePropIntPropertyCb callback)
{
    return PropIntPublisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropIntChanged(long handleId)
{
    PropIntPublisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishPropIntChanged(const std::list<int>& propInt) const
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

long SimpleArrayInterfacePublisher::subscribeToPropInt32Changed(SimpleArrayInterfacePropInt32PropertyCb callback)
{
    return PropInt32Publisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropInt32Changed(long handleId)
{
    PropInt32Publisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishPropInt32Changed(const std::list<int32_t>& propInt32) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropInt32Changed(propInt32);
    }
    PropInt32Publisher.publishChange(propInt32);
}

long SimpleArrayInterfacePublisher::subscribeToPropInt64Changed(SimpleArrayInterfacePropInt64PropertyCb callback)
{
    return PropInt64Publisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropInt64Changed(long handleId)
{
    PropInt64Publisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishPropInt64Changed(const std::list<int64_t>& propInt64) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropInt64Changed(propInt64);
    }
    PropInt64Publisher.publishChange(propInt64);
}

long SimpleArrayInterfacePublisher::subscribeToPropFloatChanged(SimpleArrayInterfacePropFloatPropertyCb callback)
{
    return PropFloatPublisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropFloatChanged(long handleId)
{
    PropFloatPublisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishPropFloatChanged(const std::list<float>& propFloat) const
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

long SimpleArrayInterfacePublisher::subscribeToPropFloat32Changed(SimpleArrayInterfacePropFloat32PropertyCb callback)
{
    return PropFloat32Publisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropFloat32Changed(long handleId)
{
    PropFloat32Publisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishPropFloat32Changed(const std::list<float>& propFloat32) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropFloat32Changed(propFloat32);
    }
    PropFloat32Publisher.publishChange(propFloat32);
}

long SimpleArrayInterfacePublisher::subscribeToPropFloat64Changed(SimpleArrayInterfacePropFloat64PropertyCb callback)
{
    return PropFloat64Publisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropFloat64Changed(long handleId)
{
    PropFloat64Publisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishPropFloat64Changed(const std::list<double>& propFloat64) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropFloat64Changed(propFloat64);
    }
    PropFloat64Publisher.publishChange(propFloat64);
}

long SimpleArrayInterfacePublisher::subscribeToPropStringChanged(SimpleArrayInterfacePropStringPropertyCb callback)
{
    return PropStringPublisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropStringChanged(long handleId)
{
    PropStringPublisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishPropStringChanged(const std::list<std::string>& propString) const
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

long SimpleArrayInterfacePublisher::subscribeToPropReadOnlyStringChanged(SimpleArrayInterfacePropReadOnlyStringPropertyCb callback)
{
    return PropReadOnlyStringPublisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropReadOnlyStringChanged(long handleId)
{
    PropReadOnlyStringPublisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishPropReadOnlyStringChanged(const std::string& propReadOnlyString) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropReadOnlyStringChanged(propReadOnlyString);
    }
    PropReadOnlyStringPublisher.publishChange(propReadOnlyString);
}

long SimpleArrayInterfacePublisher::subscribeToSigBool(SimpleArrayInterfaceSigBoolSignalCb callback)
{
    return SigBoolPublisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigBool(long handleId)
{
    SigBoolPublisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishSigBool(const std::list<bool>& paramBool) const
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

long SimpleArrayInterfacePublisher::subscribeToSigInt(SimpleArrayInterfaceSigIntSignalCb callback)
{
    return SigIntPublisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigInt(long handleId)
{
    SigIntPublisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishSigInt(const std::list<int>& paramInt) const
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

long SimpleArrayInterfacePublisher::subscribeToSigInt32(SimpleArrayInterfaceSigInt32SignalCb callback)
{
    return SigInt32Publisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigInt32(long handleId)
{
    SigInt32Publisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishSigInt32(const std::list<int32_t>& paramInt32) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigInt32(paramInt32);
    }
    SigInt32Publisher.publishChange(paramInt32);
}

long SimpleArrayInterfacePublisher::subscribeToSigInt64(SimpleArrayInterfaceSigInt64SignalCb callback)
{
    return SigInt64Publisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigInt64(long handleId)
{
    SigInt64Publisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishSigInt64(const std::list<int64_t>& paramInt64) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigInt64(paramInt64);
    }
    SigInt64Publisher.publishChange(paramInt64);
}

long SimpleArrayInterfacePublisher::subscribeToSigFloat(SimpleArrayInterfaceSigFloatSignalCb callback)
{
    return SigFloatPublisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigFloat(long handleId)
{
    SigFloatPublisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishSigFloat(const std::list<float>& paramFloat) const
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

long SimpleArrayInterfacePublisher::subscribeToSigFloat32(SimpleArrayInterfaceSigFloat32SignalCb callback)
{
    return SigFloat32Publisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigFloat32(long handleId)
{
    SigFloat32Publisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishSigFloat32(const std::list<float>& paramFloa32) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigFloat32(paramFloa32);
    }
    SigFloat32Publisher.publishChange(paramFloa32);
}

long SimpleArrayInterfacePublisher::subscribeToSigFloat64(SimpleArrayInterfaceSigFloat64SignalCb callback)
{
    return SigFloat64Publisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigFloat64(long handleId)
{
    SigFloat64Publisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishSigFloat64(const std::list<double>& paramFloat64) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigFloat64(paramFloat64);
    }
    SigFloat64Publisher.publishChange(paramFloat64);
}

long SimpleArrayInterfacePublisher::subscribeToSigString(SimpleArrayInterfaceSigStringSignalCb callback)
{
    return SigStringPublisher.subscribeForChange(callback);
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigString(long handleId)
{
    SigStringPublisher.unsubscribeFromChange(handleId);
}

void SimpleArrayInterfacePublisher::publishSigString(const std::list<std::string>& paramString) const
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

