#pragma once

#include "testbed1/generated/api/datastructs.api.h"
#include "testbed1/generated/api/structinterface.api.h"
#include "testbed1/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>
#include <apigear/utilities/single_pub.hpp>

namespace Test {
namespace Testbed1 {

/**
 * The implementation of a StructInterfacePublisher.
 * Use this class to store clients of the StructInterface and inform them about the change
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
class TEST_TESTBED1_EXPORT StructInterfacePublisher : public IStructInterfacePublisher
{
public:
    /**
    * Implementation of IStructInterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(IStructInterfaceSubscriber& subscriber) override;
    /**
    * Implementation of IStructInterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(IStructInterfaceSubscriber& subscriber) override;

    /**
    * Implementation of IStructInterfacePublisher::subscribeToPropBoolChanged
    */
    uint64_t subscribeToPropBoolChanged(StructInterfacePropBoolPropertyCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::subscribeToPropBoolChanged
    */
    void unsubscribeFromPropBoolChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructInterfacePublisher::subscribeToPropIntChanged
    */
    uint64_t subscribeToPropIntChanged(StructInterfacePropIntPropertyCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructInterfacePublisher::subscribeToPropFloatChanged
    */
    uint64_t subscribeToPropFloatChanged(StructInterfacePropFloatPropertyCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::subscribeToPropFloatChanged
    */
    void unsubscribeFromPropFloatChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructInterfacePublisher::subscribeToPropStringChanged
    */
    uint64_t subscribeToPropStringChanged(StructInterfacePropStringPropertyCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::subscribeToPropStringChanged
    */
    void unsubscribeFromPropStringChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructInterfacePublisher::subscribeToSigBool
    */
    uint64_t subscribeToSigBool(StructInterfaceSigBoolSignalCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::unsubscribeFromSigBool
    */
    void unsubscribeFromSigBool(uint64_t handleId) override;

    /**
    * Implementation of IStructInterfacePublisher::subscribeToSigInt
    */
    uint64_t subscribeToSigInt(StructInterfaceSigIntSignalCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::unsubscribeFromSigInt
    */
    void unsubscribeFromSigInt(uint64_t handleId) override;

    /**
    * Implementation of IStructInterfacePublisher::subscribeToSigFloat
    */
    uint64_t subscribeToSigFloat(StructInterfaceSigFloatSignalCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::unsubscribeFromSigFloat
    */
    void unsubscribeFromSigFloat(uint64_t handleId) override;

    /**
    * Implementation of IStructInterfacePublisher::subscribeToSigString
    */
    uint64_t subscribeToSigString(StructInterfaceSigStringSignalCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::unsubscribeFromSigString
    */
    void unsubscribeFromSigString(uint64_t handleId) override;

    /**
    * Implementation of IStructInterfacePublisher::publishPropBoolChanged
    */
    void publishPropBoolChanged(const StructBool& propBool) const override;
    /**
    * Implementation of IStructInterfacePublisher::publishPropIntChanged
    */
    void publishPropIntChanged(const StructInt& propInt) const override;
    /**
    * Implementation of IStructInterfacePublisher::publishPropFloatChanged
    */
    void publishPropFloatChanged(const StructFloat& propFloat) const override;
    /**
    * Implementation of IStructInterfacePublisher::publishPropStringChanged
    */
    void publishPropStringChanged(const StructString& propString) const override;
    /**
    * Implementation of IStructInterfacePublisher::publishSigBool
    */
    void publishSigBool(const StructBool& paramBool) const override;
    /**
    * Implementation of IStructInterfacePublisher::publishSigInt
    */
    void publishSigInt(const StructInt& paramInt) const override;
    /**
    * Implementation of IStructInterfacePublisher::publishSigFloat
    */
    void publishSigFloat(const StructFloat& paramFloat) const override;
    /**
    * Implementation of IStructInterfacePublisher::publishSigString
    */
    void publishSigString(const StructString& paramString) const override;
private:
    // Subscribers informed about any property change or signal emitted in StructInterface
    std::vector<std::reference_wrapper<IStructInterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<StructBool> PropBoolPublisher;
    ApiGear::Utilities::SinglePub<StructInt> PropIntPublisher;
    ApiGear::Utilities::SinglePub<StructFloat> PropFloatPublisher;
    ApiGear::Utilities::SinglePub<StructString> PropStringPublisher;
    ApiGear::Utilities::SinglePub<StructBool> SigBoolPublisher;
    ApiGear::Utilities::SinglePub<StructInt> SigIntPublisher;
    ApiGear::Utilities::SinglePub<StructFloat> SigFloatPublisher;
    ApiGear::Utilities::SinglePub<StructString> SigStringPublisher;
};

} // namespace Testbed1
} // namespace Test
