#pragma once

#include "testbed1/generated/api/datastructs.api.h"
#include "testbed1/generated/api/structarray2interface.api.h"
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
 * The implementation of a StructArray2InterfacePublisher.
 * Use this class to store clients of the StructArray2Interface and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning Subscription management (subscribe/unsubscribe) is thread safe. However, subscriber
 * callbacks are invoked without holding any internal lock — the subscriber itself must be
 * thread safe if it can be called from multiple threads.
 */
class TEST_TESTBED1_EXPORT StructArray2InterfacePublisher : public IStructArray2InterfacePublisher
{
public:
    /**
    * Implementation of IStructArray2InterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(IStructArray2InterfaceSubscriber& subscriber) override;
    /**
    * Implementation of IStructArray2InterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(IStructArray2InterfaceSubscriber& subscriber) override;

    /**
    * Implementation of IStructArray2InterfacePublisher::subscribeToPropBoolChanged
    */
    uint64_t subscribeToPropBoolChanged(StructArray2InterfacePropBoolPropertyCb callback) override;
    /**
    * Implementation of IStructArray2InterfacePublisher::subscribeToPropBoolChanged
    */
    void unsubscribeFromPropBoolChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructArray2InterfacePublisher::subscribeToPropIntChanged
    */
    uint64_t subscribeToPropIntChanged(StructArray2InterfacePropIntPropertyCb callback) override;
    /**
    * Implementation of IStructArray2InterfacePublisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructArray2InterfacePublisher::subscribeToPropFloatChanged
    */
    uint64_t subscribeToPropFloatChanged(StructArray2InterfacePropFloatPropertyCb callback) override;
    /**
    * Implementation of IStructArray2InterfacePublisher::subscribeToPropFloatChanged
    */
    void unsubscribeFromPropFloatChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructArray2InterfacePublisher::subscribeToPropStringChanged
    */
    uint64_t subscribeToPropStringChanged(StructArray2InterfacePropStringPropertyCb callback) override;
    /**
    * Implementation of IStructArray2InterfacePublisher::subscribeToPropStringChanged
    */
    void unsubscribeFromPropStringChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructArray2InterfacePublisher::subscribeToPropEnumChanged
    */
    uint64_t subscribeToPropEnumChanged(StructArray2InterfacePropEnumPropertyCb callback) override;
    /**
    * Implementation of IStructArray2InterfacePublisher::subscribeToPropEnumChanged
    */
    void unsubscribeFromPropEnumChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructArray2InterfacePublisher::subscribeToSigBool
    */
    uint64_t subscribeToSigBool(StructArray2InterfaceSigBoolSignalCb callback) override;
    /**
    * Implementation of IStructArray2InterfacePublisher::unsubscribeFromSigBool
    */
    void unsubscribeFromSigBool(uint64_t handleId) override;

    /**
    * Implementation of IStructArray2InterfacePublisher::subscribeToSigInt
    */
    uint64_t subscribeToSigInt(StructArray2InterfaceSigIntSignalCb callback) override;
    /**
    * Implementation of IStructArray2InterfacePublisher::unsubscribeFromSigInt
    */
    void unsubscribeFromSigInt(uint64_t handleId) override;

    /**
    * Implementation of IStructArray2InterfacePublisher::subscribeToSigFloat
    */
    uint64_t subscribeToSigFloat(StructArray2InterfaceSigFloatSignalCb callback) override;
    /**
    * Implementation of IStructArray2InterfacePublisher::unsubscribeFromSigFloat
    */
    void unsubscribeFromSigFloat(uint64_t handleId) override;

    /**
    * Implementation of IStructArray2InterfacePublisher::subscribeToSigString
    */
    uint64_t subscribeToSigString(StructArray2InterfaceSigStringSignalCb callback) override;
    /**
    * Implementation of IStructArray2InterfacePublisher::unsubscribeFromSigString
    */
    void unsubscribeFromSigString(uint64_t handleId) override;

    /**
    * Implementation of IStructArray2InterfacePublisher::publishPropBoolChanged
    */
    void publishPropBoolChanged(const StructBoolWithArray& propBool) const override;
    /**
    * Implementation of IStructArray2InterfacePublisher::publishPropIntChanged
    */
    void publishPropIntChanged(const StructIntWithArray& propInt) const override;
    /**
    * Implementation of IStructArray2InterfacePublisher::publishPropFloatChanged
    */
    void publishPropFloatChanged(const StructFloatWithArray& propFloat) const override;
    /**
    * Implementation of IStructArray2InterfacePublisher::publishPropStringChanged
    */
    void publishPropStringChanged(const StructStringWithArray& propString) const override;
    /**
    * Implementation of IStructArray2InterfacePublisher::publishPropEnumChanged
    */
    void publishPropEnumChanged(const StructEnumWithArray& propEnum) const override;
    /**
    * Implementation of IStructArray2InterfacePublisher::publishSigBool
    */
    void publishSigBool(const StructBoolWithArray& paramBool) const override;
    /**
    * Implementation of IStructArray2InterfacePublisher::publishSigInt
    */
    void publishSigInt(const StructIntWithArray& paramInt) const override;
    /**
    * Implementation of IStructArray2InterfacePublisher::publishSigFloat
    */
    void publishSigFloat(const StructFloatWithArray& paramFloat) const override;
    /**
    * Implementation of IStructArray2InterfacePublisher::publishSigString
    */
    void publishSigString(const StructStringWithArray& paramString) const override;
private:
    // Subscribers informed about any property change or signal emitted in StructArray2Interface
    std::vector<std::reference_wrapper<IStructArray2InterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<StructBoolWithArray> PropBoolPublisher;
    ApiGear::Utilities::SinglePub<StructIntWithArray> PropIntPublisher;
    ApiGear::Utilities::SinglePub<StructFloatWithArray> PropFloatPublisher;
    ApiGear::Utilities::SinglePub<StructStringWithArray> PropStringPublisher;
    ApiGear::Utilities::SinglePub<StructEnumWithArray> PropEnumPublisher;
    ApiGear::Utilities::SinglePub<StructBoolWithArray> SigBoolPublisher;
    ApiGear::Utilities::SinglePub<StructIntWithArray> SigIntPublisher;
    ApiGear::Utilities::SinglePub<StructFloatWithArray> SigFloatPublisher;
    ApiGear::Utilities::SinglePub<StructStringWithArray> SigStringPublisher;
};

} // namespace Testbed1
} // namespace Test
