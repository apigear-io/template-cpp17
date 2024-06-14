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
    * Implementation of ICounterPublisher::publishVectorChanged
    */
    void publishVectorChanged(const Test::CustomTypes::Vector3D& vector) const override;
    /**
    * Implementation of ICounterPublisher::publishExternVectorChanged
    */
    void publishExternVectorChanged(const Eigen::Vector3f& extern_vector) const override;
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
};

} // namespace Counter
} // namespace Test
