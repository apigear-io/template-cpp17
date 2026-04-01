#pragma once

#include "tb_names/generated/api/datastructs.api.h"
#include "tb_names/generated/api/names.api.h"
#include "tb_names/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>
#include <apigear/utilities/single_pub.hpp>

namespace Test {
namespace TbNames {

/**
 * The implementation of a NamEsPublisher.
 * Use this class to store clients of the Nam_Es and inform them about the change
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
class TEST_TB_NAMES_EXPORT NamEsPublisher : public INamEsPublisher
{
public:
    /**
    * Implementation of INamEsPublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(INamEsSubscriber& subscriber) override;
    /**
    * Implementation of INamEsPublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(INamEsSubscriber& subscriber) override;

    /**
    * Implementation of INamEsPublisher::subscribeToSwitchChanged
    */
    uint64_t subscribeToSwitchChanged(NamEsSwitchPropertyCb callback) override;
    /**
    * Implementation of INamEsPublisher::subscribeToSwitchChanged
    */
    void unsubscribeFromSwitchChanged(uint64_t handleId) override;

    /**
    * Implementation of INamEsPublisher::subscribeToSomePropertyChanged
    */
    uint64_t subscribeToSomePropertyChanged(NamEsSomePropertyPropertyCb callback) override;
    /**
    * Implementation of INamEsPublisher::subscribeToSomePropertyChanged
    */
    void unsubscribeFromSomePropertyChanged(uint64_t handleId) override;

    /**
    * Implementation of INamEsPublisher::subscribeToSomePoperty2Changed
    */
    uint64_t subscribeToSomePoperty2Changed(NamEsSomePoperty2PropertyCb callback) override;
    /**
    * Implementation of INamEsPublisher::subscribeToSomePoperty2Changed
    */
    void unsubscribeFromSomePoperty2Changed(uint64_t handleId) override;

    /**
    * Implementation of INamEsPublisher::subscribeToEnumPropertyChanged
    */
    uint64_t subscribeToEnumPropertyChanged(NamEsEnumPropertyPropertyCb callback) override;
    /**
    * Implementation of INamEsPublisher::subscribeToEnumPropertyChanged
    */
    void unsubscribeFromEnumPropertyChanged(uint64_t handleId) override;

    /**
    * Implementation of INamEsPublisher::subscribeToSomeSignal
    */
    uint64_t subscribeToSomeSignal(NamEsSomeSignalSignalCb callback) override;
    /**
    * Implementation of INamEsPublisher::unsubscribeFromSomeSignal
    */
    void unsubscribeFromSomeSignal(uint64_t handleId) override;

    /**
    * Implementation of INamEsPublisher::subscribeToSomeSignal2
    */
    uint64_t subscribeToSomeSignal2(NamEsSomeSignal2SignalCb callback) override;
    /**
    * Implementation of INamEsPublisher::unsubscribeFromSomeSignal2
    */
    void unsubscribeFromSomeSignal2(uint64_t handleId) override;

    /**
    * Implementation of INamEsPublisher::publishSwitchChanged
    */
    void publishSwitchChanged(bool Switch) const override;
    /**
    * Implementation of INamEsPublisher::publishSomePropertyChanged
    */
    void publishSomePropertyChanged(int SOME_PROPERTY) const override;
    /**
    * Implementation of INamEsPublisher::publishSomePoperty2Changed
    */
    void publishSomePoperty2Changed(int Some_Poperty2) const override;
    /**
    * Implementation of INamEsPublisher::publishEnumPropertyChanged
    */
    void publishEnumPropertyChanged(Enum_With_Under_scoresEnum enum_property) const override;
    /**
    * Implementation of INamEsPublisher::publishSomeSignal
    */
    void publishSomeSignal(bool SOME_PARAM) const override;
    /**
    * Implementation of INamEsPublisher::publishSomeSignal2
    */
    void publishSomeSignal2(bool Some_Param) const override;
private:
    // Subscribers informed about any property change or signal emitted in Nam_Es
    std::vector<std::reference_wrapper<INamEsSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    ApiGear::Utilities::SinglePub<bool> SwitchPublisher;
    ApiGear::Utilities::SinglePub<int> SomePropertyPublisher;
    ApiGear::Utilities::SinglePub<int> SomePoperty2Publisher;
    ApiGear::Utilities::SinglePub<Enum_With_Under_scoresEnum> EnumPropertyPublisher;
    ApiGear::Utilities::SinglePub<bool> SomeSignalPublisher;
    ApiGear::Utilities::SinglePub<bool> SomeSignal2Publisher;
};

} // namespace TbNames
} // namespace Test
