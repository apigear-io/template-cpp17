#pragma once

#include "tb_simple/generated/api/datastructs.api.h"
#include "tb_simple/generated/api/simpleinterface.api.h"
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
 * The implementation of a SimpleInterfacePublisher.
 * Use this class to store clients of the SimpleInterface and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning Subscription management (subscribe/unsubscribe) is thread safe. However, subscriber
 * callbacks are invoked without holding any internal lock — the subscriber itself must be
 * thread safe if it can be called from multiple threads.
 */
class TEST_TB_SIMPLE_EXPORT SimpleInterfacePublisher : public ISimpleInterfacePublisher
{
public:
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(ISimpleInterfaceSubscriber& subscriber) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(ISimpleInterfaceSubscriber& subscriber) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropBoolChanged
    */
    uint64_t subscribeToPropBoolChanged(SimpleInterfacePropBoolPropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropBoolChanged
    */
    void unsubscribeFromPropBoolChanged(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropIntChanged
    */
    uint64_t subscribeToPropIntChanged(SimpleInterfacePropIntPropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropInt32Changed
    */
    uint64_t subscribeToPropInt32Changed(SimpleInterfacePropInt32PropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropInt32Changed
    */
    void unsubscribeFromPropInt32Changed(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropInt64Changed
    */
    uint64_t subscribeToPropInt64Changed(SimpleInterfacePropInt64PropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropInt64Changed
    */
    void unsubscribeFromPropInt64Changed(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropFloatChanged
    */
    uint64_t subscribeToPropFloatChanged(SimpleInterfacePropFloatPropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropFloatChanged
    */
    void unsubscribeFromPropFloatChanged(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropFloat32Changed
    */
    uint64_t subscribeToPropFloat32Changed(SimpleInterfacePropFloat32PropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropFloat32Changed
    */
    void unsubscribeFromPropFloat32Changed(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropFloat64Changed
    */
    uint64_t subscribeToPropFloat64Changed(SimpleInterfacePropFloat64PropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropFloat64Changed
    */
    void unsubscribeFromPropFloat64Changed(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropStringChanged
    */
    uint64_t subscribeToPropStringChanged(SimpleInterfacePropStringPropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropStringChanged
    */
    void unsubscribeFromPropStringChanged(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigBool
    */
    uint64_t subscribeToSigBool(SimpleInterfaceSigBoolSignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigBool
    */
    void unsubscribeFromSigBool(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigInt
    */
    uint64_t subscribeToSigInt(SimpleInterfaceSigIntSignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigInt
    */
    void unsubscribeFromSigInt(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigInt32
    */
    uint64_t subscribeToSigInt32(SimpleInterfaceSigInt32SignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigInt32
    */
    void unsubscribeFromSigInt32(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigInt64
    */
    uint64_t subscribeToSigInt64(SimpleInterfaceSigInt64SignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigInt64
    */
    void unsubscribeFromSigInt64(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigFloat
    */
    uint64_t subscribeToSigFloat(SimpleInterfaceSigFloatSignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigFloat
    */
    void unsubscribeFromSigFloat(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigFloat32
    */
    uint64_t subscribeToSigFloat32(SimpleInterfaceSigFloat32SignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigFloat32
    */
    void unsubscribeFromSigFloat32(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigFloat64
    */
    uint64_t subscribeToSigFloat64(SimpleInterfaceSigFloat64SignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigFloat64
    */
    void unsubscribeFromSigFloat64(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigString
    */
    uint64_t subscribeToSigString(SimpleInterfaceSigStringSignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigString
    */
    void unsubscribeFromSigString(uint64_t handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::publishPropBoolChanged
    */
    void publishPropBoolChanged(bool propBool) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishPropIntChanged
    */
    void publishPropIntChanged(int propInt) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishPropInt32Changed
    */
    void publishPropInt32Changed(int32_t propInt32) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishPropInt64Changed
    */
    void publishPropInt64Changed(int64_t propInt64) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishPropFloatChanged
    */
    void publishPropFloatChanged(float propFloat) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishPropFloat32Changed
    */
    void publishPropFloat32Changed(float propFloat32) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishPropFloat64Changed
    */
    void publishPropFloat64Changed(double propFloat64) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishPropStringChanged
    */
    void publishPropStringChanged(const std::string& propString) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigBool
    */
    void publishSigBool(bool paramBool) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigInt
    */
    void publishSigInt(int paramInt) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigInt32
    */
    void publishSigInt32(int32_t paramInt32) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigInt64
    */
    void publishSigInt64(int64_t paramInt64) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigFloat
    */
    void publishSigFloat(float paramFloat) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigFloat32
    */
    void publishSigFloat32(float paramFloat32) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigFloat64
    */
    void publishSigFloat64(double paramFloat64) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigString
    */
    void publishSigString(const std::string& paramString) const override;
private:
    // Subscribers informed about any property change or signal emitted in SimpleInterface
    std::vector<std::reference_wrapper<ISimpleInterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<bool> PropBoolPublisher;
    ApiGear::Utilities::SinglePub<int> PropIntPublisher;
    ApiGear::Utilities::SinglePub<int32_t> PropInt32Publisher;
    ApiGear::Utilities::SinglePub<int64_t> PropInt64Publisher;
    ApiGear::Utilities::SinglePub<float> PropFloatPublisher;
    ApiGear::Utilities::SinglePub<float> PropFloat32Publisher;
    ApiGear::Utilities::SinglePub<double> PropFloat64Publisher;
    ApiGear::Utilities::SinglePub<std::string> PropStringPublisher;
    ApiGear::Utilities::SinglePub<bool> SigBoolPublisher;
    ApiGear::Utilities::SinglePub<int> SigIntPublisher;
    ApiGear::Utilities::SinglePub<int32_t> SigInt32Publisher;
    ApiGear::Utilities::SinglePub<int64_t> SigInt64Publisher;
    ApiGear::Utilities::SinglePub<float> SigFloatPublisher;
    ApiGear::Utilities::SinglePub<float> SigFloat32Publisher;
    ApiGear::Utilities::SinglePub<double> SigFloat64Publisher;
    ApiGear::Utilities::SinglePub<std::string> SigStringPublisher;
};

} // namespace TbSimple
} // namespace Test
