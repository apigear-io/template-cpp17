#pragma once

#include "tb_simple/generated/api/datastructs.api.h"
#include "tb_simple/generated/api/simplearrayinterface.api.h"
#include "tb_simple/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>
#include <apigear/utilities/single_pub.hpp>

namespace Test {
namespace TbSimple {

/**
 * The implementation of a SimpleArrayInterfacePublisher.
 * Use this class to store clients of the SimpleArrayInterface and inform them about the change
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
class TEST_TB_SIMPLE_EXPORT SimpleArrayInterfacePublisher : public ISimpleArrayInterfacePublisher
{
public:
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(ISimpleArrayInterfaceSubscriber& subscriber) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(ISimpleArrayInterfaceSubscriber& subscriber) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropBoolChanged
    */
    uint64_t subscribeToPropBoolChanged(SimpleArrayInterfacePropBoolPropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropBoolChanged
    */
    void unsubscribeFromPropBoolChanged(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropIntChanged
    */
    uint64_t subscribeToPropIntChanged(SimpleArrayInterfacePropIntPropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropInt32Changed
    */
    uint64_t subscribeToPropInt32Changed(SimpleArrayInterfacePropInt32PropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropInt32Changed
    */
    void unsubscribeFromPropInt32Changed(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropInt64Changed
    */
    uint64_t subscribeToPropInt64Changed(SimpleArrayInterfacePropInt64PropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropInt64Changed
    */
    void unsubscribeFromPropInt64Changed(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloatChanged
    */
    uint64_t subscribeToPropFloatChanged(SimpleArrayInterfacePropFloatPropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloatChanged
    */
    void unsubscribeFromPropFloatChanged(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloat32Changed
    */
    uint64_t subscribeToPropFloat32Changed(SimpleArrayInterfacePropFloat32PropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloat32Changed
    */
    void unsubscribeFromPropFloat32Changed(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloat64Changed
    */
    uint64_t subscribeToPropFloat64Changed(SimpleArrayInterfacePropFloat64PropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloat64Changed
    */
    void unsubscribeFromPropFloat64Changed(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropStringChanged
    */
    uint64_t subscribeToPropStringChanged(SimpleArrayInterfacePropStringPropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropStringChanged
    */
    void unsubscribeFromPropStringChanged(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropReadOnlyStringChanged
    */
    uint64_t subscribeToPropReadOnlyStringChanged(SimpleArrayInterfacePropReadOnlyStringPropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropReadOnlyStringChanged
    */
    void unsubscribeFromPropReadOnlyStringChanged(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigBool
    */
    uint64_t subscribeToSigBool(SimpleArrayInterfaceSigBoolSignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigBool
    */
    void unsubscribeFromSigBool(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigInt
    */
    uint64_t subscribeToSigInt(SimpleArrayInterfaceSigIntSignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigInt
    */
    void unsubscribeFromSigInt(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigInt32
    */
    uint64_t subscribeToSigInt32(SimpleArrayInterfaceSigInt32SignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigInt32
    */
    void unsubscribeFromSigInt32(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigInt64
    */
    uint64_t subscribeToSigInt64(SimpleArrayInterfaceSigInt64SignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigInt64
    */
    void unsubscribeFromSigInt64(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigFloat
    */
    uint64_t subscribeToSigFloat(SimpleArrayInterfaceSigFloatSignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigFloat
    */
    void unsubscribeFromSigFloat(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigFloat32
    */
    uint64_t subscribeToSigFloat32(SimpleArrayInterfaceSigFloat32SignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigFloat32
    */
    void unsubscribeFromSigFloat32(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigFloat64
    */
    uint64_t subscribeToSigFloat64(SimpleArrayInterfaceSigFloat64SignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigFloat64
    */
    void unsubscribeFromSigFloat64(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigString
    */
    uint64_t subscribeToSigString(SimpleArrayInterfaceSigStringSignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigString
    */
    void unsubscribeFromSigString(uint64_t handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropBoolChanged
    */
    void publishPropBoolChanged(const std::list<bool>& propBool) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropIntChanged
    */
    void publishPropIntChanged(const std::list<int>& propInt) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropInt32Changed
    */
    void publishPropInt32Changed(const std::list<int32_t>& propInt32) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropInt64Changed
    */
    void publishPropInt64Changed(const std::list<int64_t>& propInt64) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropFloatChanged
    */
    void publishPropFloatChanged(const std::list<float>& propFloat) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropFloat32Changed
    */
    void publishPropFloat32Changed(const std::list<float>& propFloat32) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropFloat64Changed
    */
    void publishPropFloat64Changed(const std::list<double>& propFloat64) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropStringChanged
    */
    void publishPropStringChanged(const std::list<std::string>& propString) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropReadOnlyStringChanged
    */
    void publishPropReadOnlyStringChanged(const std::string& propReadOnlyString) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigBool
    */
    void publishSigBool(const std::list<bool>& paramBool) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigInt
    */
    void publishSigInt(const std::list<int>& paramInt) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigInt32
    */
    void publishSigInt32(const std::list<int32_t>& paramInt32) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigInt64
    */
    void publishSigInt64(const std::list<int64_t>& paramInt64) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigFloat
    */
    void publishSigFloat(const std::list<float>& paramFloat) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigFloat32
    */
    void publishSigFloat32(const std::list<float>& paramFloa32) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigFloat64
    */
    void publishSigFloat64(const std::list<double>& paramFloat64) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigString
    */
    void publishSigString(const std::list<std::string>& paramString) const override;
private:
    // Subscribers informed about any property change or signal emitted in SimpleArrayInterface
    std::vector<std::reference_wrapper<ISimpleArrayInterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<std::list<bool>> PropBoolPublisher;
    ApiGear::Utilities::SinglePub<std::list<int>> PropIntPublisher;
    ApiGear::Utilities::SinglePub<std::list<int32_t>> PropInt32Publisher;
    ApiGear::Utilities::SinglePub<std::list<int64_t>> PropInt64Publisher;
    ApiGear::Utilities::SinglePub<std::list<float>> PropFloatPublisher;
    ApiGear::Utilities::SinglePub<std::list<float>> PropFloat32Publisher;
    ApiGear::Utilities::SinglePub<std::list<double>> PropFloat64Publisher;
    ApiGear::Utilities::SinglePub<std::list<std::string>> PropStringPublisher;
    ApiGear::Utilities::SinglePub<std::string> PropReadOnlyStringPublisher;
    ApiGear::Utilities::SinglePub<std::list<bool>> SigBoolPublisher;
    ApiGear::Utilities::SinglePub<std::list<int>> SigIntPublisher;
    ApiGear::Utilities::SinglePub<std::list<int32_t>> SigInt32Publisher;
    ApiGear::Utilities::SinglePub<std::list<int64_t>> SigInt64Publisher;
    ApiGear::Utilities::SinglePub<std::list<float>> SigFloatPublisher;
    ApiGear::Utilities::SinglePub<std::list<float>> SigFloat32Publisher;
    ApiGear::Utilities::SinglePub<std::list<double>> SigFloat64Publisher;
    ApiGear::Utilities::SinglePub<std::list<std::string>> SigStringPublisher;
};

} // namespace TbSimple
} // namespace Test
