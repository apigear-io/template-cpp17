#pragma once

#include "counter/generated/api/datastructs.api.h"
#include "counter/generated/api/counter.api.h"
#include "counter/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>
#include <apigear/utilities/single_pub.hpp>

namespace Test {
namespace Counter {

/**
 * The implementation of a CounterPublisher.
 * Use this class to store clients of the Counter and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning Subscription management (subscribe/unsubscribe) is thread safe. However, subscriber
 * callbacks are invoked without holding any internal lock — the subscriber itself must be
 * thread safe if it can be called from multiple threads.
 * @warning Subscribers are stored by reference. The caller MUST ensure that
 *          subscriber objects outlive their subscription. Destroying a subscriber
 *          without calling unsubscribeFromAllChanges() first causes undefined behavior.
 * @warning Subscriber callbacks are invoked outside any lock. Subscriber
 *          implementations must be thread-safe.
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
    uint64_t subscribeToVectorChanged(CounterVectorPropertyCb callback) override;
    /**
    * Implementation of ICounterPublisher::subscribeToVectorChanged
    */
    void unsubscribeFromVectorChanged(uint64_t handleId) override;

    /**
    * Implementation of ICounterPublisher::subscribeToExternVectorChanged
    */
    uint64_t subscribeToExternVectorChanged(CounterExternVectorPropertyCb callback) override;
    /**
    * Implementation of ICounterPublisher::subscribeToExternVectorChanged
    */
    void unsubscribeFromExternVectorChanged(uint64_t handleId) override;

    /**
    * Implementation of ICounterPublisher::subscribeToVectorArrayChanged
    */
    uint64_t subscribeToVectorArrayChanged(CounterVectorArrayPropertyCb callback) override;
    /**
    * Implementation of ICounterPublisher::subscribeToVectorArrayChanged
    */
    void unsubscribeFromVectorArrayChanged(uint64_t handleId) override;

    /**
    * Implementation of ICounterPublisher::subscribeToExternVectorArrayChanged
    */
    uint64_t subscribeToExternVectorArrayChanged(CounterExternVectorArrayPropertyCb callback) override;
    /**
    * Implementation of ICounterPublisher::subscribeToExternVectorArrayChanged
    */
    void unsubscribeFromExternVectorArrayChanged(uint64_t handleId) override;

    /**
    * Implementation of ICounterPublisher::subscribeToValueChanged
    */
    uint64_t subscribeToValueChanged(CounterValueChangedSignalCb callback) override;
    /**
    * Implementation of ICounterPublisher::unsubscribeFromValueChanged
    */
    void unsubscribeFromValueChanged(uint64_t handleId) override;

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
    ApiGear::Utilities::SinglePub<Test::CustomTypes::Vector3D> VectorPublisher;
    ApiGear::Utilities::SinglePub<Eigen::Vector3f> ExternVectorPublisher;
    ApiGear::Utilities::SinglePub<std::list<Test::CustomTypes::Vector3D>> VectorArrayPublisher;
    ApiGear::Utilities::SinglePub<std::list<Eigen::Vector3f>> ExternVectorArrayPublisher;
    ApiGear::Utilities::SinglePub<Test::CustomTypes::Vector3D,Eigen::Vector3f,std::list<Test::CustomTypes::Vector3D>,std::list<Eigen::Vector3f>> ValueChangedPublisher;
};

} // namespace Counter
} // namespace Test
