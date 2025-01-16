

#include "tb_enum/generated/core/enuminterface.publisher.h"
#include <algorithm>


using namespace Test::TbEnum;

void EnumInterfacePublisher::subscribeToAllChanges(IEnumInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<IEnumInterfaceSubscriber>(subscriber));
    }
}

void EnumInterfacePublisher::unsubscribeFromAllChanges(IEnumInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long EnumInterfacePublisher::subscribeToProp0Changed(EnumInterfaceProp0PropertyCb callback)
{
    return Prop0Publisher.subscribeForChange(callback);
}

void EnumInterfacePublisher::unsubscribeFromProp0Changed(long handleId)
{
    Prop0Publisher.unsubscribeFromChange(handleId);
}

void EnumInterfacePublisher::publishProp0Changed(Enum0Enum prop0) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onProp0Changed(prop0);
    }
    Prop0Publisher.publishChange(prop0);
}

long EnumInterfacePublisher::subscribeToProp1Changed(EnumInterfaceProp1PropertyCb callback)
{
    return Prop1Publisher.subscribeForChange(callback);
}

void EnumInterfacePublisher::unsubscribeFromProp1Changed(long handleId)
{
    Prop1Publisher.unsubscribeFromChange(handleId);
}

void EnumInterfacePublisher::publishProp1Changed(Enum1Enum prop1) const
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

long EnumInterfacePublisher::subscribeToProp2Changed(EnumInterfaceProp2PropertyCb callback)
{
    return Prop2Publisher.subscribeForChange(callback);
}

void EnumInterfacePublisher::unsubscribeFromProp2Changed(long handleId)
{
    Prop2Publisher.unsubscribeFromChange(handleId);
}

void EnumInterfacePublisher::publishProp2Changed(Enum2Enum prop2) const
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

long EnumInterfacePublisher::subscribeToProp3Changed(EnumInterfaceProp3PropertyCb callback)
{
    return Prop3Publisher.subscribeForChange(callback);
}

void EnumInterfacePublisher::unsubscribeFromProp3Changed(long handleId)
{
    Prop3Publisher.unsubscribeFromChange(handleId);
}

void EnumInterfacePublisher::publishProp3Changed(Enum3Enum prop3) const
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

long EnumInterfacePublisher::subscribeToSig0(EnumInterfaceSig0SignalCb callback)
{
    return Sig0Publisher.subscribeForChange(callback);
}

void EnumInterfacePublisher::unsubscribeFromSig0(long handleId)
{
    Sig0Publisher.unsubscribeFromChange(handleId);
}

void EnumInterfacePublisher::publishSig0(Enum0Enum param0) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSig0(param0);
    }
    Sig0Publisher.publishChange(param0);
}

long EnumInterfacePublisher::subscribeToSig1(EnumInterfaceSig1SignalCb callback)
{
    return Sig1Publisher.subscribeForChange(callback);
}

void EnumInterfacePublisher::unsubscribeFromSig1(long handleId)
{
    Sig1Publisher.unsubscribeFromChange(handleId);
}

void EnumInterfacePublisher::publishSig1(Enum1Enum param1) const
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

long EnumInterfacePublisher::subscribeToSig2(EnumInterfaceSig2SignalCb callback)
{
    return Sig2Publisher.subscribeForChange(callback);
}

void EnumInterfacePublisher::unsubscribeFromSig2(long handleId)
{
    Sig2Publisher.unsubscribeFromChange(handleId);
}

void EnumInterfacePublisher::publishSig2(Enum2Enum param2) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSig2(param2);
    }
    Sig2Publisher.publishChange(param2);
}

long EnumInterfacePublisher::subscribeToSig3(EnumInterfaceSig3SignalCb callback)
{
    return Sig3Publisher.subscribeForChange(callback);
}

void EnumInterfacePublisher::unsubscribeFromSig3(long handleId)
{
    Sig3Publisher.unsubscribeFromChange(handleId);
}

void EnumInterfacePublisher::publishSig3(Enum3Enum param3) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSig3(param3);
    }
    Sig3Publisher.publishChange(param3);
}

