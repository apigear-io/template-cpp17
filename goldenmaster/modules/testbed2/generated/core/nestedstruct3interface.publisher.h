#pragma once

#include "testbed2/generated/api/datastructs.api.h"
#include "testbed2/generated/api/nestedstruct3interface.api.h"
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
 * The implementation of a NestedStruct3InterfacePublisher.
 * Use this class to store clients of the NestedStruct3Interface and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning Subscription management (subscribe/unsubscribe) is thread safe. However, subscriber
 * callbacks are invoked without holding any internal lock — the subscriber itself must be
 * thread safe if it can be called from multiple threads.
 */
class TEST_TESTBED2_EXPORT NestedStruct3InterfacePublisher : public INestedStruct3InterfacePublisher
{
public:
    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(INestedStruct3InterfaceSubscriber& subscriber) override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(INestedStruct3InterfaceSubscriber& subscriber) override;

    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToProp1Changed
    */
    uint64_t subscribeToProp1Changed(NestedStruct3InterfaceProp1PropertyCb callback) override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToProp1Changed
    */
    void unsubscribeFromProp1Changed(uint64_t handleId) override;

    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToProp2Changed
    */
    uint64_t subscribeToProp2Changed(NestedStruct3InterfaceProp2PropertyCb callback) override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToProp2Changed
    */
    void unsubscribeFromProp2Changed(uint64_t handleId) override;

    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToProp3Changed
    */
    uint64_t subscribeToProp3Changed(NestedStruct3InterfaceProp3PropertyCb callback) override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToProp3Changed
    */
    void unsubscribeFromProp3Changed(uint64_t handleId) override;

    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToSig1
    */
    uint64_t subscribeToSig1(NestedStruct3InterfaceSig1SignalCb callback) override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::unsubscribeFromSig1
    */
    void unsubscribeFromSig1(uint64_t handleId) override;

    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToSig2
    */
    uint64_t subscribeToSig2(NestedStruct3InterfaceSig2SignalCb callback) override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::unsubscribeFromSig2
    */
    void unsubscribeFromSig2(uint64_t handleId) override;

    /**
    * Implementation of INestedStruct3InterfacePublisher::subscribeToSig3
    */
    uint64_t subscribeToSig3(NestedStruct3InterfaceSig3SignalCb callback) override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::unsubscribeFromSig3
    */
    void unsubscribeFromSig3(uint64_t handleId) override;

    /**
    * Implementation of INestedStruct3InterfacePublisher::publishProp1Changed
    */
    void publishProp1Changed(const NestedStruct1& prop1) const override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::publishProp2Changed
    */
    void publishProp2Changed(const NestedStruct2& prop2) const override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::publishProp3Changed
    */
    void publishProp3Changed(const NestedStruct3& prop3) const override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::publishSig1
    */
    void publishSig1(const NestedStruct1& param1) const override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::publishSig2
    */
    void publishSig2(const NestedStruct1& param1, const NestedStruct2& param2) const override;
    /**
    * Implementation of INestedStruct3InterfacePublisher::publishSig3
    */
    void publishSig3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3) const override;
private:
    // Subscribers informed about any property change or signal emitted in NestedStruct3Interface
    std::vector<std::reference_wrapper<INestedStruct3InterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<NestedStruct1> Prop1Publisher;
    ApiGear::Utilities::SinglePub<NestedStruct2> Prop2Publisher;
    ApiGear::Utilities::SinglePub<NestedStruct3> Prop3Publisher;
    ApiGear::Utilities::SinglePub<NestedStruct1> Sig1Publisher;
    ApiGear::Utilities::SinglePub<NestedStruct1,NestedStruct2> Sig2Publisher;
    ApiGear::Utilities::SinglePub<NestedStruct1,NestedStruct2,NestedStruct3> Sig3Publisher;
};

} // namespace Testbed2
} // namespace Test
