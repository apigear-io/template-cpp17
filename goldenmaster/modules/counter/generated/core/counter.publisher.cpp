

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

uint64_t CounterPublisher::subscribeToVectorChanged(CounterVectorPropertyCb callback)
{
    return VectorPublisher.subscribeForChange(callback);
}

void CounterPublisher::unsubscribeFromVectorChanged(uint64_t handleId)
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

uint64_t CounterPublisher::subscribeToExternVectorChanged(CounterExternVectorPropertyCb callback)
{
    return ExternVectorPublisher.subscribeForChange(callback);
}

void CounterPublisher::unsubscribeFromExternVectorChanged(uint64_t handleId)
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

uint64_t CounterPublisher::subscribeToVectorArrayChanged(CounterVectorArrayPropertyCb callback)
{
    return VectorArrayPublisher.subscribeForChange(callback);
}

void CounterPublisher::unsubscribeFromVectorArrayChanged(uint64_t handleId)
{
    VectorArrayPublisher.unsubscribeFromChange(handleId);
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
    VectorArrayPublisher.publishChange(vectorArray);
}

uint64_t CounterPublisher::subscribeToExternVectorArrayChanged(CounterExternVectorArrayPropertyCb callback)
{
    return ExternVectorArrayPublisher.subscribeForChange(callback);
}

void CounterPublisher::unsubscribeFromExternVectorArrayChanged(uint64_t handleId)
{
    ExternVectorArrayPublisher.unsubscribeFromChange(handleId);
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
    ExternVectorArrayPublisher.publishChange(extern_vectorArray);
}

uint64_t CounterPublisher::subscribeToValueChanged(CounterValueChangedSignalCb callback)
{
    return ValueChangedPublisher.subscribeForChange(callback);
}

void CounterPublisher::unsubscribeFromValueChanged(uint64_t handleId)
{
    ValueChangedPublisher.unsubscribeFromChange(handleId);
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
    ValueChangedPublisher.publishChange(vector, extern_vector, vectorArray, extern_vectorArray);
}

