#pragma once

#include <future>
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/datastructs.api.h"

namespace Test {
namespace TbSimple {

class ISimpleArrayInterfaceSubscriber;
class ISimpleArrayInterfacePublisher;

/**
*
* ISimpleArrayInterface provides an interface for
 *  - methods defined for your SimpleArrayInterface 
 *  - property setters and getters for defined properties
 * The ISimpleArrayInterface also provides an interface to access a publisher ISimpleArrayInterfacePublisher, a class used by ISimpleArrayInterfaceSubscriber clients.
 * The implementation should notify the publisher ISimpleArrayInterfacePublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also ISimpleArrayInterfaceSubscriber, ISimpleArrayInterfacePublisher
 * and the example implementation SimpleArrayInterface  or the
 */
class TEST_TB_SIMPLE_EXPORT ISimpleArrayInterface
{
public:
    virtual ~ISimpleArrayInterface() = default;


    virtual std::list<bool> funcBool(const std::list<bool>& paramBool) = 0;
    /**
    * Asynchronous version of funcBool(const std::list<bool>& paramBool)
    * @return Promise of type std::list<bool> which is set once the function has completed
    */
    virtual std::future<std::list<bool>> funcBoolAsync(const std::list<bool>& paramBool) = 0;


    virtual std::list<int> funcInt(const std::list<int>& paramInt) = 0;
    /**
    * Asynchronous version of funcInt(const std::list<int>& paramInt)
    * @return Promise of type std::list<int> which is set once the function has completed
    */
    virtual std::future<std::list<int>> funcIntAsync(const std::list<int>& paramInt) = 0;


    virtual std::list<int32_t> funcInt32(const std::list<int32_t>& paramInt32) = 0;
    /**
    * Asynchronous version of funcInt32(const std::list<int32_t>& paramInt32)
    * @return Promise of type std::list<int32_t> which is set once the function has completed
    */
    virtual std::future<std::list<int32_t>> funcInt32Async(const std::list<int32_t>& paramInt32) = 0;


    virtual std::list<int64_t> funcInt64(const std::list<int64_t>& paramInt64) = 0;
    /**
    * Asynchronous version of funcInt64(const std::list<int64_t>& paramInt64)
    * @return Promise of type std::list<int64_t> which is set once the function has completed
    */
    virtual std::future<std::list<int64_t>> funcInt64Async(const std::list<int64_t>& paramInt64) = 0;


    virtual std::list<float> funcFloat(const std::list<float>& paramFloat) = 0;
    /**
    * Asynchronous version of funcFloat(const std::list<float>& paramFloat)
    * @return Promise of type std::list<float> which is set once the function has completed
    */
    virtual std::future<std::list<float>> funcFloatAsync(const std::list<float>& paramFloat) = 0;


    virtual std::list<float> funcFloat32(const std::list<float>& paramFloat32) = 0;
    /**
    * Asynchronous version of funcFloat32(const std::list<float>& paramFloat32)
    * @return Promise of type std::list<float> which is set once the function has completed
    */
    virtual std::future<std::list<float>> funcFloat32Async(const std::list<float>& paramFloat32) = 0;


    virtual std::list<double> funcFloat64(const std::list<double>& paramFloat) = 0;
    /**
    * Asynchronous version of funcFloat64(const std::list<double>& paramFloat)
    * @return Promise of type std::list<double> which is set once the function has completed
    */
    virtual std::future<std::list<double>> funcFloat64Async(const std::list<double>& paramFloat) = 0;


    virtual std::list<std::string> funcString(const std::list<std::string>& paramString) = 0;
    /**
    * Asynchronous version of funcString(const std::list<std::string>& paramString)
    * @return Promise of type std::list<std::string> which is set once the function has completed
    */
    virtual std::future<std::list<std::string>> funcStringAsync(const std::list<std::string>& paramString) = 0;

    /**
    * Sets the value of the propBool property.
    */
    virtual void setPropBool(const std::list<bool>& propBool) = 0;
    /**
    * Gets the value of the propBool property.
    */
    virtual const std::list<bool>& getPropBool() const = 0;

    /**
    * Sets the value of the propInt property.
    */
    virtual void setPropInt(const std::list<int>& propInt) = 0;
    /**
    * Gets the value of the propInt property.
    */
    virtual const std::list<int>& getPropInt() const = 0;

    /**
    * Sets the value of the propInt32 property.
    */
    virtual void setPropInt32(const std::list<int32_t>& propInt32) = 0;
    /**
    * Gets the value of the propInt32 property.
    */
    virtual const std::list<int32_t>& getPropInt32() const = 0;

    /**
    * Sets the value of the propInt64 property.
    */
    virtual void setPropInt64(const std::list<int64_t>& propInt64) = 0;
    /**
    * Gets the value of the propInt64 property.
    */
    virtual const std::list<int64_t>& getPropInt64() const = 0;

    /**
    * Sets the value of the propFloat property.
    */
    virtual void setPropFloat(const std::list<float>& propFloat) = 0;
    /**
    * Gets the value of the propFloat property.
    */
    virtual const std::list<float>& getPropFloat() const = 0;

    /**
    * Sets the value of the propFloat32 property.
    */
    virtual void setPropFloat32(const std::list<float>& propFloat32) = 0;
    /**
    * Gets the value of the propFloat32 property.
    */
    virtual const std::list<float>& getPropFloat32() const = 0;

    /**
    * Sets the value of the propFloat64 property.
    */
    virtual void setPropFloat64(const std::list<double>& propFloat64) = 0;
    /**
    * Gets the value of the propFloat64 property.
    */
    virtual const std::list<double>& getPropFloat64() const = 0;

    /**
    * Sets the value of the propString property.
    */
    virtual void setPropString(const std::list<std::string>& propString) = 0;
    /**
    * Gets the value of the propString property.
    */
    virtual const std::list<std::string>& getPropString() const = 0;

    /**
    * Gets the value of the propReadOnlyString property.
    */
    virtual const std::string& getPropReadOnlyString() const = 0;

    /**
    * Access to a publisher, use it to subscribe for SimpleArrayInterface changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for SimpleArrayInterface.
    */
    virtual ISimpleArrayInterfacePublisher& _getPublisher() const = 0;
};


/**
 * The ISimpleArrayInterfaceSubscriber contains functions to allow informing about signals or property changes of the ISimpleArrayInterface implementation.
 * The implementation for ISimpleArrayInterface should provide mechanism for subscription of the ISimpleArrayInterfaceSubscriber clients.
 * See ISimpleArrayInterfacePublisher, which provides facilitation for this purpose.
 * The implementation for ISimpleArrayInterface should call the ISimpleArrayInterfaceSubscriber interface functions on either signal emit or property change.
 * You can use ISimpleArrayInterfaceSubscriber class to implement clients of the ISimpleArrayInterface or the network adapter - see Olink Server and Client example.
 */
class TEST_TB_SIMPLE_EXPORT ISimpleArrayInterfaceSubscriber
{
public:
    virtual ~ISimpleArrayInterfaceSubscriber() = default;
    /**
    * Called by the ISimpleArrayInterfacePublisher when the SimpleArrayInterface emits sigBool, if subscribed for the sigBool.
    * @param paramBool 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigBool(const std::list<bool>& paramBool) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when the SimpleArrayInterface emits sigInt, if subscribed for the sigInt.
    * @param paramInt 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigInt(const std::list<int>& paramInt) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when the SimpleArrayInterface emits sigInt32, if subscribed for the sigInt32.
    * @param paramInt32 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigInt32(const std::list<int32_t>& paramInt32) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when the SimpleArrayInterface emits sigInt64, if subscribed for the sigInt64.
    * @param paramInt64 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigInt64(const std::list<int64_t>& paramInt64) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when the SimpleArrayInterface emits sigFloat, if subscribed for the sigFloat.
    * @param paramFloat 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigFloat(const std::list<float>& paramFloat) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when the SimpleArrayInterface emits sigFloat32, if subscribed for the sigFloat32.
    * @param paramFloa32 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigFloat32(const std::list<float>& paramFloa32) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when the SimpleArrayInterface emits sigFloat64, if subscribed for the sigFloat64.
    * @param paramFloat64 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigFloat64(const std::list<double>& paramFloat64) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when the SimpleArrayInterface emits sigString, if subscribed for the sigString.
    * @param paramString 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigString(const std::list<std::string>& paramString) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when propBool value has changed if subscribed for the propBool change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropBoolChanged(const std::list<bool>& propBool) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when propInt value has changed if subscribed for the propInt change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropIntChanged(const std::list<int>& propInt) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when propInt32 value has changed if subscribed for the propInt32 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropInt32Changed(const std::list<int32_t>& propInt32) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when propInt64 value has changed if subscribed for the propInt64 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropInt64Changed(const std::list<int64_t>& propInt64) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when propFloat value has changed if subscribed for the propFloat change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropFloatChanged(const std::list<float>& propFloat) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when propFloat32 value has changed if subscribed for the propFloat32 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropFloat32Changed(const std::list<float>& propFloat32) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when propFloat64 value has changed if subscribed for the propFloat64 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropFloat64Changed(const std::list<double>& propFloat64) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when propString value has changed if subscribed for the propString change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropStringChanged(const std::list<std::string>& propString) = 0;
    /**
    * Called by the ISimpleArrayInterfacePublisher when propReadOnlyString value has changed if subscribed for the propReadOnlyString change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropReadOnlyStringChanged(const std::string& propReadOnlyString) = 0;
};

/** Callback for changes of propBool */
using SimpleArrayInterfacePropBoolPropertyCb = std::function<void(const std::list<bool>& propBool)>;
/** Callback for changes of propInt */
using SimpleArrayInterfacePropIntPropertyCb = std::function<void(const std::list<int>& propInt)>;
/** Callback for changes of propInt32 */
using SimpleArrayInterfacePropInt32PropertyCb = std::function<void(const std::list<int32_t>& propInt32)>;
/** Callback for changes of propInt64 */
using SimpleArrayInterfacePropInt64PropertyCb = std::function<void(const std::list<int64_t>& propInt64)>;
/** Callback for changes of propFloat */
using SimpleArrayInterfacePropFloatPropertyCb = std::function<void(const std::list<float>& propFloat)>;
/** Callback for changes of propFloat32 */
using SimpleArrayInterfacePropFloat32PropertyCb = std::function<void(const std::list<float>& propFloat32)>;
/** Callback for changes of propFloat64 */
using SimpleArrayInterfacePropFloat64PropertyCb = std::function<void(const std::list<double>& propFloat64)>;
/** Callback for changes of propString */
using SimpleArrayInterfacePropStringPropertyCb = std::function<void(const std::list<std::string>& propString)>;
/** Callback for changes of propReadOnlyString */
using SimpleArrayInterfacePropReadOnlyStringPropertyCb = std::function<void(const std::string& propReadOnlyString)>;
/** Callback for sigBool signal triggers */
using SimpleArrayInterfaceSigBoolSignalCb = std::function<void(const std::list<bool>& paramBool)> ;
/** Callback for sigInt signal triggers */
using SimpleArrayInterfaceSigIntSignalCb = std::function<void(const std::list<int>& paramInt)> ;
/** Callback for sigInt32 signal triggers */
using SimpleArrayInterfaceSigInt32SignalCb = std::function<void(const std::list<int32_t>& paramInt32)> ;
/** Callback for sigInt64 signal triggers */
using SimpleArrayInterfaceSigInt64SignalCb = std::function<void(const std::list<int64_t>& paramInt64)> ;
/** Callback for sigFloat signal triggers */
using SimpleArrayInterfaceSigFloatSignalCb = std::function<void(const std::list<float>& paramFloat)> ;
/** Callback for sigFloat32 signal triggers */
using SimpleArrayInterfaceSigFloat32SignalCb = std::function<void(const std::list<float>& paramFloa32)> ;
/** Callback for sigFloat64 signal triggers */
using SimpleArrayInterfaceSigFloat64SignalCb = std::function<void(const std::list<double>& paramFloat64)> ;
/** Callback for sigString signal triggers */
using SimpleArrayInterfaceSigStringSignalCb = std::function<void(const std::list<std::string>& paramString)> ;


/**
 * The ISimpleArrayInterfacePublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your ISimpleArrayInterface implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a ISimpleArrayInterfaceSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IISimpleArrayInterface on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TB_SIMPLE_EXPORT ISimpleArrayInterfacePublisher
{
public:
    virtual ~ISimpleArrayInterfacePublisher() = default;

    /**
    * Use this function to subscribe for any change of the SimpleArrayInterface.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param ISimpleArrayInterfaceSubscriber which is subscribed in this function to any change of the SimpleArrayInterface.
    */
    virtual void subscribeToAllChanges(ISimpleArrayInterfaceSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the SimpleArrayInterface.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param ISimpleArrayInterfaceSubscriber which subscription for any change of the SimpleArrayInterface is removed.
    */
    virtual void unsubscribeFromAllChanges(ISimpleArrayInterfaceSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for propBool value changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleArrayInterfacePropBoolPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropBoolChanged(SimpleArrayInterfacePropBoolPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propBool property changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropBoolChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propInt value changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleArrayInterfacePropIntPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropIntChanged(SimpleArrayInterfacePropIntPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propInt property changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropIntChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propInt32 value changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleArrayInterfacePropInt32PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropInt32Changed(SimpleArrayInterfacePropInt32PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propInt32 property changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropInt32Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for propInt64 value changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleArrayInterfacePropInt64PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropInt64Changed(SimpleArrayInterfacePropInt64PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propInt64 property changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropInt64Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for propFloat value changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleArrayInterfacePropFloatPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropFloatChanged(SimpleArrayInterfacePropFloatPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propFloat property changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropFloatChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propFloat32 value changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleArrayInterfacePropFloat32PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropFloat32Changed(SimpleArrayInterfacePropFloat32PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propFloat32 property changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropFloat32Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for propFloat64 value changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleArrayInterfacePropFloat64PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropFloat64Changed(SimpleArrayInterfacePropFloat64PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propFloat64 property changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropFloat64Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for propString value changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleArrayInterfacePropStringPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropStringChanged(SimpleArrayInterfacePropStringPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propString property changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropStringChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propReadOnlyString value changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleArrayInterfacePropReadOnlyStringPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropReadOnlyStringChanged(SimpleArrayInterfacePropReadOnlyStringPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propReadOnlyString property changes.
    * If your subscriber uses subscription with ISimpleArrayInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropReadOnlyStringChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for sigBool signal changes.
    * @param SimpleArrayInterfaceSigBoolSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigBool(SimpleArrayInterfaceSigBoolSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigBool signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigBool(long handleId) = 0;

    /**
    * Use this function to subscribe for sigInt signal changes.
    * @param SimpleArrayInterfaceSigIntSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigInt(SimpleArrayInterfaceSigIntSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigInt signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigInt(long handleId) = 0;

    /**
    * Use this function to subscribe for sigInt32 signal changes.
    * @param SimpleArrayInterfaceSigInt32SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigInt32(SimpleArrayInterfaceSigInt32SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigInt32 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigInt32(long handleId) = 0;

    /**
    * Use this function to subscribe for sigInt64 signal changes.
    * @param SimpleArrayInterfaceSigInt64SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigInt64(SimpleArrayInterfaceSigInt64SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigInt64 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigInt64(long handleId) = 0;

    /**
    * Use this function to subscribe for sigFloat signal changes.
    * @param SimpleArrayInterfaceSigFloatSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigFloat(SimpleArrayInterfaceSigFloatSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigFloat signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigFloat(long handleId) = 0;

    /**
    * Use this function to subscribe for sigFloat32 signal changes.
    * @param SimpleArrayInterfaceSigFloat32SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigFloat32(SimpleArrayInterfaceSigFloat32SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigFloat32 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigFloat32(long handleId) = 0;

    /**
    * Use this function to subscribe for sigFloat64 signal changes.
    * @param SimpleArrayInterfaceSigFloat64SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigFloat64(SimpleArrayInterfaceSigFloat64SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigFloat64 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigFloat64(long handleId) = 0;

    /**
    * Use this function to subscribe for sigString signal changes.
    * @param SimpleArrayInterfaceSigStringSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigString(SimpleArrayInterfaceSigStringSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigString signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigString(long handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when property propBool changes.
    * @param The new value of propBool.
    */
    virtual void publishPropBoolChanged(const std::list<bool>& propBool) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when property propInt changes.
    * @param The new value of propInt.
    */
    virtual void publishPropIntChanged(const std::list<int>& propInt) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when property propInt32 changes.
    * @param The new value of propInt32.
    */
    virtual void publishPropInt32Changed(const std::list<int32_t>& propInt32) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when property propInt64 changes.
    * @param The new value of propInt64.
    */
    virtual void publishPropInt64Changed(const std::list<int64_t>& propInt64) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when property propFloat changes.
    * @param The new value of propFloat.
    */
    virtual void publishPropFloatChanged(const std::list<float>& propFloat) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when property propFloat32 changes.
    * @param The new value of propFloat32.
    */
    virtual void publishPropFloat32Changed(const std::list<float>& propFloat32) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when property propFloat64 changes.
    * @param The new value of propFloat64.
    */
    virtual void publishPropFloat64Changed(const std::list<double>& propFloat64) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when property propString changes.
    * @param The new value of propString.
    */
    virtual void publishPropStringChanged(const std::list<std::string>& propString) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when property propReadOnlyString changes.
    * @param The new value of propReadOnlyString.
    */
    virtual void publishPropReadOnlyStringChanged(const std::string& propReadOnlyString) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when sigBool is emitted.
    * @param paramBool 
    */
    virtual void publishSigBool(const std::list<bool>& paramBool) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when sigInt is emitted.
    * @param paramInt 
    */
    virtual void publishSigInt(const std::list<int>& paramInt) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when sigInt32 is emitted.
    * @param paramInt32 
    */
    virtual void publishSigInt32(const std::list<int32_t>& paramInt32) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when sigInt64 is emitted.
    * @param paramInt64 
    */
    virtual void publishSigInt64(const std::list<int64_t>& paramInt64) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when sigFloat is emitted.
    * @param paramFloat 
    */
    virtual void publishSigFloat(const std::list<float>& paramFloat) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when sigFloat32 is emitted.
    * @param paramFloa32 
    */
    virtual void publishSigFloat32(const std::list<float>& paramFloa32) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when sigFloat64 is emitted.
    * @param paramFloat64 
    */
    virtual void publishSigFloat64(const std::list<double>& paramFloat64) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleArrayInterface implementation when sigString is emitted.
    * @param paramString 
    */
    virtual void publishSigString(const std::list<std::string>& paramString) const = 0;
};


} // namespace TbSimple
} // namespace Test
