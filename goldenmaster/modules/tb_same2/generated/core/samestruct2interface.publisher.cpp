

#include "tb_same2/generated/core/samestruct2interface.publisher.h"
#include <algorithm>


using namespace Test::TbSame2;

void SameStruct2InterfacePublisher::subscribeToAllChanges(ISameStruct2InterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<ISameStruct2InterfaceSubscriber>(subscriber));
    }
}

void SameStruct2InterfacePublisher::unsubscribeFromAllChanges(ISameStruct2InterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long SameStruct2InterfacePublisher::subscribeToProp1Changed(SameStruct2InterfaceProp1PropertyCb callback)
{
    return Prop1Publisher.subscribeForChange(callback);
}

void SameStruct2InterfacePublisher::unsubscribeFromProp1Changed(long handleId)
{
    Prop1Publisher.unsubscribeFromChange(handleId);
}

void SameStruct2InterfacePublisher::publishProp1Changed(const Struct2& prop1) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onProp1Changed(prop1);
    }
    Prop1Publisher.publishChange(prop1);
}

long SameStruct2InterfacePublisher::subscribeToProp2Changed(SameStruct2InterfaceProp2PropertyCb callback)
{
    return Prop2Publisher.subscribeForChange(callback);
}

void SameStruct2InterfacePublisher::unsubscribeFromProp2Changed(long handleId)
{
    Prop2Publisher.unsubscribeFromChange(handleId);
}

void SameStruct2InterfacePublisher::publishProp2Changed(const Struct2& prop2) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onProp2Changed(prop2);
    }
    Prop2Publisher.publishChange(prop2);
}

long SameStruct2InterfacePublisher::subscribeToSig1(SameStruct2InterfaceSig1SignalCb callback)
{
    return Sig1Publisher.subscribeForChange(callback);
}

void SameStruct2InterfacePublisher::unsubscribeFromSig1(long handleId)
{
    Sig1Publisher.unsubscribeFromChange(handleId);
}

void SameStruct2InterfacePublisher::publishSig1(const Struct1& param1) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSig1(param1);
    }
    Sig1Publisher.publishChange(param1);
}

long SameStruct2InterfacePublisher::subscribeToSig2(SameStruct2InterfaceSig2SignalCb callback)
{
    return Sig2Publisher.subscribeForChange(callback);
}

void SameStruct2InterfacePublisher::unsubscribeFromSig2(long handleId)
{
    Sig2Publisher.unsubscribeFromChange(handleId);
}

void SameStruct2InterfacePublisher::publishSig2(const Struct1& param1, const Struct2& param2) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSig2(param1, param2);
    }
    Sig2Publisher.publishChange(param1, param2);
}

