

#include "tb_same1/generated/core/samestruct1interface.publisher.h"
#include <algorithm>


using namespace Test::TbSame1;

void SameStruct1InterfacePublisher::subscribeToAllChanges(ISameStruct1InterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<ISameStruct1InterfaceSubscriber>(subscriber));
    }
}

void SameStruct1InterfacePublisher::unsubscribeFromAllChanges(ISameStruct1InterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long SameStruct1InterfacePublisher::subscribeToProp1Changed(SameStruct1InterfaceProp1PropertyCb callback)
{
    return Prop1Publisher.subscribeForChange(callback);
}

void SameStruct1InterfacePublisher::unsubscribeFromProp1Changed(long handleId)
{
    Prop1Publisher.unsubscribeFromChange(handleId);
}

void SameStruct1InterfacePublisher::publishProp1Changed(const Struct1& prop1) const
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

long SameStruct1InterfacePublisher::subscribeToSig1(SameStruct1InterfaceSig1SignalCb callback)
{
    return Sig1Publisher.subscribeForChange(callback);
}

void SameStruct1InterfacePublisher::unsubscribeFromSig1(long handleId)
{
    Sig1Publisher.unsubscribeFromChange(handleId);
}

void SameStruct1InterfacePublisher::publishSig1(const Struct1& param1) const
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

