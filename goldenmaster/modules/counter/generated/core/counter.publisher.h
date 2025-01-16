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
    ApiGear::Utilities::SinglePub<Test::CustomTypes::Vector3D> VectorPublisher;
    ApiGear::Utilities::SinglePub<Eigen::Vector3f> ExternVectorPublisher;
};

} // namespace Counter
} // namespace Test
