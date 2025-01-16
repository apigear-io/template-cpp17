

#include "testbed2/generated/core/nestedstruct3interface.publisher.h"
#include <algorithm>


using namespace Test::Testbed2;

void NestedStruct3InterfacePublisher::subscribeToAllChanges(INestedStruct3InterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<INestedStruct3InterfaceSubscriber>(subscriber));
    }
}

void NestedStruct3InterfacePublisher::unsubscribeFromAllChanges(INestedStruct3InterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long NestedStruct3InterfacePublisher::subscribeToProp1Changed(NestedStruct3InterfaceProp1PropertyCb callback)
{
    return Prop1Publisher.subscribeForChange(callback);
}

void NestedStruct3InterfacePublisher::unsubscribeFromProp1Changed(long handleId)
{
    Prop1Publisher.unsubscribeFromChange(handleId);
}

void NestedStruct3InterfacePublisher::publishProp1Changed(const NestedStruct1& prop1) const
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

long NestedStruct3InterfacePublisher::subscribeToProp2Changed(NestedStruct3InterfaceProp2PropertyCb callback)
{
    return Prop2Publisher.subscribeForChange(callback);
}

void NestedStruct3InterfacePublisher::unsubscribeFromProp2Changed(long handleId)
{
    Prop2Publisher.unsubscribeFromChange(handleId);
}

void NestedStruct3InterfacePublisher::publishProp2Changed(const NestedStruct2& prop2) const
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

long NestedStruct3InterfacePublisher::subscribeToProp3Changed(NestedStruct3InterfaceProp3PropertyCb callback)
{
    return Prop3Publisher.subscribeForChange(callback);
}

void NestedStruct3InterfacePublisher::unsubscribeFromProp3Changed(long handleId)
{
    Prop3Publisher.unsubscribeFromChange(handleId);
}

void NestedStruct3InterfacePublisher::publishProp3Changed(const NestedStruct3& prop3) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onProp3Changed(prop3);
    }
    Prop3Publisher.publishChange(prop3);
}

long NestedStruct3InterfacePublisher::subscribeToSig1(NestedStruct3InterfaceSig1SignalCb callback)
{
    return Sig1Publisher.subscribeForChange(callback);
}

void NestedStruct3InterfacePublisher::unsubscribeFromSig1(long handleId)
{
    Sig1Publisher.unsubscribeFromChange(handleId);
}

void NestedStruct3InterfacePublisher::publishSig1(const NestedStruct1& param1) const
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

long NestedStruct3InterfacePublisher::subscribeToSig2(NestedStruct3InterfaceSig2SignalCb callback)
{
    return Sig2Publisher.subscribeForChange(callback);
}

void NestedStruct3InterfacePublisher::unsubscribeFromSig2(long handleId)
{
    Sig2Publisher.unsubscribeFromChange(handleId);
}

void NestedStruct3InterfacePublisher::publishSig2(const NestedStruct1& param1, const NestedStruct2& param2) const
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

long NestedStruct3InterfacePublisher::subscribeToSig3(NestedStruct3InterfaceSig3SignalCb callback)
{
    return Sig3Publisher.subscribeForChange(callback);
}

void NestedStruct3InterfacePublisher::unsubscribeFromSig3(long handleId)
{
    Sig3Publisher.unsubscribeFromChange(handleId);
}

void NestedStruct3InterfacePublisher::publishSig3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSig3(param1, param2, param3);
    }
    Sig3Publisher.publishChange(param1, param2, param3);
}

