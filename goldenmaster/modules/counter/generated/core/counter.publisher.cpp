

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

long CounterPublisher::subscribeToVectorArrayChanged(CounterVectorArrayPropertyCb callback)
{
    auto handleId = m_vectorArrayChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_vectorArrayCallbacksMutex);
    m_vectorArrayCallbacks[handleId] = callback;
    return handleId;
}

void CounterPublisher::unsubscribeFromVectorArrayChanged(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_vectorArrayCallbacksMutex);
    m_vectorArrayCallbacks.erase(handleId);
}

void CounterPublisher::publishVectorArrayChanged(const std::list<Test::CustomTypes::Vector3D>& vectorArray) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onVectorArrayChanged(vectorArray);
    }
    std::shared_lock<std::shared_timed_mutex> vectorArrayCallbacksLock(m_vectorArrayCallbacksMutex);
    const auto vectorArrayCallbacks = m_vectorArrayCallbacks;
    vectorArrayCallbacksLock.unlock();
    for(const auto& callbackEntry: vectorArrayCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(vectorArray);
        }
    }
}

long CounterPublisher::subscribeToExternVectorArrayChanged(CounterExternVectorArrayPropertyCb callback)
{
    auto handleId = m_externVectorArrayChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_externVectorArrayCallbacksMutex);
    m_externVectorArrayCallbacks[handleId] = callback;
    return handleId;
}

void CounterPublisher::unsubscribeFromExternVectorArrayChanged(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_externVectorArrayCallbacksMutex);
    m_externVectorArrayCallbacks.erase(handleId);
}

void CounterPublisher::publishExternVectorArrayChanged(const std::list<Eigen::Vector3f>& extern_vectorArray) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onExternVectorArrayChanged(extern_vectorArray);
    }
    std::shared_lock<std::shared_timed_mutex> externVectorArrayCallbacksLock(m_externVectorArrayCallbacksMutex);
    const auto externVectorArrayCallbacks = m_externVectorArrayCallbacks;
    externVectorArrayCallbacksLock.unlock();
    for(const auto& callbackEntry: externVectorArrayCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(extern_vectorArray);
        }
    }
}

long CounterPublisher::subscribeToValueChanged(CounterValueChangedSignalCb callback)
{
    // this is a short term workaround - we need a better solution for unique handle identifiers
    auto handleId = m_valueChangedSignalCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_valueChangedCallbacksMutex);
    m_valueChangedCallbacks[handleId] = callback;
    return handleId;
}

void CounterPublisher::unsubscribeFromValueChanged(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_valueChangedCallbacksMutex);
    m_valueChangedCallbacks.erase(handleId);
}

void CounterPublisher::publishValueChanged(const Test::CustomTypes::Vector3D& vector, const Eigen::Vector3f& extern_vector, const std::list<Test::CustomTypes::Vector3D>& vectorArray, const std::list<Eigen::Vector3f>& extern_vectorArray) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onValueChanged(vector, extern_vector, vectorArray, extern_vectorArray);
    }
    std::shared_lock<std::shared_timed_mutex> valueChangedCallbacksLock(m_valueChangedCallbacksMutex);
    const auto valueChangedCallbacks = m_valueChangedCallbacks;
    valueChangedCallbacksLock.unlock();
    for(const auto& callbackEntry: valueChangedCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(vector, extern_vector, vectorArray, extern_vectorArray);
        }
    }
}

