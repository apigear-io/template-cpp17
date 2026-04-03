

#include "tb_struct_array/generated/core/structarrayfieldinterface.publisher.h"
#include <algorithm>


using namespace Test::TbStructArray;

void StructArrayFieldInterfacePublisher::subscribeToAllChanges(IStructArrayFieldInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<IStructArrayFieldInterfaceSubscriber>(subscriber));
    }
}

void StructArrayFieldInterfacePublisher::unsubscribeFromAllChanges(IStructArrayFieldInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

uint64_t StructArrayFieldInterfacePublisher::subscribeToPropStructArrayChanged(StructArrayFieldInterfacePropStructArrayPropertyCb callback)
{
    return PropStructArrayPublisher.subscribeForChange(callback);
}

void StructArrayFieldInterfacePublisher::unsubscribeFromPropStructArrayChanged(uint64_t handleId)
{
    PropStructArrayPublisher.unsubscribeFromChange(handleId);
}

void StructArrayFieldInterfacePublisher::publishPropStructArrayChanged(const StructWithArrayOfStructs& propStructArray) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropStructArrayChanged(propStructArray);
    }
    PropStructArrayPublisher.publishChange(propStructArray);
}

uint64_t StructArrayFieldInterfacePublisher::subscribeToPropEnumArrayChanged(StructArrayFieldInterfacePropEnumArrayPropertyCb callback)
{
    return PropEnumArrayPublisher.subscribeForChange(callback);
}

void StructArrayFieldInterfacePublisher::unsubscribeFromPropEnumArrayChanged(uint64_t handleId)
{
    PropEnumArrayPublisher.unsubscribeFromChange(handleId);
}

void StructArrayFieldInterfacePublisher::publishPropEnumArrayChanged(const StructWithArrayOfEnums& propEnumArray) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropEnumArrayChanged(propEnumArray);
    }
    PropEnumArrayPublisher.publishChange(propEnumArray);
}

uint64_t StructArrayFieldInterfacePublisher::subscribeToPropIntArrayChanged(StructArrayFieldInterfacePropIntArrayPropertyCb callback)
{
    return PropIntArrayPublisher.subscribeForChange(callback);
}

void StructArrayFieldInterfacePublisher::unsubscribeFromPropIntArrayChanged(uint64_t handleId)
{
    PropIntArrayPublisher.unsubscribeFromChange(handleId);
}

void StructArrayFieldInterfacePublisher::publishPropIntArrayChanged(const StructWithArrayOfInts& propIntArray) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropIntArrayChanged(propIntArray);
    }
    PropIntArrayPublisher.publishChange(propIntArray);
}

uint64_t StructArrayFieldInterfacePublisher::subscribeToPropMixedChanged(StructArrayFieldInterfacePropMixedPropertyCb callback)
{
    return PropMixedPublisher.subscribeForChange(callback);
}

void StructArrayFieldInterfacePublisher::unsubscribeFromPropMixedChanged(uint64_t handleId)
{
    PropMixedPublisher.unsubscribeFromChange(handleId);
}

void StructArrayFieldInterfacePublisher::publishPropMixedChanged(const MixedStruct& propMixed) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropMixedChanged(propMixed);
    }
    PropMixedPublisher.publishChange(propMixed);
}

uint64_t StructArrayFieldInterfacePublisher::subscribeToSigMixed(StructArrayFieldInterfaceSigMixedSignalCb callback)
{
    return SigMixedPublisher.subscribeForChange(callback);
}

void StructArrayFieldInterfacePublisher::unsubscribeFromSigMixed(uint64_t handleId)
{
    SigMixedPublisher.unsubscribeFromChange(handleId);
}

void StructArrayFieldInterfacePublisher::publishSigMixed(const MixedStruct& paramMixed) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigMixed(paramMixed);
    }
    SigMixedPublisher.publishChange(paramMixed);
}

uint64_t StructArrayFieldInterfacePublisher::subscribeToSigStructArray(StructArrayFieldInterfaceSigStructArraySignalCb callback)
{
    return SigStructArrayPublisher.subscribeForChange(callback);
}

void StructArrayFieldInterfacePublisher::unsubscribeFromSigStructArray(uint64_t handleId)
{
    SigStructArrayPublisher.unsubscribeFromChange(handleId);
}

void StructArrayFieldInterfacePublisher::publishSigStructArray(const StructWithArrayOfStructs& paramPoints) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigStructArray(paramPoints);
    }
    SigStructArrayPublisher.publishChange(paramPoints);
}

