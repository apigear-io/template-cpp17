

#include "tb_simple/generated/core/simpleinterface.publisher.h"
#include <algorithm>


using namespace Test::TbSimple;

void SimpleInterfacePublisher::subscribeToAllChanges(ISimpleInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<ISimpleInterfaceSubscriber>(subscriber));
    }
}

void SimpleInterfacePublisher::unsubscribeFromAllChanges(ISimpleInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long SimpleInterfacePublisher::subscribeToPropBoolChanged(SimpleInterfacePropBoolPropertyCb callback)
{
    return PropBoolPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropBoolChanged(long handleId)
{
    PropBoolPublisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishPropBoolChanged(bool propBool) const
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

long SimpleInterfacePublisher::subscribeToPropIntChanged(SimpleInterfacePropIntPropertyCb callback)
{
    return PropIntPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropIntChanged(long handleId)
{
    PropIntPublisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishPropIntChanged(int propInt) const
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

long SimpleInterfacePublisher::subscribeToPropInt32Changed(SimpleInterfacePropInt32PropertyCb callback)
{
    return PropInt32Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropInt32Changed(long handleId)
{
    PropInt32Publisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishPropInt32Changed(int32_t propInt32) const
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

long SimpleInterfacePublisher::subscribeToPropInt64Changed(SimpleInterfacePropInt64PropertyCb callback)
{
    return PropInt64Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropInt64Changed(long handleId)
{
    PropInt64Publisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishPropInt64Changed(int64_t propInt64) const
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

long SimpleInterfacePublisher::subscribeToPropFloatChanged(SimpleInterfacePropFloatPropertyCb callback)
{
    return PropFloatPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropFloatChanged(long handleId)
{
    PropFloatPublisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishPropFloatChanged(float propFloat) const
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

long SimpleInterfacePublisher::subscribeToPropFloat32Changed(SimpleInterfacePropFloat32PropertyCb callback)
{
    return PropFloat32Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropFloat32Changed(long handleId)
{
    PropFloat32Publisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishPropFloat32Changed(float propFloat32) const
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

long SimpleInterfacePublisher::subscribeToPropFloat64Changed(SimpleInterfacePropFloat64PropertyCb callback)
{
    return PropFloat64Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropFloat64Changed(long handleId)
{
    PropFloat64Publisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishPropFloat64Changed(double propFloat64) const
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

long SimpleInterfacePublisher::subscribeToPropStringChanged(SimpleInterfacePropStringPropertyCb callback)
{
    return PropStringPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropStringChanged(long handleId)
{
    PropStringPublisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishPropStringChanged(const std::string& propString) const
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

long SimpleInterfacePublisher::subscribeToSigBool(SimpleInterfaceSigBoolSignalCb callback)
{
    return SigBoolPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigBool(long handleId)
{
    SigBoolPublisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishSigBool(bool paramBool) const
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

long SimpleInterfacePublisher::subscribeToSigInt(SimpleInterfaceSigIntSignalCb callback)
{
    return SigIntPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigInt(long handleId)
{
    SigIntPublisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishSigInt(int paramInt) const
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

long SimpleInterfacePublisher::subscribeToSigInt32(SimpleInterfaceSigInt32SignalCb callback)
{
    return SigInt32Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigInt32(long handleId)
{
    SigInt32Publisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishSigInt32(int32_t paramInt32) const
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

long SimpleInterfacePublisher::subscribeToSigInt64(SimpleInterfaceSigInt64SignalCb callback)
{
    return SigInt64Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigInt64(long handleId)
{
    SigInt64Publisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishSigInt64(int64_t paramInt64) const
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

long SimpleInterfacePublisher::subscribeToSigFloat(SimpleInterfaceSigFloatSignalCb callback)
{
    return SigFloatPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigFloat(long handleId)
{
    SigFloatPublisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishSigFloat(float paramFloat) const
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

long SimpleInterfacePublisher::subscribeToSigFloat32(SimpleInterfaceSigFloat32SignalCb callback)
{
    return SigFloat32Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigFloat32(long handleId)
{
    SigFloat32Publisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishSigFloat32(float paramFloa32) const
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

long SimpleInterfacePublisher::subscribeToSigFloat64(SimpleInterfaceSigFloat64SignalCb callback)
{
    return SigFloat64Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigFloat64(long handleId)
{
    SigFloat64Publisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishSigFloat64(double paramFloat64) const
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

long SimpleInterfacePublisher::subscribeToSigString(SimpleInterfaceSigStringSignalCb callback)
{
    return SigStringPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigString(long handleId)
{
    SigStringPublisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishSigString(const std::string& paramString) const
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

