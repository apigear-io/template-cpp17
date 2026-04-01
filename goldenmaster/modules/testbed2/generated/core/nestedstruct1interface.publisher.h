#pragma once

#include "testbed2/generated/api/datastructs.api.h"
#include "testbed2/generated/api/nestedstruct1interface.api.h"
#include "testbed2/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>
#include <apigear/utilities/single_pub.hpp>

namespace Test {
namespace Testbed2 {

/**
 * The implementation of a NestedStruct1InterfacePublisher.
 * Use this class to store clients of the NestedStruct1Interface and inform them about the change
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
class TEST_TESTBED2_EXPORT NestedStruct1InterfacePublisher : public INestedStruct1InterfacePublisher
{
public:
    /**
    * Implementation of INestedStruct1InterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(INestedStruct1InterfaceSubscriber& subscriber) override;
    /**
    * Implementation of INestedStruct1InterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(INestedStruct1InterfaceSubscriber& subscriber) override;

    /**
    * Implementation of INestedStruct1InterfacePublisher::subscribeToProp1Changed
    */
    uint64_t subscribeToProp1Changed(NestedStruct1InterfaceProp1PropertyCb callback) override;
    /**
    * Implementation of INestedStruct1InterfacePublisher::subscribeToProp1Changed
    */
    void unsubscribeFromProp1Changed(uint64_t handleId) override;

    /**
    * Implementation of INestedStruct1InterfacePublisher::subscribeToSig1
    */
    uint64_t subscribeToSig1(NestedStruct1InterfaceSig1SignalCb callback) override;
    /**
    * Implementation of INestedStruct1InterfacePublisher::unsubscribeFromSig1
    */
    void unsubscribeFromSig1(uint64_t handleId) override;

    /**
    * Implementation of INestedStruct1InterfacePublisher::publishProp1Changed
    */
    void publishProp1Changed(const NestedStruct1& prop1) const override;
    /**
    * Implementation of INestedStruct1InterfacePublisher::publishSig1
    */
    void publishSig1(const NestedStruct1& param1) const override;
private:
    // Subscribers informed about any property change or signal emitted in NestedStruct1Interface
    std::vector<std::reference_wrapper<INestedStruct1InterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<NestedStruct1> Prop1Publisher;
    ApiGear::Utilities::SinglePub<NestedStruct1> Sig1Publisher;
};

} // namespace Testbed2
} // namespace Test
