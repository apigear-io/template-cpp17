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
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
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
    long subscribeToSwitchChanged(NamEsSwitchPropertyCb callback) override;
    /**
    * Implementation of INamEsPublisher::subscribeToSwitchChanged
    */
    void unsubscribeFromSwitchChanged(long handleId) override;

    /**
    * Implementation of INamEsPublisher::subscribeToSomePropertyChanged
    */
    long subscribeToSomePropertyChanged(NamEsSomePropertyPropertyCb callback) override;
    /**
    * Implementation of INamEsPublisher::subscribeToSomePropertyChanged
    */
    void unsubscribeFromSomePropertyChanged(long handleId) override;

    /**
    * Implementation of INamEsPublisher::subscribeToSomePoperty2Changed
    */
    long subscribeToSomePoperty2Changed(NamEsSomePoperty2PropertyCb callback) override;
    /**
    * Implementation of INamEsPublisher::subscribeToSomePoperty2Changed
    */
    void unsubscribeFromSomePoperty2Changed(long handleId) override;

    /**
    * Implementation of INamEsPublisher::subscribeToSomeSignal
    */
    long subscribeToSomeSignal(NamEsSomeSignalSignalCb callback) override;
    /**
    * Implementation of INamEsPublisher::unsubscribeFromSomeSignal
    */
    void unsubscribeFromSomeSignal(long handleId) override;

    /**
    * Implementation of INamEsPublisher::subscribeToSomeSignal2
    */
    long subscribeToSomeSignal2(NamEsSomeSignal2SignalCb callback) override;
    /**
    * Implementation of INamEsPublisher::unsubscribeFromSomeSignal2
    */
    void unsubscribeFromSomeSignal2(long handleId) override;

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
    ApiGear::Utilities::SinglePub<bool> SomeSignalPublisher;
    ApiGear::Utilities::SinglePub<bool> SomeSignal2Publisher;
};

} // namespace TbNames
} // namespace Test
