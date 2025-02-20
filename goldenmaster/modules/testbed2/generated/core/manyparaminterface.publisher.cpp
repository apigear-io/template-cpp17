

#include "testbed2/generated/core/manyparaminterface.publisher.h"
#include <algorithm>


using namespace Test::Testbed2;

void ManyParamInterfacePublisher::subscribeToAllChanges(IManyParamInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<IManyParamInterfaceSubscriber>(subscriber));
    }
}

void ManyParamInterfacePublisher::unsubscribeFromAllChanges(IManyParamInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long ManyParamInterfacePublisher::subscribeToProp1Changed(ManyParamInterfaceProp1PropertyCb callback)
{
    return Prop1Publisher.subscribeForChange(callback);
}

void ManyParamInterfacePublisher::unsubscribeFromProp1Changed(long handleId)
{
    Prop1Publisher.unsubscribeFromChange(handleId);
}

void ManyParamInterfacePublisher::publishProp1Changed(int prop1) const
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

long ManyParamInterfacePublisher::subscribeToProp2Changed(ManyParamInterfaceProp2PropertyCb callback)
{
    return Prop2Publisher.subscribeForChange(callback);
}

void ManyParamInterfacePublisher::unsubscribeFromProp2Changed(long handleId)
{
    Prop2Publisher.unsubscribeFromChange(handleId);
}

void ManyParamInterfacePublisher::publishProp2Changed(int prop2) const
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

long ManyParamInterfacePublisher::subscribeToProp3Changed(ManyParamInterfaceProp3PropertyCb callback)
{
    return Prop3Publisher.subscribeForChange(callback);
}

void ManyParamInterfacePublisher::unsubscribeFromProp3Changed(long handleId)
{
    Prop3Publisher.unsubscribeFromChange(handleId);
}

void ManyParamInterfacePublisher::publishProp3Changed(int prop3) const
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

long ManyParamInterfacePublisher::subscribeToProp4Changed(ManyParamInterfaceProp4PropertyCb callback)
{
    return Prop4Publisher.subscribeForChange(callback);
}

void ManyParamInterfacePublisher::unsubscribeFromProp4Changed(long handleId)
{
    Prop4Publisher.unsubscribeFromChange(handleId);
}

void ManyParamInterfacePublisher::publishProp4Changed(int prop4) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onProp4Changed(prop4);
    }
    Prop4Publisher.publishChange(prop4);
}

long ManyParamInterfacePublisher::subscribeToSig1(ManyParamInterfaceSig1SignalCb callback)
{
    return Sig1Publisher.subscribeForChange(callback);
}

void ManyParamInterfacePublisher::unsubscribeFromSig1(long handleId)
{
    Sig1Publisher.unsubscribeFromChange(handleId);
}

void ManyParamInterfacePublisher::publishSig1(int param1) const
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

long ManyParamInterfacePublisher::subscribeToSig2(ManyParamInterfaceSig2SignalCb callback)
{
    return Sig2Publisher.subscribeForChange(callback);
}

void ManyParamInterfacePublisher::unsubscribeFromSig2(long handleId)
{
    Sig2Publisher.unsubscribeFromChange(handleId);
}

void ManyParamInterfacePublisher::publishSig2(int param1, int param2) const
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

long ManyParamInterfacePublisher::subscribeToSig3(ManyParamInterfaceSig3SignalCb callback)
{
    return Sig3Publisher.subscribeForChange(callback);
}

void ManyParamInterfacePublisher::unsubscribeFromSig3(long handleId)
{
    Sig3Publisher.unsubscribeFromChange(handleId);
}

void ManyParamInterfacePublisher::publishSig3(int param1, int param2, int param3) const
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

long ManyParamInterfacePublisher::subscribeToSig4(ManyParamInterfaceSig4SignalCb callback)
{
    return Sig4Publisher.subscribeForChange(callback);
}

void ManyParamInterfacePublisher::unsubscribeFromSig4(long handleId)
{
    Sig4Publisher.unsubscribeFromChange(handleId);
}

void ManyParamInterfacePublisher::publishSig4(int param1, int param2, int param3, int param4) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSig4(param1, param2, param3, param4);
    }
    Sig4Publisher.publishChange(param1, param2, param3, param4);
}

