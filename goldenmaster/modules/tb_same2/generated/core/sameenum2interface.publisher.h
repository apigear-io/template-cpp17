#pragma once

#include "tb_same2/generated/api/datastructs.api.h"
#include "tb_same2/generated/api/sameenum2interface.api.h"
#include "tb_same2/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>
#include <apigear/utilities/single_pub.hpp>

namespace Test {
namespace TbSame2 {

/**
 * The implementation of a SameEnum2InterfacePublisher.
 * Use this class to store clients of the SameEnum2Interface and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
 */
class TEST_TB_SAME2_EXPORT SameEnum2InterfacePublisher : public ISameEnum2InterfacePublisher
{
public:
    /**
    * Implementation of ISameEnum2InterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(ISameEnum2InterfaceSubscriber& subscriber) override;
    /**
    * Implementation of ISameEnum2InterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(ISameEnum2InterfaceSubscriber& subscriber) override;

    /**
    * Implementation of ISameEnum2InterfacePublisher::subscribeToProp1Changed
    */
    long subscribeToProp1Changed(SameEnum2InterfaceProp1PropertyCb callback) override;
    /**
    * Implementation of ISameEnum2InterfacePublisher::subscribeToProp1Changed
    */
    void unsubscribeFromProp1Changed(long handleId) override;

    /**
    * Implementation of ISameEnum2InterfacePublisher::subscribeToProp2Changed
    */
    long subscribeToProp2Changed(SameEnum2InterfaceProp2PropertyCb callback) override;
    /**
    * Implementation of ISameEnum2InterfacePublisher::subscribeToProp2Changed
    */
    void unsubscribeFromProp2Changed(long handleId) override;

    /**
    * Implementation of ISameEnum2InterfacePublisher::subscribeToSig1
    */
    long subscribeToSig1(SameEnum2InterfaceSig1SignalCb callback) override;
    /**
    * Implementation of ISameEnum2InterfacePublisher::unsubscribeFromSig1
    */
    void unsubscribeFromSig1(long handleId) override;

    /**
    * Implementation of ISameEnum2InterfacePublisher::subscribeToSig2
    */
    long subscribeToSig2(SameEnum2InterfaceSig2SignalCb callback) override;
    /**
    * Implementation of ISameEnum2InterfacePublisher::unsubscribeFromSig2
    */
    void unsubscribeFromSig2(long handleId) override;

    /**
    * Implementation of ISameEnum2InterfacePublisher::publishProp1Changed
    */
    void publishProp1Changed(Enum1Enum prop1) const override;
    /**
    * Implementation of ISameEnum2InterfacePublisher::publishProp2Changed
    */
    void publishProp2Changed(Enum2Enum prop2) const override;
    /**
    * Implementation of ISameEnum2InterfacePublisher::publishSig1
    */
    void publishSig1(Enum1Enum param1) const override;
    /**
    * Implementation of ISameEnum2InterfacePublisher::publishSig2
    */
    void publishSig2(Enum1Enum param1, Enum2Enum param2) const override;
private:
    // Subscribers informed about any property change or signal emitted in SameEnum2Interface
    std::vector<std::reference_wrapper<ISameEnum2InterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<Enum1Enum> Prop1Publisher;
    ApiGear::Utilities::SinglePub<Enum2Enum> Prop2Publisher;
    ApiGear::Utilities::SinglePub<Enum1Enum> Sig1Publisher;
    ApiGear::Utilities::SinglePub<Enum1Enum,Enum2Enum> Sig2Publisher;
};

} // namespace TbSame2
} // namespace Test
