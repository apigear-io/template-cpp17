

#include "tb_simple/generated/core/simplearrayinterface.publisher.h"
#include <algorithm>


using namespace Test::TbSimple;

void SimpleArrayInterfacePublisher::subscribeToAllChanges(ISimpleArrayInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<ISimpleArrayInterfaceSubscriber>(subscriber));
    }
}

void SimpleArrayInterfacePublisher::unsubscribeFromAllChanges(ISimpleArrayInterfaceSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long SimpleArrayInterfacePublisher::subscribeToPropBoolChanged(SimpleArrayInterfacePropBoolPropertyCb callback)
{
    auto handleId = m_propBoolChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_propBoolCallbacksMutex);
    m_propBoolCallbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropBoolChanged(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propBoolCallbacksMutex);
    m_propBoolCallbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishPropBoolChanged(const std::list<bool>& propBool) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropBoolChanged(propBool);
    }
    std::shared_lock<std::shared_timed_mutex> propBoolCallbacksLock(m_propBoolCallbacksMutex);
    const auto propBoolCallbacks = m_propBoolCallbacks;
    propBoolCallbacksLock.unlock();
    for(const auto& callbackEntry: propBoolCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(propBool);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToPropIntChanged(SimpleArrayInterfacePropIntPropertyCb callback)
{
    auto handleId = m_propIntChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_propIntCallbacksMutex);
    m_propIntCallbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropIntChanged(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propIntCallbacksMutex);
    m_propIntCallbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishPropIntChanged(const std::list<int>& propInt) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropIntChanged(propInt);
    }
    std::shared_lock<std::shared_timed_mutex> propIntCallbacksLock(m_propIntCallbacksMutex);
    const auto propIntCallbacks = m_propIntCallbacks;
    propIntCallbacksLock.unlock();
    for(const auto& callbackEntry: propIntCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(propInt);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToPropInt32Changed(SimpleArrayInterfacePropInt32PropertyCb callback)
{
    auto handleId = m_propInt32ChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_propInt32CallbacksMutex);
    m_propInt32Callbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropInt32Changed(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propInt32CallbacksMutex);
    m_propInt32Callbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishPropInt32Changed(const std::list<int32_t>& propInt32) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropInt32Changed(propInt32);
    }
    std::shared_lock<std::shared_timed_mutex> propInt32CallbacksLock(m_propInt32CallbacksMutex);
    const auto propInt32Callbacks = m_propInt32Callbacks;
    propInt32CallbacksLock.unlock();
    for(const auto& callbackEntry: propInt32Callbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(propInt32);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToPropInt64Changed(SimpleArrayInterfacePropInt64PropertyCb callback)
{
    auto handleId = m_propInt64ChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_propInt64CallbacksMutex);
    m_propInt64Callbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropInt64Changed(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propInt64CallbacksMutex);
    m_propInt64Callbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishPropInt64Changed(const std::list<int64_t>& propInt64) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropInt64Changed(propInt64);
    }
    std::shared_lock<std::shared_timed_mutex> propInt64CallbacksLock(m_propInt64CallbacksMutex);
    const auto propInt64Callbacks = m_propInt64Callbacks;
    propInt64CallbacksLock.unlock();
    for(const auto& callbackEntry: propInt64Callbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(propInt64);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToPropFloatChanged(SimpleArrayInterfacePropFloatPropertyCb callback)
{
    auto handleId = m_propFloatChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloatCallbacksMutex);
    m_propFloatCallbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropFloatChanged(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloatCallbacksMutex);
    m_propFloatCallbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishPropFloatChanged(const std::list<float>& propFloat) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropFloatChanged(propFloat);
    }
    std::shared_lock<std::shared_timed_mutex> propFloatCallbacksLock(m_propFloatCallbacksMutex);
    const auto propFloatCallbacks = m_propFloatCallbacks;
    propFloatCallbacksLock.unlock();
    for(const auto& callbackEntry: propFloatCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(propFloat);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToPropFloat32Changed(SimpleArrayInterfacePropFloat32PropertyCb callback)
{
    auto handleId = m_propFloat32ChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloat32CallbacksMutex);
    m_propFloat32Callbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropFloat32Changed(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloat32CallbacksMutex);
    m_propFloat32Callbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishPropFloat32Changed(const std::list<float>& propFloat32) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropFloat32Changed(propFloat32);
    }
    std::shared_lock<std::shared_timed_mutex> propFloat32CallbacksLock(m_propFloat32CallbacksMutex);
    const auto propFloat32Callbacks = m_propFloat32Callbacks;
    propFloat32CallbacksLock.unlock();
    for(const auto& callbackEntry: propFloat32Callbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(propFloat32);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToPropFloat64Changed(SimpleArrayInterfacePropFloat64PropertyCb callback)
{
    auto handleId = m_propFloat64ChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloat64CallbacksMutex);
    m_propFloat64Callbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropFloat64Changed(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloat64CallbacksMutex);
    m_propFloat64Callbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishPropFloat64Changed(const std::list<double>& propFloat64) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropFloat64Changed(propFloat64);
    }
    std::shared_lock<std::shared_timed_mutex> propFloat64CallbacksLock(m_propFloat64CallbacksMutex);
    const auto propFloat64Callbacks = m_propFloat64Callbacks;
    propFloat64CallbacksLock.unlock();
    for(const auto& callbackEntry: propFloat64Callbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(propFloat64);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToPropStringChanged(SimpleArrayInterfacePropStringPropertyCb callback)
{
    auto handleId = m_propStringChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_propStringCallbacksMutex);
    m_propStringCallbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropStringChanged(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propStringCallbacksMutex);
    m_propStringCallbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishPropStringChanged(const std::list<std::string>& propString) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropStringChanged(propString);
    }
    std::shared_lock<std::shared_timed_mutex> propStringCallbacksLock(m_propStringCallbacksMutex);
    const auto propStringCallbacks = m_propStringCallbacks;
    propStringCallbacksLock.unlock();
    for(const auto& callbackEntry: propStringCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(propString);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToPropReadOnlyStringChanged(SimpleArrayInterfacePropReadOnlyStringPropertyCb callback)
{
    auto handleId = m_propReadOnlyStringChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_propReadOnlyStringCallbacksMutex);
    m_propReadOnlyStringCallbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromPropReadOnlyStringChanged(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propReadOnlyStringCallbacksMutex);
    m_propReadOnlyStringCallbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishPropReadOnlyStringChanged(const std::string& propReadOnlyString) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onPropReadOnlyStringChanged(propReadOnlyString);
    }
    std::shared_lock<std::shared_timed_mutex> propReadOnlyStringCallbacksLock(m_propReadOnlyStringCallbacksMutex);
    const auto propReadOnlyStringCallbacks = m_propReadOnlyStringCallbacks;
    propReadOnlyStringCallbacksLock.unlock();
    for(const auto& callbackEntry: propReadOnlyStringCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(propReadOnlyString);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToSigBool(SimpleArrayInterfaceSigBoolSignalCb callback)
{
    // this is a short term workaround - we need a better solution for unique handle identifiers
    auto handleId = m_sigBoolSignalCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_sigBoolCallbacksMutex);
    m_sigBoolCallbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigBool(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_sigBoolCallbacksMutex);
    m_sigBoolCallbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishSigBool(const std::list<bool>& paramBool) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigBool(paramBool);
    }
    std::shared_lock<std::shared_timed_mutex> sigBoolCallbacksLock(m_sigBoolCallbacksMutex);
    const auto sigBoolCallbacks = m_sigBoolCallbacks;
    sigBoolCallbacksLock.unlock();
    for(const auto& callbackEntry: sigBoolCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(paramBool);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToSigInt(SimpleArrayInterfaceSigIntSignalCb callback)
{
    // this is a short term workaround - we need a better solution for unique handle identifiers
    auto handleId = m_sigIntSignalCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_sigIntCallbacksMutex);
    m_sigIntCallbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigInt(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_sigIntCallbacksMutex);
    m_sigIntCallbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishSigInt(const std::list<int>& paramInt) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigInt(paramInt);
    }
    std::shared_lock<std::shared_timed_mutex> sigIntCallbacksLock(m_sigIntCallbacksMutex);
    const auto sigIntCallbacks = m_sigIntCallbacks;
    sigIntCallbacksLock.unlock();
    for(const auto& callbackEntry: sigIntCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(paramInt);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToSigInt32(SimpleArrayInterfaceSigInt32SignalCb callback)
{
    // this is a short term workaround - we need a better solution for unique handle identifiers
    auto handleId = m_sigInt32SignalCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_sigInt32CallbacksMutex);
    m_sigInt32Callbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigInt32(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_sigInt32CallbacksMutex);
    m_sigInt32Callbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishSigInt32(const std::list<int32_t>& paramInt32) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigInt32(paramInt32);
    }
    std::shared_lock<std::shared_timed_mutex> sigInt32CallbacksLock(m_sigInt32CallbacksMutex);
    const auto sigInt32Callbacks = m_sigInt32Callbacks;
    sigInt32CallbacksLock.unlock();
    for(const auto& callbackEntry: sigInt32Callbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(paramInt32);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToSigInt64(SimpleArrayInterfaceSigInt64SignalCb callback)
{
    // this is a short term workaround - we need a better solution for unique handle identifiers
    auto handleId = m_sigInt64SignalCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_sigInt64CallbacksMutex);
    m_sigInt64Callbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigInt64(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_sigInt64CallbacksMutex);
    m_sigInt64Callbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishSigInt64(const std::list<int64_t>& paramInt64) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigInt64(paramInt64);
    }
    std::shared_lock<std::shared_timed_mutex> sigInt64CallbacksLock(m_sigInt64CallbacksMutex);
    const auto sigInt64Callbacks = m_sigInt64Callbacks;
    sigInt64CallbacksLock.unlock();
    for(const auto& callbackEntry: sigInt64Callbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(paramInt64);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToSigFloat(SimpleArrayInterfaceSigFloatSignalCb callback)
{
    // this is a short term workaround - we need a better solution for unique handle identifiers
    auto handleId = m_sigFloatSignalCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_sigFloatCallbacksMutex);
    m_sigFloatCallbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigFloat(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_sigFloatCallbacksMutex);
    m_sigFloatCallbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishSigFloat(const std::list<float>& paramFloat) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigFloat(paramFloat);
    }
    std::shared_lock<std::shared_timed_mutex> sigFloatCallbacksLock(m_sigFloatCallbacksMutex);
    const auto sigFloatCallbacks = m_sigFloatCallbacks;
    sigFloatCallbacksLock.unlock();
    for(const auto& callbackEntry: sigFloatCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(paramFloat);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToSigFloat32(SimpleArrayInterfaceSigFloat32SignalCb callback)
{
    // this is a short term workaround - we need a better solution for unique handle identifiers
    auto handleId = m_sigFloat32SignalCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_sigFloat32CallbacksMutex);
    m_sigFloat32Callbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigFloat32(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_sigFloat32CallbacksMutex);
    m_sigFloat32Callbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishSigFloat32(const std::list<float>& paramFloa32) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigFloat32(paramFloa32);
    }
    std::shared_lock<std::shared_timed_mutex> sigFloat32CallbacksLock(m_sigFloat32CallbacksMutex);
    const auto sigFloat32Callbacks = m_sigFloat32Callbacks;
    sigFloat32CallbacksLock.unlock();
    for(const auto& callbackEntry: sigFloat32Callbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(paramFloa32);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToSigFloat64(SimpleArrayInterfaceSigFloat64SignalCb callback)
{
    // this is a short term workaround - we need a better solution for unique handle identifiers
    auto handleId = m_sigFloat64SignalCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_sigFloat64CallbacksMutex);
    m_sigFloat64Callbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigFloat64(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_sigFloat64CallbacksMutex);
    m_sigFloat64Callbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishSigFloat64(const std::list<double>& paramFloat64) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigFloat64(paramFloat64);
    }
    std::shared_lock<std::shared_timed_mutex> sigFloat64CallbacksLock(m_sigFloat64CallbacksMutex);
    const auto sigFloat64Callbacks = m_sigFloat64Callbacks;
    sigFloat64CallbacksLock.unlock();
    for(const auto& callbackEntry: sigFloat64Callbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(paramFloat64);
        }
    }
}

long SimpleArrayInterfacePublisher::subscribeToSigString(SimpleArrayInterfaceSigStringSignalCb callback)
{
    // this is a short term workaround - we need a better solution for unique handle identifiers
    auto handleId = m_sigStringSignalCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_sigStringCallbacksMutex);
    m_sigStringCallbacks[handleId] = callback;
    return handleId;
}

void SimpleArrayInterfacePublisher::unsubscribeFromSigString(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_sigStringCallbacksMutex);
    m_sigStringCallbacks.erase(handleId);
}

void SimpleArrayInterfacePublisher::publishSigString(const std::list<std::string>& paramString) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSigString(paramString);
    }
    std::shared_lock<std::shared_timed_mutex> sigStringCallbacksLock(m_sigStringCallbacksMutex);
    const auto sigStringCallbacks = m_sigStringCallbacks;
    sigStringCallbacksLock.unlock();
    for(const auto& callbackEntry: sigStringCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(paramString);
        }
    }
}

