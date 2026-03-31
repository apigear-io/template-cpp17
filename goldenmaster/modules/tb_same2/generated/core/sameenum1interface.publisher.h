#pragma once

#include "tb_same2/generated/api/datastructs.api.h"
#include "tb_same2/generated/api/sameenum1interface.api.h"
#include "tb_same2/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>
#include <apigear/utilities/single_pub.hpp>

namespace Test {
namespace TbSame2 {

/**
 * The implementation of a SameEnum1InterfacePublisher.
 * Use this class to store clients of the SameEnum1Interface and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning Subscription management (subscribe/unsubscribe) is thread safe. However, subscriber
 * callbacks are invoked without holding any internal lock — the subscriber itself must be
 * thread safe if it can be called from multiple threads.
 */
class TEST_TB_SAME2_EXPORT SameEnum1InterfacePublisher : public ISameEnum1InterfacePublisher
{
public:
    /**
    * Implementation of ISameEnum1InterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(ISameEnum1InterfaceSubscriber& subscriber) override;
    /**
    * Implementation of ISameEnum1InterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(ISameEnum1InterfaceSubscriber& subscriber) override;

    /**
    * Implementation of ISameEnum1InterfacePublisher::subscribeToProp1Changed
    */
    uint64_t subscribeToProp1Changed(SameEnum1InterfaceProp1PropertyCb callback) override;
    /**
    * Implementation of ISameEnum1InterfacePublisher::subscribeToProp1Changed
    */
    void unsubscribeFromProp1Changed(uint64_t handleId) override;

    /**
    * Implementation of ISameEnum1InterfacePublisher::subscribeToSig1
    */
    uint64_t subscribeToSig1(SameEnum1InterfaceSig1SignalCb callback) override;
    /**
    * Implementation of ISameEnum1InterfacePublisher::unsubscribeFromSig1
    */
    void unsubscribeFromSig1(uint64_t handleId) override;

    /**
    * Implementation of ISameEnum1InterfacePublisher::publishProp1Changed
    */
    void publishProp1Changed(Enum1Enum prop1) const override;
    /**
    * Implementation of ISameEnum1InterfacePublisher::publishSig1
    */
    void publishSig1(Enum1Enum param1) const override;
private:
    // Subscribers informed about any property change or signal emitted in SameEnum1Interface
    std::vector<std::reference_wrapper<ISameEnum1InterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<Enum1Enum> Prop1Publisher;
    ApiGear::Utilities::SinglePub<Enum1Enum> Sig1Publisher;
};

} // namespace TbSame2
} // namespace Test
