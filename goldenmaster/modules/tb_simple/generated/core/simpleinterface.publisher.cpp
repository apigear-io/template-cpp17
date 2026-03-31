

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

uint64_t SimpleInterfacePublisher::subscribeToPropBoolChanged(SimpleInterfacePropBoolPropertyCb callback)
{
    return PropBoolPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropBoolChanged(uint64_t handleId)
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

uint64_t SimpleInterfacePublisher::subscribeToPropIntChanged(SimpleInterfacePropIntPropertyCb callback)
{
    return PropIntPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropIntChanged(uint64_t handleId)
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

uint64_t SimpleInterfacePublisher::subscribeToPropInt32Changed(SimpleInterfacePropInt32PropertyCb callback)
{
    return PropInt32Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropInt32Changed(uint64_t handleId)
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

uint64_t SimpleInterfacePublisher::subscribeToPropInt64Changed(SimpleInterfacePropInt64PropertyCb callback)
{
    return PropInt64Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropInt64Changed(uint64_t handleId)
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

uint64_t SimpleInterfacePublisher::subscribeToPropFloatChanged(SimpleInterfacePropFloatPropertyCb callback)
{
    return PropFloatPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropFloatChanged(uint64_t handleId)
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

uint64_t SimpleInterfacePublisher::subscribeToPropFloat32Changed(SimpleInterfacePropFloat32PropertyCb callback)
{
    return PropFloat32Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropFloat32Changed(uint64_t handleId)
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

uint64_t SimpleInterfacePublisher::subscribeToPropFloat64Changed(SimpleInterfacePropFloat64PropertyCb callback)
{
    return PropFloat64Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropFloat64Changed(uint64_t handleId)
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

uint64_t SimpleInterfacePublisher::subscribeToPropStringChanged(SimpleInterfacePropStringPropertyCb callback)
{
    return PropStringPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromPropStringChanged(uint64_t handleId)
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

uint64_t SimpleInterfacePublisher::subscribeToSigBool(SimpleInterfaceSigBoolSignalCb callback)
{
    return SigBoolPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigBool(uint64_t handleId)
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

uint64_t SimpleInterfacePublisher::subscribeToSigInt(SimpleInterfaceSigIntSignalCb callback)
{
    return SigIntPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigInt(uint64_t handleId)
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

uint64_t SimpleInterfacePublisher::subscribeToSigInt32(SimpleInterfaceSigInt32SignalCb callback)
{
    return SigInt32Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigInt32(uint64_t handleId)
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

uint64_t SimpleInterfacePublisher::subscribeToSigInt64(SimpleInterfaceSigInt64SignalCb callback)
{
    return SigInt64Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigInt64(uint64_t handleId)
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

uint64_t SimpleInterfacePublisher::subscribeToSigFloat(SimpleInterfaceSigFloatSignalCb callback)
{
    return SigFloatPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigFloat(uint64_t handleId)
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

uint64_t SimpleInterfacePublisher::subscribeToSigFloat32(SimpleInterfaceSigFloat32SignalCb callback)
{
    return SigFloat32Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigFloat32(uint64_t handleId)
{
    SigFloat32Publisher.unsubscribeFromChange(handleId);
}

void SimpleInterfacePublisher::publishSigFloat32(float paramFloat32) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigFloat32(paramFloat32);
    }
    SigFloat32Publisher.publishChange(paramFloat32);
}

uint64_t SimpleInterfacePublisher::subscribeToSigFloat64(SimpleInterfaceSigFloat64SignalCb callback)
{
    return SigFloat64Publisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigFloat64(uint64_t handleId)
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

uint64_t SimpleInterfacePublisher::subscribeToSigString(SimpleInterfaceSigStringSignalCb callback)
{
    return SigStringPublisher.subscribeForChange(callback);
}

void SimpleInterfacePublisher::unsubscribeFromSigString(uint64_t handleId)
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

