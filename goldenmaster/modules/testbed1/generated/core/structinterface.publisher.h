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
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
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
    long subscribeToPropBoolChanged(StructInterfacePropBoolPropertyCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::subscribeToPropBoolChanged
    */
    void unsubscribeFromPropBoolChanged(long handleId) override;

    /**
    * Implementation of IStructInterfacePublisher::subscribeToPropIntChanged
    */
    long subscribeToPropIntChanged(StructInterfacePropIntPropertyCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(long handleId) override;

    /**
    * Implementation of IStructInterfacePublisher::subscribeToPropFloatChanged
    */
    long subscribeToPropFloatChanged(StructInterfacePropFloatPropertyCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::subscribeToPropFloatChanged
    */
    void unsubscribeFromPropFloatChanged(long handleId) override;

    /**
    * Implementation of IStructInterfacePublisher::subscribeToPropStringChanged
    */
    long subscribeToPropStringChanged(StructInterfacePropStringPropertyCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::subscribeToPropStringChanged
    */
    void unsubscribeFromPropStringChanged(long handleId) override;

    /**
    * Implementation of IStructInterfacePublisher::subscribeToSigBool
    */
    long subscribeToSigBool(StructInterfaceSigBoolSignalCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::unsubscribeFromSigBool
    */
    void unsubscribeFromSigBool(long handleId) override;

    /**
    * Implementation of IStructInterfacePublisher::subscribeToSigInt
    */
    long subscribeToSigInt(StructInterfaceSigIntSignalCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::unsubscribeFromSigInt
    */
    void unsubscribeFromSigInt(long handleId) override;

    /**
    * Implementation of IStructInterfacePublisher::subscribeToSigFloat
    */
    long subscribeToSigFloat(StructInterfaceSigFloatSignalCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::unsubscribeFromSigFloat
    */
    void unsubscribeFromSigFloat(long handleId) override;

    /**
    * Implementation of IStructInterfacePublisher::subscribeToSigString
    */
    long subscribeToSigString(StructInterfaceSigStringSignalCb callback) override;
    /**
    * Implementation of IStructInterfacePublisher::unsubscribeFromSigString
    */
    void unsubscribeFromSigString(long handleId) override;

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
