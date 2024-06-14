

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
    auto handleId = m_vectorChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_vectorCallbacksMutex);
    m_vectorCallbacks[handleId] = callback;
    return handleId;
}

void CounterPublisher::unsubscribeFromVectorChanged(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_vectorCallbacksMutex);
    m_vectorCallbacks.erase(handleId);
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
    std::shared_lock<std::shared_timed_mutex> vectorCallbacksLock(m_vectorCallbacksMutex);
    const auto vectorCallbacks = m_vectorCallbacks;
    vectorCallbacksLock.unlock();
    for(const auto& callbackEntry: vectorCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(vector);
        }
    }
}

long CounterPublisher::subscribeToExternVectorChanged(CounterExternVectorPropertyCb callback)
{
    auto handleId = m_externVectorChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_externVectorCallbacksMutex);
    m_externVectorCallbacks[handleId] = callback;
    return handleId;
}

void CounterPublisher::unsubscribeFromExternVectorChanged(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_externVectorCallbacksMutex);
    m_externVectorCallbacks.erase(handleId);
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
    std::shared_lock<std::shared_timed_mutex> externVectorCallbacksLock(m_externVectorCallbacksMutex);
    const auto externVectorCallbacks = m_externVectorCallbacks;
    externVectorCallbacksLock.unlock();
    for(const auto& callbackEntry: externVectorCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(extern_vector);
        }
    }
}

