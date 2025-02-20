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
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
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
    long subscribeToPropBoolChanged(StructArrayInterfacePropBoolPropertyCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropBoolChanged
    */
    void unsubscribeFromPropBoolChanged(long handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropIntChanged
    */
    long subscribeToPropIntChanged(StructArrayInterfacePropIntPropertyCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(long handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropFloatChanged
    */
    long subscribeToPropFloatChanged(StructArrayInterfacePropFloatPropertyCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropFloatChanged
    */
    void unsubscribeFromPropFloatChanged(long handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropStringChanged
    */
    long subscribeToPropStringChanged(StructArrayInterfacePropStringPropertyCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToPropStringChanged
    */
    void unsubscribeFromPropStringChanged(long handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToSigBool
    */
    long subscribeToSigBool(StructArrayInterfaceSigBoolSignalCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::unsubscribeFromSigBool
    */
    void unsubscribeFromSigBool(long handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToSigInt
    */
    long subscribeToSigInt(StructArrayInterfaceSigIntSignalCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::unsubscribeFromSigInt
    */
    void unsubscribeFromSigInt(long handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToSigFloat
    */
    long subscribeToSigFloat(StructArrayInterfaceSigFloatSignalCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::unsubscribeFromSigFloat
    */
    void unsubscribeFromSigFloat(long handleId) override;

    /**
    * Implementation of IStructArrayInterfacePublisher::subscribeToSigString
    */
    long subscribeToSigString(StructArrayInterfaceSigStringSignalCb callback) override;
    /**
    * Implementation of IStructArrayInterfacePublisher::unsubscribeFromSigString
    */
    void unsubscribeFromSigString(long handleId) override;

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
private:
    // Subscribers informed about any property change or signal emitted in StructArrayInterface
    std::vector<std::reference_wrapper<IStructArrayInterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<std::list<StructBool>> PropBoolPublisher;
    ApiGear::Utilities::SinglePub<std::list<StructInt>> PropIntPublisher;
    ApiGear::Utilities::SinglePub<std::list<StructFloat>> PropFloatPublisher;
    ApiGear::Utilities::SinglePub<std::list<StructString>> PropStringPublisher;
    ApiGear::Utilities::SinglePub<std::list<StructBool>> SigBoolPublisher;
    ApiGear::Utilities::SinglePub<std::list<StructInt>> SigIntPublisher;
    ApiGear::Utilities::SinglePub<std::list<StructFloat>> SigFloatPublisher;
    ApiGear::Utilities::SinglePub<std::list<StructString>> SigStringPublisher;
};

} // namespace Testbed1
} // namespace Test
