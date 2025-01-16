

#include "tb_simple/generated/core/nopropertiesinterface.publisher.h"
#include <algorithm>


using namespace Test::TbSimple;

void NoPropertiesInterfacePublisher::subscribeToAllChanges(INoPropertiesInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<INoPropertiesInterfaceSubscriber>(subscriber));
    }
}

void NoPropertiesInterfacePublisher::unsubscribeFromAllChanges(INoPropertiesInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long NoPropertiesInterfacePublisher::subscribeToSigVoid(NoPropertiesInterfaceSigVoidSignalCb callback)
{
    return SigVoidPublisher.subscribeForChange(callback);
}

void NoPropertiesInterfacePublisher::unsubscribeFromSigVoid(long handleId)
{
    SigVoidPublisher.unsubscribeFromChange(handleId);
}

void NoPropertiesInterfacePublisher::publishSigVoid() const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigVoid();
    }
    SigVoidPublisher.publishChange();
}

long NoPropertiesInterfacePublisher::subscribeToSigBool(NoPropertiesInterfaceSigBoolSignalCb callback)
{
    return SigBoolPublisher.subscribeForChange(callback);
}

void NoPropertiesInterfacePublisher::unsubscribeFromSigBool(long handleId)
{
    SigBoolPublisher.unsubscribeFromChange(handleId);
}

void NoPropertiesInterfacePublisher::publishSigBool(bool paramBool) const
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

