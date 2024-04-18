#pragma once

#include "tb_simple/generated/api/datastructs.api.h"
#include "tb_simple/generated/api/simplearrayinterface.api.h"
#include "tb_simple/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>

namespace Test {
namespace TbSimple {

/**
 * The implementation of a SimpleArrayInterfacePublisher.
 * Use this class to store clients of the SimpleArrayInterface and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
 */
class TEST_TB_SIMPLE_EXPORT SimpleArrayInterfacePublisher : public ISimpleArrayInterfacePublisher
{
public:
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(ISimpleArrayInterfaceSubscriber& subscriber) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(ISimpleArrayInterfaceSubscriber& subscriber) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropBoolChanged
    */
    long subscribeToPropBoolChanged(SimpleArrayInterfacePropBoolPropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropBoolChanged
    */
    void unsubscribeFromPropBoolChanged(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropIntChanged
    */
    long subscribeToPropIntChanged(SimpleArrayInterfacePropIntPropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropInt32Changed
    */
    long subscribeToPropInt32Changed(SimpleArrayInterfacePropInt32PropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropInt32Changed
    */
    void unsubscribeFromPropInt32Changed(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropInt64Changed
    */
    long subscribeToPropInt64Changed(SimpleArrayInterfacePropInt64PropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropInt64Changed
    */
    void unsubscribeFromPropInt64Changed(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloatChanged
    */
    long subscribeToPropFloatChanged(SimpleArrayInterfacePropFloatPropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloatChanged
    */
    void unsubscribeFromPropFloatChanged(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloat32Changed
    */
    long subscribeToPropFloat32Changed(SimpleArrayInterfacePropFloat32PropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloat32Changed
    */
    void unsubscribeFromPropFloat32Changed(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloat64Changed
    */
    long subscribeToPropFloat64Changed(SimpleArrayInterfacePropFloat64PropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropFloat64Changed
    */
    void unsubscribeFromPropFloat64Changed(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropStringChanged
    */
    long subscribeToPropStringChanged(SimpleArrayInterfacePropStringPropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropStringChanged
    */
    void unsubscribeFromPropStringChanged(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropReadOnlyStringChanged
    */
    long subscribeToPropReadOnlyStringChanged(SimpleArrayInterfacePropReadOnlyStringPropertyCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToPropReadOnlyStringChanged
    */
    void unsubscribeFromPropReadOnlyStringChanged(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigBool
    */
    long subscribeToSigBool(SimpleArrayInterfaceSigBoolSignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigBool
    */
    void unsubscribeFromSigBool(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigInt
    */
    long subscribeToSigInt(SimpleArrayInterfaceSigIntSignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigInt
    */
    void unsubscribeFromSigInt(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigInt32
    */
    long subscribeToSigInt32(SimpleArrayInterfaceSigInt32SignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigInt32
    */
    void unsubscribeFromSigInt32(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigInt64
    */
    long subscribeToSigInt64(SimpleArrayInterfaceSigInt64SignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigInt64
    */
    void unsubscribeFromSigInt64(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigFloat
    */
    long subscribeToSigFloat(SimpleArrayInterfaceSigFloatSignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigFloat
    */
    void unsubscribeFromSigFloat(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigFloat32
    */
    long subscribeToSigFloat32(SimpleArrayInterfaceSigFloat32SignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigFloat32
    */
    void unsubscribeFromSigFloat32(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigFloat64
    */
    long subscribeToSigFloat64(SimpleArrayInterfaceSigFloat64SignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigFloat64
    */
    void unsubscribeFromSigFloat64(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::subscribeToSigString
    */
    long subscribeToSigString(SimpleArrayInterfaceSigStringSignalCb callback) override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::unsubscribeFromSigString
    */
    void unsubscribeFromSigString(long handleId) override;

    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropBoolChanged
    */
    void publishPropBoolChanged(const std::list<bool>& propBool) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropIntChanged
    */
    void publishPropIntChanged(const std::list<int>& propInt) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropInt32Changed
    */
    void publishPropInt32Changed(const std::list<int32_t>& propInt32) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropInt64Changed
    */
    void publishPropInt64Changed(const std::list<int64_t>& propInt64) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropFloatChanged
    */
    void publishPropFloatChanged(const std::list<float>& propFloat) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropFloat32Changed
    */
    void publishPropFloat32Changed(const std::list<float>& propFloat32) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropFloat64Changed
    */
    void publishPropFloat64Changed(const std::list<double>& propFloat64) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropStringChanged
    */
    void publishPropStringChanged(const std::list<std::string>& propString) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishPropReadOnlyStringChanged
    */
    void publishPropReadOnlyStringChanged(const std::string& propReadOnlyString) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigBool
    */
    void publishSigBool(const std::list<bool>& paramBool) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigInt
    */
    void publishSigInt(const std::list<int>& paramInt) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigInt32
    */
    void publishSigInt32(const std::list<int32_t>& paramInt32) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigInt64
    */
    void publishSigInt64(const std::list<int64_t>& paramInt64) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigFloat
    */
    void publishSigFloat(const std::list<float>& paramFloat) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigFloat32
    */
    void publishSigFloat32(const std::list<float>& paramFloa32) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigFloat64
    */
    void publishSigFloat64(const std::list<double>& paramFloat64) const override;
    /**
    * Implementation of ISimpleArrayInterfacePublisher::publishSigString
    */
    void publishSigString(const std::list<std::string>& paramString) const override;
private:
    // Subscribers informed about any property change or signal emitted in SimpleArrayInterface
    std::vector<std::reference_wrapper<ISimpleArrayInterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    // Next free unique identifier to subscribe for the PropBool change.
    std::atomic<long> m_propBoolChangedCallbackNextId {0};
    // Subscribed callbacks for the PropBool change.
    std::map<long, SimpleArrayInterfacePropBoolPropertyCb> m_propBoolCallbacks;
    // Mutex for m_propBoolCallbacks
    mutable std::shared_timed_mutex m_propBoolCallbacksMutex;
    // Next free unique identifier to subscribe for the PropInt change.
    std::atomic<long> m_propIntChangedCallbackNextId {0};
    // Subscribed callbacks for the PropInt change.
    std::map<long, SimpleArrayInterfacePropIntPropertyCb> m_propIntCallbacks;
    // Mutex for m_propIntCallbacks
    mutable std::shared_timed_mutex m_propIntCallbacksMutex;
    // Next free unique identifier to subscribe for the PropInt32 change.
    std::atomic<long> m_propInt32ChangedCallbackNextId {0};
    // Subscribed callbacks for the PropInt32 change.
    std::map<long, SimpleArrayInterfacePropInt32PropertyCb> m_propInt32Callbacks;
    // Mutex for m_propInt32Callbacks
    mutable std::shared_timed_mutex m_propInt32CallbacksMutex;
    // Next free unique identifier to subscribe for the PropInt64 change.
    std::atomic<long> m_propInt64ChangedCallbackNextId {0};
    // Subscribed callbacks for the PropInt64 change.
    std::map<long, SimpleArrayInterfacePropInt64PropertyCb> m_propInt64Callbacks;
    // Mutex for m_propInt64Callbacks
    mutable std::shared_timed_mutex m_propInt64CallbacksMutex;
    // Next free unique identifier to subscribe for the PropFloat change.
    std::atomic<long> m_propFloatChangedCallbackNextId {0};
    // Subscribed callbacks for the PropFloat change.
    std::map<long, SimpleArrayInterfacePropFloatPropertyCb> m_propFloatCallbacks;
    // Mutex for m_propFloatCallbacks
    mutable std::shared_timed_mutex m_propFloatCallbacksMutex;
    // Next free unique identifier to subscribe for the PropFloat32 change.
    std::atomic<long> m_propFloat32ChangedCallbackNextId {0};
    // Subscribed callbacks for the PropFloat32 change.
    std::map<long, SimpleArrayInterfacePropFloat32PropertyCb> m_propFloat32Callbacks;
    // Mutex for m_propFloat32Callbacks
    mutable std::shared_timed_mutex m_propFloat32CallbacksMutex;
    // Next free unique identifier to subscribe for the PropFloat64 change.
    std::atomic<long> m_propFloat64ChangedCallbackNextId {0};
    // Subscribed callbacks for the PropFloat64 change.
    std::map<long, SimpleArrayInterfacePropFloat64PropertyCb> m_propFloat64Callbacks;
    // Mutex for m_propFloat64Callbacks
    mutable std::shared_timed_mutex m_propFloat64CallbacksMutex;
    // Next free unique identifier to subscribe for the PropString change.
    std::atomic<long> m_propStringChangedCallbackNextId {0};
    // Subscribed callbacks for the PropString change.
    std::map<long, SimpleArrayInterfacePropStringPropertyCb> m_propStringCallbacks;
    // Mutex for m_propStringCallbacks
    mutable std::shared_timed_mutex m_propStringCallbacksMutex;
    // Next free unique identifier to subscribe for the PropReadOnlyString change.
    std::atomic<long> m_propReadOnlyStringChangedCallbackNextId {0};
    // Subscribed callbacks for the PropReadOnlyString change.
    std::map<long, SimpleArrayInterfacePropReadOnlyStringPropertyCb> m_propReadOnlyStringCallbacks;
    // Mutex for m_propReadOnlyStringCallbacks
    mutable std::shared_timed_mutex m_propReadOnlyStringCallbacksMutex;
    // Next free unique identifier to subscribe for the SigBool emission.
    std::atomic<long> m_sigBoolSignalCallbackNextId {0};
    // Subscribed callbacks for the SigBool emission.
    std::map<long, SimpleArrayInterfaceSigBoolSignalCb > m_sigBoolCallbacks;
    // Mutex for m_sigBoolSignalCallbackNextId and m_sigBoolCallbacks
    mutable std::shared_timed_mutex m_sigBoolCallbacksMutex;
    // Next free unique identifier to subscribe for the SigInt emission.
    std::atomic<long> m_sigIntSignalCallbackNextId {0};
    // Subscribed callbacks for the SigInt emission.
    std::map<long, SimpleArrayInterfaceSigIntSignalCb > m_sigIntCallbacks;
    // Mutex for m_sigIntSignalCallbackNextId and m_sigIntCallbacks
    mutable std::shared_timed_mutex m_sigIntCallbacksMutex;
    // Next free unique identifier to subscribe for the SigInt32 emission.
    std::atomic<long> m_sigInt32SignalCallbackNextId {0};
    // Subscribed callbacks for the SigInt32 emission.
    std::map<long, SimpleArrayInterfaceSigInt32SignalCb > m_sigInt32Callbacks;
    // Mutex for m_sigInt32SignalCallbackNextId and m_sigInt32Callbacks
    mutable std::shared_timed_mutex m_sigInt32CallbacksMutex;
    // Next free unique identifier to subscribe for the SigInt64 emission.
    std::atomic<long> m_sigInt64SignalCallbackNextId {0};
    // Subscribed callbacks for the SigInt64 emission.
    std::map<long, SimpleArrayInterfaceSigInt64SignalCb > m_sigInt64Callbacks;
    // Mutex for m_sigInt64SignalCallbackNextId and m_sigInt64Callbacks
    mutable std::shared_timed_mutex m_sigInt64CallbacksMutex;
    // Next free unique identifier to subscribe for the SigFloat emission.
    std::atomic<long> m_sigFloatSignalCallbackNextId {0};
    // Subscribed callbacks for the SigFloat emission.
    std::map<long, SimpleArrayInterfaceSigFloatSignalCb > m_sigFloatCallbacks;
    // Mutex for m_sigFloatSignalCallbackNextId and m_sigFloatCallbacks
    mutable std::shared_timed_mutex m_sigFloatCallbacksMutex;
    // Next free unique identifier to subscribe for the SigFloat32 emission.
    std::atomic<long> m_sigFloat32SignalCallbackNextId {0};
    // Subscribed callbacks for the SigFloat32 emission.
    std::map<long, SimpleArrayInterfaceSigFloat32SignalCb > m_sigFloat32Callbacks;
    // Mutex for m_sigFloat32SignalCallbackNextId and m_sigFloat32Callbacks
    mutable std::shared_timed_mutex m_sigFloat32CallbacksMutex;
    // Next free unique identifier to subscribe for the SigFloat64 emission.
    std::atomic<long> m_sigFloat64SignalCallbackNextId {0};
    // Subscribed callbacks for the SigFloat64 emission.
    std::map<long, SimpleArrayInterfaceSigFloat64SignalCb > m_sigFloat64Callbacks;
    // Mutex for m_sigFloat64SignalCallbackNextId and m_sigFloat64Callbacks
    mutable std::shared_timed_mutex m_sigFloat64CallbacksMutex;
    // Next free unique identifier to subscribe for the SigString emission.
    std::atomic<long> m_sigStringSignalCallbackNextId {0};
    // Subscribed callbacks for the SigString emission.
    std::map<long, SimpleArrayInterfaceSigStringSignalCb > m_sigStringCallbacks;
    // Mutex for m_sigStringSignalCallbackNextId and m_sigStringCallbacks
    mutable std::shared_timed_mutex m_sigStringCallbacksMutex;
};

} // namespace TbSimple
} // namespace Test
