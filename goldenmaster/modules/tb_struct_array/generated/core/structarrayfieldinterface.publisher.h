#pragma once

#include "tb_struct_array/generated/api/datastructs.api.h"
#include "tb_struct_array/generated/api/structarrayfieldinterface.api.h"
#include "tb_struct_array/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>
#include <apigear/utilities/single_pub.hpp>

namespace Test {
namespace TbStructArray {

/**
 * The implementation of a StructArrayFieldInterfacePublisher.
 * Use this class to store clients of the StructArrayFieldInterface and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning Subscription management (subscribe/unsubscribe) is thread safe. However, subscriber
 * callbacks are invoked without holding any internal lock — the subscriber itself must be
 * thread safe if it can be called from multiple threads.
 */
class TEST_TB_STRUCT_ARRAY_EXPORT StructArrayFieldInterfacePublisher : public IStructArrayFieldInterfacePublisher
{
public:
    /**
    * Implementation of IStructArrayFieldInterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(IStructArrayFieldInterfaceSubscriber& subscriber) override;
    /**
    * Implementation of IStructArrayFieldInterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(IStructArrayFieldInterfaceSubscriber& subscriber) override;

    /**
    * Implementation of IStructArrayFieldInterfacePublisher::subscribeToPropStructArrayChanged
    */
    uint64_t subscribeToPropStructArrayChanged(StructArrayFieldInterfacePropStructArrayPropertyCb callback) override;
    /**
    * Implementation of IStructArrayFieldInterfacePublisher::subscribeToPropStructArrayChanged
    */
    void unsubscribeFromPropStructArrayChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayFieldInterfacePublisher::subscribeToPropEnumArrayChanged
    */
    uint64_t subscribeToPropEnumArrayChanged(StructArrayFieldInterfacePropEnumArrayPropertyCb callback) override;
    /**
    * Implementation of IStructArrayFieldInterfacePublisher::subscribeToPropEnumArrayChanged
    */
    void unsubscribeFromPropEnumArrayChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayFieldInterfacePublisher::subscribeToPropIntArrayChanged
    */
    uint64_t subscribeToPropIntArrayChanged(StructArrayFieldInterfacePropIntArrayPropertyCb callback) override;
    /**
    * Implementation of IStructArrayFieldInterfacePublisher::subscribeToPropIntArrayChanged
    */
    void unsubscribeFromPropIntArrayChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayFieldInterfacePublisher::subscribeToPropMixedChanged
    */
    uint64_t subscribeToPropMixedChanged(StructArrayFieldInterfacePropMixedPropertyCb callback) override;
    /**
    * Implementation of IStructArrayFieldInterfacePublisher::subscribeToPropMixedChanged
    */
    void unsubscribeFromPropMixedChanged(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayFieldInterfacePublisher::subscribeToSigMixed
    */
    uint64_t subscribeToSigMixed(StructArrayFieldInterfaceSigMixedSignalCb callback) override;
    /**
    * Implementation of IStructArrayFieldInterfacePublisher::unsubscribeFromSigMixed
    */
    void unsubscribeFromSigMixed(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayFieldInterfacePublisher::subscribeToSigStructArray
    */
    uint64_t subscribeToSigStructArray(StructArrayFieldInterfaceSigStructArraySignalCb callback) override;
    /**
    * Implementation of IStructArrayFieldInterfacePublisher::unsubscribeFromSigStructArray
    */
    void unsubscribeFromSigStructArray(uint64_t handleId) override;

    /**
    * Implementation of IStructArrayFieldInterfacePublisher::publishPropStructArrayChanged
    */
    void publishPropStructArrayChanged(const StructWithArrayOfStructs& propStructArray) const override;
    /**
    * Implementation of IStructArrayFieldInterfacePublisher::publishPropEnumArrayChanged
    */
    void publishPropEnumArrayChanged(const StructWithArrayOfEnums& propEnumArray) const override;
    /**
    * Implementation of IStructArrayFieldInterfacePublisher::publishPropIntArrayChanged
    */
    void publishPropIntArrayChanged(const StructWithArrayOfInts& propIntArray) const override;
    /**
    * Implementation of IStructArrayFieldInterfacePublisher::publishPropMixedChanged
    */
    void publishPropMixedChanged(const MixedStruct& propMixed) const override;
    /**
    * Implementation of IStructArrayFieldInterfacePublisher::publishSigMixed
    */
    void publishSigMixed(const MixedStruct& paramMixed) const override;
    /**
    * Implementation of IStructArrayFieldInterfacePublisher::publishSigStructArray
    */
    void publishSigStructArray(const StructWithArrayOfStructs& paramPoints) const override;
private:
    // Subscribers informed about any property change or signal emitted in StructArrayFieldInterface
    std::vector<std::reference_wrapper<IStructArrayFieldInterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<StructWithArrayOfStructs> PropStructArrayPublisher;
    ApiGear::Utilities::SinglePub<StructWithArrayOfEnums> PropEnumArrayPublisher;
    ApiGear::Utilities::SinglePub<StructWithArrayOfInts> PropIntArrayPublisher;
    ApiGear::Utilities::SinglePub<MixedStruct> PropMixedPublisher;
    ApiGear::Utilities::SinglePub<MixedStruct> SigMixedPublisher;
    ApiGear::Utilities::SinglePub<StructWithArrayOfStructs> SigStructArrayPublisher;
};

} // namespace TbStructArray
} // namespace Test
