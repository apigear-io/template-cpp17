#pragma once

#include "counter/generated/api/datastructs.api.h"
#include "counter/generated/api/counter.api.h"
#include "counter/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>

namespace Test {
namespace Counter {

/**
 * The implementation of a CounterPublisher.
 * Use this class to store clients of the Counter and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
 */
class TEST_COUNTER_EXPORT CounterPublisher : public ICounterPublisher
{
public:
    /**
    * Implementation of ICounterPublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(ICounterSubscriber& subscriber) override;
    /**
    * Implementation of ICounterPublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(ICounterSubscriber& subscriber) override;

    /**
    * Implementation of ICounterPublisher::subscribeToVectorChanged
    */
    long subscribeToVectorChanged(CounterVectorPropertyCb callback) override;
    /**
    * Implementation of ICounterPublisher::subscribeToVectorChanged
    */
    void unsubscribeFromVectorChanged(long handleId) override;

    /**
    * Implementation of ICounterPublisher::subscribeToExternVectorChanged
    */
    long subscribeToExternVectorChanged(CounterExternVectorPropertyCb callback) override;
    /**
    * Implementation of ICounterPublisher::subscribeToExternVectorChanged
    */
    void unsubscribeFromExternVectorChanged(long handleId) override;

    /**
    * Implementation of ICounterPublisher::subscribeToVectorArrayChanged
    */
    long subscribeToVectorArrayChanged(CounterVectorArrayPropertyCb callback) override;
    /**
    * Implementation of ICounterPublisher::subscribeToVectorArrayChanged
    */
    void unsubscribeFromVectorArrayChanged(long handleId) override;

    /**
    * Implementation of ICounterPublisher::subscribeToExternVectorArrayChanged
    */
    long subscribeToExternVectorArrayChanged(CounterExternVectorArrayPropertyCb callback) override;
    /**
    * Implementation of ICounterPublisher::subscribeToExternVectorArrayChanged
    */
    void unsubscribeFromExternVectorArrayChanged(long handleId) override;

    /**
    * Implementation of ICounterPublisher::subscribeToValueChanged
    */
    long subscribeToValueChanged(CounterValueChangedSignalCb callback) override;
    /**
    * Implementation of ICounterPublisher::unsubscribeFromValueChanged
    */
    void unsubscribeFromValueChanged(long handleId) override;

    /**
    * Implementation of ICounterPublisher::publishVectorChanged
    */
    void publishVectorChanged(const Test::CustomTypes::Vector3D& vector) const override;
    /**
    * Implementation of ICounterPublisher::publishExternVectorChanged
    */
    void publishExternVectorChanged(const Eigen::Vector3f& extern_vector) const override;
    /**
    * Implementation of ICounterPublisher::publishVectorArrayChanged
    */
    void publishVectorArrayChanged(const std::list<Test::CustomTypes::Vector3D>& vectorArray) const override;
    /**
    * Implementation of ICounterPublisher::publishExternVectorArrayChanged
    */
    void publishExternVectorArrayChanged(const std::list<Eigen::Vector3f>& extern_vectorArray) const override;
    /**
    * Implementation of ICounterPublisher::publishValueChanged
    */
    void publishValueChanged(const Test::CustomTypes::Vector3D& vector, const Eigen::Vector3f& extern_vector, const std::list<Test::CustomTypes::Vector3D>& vectorArray, const std::list<Eigen::Vector3f>& extern_vectorArray) const override;
private:
    // Subscribers informed about any property change or signal emitted in Counter
    std::vector<std::reference_wrapper<ICounterSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    // Next free unique identifier to subscribe for the Vector change.
    std::atomic<long> m_vectorChangedCallbackNextId {0};
    // Subscribed callbacks for the Vector change.
    std::map<long, CounterVectorPropertyCb> m_vectorCallbacks;
    // Mutex for m_vectorCallbacks
    mutable std::shared_timed_mutex m_vectorCallbacksMutex;
    // Next free unique identifier to subscribe for the ExternVector change.
    std::atomic<long> m_externVectorChangedCallbackNextId {0};
    // Subscribed callbacks for the ExternVector change.
    std::map<long, CounterExternVectorPropertyCb> m_externVectorCallbacks;
    // Mutex for m_externVectorCallbacks
    mutable std::shared_timed_mutex m_externVectorCallbacksMutex;
    // Next free unique identifier to subscribe for the VectorArray change.
    std::atomic<long> m_vectorArrayChangedCallbackNextId {0};
    // Subscribed callbacks for the VectorArray change.
    std::map<long, CounterVectorArrayPropertyCb> m_vectorArrayCallbacks;
    // Mutex for m_vectorArrayCallbacks
    mutable std::shared_timed_mutex m_vectorArrayCallbacksMutex;
    // Next free unique identifier to subscribe for the ExternVectorArray change.
    std::atomic<long> m_externVectorArrayChangedCallbackNextId {0};
    // Subscribed callbacks for the ExternVectorArray change.
    std::map<long, CounterExternVectorArrayPropertyCb> m_externVectorArrayCallbacks;
    // Mutex for m_externVectorArrayCallbacks
    mutable std::shared_timed_mutex m_externVectorArrayCallbacksMutex;
    // Next free unique identifier to subscribe for the ValueChanged emission.
    std::atomic<long> m_valueChangedSignalCallbackNextId {0};
    // Subscribed callbacks for the ValueChanged emission.
    std::map<long, CounterValueChangedSignalCb > m_valueChangedCallbacks;
    // Mutex for m_valueChangedSignalCallbackNextId and m_valueChangedCallbacks
    mutable std::shared_timed_mutex m_valueChangedCallbacksMutex;
};

} // namespace Counter
} // namespace Test
