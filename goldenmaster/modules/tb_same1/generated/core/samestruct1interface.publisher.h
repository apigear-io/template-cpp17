#pragma once

#include "tb_same1/generated/api/datastructs.api.h"
#include "tb_same1/generated/api/samestruct1interface.api.h"
#include "tb_same1/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>
#include <apigear/utilities/single_pub.hpp>

namespace Test {
namespace TbSame1 {

/**
 * The implementation of a SameStruct1InterfacePublisher.
 * Use this class to store clients of the SameStruct1Interface and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning Subscription management (subscribe/unsubscribe) is thread safe. However, subscriber
 * callbacks are invoked without holding any internal lock — the subscriber itself must be
 * thread safe if it can be called from multiple threads.
 */
class TEST_TB_SAME1_EXPORT SameStruct1InterfacePublisher : public ISameStruct1InterfacePublisher
{
public:
    /**
    * Implementation of ISameStruct1InterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(ISameStruct1InterfaceSubscriber& subscriber) override;
    /**
    * Implementation of ISameStruct1InterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(ISameStruct1InterfaceSubscriber& subscriber) override;

    /**
    * Implementation of ISameStruct1InterfacePublisher::subscribeToProp1Changed
    */
    uint64_t subscribeToProp1Changed(SameStruct1InterfaceProp1PropertyCb callback) override;
    /**
    * Implementation of ISameStruct1InterfacePublisher::subscribeToProp1Changed
    */
    void unsubscribeFromProp1Changed(uint64_t handleId) override;

    /**
    * Implementation of ISameStruct1InterfacePublisher::subscribeToSig1
    */
    uint64_t subscribeToSig1(SameStruct1InterfaceSig1SignalCb callback) override;
    /**
    * Implementation of ISameStruct1InterfacePublisher::unsubscribeFromSig1
    */
    void unsubscribeFromSig1(uint64_t handleId) override;

    /**
    * Implementation of ISameStruct1InterfacePublisher::publishProp1Changed
    */
    void publishProp1Changed(const Struct1& prop1) const override;
    /**
    * Implementation of ISameStruct1InterfacePublisher::publishSig1
    */
    void publishSig1(const Struct1& param1) const override;
private:
    // Subscribers informed about any property change or signal emitted in SameStruct1Interface
    std::vector<std::reference_wrapper<ISameStruct1InterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<Struct1> Prop1Publisher;
    ApiGear::Utilities::SinglePub<Struct1> Sig1Publisher;
};

} // namespace TbSame1
} // namespace Test
