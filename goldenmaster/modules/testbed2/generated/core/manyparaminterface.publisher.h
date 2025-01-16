#pragma once

#include "testbed2/generated/api/datastructs.api.h"
#include "testbed2/generated/api/manyparaminterface.api.h"
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
 * The implementation of a ManyParamInterfacePublisher.
 * Use this class to store clients of the ManyParamInterface and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
 */
class TEST_TESTBED2_EXPORT ManyParamInterfacePublisher : public IManyParamInterfacePublisher
{
public:
    /**
    * Implementation of IManyParamInterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(IManyParamInterfaceSubscriber& subscriber) override;
    /**
    * Implementation of IManyParamInterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(IManyParamInterfaceSubscriber& subscriber) override;

    /**
    * Implementation of IManyParamInterfacePublisher::subscribeToProp1Changed
    */
    long subscribeToProp1Changed(ManyParamInterfaceProp1PropertyCb callback) override;
    /**
    * Implementation of IManyParamInterfacePublisher::subscribeToProp1Changed
    */
    void unsubscribeFromProp1Changed(long handleId) override;

    /**
    * Implementation of IManyParamInterfacePublisher::subscribeToProp2Changed
    */
    long subscribeToProp2Changed(ManyParamInterfaceProp2PropertyCb callback) override;
    /**
    * Implementation of IManyParamInterfacePublisher::subscribeToProp2Changed
    */
    void unsubscribeFromProp2Changed(long handleId) override;

    /**
    * Implementation of IManyParamInterfacePublisher::subscribeToProp3Changed
    */
    long subscribeToProp3Changed(ManyParamInterfaceProp3PropertyCb callback) override;
    /**
    * Implementation of IManyParamInterfacePublisher::subscribeToProp3Changed
    */
    void unsubscribeFromProp3Changed(long handleId) override;

    /**
    * Implementation of IManyParamInterfacePublisher::subscribeToProp4Changed
    */
    long subscribeToProp4Changed(ManyParamInterfaceProp4PropertyCb callback) override;
    /**
    * Implementation of IManyParamInterfacePublisher::subscribeToProp4Changed
    */
    void unsubscribeFromProp4Changed(long handleId) override;

    /**
    * Implementation of IManyParamInterfacePublisher::subscribeToSig1
    */
    long subscribeToSig1(ManyParamInterfaceSig1SignalCb callback) override;
    /**
    * Implementation of IManyParamInterfacePublisher::unsubscribeFromSig1
    */
    void unsubscribeFromSig1(long handleId) override;

    /**
    * Implementation of IManyParamInterfacePublisher::subscribeToSig2
    */
    long subscribeToSig2(ManyParamInterfaceSig2SignalCb callback) override;
    /**
    * Implementation of IManyParamInterfacePublisher::unsubscribeFromSig2
    */
    void unsubscribeFromSig2(long handleId) override;

    /**
    * Implementation of IManyParamInterfacePublisher::subscribeToSig3
    */
    long subscribeToSig3(ManyParamInterfaceSig3SignalCb callback) override;
    /**
    * Implementation of IManyParamInterfacePublisher::unsubscribeFromSig3
    */
    void unsubscribeFromSig3(long handleId) override;

    /**
    * Implementation of IManyParamInterfacePublisher::subscribeToSig4
    */
    long subscribeToSig4(ManyParamInterfaceSig4SignalCb callback) override;
    /**
    * Implementation of IManyParamInterfacePublisher::unsubscribeFromSig4
    */
    void unsubscribeFromSig4(long handleId) override;

    /**
    * Implementation of IManyParamInterfacePublisher::publishProp1Changed
    */
    void publishProp1Changed(int prop1) const override;
    /**
    * Implementation of IManyParamInterfacePublisher::publishProp2Changed
    */
    void publishProp2Changed(int prop2) const override;
    /**
    * Implementation of IManyParamInterfacePublisher::publishProp3Changed
    */
    void publishProp3Changed(int prop3) const override;
    /**
    * Implementation of IManyParamInterfacePublisher::publishProp4Changed
    */
    void publishProp4Changed(int prop4) const override;
    /**
    * Implementation of IManyParamInterfacePublisher::publishSig1
    */
    void publishSig1(int param1) const override;
    /**
    * Implementation of IManyParamInterfacePublisher::publishSig2
    */
    void publishSig2(int param1, int param2) const override;
    /**
    * Implementation of IManyParamInterfacePublisher::publishSig3
    */
    void publishSig3(int param1, int param2, int param3) const override;
    /**
    * Implementation of IManyParamInterfacePublisher::publishSig4
    */
    void publishSig4(int param1, int param2, int param3, int param4) const override;
private:
    // Subscribers informed about any property change or signal emitted in ManyParamInterface
    std::vector<std::reference_wrapper<IManyParamInterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<int> Prop1Publisher;
    ApiGear::Utilities::SinglePub<int> Prop2Publisher;
    ApiGear::Utilities::SinglePub<int> Prop3Publisher;
    ApiGear::Utilities::SinglePub<int> Prop4Publisher;
    ApiGear::Utilities::SinglePub<int> Sig1Publisher;
    ApiGear::Utilities::SinglePub<int,int> Sig2Publisher;
    ApiGear::Utilities::SinglePub<int,int,int> Sig3Publisher;
    ApiGear::Utilities::SinglePub<int,int,int,int> Sig4Publisher;
};

} // namespace Testbed2
} // namespace Test
