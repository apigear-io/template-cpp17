#pragma once

#include "testbed1/generated/api/datastructs.api.h"
#include "testbed1/generated/api/structarrayinterface.api.h"
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
 * The implementation of a StructArrayInterfacePublisher.
 * Use this class to store clients of the StructArrayInterface and inform them about the change
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
class TEST_TESTBED1_EXPORT StructArrayInterfacePublisher : public IStructArrayInterfacePublisher
{
public:
    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(IStructArrayInterfaceSubscriber& subscriber) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(IStructArrayInterfaceSubscriber& subscriber) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropBoolChanged
    */
    uint64_t subscribeToPropBoolChanged(StructArrayInterfacePropBoolPropertyCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropBoolChanged
    */
    void unsubscribeFromPropBoolChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropIntChanged
    */
    uint64_t subscribeToPropIntChanged(StructArrayInterfacePropIntPropertyCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropFloatChanged
    */
    uint64_t subscribeToPropFloatChanged(StructArrayInterfacePropFloatPropertyCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropFloatChanged
    */
    void unsubscribeFromPropFloatChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropStringChanged
    */
    uint64_t subscribeToPropStringChanged(StructArrayInterfacePropStringPropertyCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropStringChanged
    */
    void unsubscribeFromPropStringChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropEnumChanged
    */
    uint64_t subscribeToPropEnumChanged(StructArrayInterfacePropEnumPropertyCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropEnumChanged
    */
    void unsubscribeFromPropEnumChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToSigBool
    */
    uint64_t subscribeToSigBool(StructArrayInterfaceSigBoolSignalCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::unsubscribeFromSigBool
    */
    void unsubscribeFromSigBool(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToSigInt
    */
    uint64_t subscribeToSigInt(StructArrayInterfaceSigIntSignalCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::unsubscribeFromSigInt
    */
    void unsubscribeFromSigInt(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToSigFloat
    */
    uint64_t subscribeToSigFloat(StructArrayInterfaceSigFloatSignalCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::unsubscribeFromSigFloat
    */
    void unsubscribeFromSigFloat(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToSigString
    */
    uint64_t subscribeToSigString(StructArrayInterfaceSigStringSignalCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::unsubscribeFromSigString
    */
    void unsubscribeFromSigString(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToSigEnum
    */
    uint64_t subscribeToSigEnum(StructArrayInterfaceSigEnumSignalCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::unsubscribeFromSigEnum
    */
    void unsubscribeFromSigEnum(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::publishPropBoolChanged
    */
    void publishPropBoolChanged(const std::list<StructBool>& propBool) const override;
    /**
    * Implementation of IStructArrayInterfacePublisher::publishPropIntChanged
    */
    void publishPropIntChanged(const std::list<StructInt>& propInt) const override;
    /**
    * Implementation of IStructArrayInterfacePublisher::publishPropFloatChanged
    */
    void publishPropFloatChanged(const std::list<StructFloat>& propFloat) const override;
    /**
    * Implementation of IStructArrayInterfacePublisher::publishPropStringChanged
    */
    void publishPropStringChanged(const std::list<StructString>& propString) const override;
    /**
    * Implementation of IStructArrayInterfacePublisher::publishPropEnumChanged
    */
    void publishPropEnumChanged(const std::list<Enum0Enum>& propEnum) const override;
    /**
    * Implementation of IStructArrayInterfacePublisher::publishSigBool
    */
    void publishSigBool(const std::list<StructBool>& paramBool) const override;
    /**
    * Implementation of IStructArrayInterfacePublisher::publishSigInt
    */
    void publishSigInt(const std::list<StructInt>& paramInt) const override;
    /**
    * Implementation of IStructArrayInterfacePublisher::publishSigFloat
    */
    void publishSigFloat(const std::list<StructFloat>& paramFloat) const override;
    /**
    * Implementation of IStructArrayInterfacePublisher::publishSigString
    */
    void publishSigString(const std::list<StructString>& paramString) const override;
    /**
    * Implementation of IStructArrayInterfacePublisher::publishSigEnum
    */
    void publishSigEnum(const std::list<Enum0Enum>& paramEnum) const override;
private:
    // Subscribers informed about any property change or signal emitted in StructArrayInterface
    std::vector<std::reference_wrapper<IStructArrayInterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<std::list<StructBool>> PropBoolPublisher;
    ApiGear::Utilities::SinglePub<std::list<StructInt>> PropIntPublisher;
    ApiGear::Utilities::SinglePub<std::list<StructFloat>> PropFloatPublisher;
    ApiGear::Utilities::SinglePub<std::list<StructString>> PropStringPublisher;
    ApiGear::Utilities::SinglePub<std::list<Enum0Enum>> PropEnumPublisher;
    ApiGear::Utilities::SinglePub<std::list<StructBool>> SigBoolPublisher;
    ApiGear::Utilities::SinglePub<std::list<StructInt>> SigIntPublisher;
    ApiGear::Utilities::SinglePub<std::list<StructFloat>> SigFloatPublisher;
    ApiGear::Utilities::SinglePub<std::list<StructString>> SigStringPublisher;
    ApiGear::Utilities::SinglePub<std::list<Enum0Enum>> SigEnumPublisher;
};

} // namespace Testbed1
} // namespace Test
