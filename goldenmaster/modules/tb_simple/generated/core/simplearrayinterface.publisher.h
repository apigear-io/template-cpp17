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
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
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
    long subscribeToPropBoolChanged(SimpleArrayInterfacePropBoolPropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropBoolChanged
    */
    void unsubscribeFromPropBoolChanged(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropIntChanged
    */
    long subscribeToPropIntChanged(SimpleArrayInterfacePropIntPropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropInt32Changed
    */
    long subscribeToPropInt32Changed(SimpleArrayInterfacePropInt32PropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropInt32Changed
    */
    void unsubscribeFromPropInt32Changed(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropInt64Changed
    */
    long subscribeToPropInt64Changed(SimpleArrayInterfacePropInt64PropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropInt64Changed
    */
    void unsubscribeFromPropInt64Changed(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloatChanged
    */
    long subscribeToPropFloatChanged(SimpleArrayInterfacePropFloatPropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloatChanged
    */
    void unsubscribeFromPropFloatChanged(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloat32Changed
    */
    long subscribeToPropFloat32Changed(SimpleArrayInterfacePropFloat32PropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloat32Changed
    */
    void unsubscribeFromPropFloat32Changed(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloat64Changed
    */
    long subscribeToPropFloat64Changed(SimpleArrayInterfacePropFloat64PropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloat64Changed
    */
    void unsubscribeFromPropFloat64Changed(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropStringChanged
    */
    long subscribeToPropStringChanged(SimpleArrayInterfacePropStringPropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropStringChanged
    */
    void unsubscribeFromPropStringChanged(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropReadOnlyStringChanged
    */
    long subscribeToPropReadOnlyStringChanged(SimpleArrayInterfacePropReadOnlyStringPropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropReadOnlyStringChanged
    */
    void unsubscribeFromPropReadOnlyStringChanged(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigBool
    */
    long subscribeToSigBool(SimpleArrayInterfaceSigBoolSignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigBool
    */
    void unsubscribeFromSigBool(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigInt
    */
    long subscribeToSigInt(SimpleArrayInterfaceSigIntSignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigInt
    */
    void unsubscribeFromSigInt(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigInt32
    */
    long subscribeToSigInt32(SimpleArrayInterfaceSigInt32SignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigInt32
    */
    void unsubscribeFromSigInt32(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigInt64
    */
    long subscribeToSigInt64(SimpleArrayInterfaceSigInt64SignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigInt64
    */
    void unsubscribeFromSigInt64(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigFloat
    */
    long subscribeToSigFloat(SimpleArrayInterfaceSigFloatSignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigFloat
    */
    void unsubscribeFromSigFloat(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigFloat32
    */
    long subscribeToSigFloat32(SimpleArrayInterfaceSigFloat32SignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigFloat32
    */
    void unsubscribeFromSigFloat32(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigFloat64
    */
    long subscribeToSigFloat64(SimpleArrayInterfaceSigFloat64SignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigFloat64
    */
    void unsubscribeFromSigFloat64(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigString
    */
    long subscribeToSigString(SimpleArrayInterfaceSigStringSignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigString
    */
    void unsubscribeFromSigString(long handleId) override;

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
