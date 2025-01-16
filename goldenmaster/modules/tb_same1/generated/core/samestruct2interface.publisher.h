#pragma once

#include "tb_same1/generated/api/datastructs.api.h"
#include "tb_same1/generated/api/samestruct2interface.api.h"
#include "tb_same1/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>
#include <apigear/utilities/single_pub.hpp>

namespace Test {
namespace TbSame1 {

/**
 * The implementation of a SameStruct2InterfacePublisher.
 * Use this class to store clients of the SameStruct2Interface and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
 */
class TEST_TB_SAME1_EXPORT SameStruct2InterfacePublisher : public ISameStruct2InterfacePublisher
{
public:
    /**
    * Implementation of ISameStruct2InterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(ISameStruct2InterfaceSubscriber& subscriber) override;
    /**
    * Implementation of ISameStruct2InterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(ISameStruct2InterfaceSubscriber& subscriber) override;

    /**
    * Implementation of ISameStruct2InterfacePublisher::subscribeToProp1Changed
    */
    long subscribeToProp1Changed(SameStruct2InterfaceProp1PropertyCb callback) override;
    /**
    * Implementation of ISameStruct2InterfacePublisher::subscribeToProp1Changed
    */
    void unsubscribeFromProp1Changed(long handleId) override;

    /**
    * Implementation of ISameStruct2InterfacePublisher::subscribeToProp2Changed
    */
    long subscribeToProp2Changed(SameStruct2InterfaceProp2PropertyCb callback) override;
    /**
    * Implementation of ISameStruct2InterfacePublisher::subscribeToProp2Changed
    */
    void unsubscribeFromProp2Changed(long handleId) override;

    /**
    * Implementation of ISameStruct2InterfacePublisher::subscribeToSig1
    */
    long subscribeToSig1(SameStruct2InterfaceSig1SignalCb callback) override;
    /**
    * Implementation of ISameStruct2InterfacePublisher::unsubscribeFromSig1
    */
    void unsubscribeFromSig1(long handleId) override;

    /**
    * Implementation of ISameStruct2InterfacePublisher::subscribeToSig2
    */
    long subscribeToSig2(SameStruct2InterfaceSig2SignalCb callback) override;
    /**
    * Implementation of ISameStruct2InterfacePublisher::unsubscribeFromSig2
    */
    void unsubscribeFromSig2(long handleId) override;

    /**
    * Implementation of ISameStruct2InterfacePublisher::publishProp1Changed
    */
    void publishProp1Changed(const Struct2& prop1) const override;
    /**
    * Implementation of ISameStruct2InterfacePublisher::publishProp2Changed
    */
    void publishProp2Changed(const Struct2& prop2) const override;
    /**
    * Implementation of ISameStruct2InterfacePublisher::publishSig1
    */
    void publishSig1(const Struct1& param1) const override;
    /**
    * Implementation of ISameStruct2InterfacePublisher::publishSig2
    */
    void publishSig2(const Struct1& param1, const Struct2& param2) const override;
private:
    // Subscribers informed about any property change or signal emitted in SameStruct2Interface
    std::vector<std::reference_wrapper<ISameStruct2InterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<Struct2> Prop1Publisher;
    ApiGear::Utilities::SinglePub<Struct2> Prop2Publisher;
    ApiGear::Utilities::SinglePub<Struct1> Sig1Publisher;
    ApiGear::Utilities::SinglePub<Struct1,Struct2> Sig2Publisher;
};

} // namespace TbSame1
} // namespace Test
