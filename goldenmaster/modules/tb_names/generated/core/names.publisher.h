#pragma once

#include "tb_names/generated/api/datastructs.api.h"
#include "tb_names/generated/api/names.api.h"
#include "tb_names/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>

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
    * Implementation of INamEsPublisher::subscribeToEnumPropertyChanged
    */
    long subscribeToEnumPropertyChanged(NamEsEnumPropertyPropertyCb callback) override;
    /**
    * Implementation of INamEsPublisher::subscribeToEnumPropertyChanged
    */
    void unsubscribeFromEnumPropertyChanged(long handleId) override;

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
    // Next free unique identifier to subscribe for the Switch change.
    std::atomic<long> m_switchChangedCallbackNextId {0};
    // Subscribed callbacks for the Switch change.
    std::map<long, NamEsSwitchPropertyCb> m_switchCallbacks;
    // Mutex for m_switchCallbacks
    mutable std::shared_timed_mutex m_switchCallbacksMutex;
    // Next free unique identifier to subscribe for the SomeProperty change.
    std::atomic<long> m_somePropertyChangedCallbackNextId {0};
    // Subscribed callbacks for the SomeProperty change.
    std::map<long, NamEsSomePropertyPropertyCb> m_somePropertyCallbacks;
    // Mutex for m_somePropertyCallbacks
    mutable std::shared_timed_mutex m_somePropertyCallbacksMutex;
    // Next free unique identifier to subscribe for the SomePoperty2 change.
    std::atomic<long> m_somePoperty2ChangedCallbackNextId {0};
    // Subscribed callbacks for the SomePoperty2 change.
    std::map<long, NamEsSomePoperty2PropertyCb> m_somePoperty2Callbacks;
    // Mutex for m_somePoperty2Callbacks
    mutable std::shared_timed_mutex m_somePoperty2CallbacksMutex;
    // Next free unique identifier to subscribe for the EnumProperty change.
    std::atomic<long> m_enumPropertyChangedCallbackNextId {0};
    // Subscribed callbacks for the EnumProperty change.
    std::map<long, NamEsEnumPropertyPropertyCb> m_enumPropertyCallbacks;
    // Mutex for m_enumPropertyCallbacks
    mutable std::shared_timed_mutex m_enumPropertyCallbacksMutex;
    // Next free unique identifier to subscribe for the SomeSignal emission.
    std::atomic<long> m_someSignalSignalCallbackNextId {0};
    // Subscribed callbacks for the SomeSignal emission.
    std::map<long, NamEsSomeSignalSignalCb > m_someSignalCallbacks;
    // Mutex for m_someSignalSignalCallbackNextId and m_someSignalCallbacks
    mutable std::shared_timed_mutex m_someSignalCallbacksMutex;
    // Next free unique identifier to subscribe for the SomeSignal2 emission.
    std::atomic<long> m_someSignal2SignalCallbackNextId {0};
    // Subscribed callbacks for the SomeSignal2 emission.
    std::map<long, NamEsSomeSignal2SignalCb > m_someSignal2Callbacks;
    // Mutex for m_someSignal2SignalCallbackNextId and m_someSignal2Callbacks
    mutable std::shared_timed_mutex m_someSignal2CallbacksMutex;
};

} // namespace TbNames
} // namespace Test
