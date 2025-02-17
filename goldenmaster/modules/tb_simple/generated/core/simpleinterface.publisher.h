#pragma once

#include "tb_simple/generated/api/datastructs.api.h"
#include "tb_simple/generated/api/simpleinterface.api.h"
#include "tb_simple/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>

namespace Test {
namespace TbSimple {

/**
 * The implementation of a SimpleInterfacePublisher.
 * Use this class to store clients of the SimpleInterface and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
 */
class TEST_TB_SIMPLE_EXPORT SimpleInterfacePublisher : public ISimpleInterfacePublisher
{
public:
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(ISimpleInterfaceSubscriber& subscriber) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(ISimpleInterfaceSubscriber& subscriber) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropBoolChanged
    */
    long subscribeToPropBoolChanged(SimpleInterfacePropBoolPropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropBoolChanged
    */
    void unsubscribeFromPropBoolChanged(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropIntChanged
    */
    long subscribeToPropIntChanged(SimpleInterfacePropIntPropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropInt32Changed
    */
    long subscribeToPropInt32Changed(SimpleInterfacePropInt32PropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropInt32Changed
    */
    void unsubscribeFromPropInt32Changed(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropInt64Changed
    */
    long subscribeToPropInt64Changed(SimpleInterfacePropInt64PropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropInt64Changed
    */
    void unsubscribeFromPropInt64Changed(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropFloatChanged
    */
    long subscribeToPropFloatChanged(SimpleInterfacePropFloatPropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropFloatChanged
    */
    void unsubscribeFromPropFloatChanged(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropFloat32Changed
    */
    long subscribeToPropFloat32Changed(SimpleInterfacePropFloat32PropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropFloat32Changed
    */
    void unsubscribeFromPropFloat32Changed(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropFloat64Changed
    */
    long subscribeToPropFloat64Changed(SimpleInterfacePropFloat64PropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropFloat64Changed
    */
    void unsubscribeFromPropFloat64Changed(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropStringChanged
    */
    long subscribeToPropStringChanged(SimpleInterfacePropStringPropertyCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToPropStringChanged
    */
    void unsubscribeFromPropStringChanged(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigBool
    */
    long subscribeToSigBool(SimpleInterfaceSigBoolSignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigBool
    */
    void unsubscribeFromSigBool(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigInt
    */
    long subscribeToSigInt(SimpleInterfaceSigIntSignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigInt
    */
    void unsubscribeFromSigInt(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigInt32
    */
    long subscribeToSigInt32(SimpleInterfaceSigInt32SignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigInt32
    */
    void unsubscribeFromSigInt32(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigInt64
    */
    long subscribeToSigInt64(SimpleInterfaceSigInt64SignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigInt64
    */
    void unsubscribeFromSigInt64(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigFloat
    */
    long subscribeToSigFloat(SimpleInterfaceSigFloatSignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigFloat
    */
    void unsubscribeFromSigFloat(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigFloat32
    */
    long subscribeToSigFloat32(SimpleInterfaceSigFloat32SignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigFloat32
    */
    void unsubscribeFromSigFloat32(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigFloat64
    */
    long subscribeToSigFloat64(SimpleInterfaceSigFloat64SignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigFloat64
    */
    void unsubscribeFromSigFloat64(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::subscribeToSigString
    */
    long subscribeToSigString(SimpleInterfaceSigStringSignalCb callback) override;
    /**
    * Implementation of ISimpleInterfacePublisher::unsubscribeFromSigString
    */
    void unsubscribeFromSigString(long handleId) override;

    /**
    * Implementation of ISimpleInterfacePublisher::publishPropBoolChanged
    */
    void publishPropBoolChanged(bool propBool) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishPropIntChanged
    */
    void publishPropIntChanged(int propInt) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishPropInt32Changed
    */
    void publishPropInt32Changed(int32_t propInt32) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishPropInt64Changed
    */
    void publishPropInt64Changed(int64_t propInt64) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishPropFloatChanged
    */
    void publishPropFloatChanged(float propFloat) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishPropFloat32Changed
    */
    void publishPropFloat32Changed(float propFloat32) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishPropFloat64Changed
    */
    void publishPropFloat64Changed(double propFloat64) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishPropStringChanged
    */
    void publishPropStringChanged(const std::string& propString) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigBool
    */
    void publishSigBool(bool paramBool) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigInt
    */
    void publishSigInt(int paramInt) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigInt32
    */
    void publishSigInt32(int32_t paramInt32) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigInt64
    */
    void publishSigInt64(int64_t paramInt64) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigFloat
    */
    void publishSigFloat(float paramFloat) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigFloat32
    */
    void publishSigFloat32(float paramFloat32) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigFloat64
    */
    void publishSigFloat64(double paramFloat64) const override;
    /**
    * Implementation of ISimpleInterfacePublisher::publishSigString
    */
    void publishSigString(const std::string& paramString) const override;
private:
    // Subscribers informed about any property change or signal emitted in SimpleInterface
    std::vector<std::reference_wrapper<ISimpleInterfaceSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    // Next free unique identifier to subscribe for the PropBool change.
    std::atomic<long> m_propBoolChangedCallbackNextId {0};
    // Subscribed callbacks for the PropBool change.
    std::map<long, SimpleInterfacePropBoolPropertyCb> m_propBoolCallbacks;
    // Mutex for m_propBoolCallbacks
    mutable std::shared_timed_mutex m_propBoolCallbacksMutex;
    // Next free unique identifier to subscribe for the PropInt change.
    std::atomic<long> m_propIntChangedCallbackNextId {0};
    // Subscribed callbacks for the PropInt change.
    std::map<long, SimpleInterfacePropIntPropertyCb> m_propIntCallbacks;
    // Mutex for m_propIntCallbacks
    mutable std::shared_timed_mutex m_propIntCallbacksMutex;
    // Next free unique identifier to subscribe for the PropInt32 change.
    std::atomic<long> m_propInt32ChangedCallbackNextId {0};
    // Subscribed callbacks for the PropInt32 change.
    std::map<long, SimpleInterfacePropInt32PropertyCb> m_propInt32Callbacks;
    // Mutex for m_propInt32Callbacks
    mutable std::shared_timed_mutex m_propInt32CallbacksMutex;
    // Next free unique identifier to subscribe for the PropInt64 change.
    std::atomic<long> m_propInt64ChangedCallbackNextId {0};
    // Subscribed callbacks for the PropInt64 change.
    std::map<long, SimpleInterfacePropInt64PropertyCb> m_propInt64Callbacks;
    // Mutex for m_propInt64Callbacks
    mutable std::shared_timed_mutex m_propInt64CallbacksMutex;
    // Next free unique identifier to subscribe for the PropFloat change.
    std::atomic<long> m_propFloatChangedCallbackNextId {0};
    // Subscribed callbacks for the PropFloat change.
    std::map<long, SimpleInterfacePropFloatPropertyCb> m_propFloatCallbacks;
    // Mutex for m_propFloatCallbacks
    mutable std::shared_timed_mutex m_propFloatCallbacksMutex;
    // Next free unique identifier to subscribe for the PropFloat32 change.
    std::atomic<long> m_propFloat32ChangedCallbackNextId {0};
    // Subscribed callbacks for the PropFloat32 change.
    std::map<long, SimpleInterfacePropFloat32PropertyCb> m_propFloat32Callbacks;
    // Mutex for m_propFloat32Callbacks
    mutable std::shared_timed_mutex m_propFloat32CallbacksMutex;
    // Next free unique identifier to subscribe for the PropFloat64 change.
    std::atomic<long> m_propFloat64ChangedCallbackNextId {0};
    // Subscribed callbacks for the PropFloat64 change.
    std::map<long, SimpleInterfacePropFloat64PropertyCb> m_propFloat64Callbacks;
    // Mutex for m_propFloat64Callbacks
    mutable std::shared_timed_mutex m_propFloat64CallbacksMutex;
    // Next free unique identifier to subscribe for the PropString change.
    std::atomic<long> m_propStringChangedCallbackNextId {0};
    // Subscribed callbacks for the PropString change.
    std::map<long, SimpleInterfacePropStringPropertyCb> m_propStringCallbacks;
    // Mutex for m_propStringCallbacks
    mutable std::shared_timed_mutex m_propStringCallbacksMutex;
    // Next free unique identifier to subscribe for the SigBool emission.
    std::atomic<long> m_sigBoolSignalCallbackNextId {0};
    // Subscribed callbacks for the SigBool emission.
    std::map<long, SimpleInterfaceSigBoolSignalCb > m_sigBoolCallbacks;
    // Mutex for m_sigBoolSignalCallbackNextId and m_sigBoolCallbacks
    mutable std::shared_timed_mutex m_sigBoolCallbacksMutex;
    // Next free unique identifier to subscribe for the SigInt emission.
    std::atomic<long> m_sigIntSignalCallbackNextId {0};
    // Subscribed callbacks for the SigInt emission.
    std::map<long, SimpleInterfaceSigIntSignalCb > m_sigIntCallbacks;
    // Mutex for m_sigIntSignalCallbackNextId and m_sigIntCallbacks
    mutable std::shared_timed_mutex m_sigIntCallbacksMutex;
    // Next free unique identifier to subscribe for the SigInt32 emission.
    std::atomic<long> m_sigInt32SignalCallbackNextId {0};
    // Subscribed callbacks for the SigInt32 emission.
    std::map<long, SimpleInterfaceSigInt32SignalCb > m_sigInt32Callbacks;
    // Mutex for m_sigInt32SignalCallbackNextId and m_sigInt32Callbacks
    mutable std::shared_timed_mutex m_sigInt32CallbacksMutex;
    // Next free unique identifier to subscribe for the SigInt64 emission.
    std::atomic<long> m_sigInt64SignalCallbackNextId {0};
    // Subscribed callbacks for the SigInt64 emission.
    std::map<long, SimpleInterfaceSigInt64SignalCb > m_sigInt64Callbacks;
    // Mutex for m_sigInt64SignalCallbackNextId and m_sigInt64Callbacks
    mutable std::shared_timed_mutex m_sigInt64CallbacksMutex;
    // Next free unique identifier to subscribe for the SigFloat emission.
    std::atomic<long> m_sigFloatSignalCallbackNextId {0};
    // Subscribed callbacks for the SigFloat emission.
    std::map<long, SimpleInterfaceSigFloatSignalCb > m_sigFloatCallbacks;
    // Mutex for m_sigFloatSignalCallbackNextId and m_sigFloatCallbacks
    mutable std::shared_timed_mutex m_sigFloatCallbacksMutex;
    // Next free unique identifier to subscribe for the SigFloat32 emission.
    std::atomic<long> m_sigFloat32SignalCallbackNextId {0};
    // Subscribed callbacks for the SigFloat32 emission.
    std::map<long, SimpleInterfaceSigFloat32SignalCb > m_sigFloat32Callbacks;
    // Mutex for m_sigFloat32SignalCallbackNextId and m_sigFloat32Callbacks
    mutable std::shared_timed_mutex m_sigFloat32CallbacksMutex;
    // Next free unique identifier to subscribe for the SigFloat64 emission.
    std::atomic<long> m_sigFloat64SignalCallbackNextId {0};
    // Subscribed callbacks for the SigFloat64 emission.
    std::map<long, SimpleInterfaceSigFloat64SignalCb > m_sigFloat64Callbacks;
    // Mutex for m_sigFloat64SignalCallbackNextId and m_sigFloat64Callbacks
    mutable std::shared_timed_mutex m_sigFloat64CallbacksMutex;
    // Next free unique identifier to subscribe for the SigString emission.
    std::atomic<long> m_sigStringSignalCallbackNextId {0};
    // Subscribed callbacks for the SigString emission.
    std::map<long, SimpleInterfaceSigStringSignalCb > m_sigStringCallbacks;
    // Mutex for m_sigStringSignalCallbackNextId and m_sigStringCallbacks
    mutable std::shared_timed_mutex m_sigStringCallbacksMutex;
};

} // namespace TbSimple
} // namespace Test
