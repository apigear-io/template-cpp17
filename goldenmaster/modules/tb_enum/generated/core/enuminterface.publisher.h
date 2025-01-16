#pragma once

#include "tb_enum/generated/api/datastructs.api.h"
#include "tb_enum/generated/api/enuminterface.api.h"
#include "tb_enum/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>
#include <apigear/utilities/single_pub.hpp>

namespace Test {
namespace TbEnum {

/**
 * The implementation of a EnumInterfacePublisher.
 * Use this class to store clients of the EnumInterface and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
 */
class TEST_TB_ENUM_EXPORT EnumInterfacePublisher : public IEnumInterfacePublisher
{
public:
    /**
    * Implementation of IEnumInterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(IEnumInterfaceSubscriber& subscriber) override;
    /**
    * Implementation of IEnumInterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(IEnumInterfaceSubscriber& subscriber) override;

    /**
    * Implementation of IEnumInterfacePublisher::subscribeToProp0Changed
    */
    long subscribeToProp0Changed(EnumInterfaceProp0PropertyCb callback) override;
    /**
    * Implementation of IEnumInterfacePublisher::subscribeToProp0Changed
    */
    void unsubscribeFromProp0Changed(long handleId) override;

    /**
    * Implementation of IEnumInterfacePublisher::subscribeToProp1Changed
    */
    long subscribeToProp1Changed(EnumInterfaceProp1PropertyCb callback) override;
    /**
    * Implementation of IEnumInterfacePublisher::subscribeToProp1Changed
    */
    void unsubscribeFromProp1Changed(long handleId) override;

    /**
    * Implementation of IEnumInterfacePublisher::subscribeToProp2Changed
    */
    long subscribeToProp2Changed(EnumInterfaceProp2PropertyCb callback) override;
    /**
    * Implementation of IEnumInterfacePublisher::subscribeToProp2Changed
    */
    void unsubscribeFromProp2Changed(long handleId) override;

    /**
    * Implementation of IEnumInterfacePublisher::subscribeToProp3Changed
    */
    long subscribeToProp3Changed(EnumInterfaceProp3PropertyCb callback) override;
    /**
    * Implementation of IEnumInterfacePublisher::subscribeToProp3Changed
    */
    void unsubscribeFromProp3Changed(long handleId) override;

    /**
    * Implementation of IEnumInterfacePublisher::subscribeToSig0
    */
    long subscribeToSig0(EnumInterfaceSig0SignalCb callback) override;
    /**
    * Implementation of IEnumInterfacePublisher::unsubscribeFromSig0
    */
    void unsubscribeFromSig0(long handleId) override;

    /**
    * Implementation of IEnumInterfacePublisher::subscribeToSig1
    */
    long subscribeToSig1(EnumInterfaceSig1SignalCb callback) override;
    /**
    * Implementation of IEnumInterfacePublisher::unsubscribeFromSig1
    */
    void unsubscribeFromSig1(long handleId) override;

    /**
    * Implementation of IEnumInterfacePublisher::subscribeToSig2
    */
    long subscribeToSig2(EnumInterfaceSig2SignalCb callback) override;
    /**
    * Implementation of IEnumInterfacePublisher::unsubscribeFromSig2
    */
    void unsubscribeFromSig2(long handleId) override;

    /**
    * Implementation of IEnumInterfacePublisher::subscribeToSig3
    */
    long subscribeToSig3(EnumInterfaceSig3SignalCb callback) override;
    /**
    * Implementation of IEnumInterfacePublisher::unsubscribeFromSig3
    */
    void unsubscribeFromSig3(long handleId) override;

    /**
    * Implementation of IEnumInterfacePublisher::publishProp0Changed
    */
    void publishProp0Changed(Enum0Enum prop0) const override;
    /**
    * Implementation of IEnumInterfacePublisher::publishProp1Changed
    */
    void publishProp1Changed(Enum1Enum prop1) const override;
    /**
    * Implementation of IEnumInterfacePublisher::publishProp2Changed
    */
    void publishProp2Changed(Enum2Enum prop2) const override;
    /**
    * Implementation of IEnumInterfacePublisher::publishProp3Changed
    */
    void publishProp3Changed(Enum3Enum prop3) const override;
    /**
    * Implementation of IEnumInterfacePublisher::publishSig0
    */
    void publishSig0(Enum0Enum param0) const override;
    /**
    * Implementation of IEnumInterfacePublisher::publishSig1
    */
    void publishSig1(Enum1Enum param1) const override;
    /**
    * Implementation of IEnumInterfacePublisher::publishSig2
    */
    void publishSig2(Enum2Enum param2) const override;
    /**
    * Implementation of IEnumInterfacePublisher::publishSig3
    */
    void publishSig3(Enum3Enum param3) const override;
private:
    // Subscribers informed about any property change or signal emitted in EnumInterface
    std::vector<std::reference_wrapper<IEnumInterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<Enum0Enum> Prop0Publisher;
    ApiGear::Utilities::SinglePub<Enum1Enum> Prop1Publisher;
    ApiGear::Utilities::SinglePub<Enum2Enum> Prop2Publisher;
    ApiGear::Utilities::SinglePub<Enum3Enum> Prop3Publisher;
    ApiGear::Utilities::SinglePub<Enum0Enum> Sig0Publisher;
    ApiGear::Utilities::SinglePub<Enum1Enum> Sig1Publisher;
    ApiGear::Utilities::SinglePub<Enum2Enum> Sig2Publisher;
    ApiGear::Utilities::SinglePub<Enum3Enum> Sig3Publisher;
};

} // namespace TbEnum
} // namespace Test
