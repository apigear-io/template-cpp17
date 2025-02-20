

#include "testbed2/generated/core/nestedstruct2interface.publisher.h"
#include <algorithm>


using namespace Test::Testbed2;

void NestedStruct2InterfacePublisher::subscribeToAllChanges(INestedStruct2InterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<INestedStruct2InterfaceSubscriber>(subscriber));
    }
}

void NestedStruct2InterfacePublisher::unsubscribeFromAllChanges(INestedStruct2InterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long NestedStruct2InterfacePublisher::subscribeToProp1Changed(NestedStruct2InterfaceProp1PropertyCb callback)
{
    return Prop1Publisher.subscribeForChange(callback);
}

void NestedStruct2InterfacePublisher::unsubscribeFromProp1Changed(long handleId)
{
    Prop1Publisher.unsubscribeFromChange(handleId);
}

void NestedStruct2InterfacePublisher::publishProp1Changed(const NestedStruct1& prop1) const
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

long NestedStruct2InterfacePublisher::subscribeToProp2Changed(NestedStruct2InterfaceProp2PropertyCb callback)
{
    return Prop2Publisher.subscribeForChange(callback);
}

void NestedStruct2InterfacePublisher::unsubscribeFromProp2Changed(long handleId)
{
    Prop2Publisher.unsubscribeFromChange(handleId);
}

void NestedStruct2InterfacePublisher::publishProp2Changed(const NestedStruct2& prop2) const
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

long NestedStruct2InterfacePublisher::subscribeToSig1(NestedStruct2InterfaceSig1SignalCb callback)
{
    return Sig1Publisher.subscribeForChange(callback);
}

void NestedStruct2InterfacePublisher::unsubscribeFromSig1(long handleId)
{
    Sig1Publisher.unsubscribeFromChange(handleId);
}

void NestedStruct2InterfacePublisher::publishSig1(const NestedStruct1& param1) const
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

long NestedStruct2InterfacePublisher::subscribeToSig2(NestedStruct2InterfaceSig2SignalCb callback)
{
    return Sig2Publisher.subscribeForChange(callback);
}

void NestedStruct2InterfacePublisher::unsubscribeFromSig2(long handleId)
{
    Sig2Publisher.unsubscribeFromChange(handleId);
}

void NestedStruct2InterfacePublisher::publishSig2(const NestedStruct1& param1, const NestedStruct2& param2) const
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

