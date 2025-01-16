

#include "counter/generated/core/counter.publisher.h"
#include <algorithm>


using namespace Test::Counter;

void CounterPublisher::subscribeToAllChanges(ICounterSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<ICounterSubscriber>(subscriber));
    }
}

void CounterPublisher::unsubscribeFromAllChanges(ICounterSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long CounterPublisher::subscribeToVectorChanged(CounterVectorPropertyCb callback)
{
    return VectorPublisher.subscribeForChange(callback);
}

void CounterPublisher::unsubscribeFromVectorChanged(long handleId)
{
    VectorPublisher.unsubscribeFromChange(handleId);
}

void CounterPublisher::publishVectorChanged(const Test::CustomTypes::Vector3D& vector) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onVectorChanged(vector);
    }
    VectorPublisher.publishChange(vector);
}

long CounterPublisher::subscribeToExternVectorChanged(CounterExternVectorPropertyCb callback)
{
    return ExternVectorPublisher.subscribeForChange(callback);
}

void CounterPublisher::unsubscribeFromExternVectorChanged(long handleId)
{
    ExternVectorPublisher.unsubscribeFromChange(handleId);
}

void CounterPublisher::publishExternVectorChanged(const Eigen::Vector3f& extern_vector) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onExternVectorChanged(extern_vector);
    }
    ExternVectorPublisher.publishChange(extern_vector);
}

