#pragma once

#include <future>
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/datastructs.api.h"

namespace Test {
namespace TbSimple {

class ISimpleInterfaceSubscriber;
class ISimpleInterfacePublisher;

/**
*
* ISimpleInterface provides an interface for
 *  - methods defined for your SimpleInterface 
 *  - property setters and getters for defined properties
 * The ISimpleInterface also provides an interface to access a publisher ISimpleInterfacePublisher, a class used by ISimpleInterfaceSubscriber clients.
 * The implementation should notify the publisher ISimpleInterfacePublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also ISimpleInterfaceSubscriber, ISimpleInterfacePublisher
 * and the example implementation SimpleInterface  or the
 */
class TEST_TB_SIMPLE_EXPORT ISimpleInterface
{
public:
    virtual ~ISimpleInterface() = default;


    virtual void funcNoReturnValue(bool paramBool) = 0;
    /**
    * Asynchronous version of funcNoReturnValue(bool paramBool)
    * @return Promise of type void which is set once the function has completed
    */
    virtual std::future<void> funcNoReturnValueAsync(bool paramBool) = 0;


    virtual bool funcBool(bool paramBool) = 0;
    /**
    * Asynchronous version of funcBool(bool paramBool)
    * @return Promise of type bool which is set once the function has completed
    */
    virtual std::future<bool> funcBoolAsync(bool paramBool) = 0;


    virtual int funcInt(int paramInt) = 0;
    /**
    * Asynchronous version of funcInt(int paramInt)
    * @return Promise of type int which is set once the function has completed
    */
    virtual std::future<int> funcIntAsync(int paramInt) = 0;


    virtual int32_t funcInt32(int32_t paramInt32) = 0;
    /**
    * Asynchronous version of funcInt32(int32_t paramInt32)
    * @return Promise of type int32_t which is set once the function has completed
    */
    virtual std::future<int32_t> funcInt32Async(int32_t paramInt32) = 0;


    virtual int64_t funcInt64(int64_t paramInt64) = 0;
    /**
    * Asynchronous version of funcInt64(int64_t paramInt64)
    * @return Promise of type int64_t which is set once the function has completed
    */
    virtual std::future<int64_t> funcInt64Async(int64_t paramInt64) = 0;


    virtual float funcFloat(float paramFloat) = 0;
    /**
    * Asynchronous version of funcFloat(float paramFloat)
    * @return Promise of type float which is set once the function has completed
    */
    virtual std::future<float> funcFloatAsync(float paramFloat) = 0;


    virtual float funcFloat32(float paramFloat32) = 0;
    /**
    * Asynchronous version of funcFloat32(float paramFloat32)
    * @return Promise of type float which is set once the function has completed
    */
    virtual std::future<float> funcFloat32Async(float paramFloat32) = 0;


    virtual double funcFloat64(double paramFloat) = 0;
    /**
    * Asynchronous version of funcFloat64(double paramFloat)
    * @return Promise of type double which is set once the function has completed
    */
    virtual std::future<double> funcFloat64Async(double paramFloat) = 0;


    virtual std::string funcString(const std::string& paramString) = 0;
    /**
    * Asynchronous version of funcString(const std::string& paramString)
    * @return Promise of type std::string which is set once the function has completed
    */
    virtual std::future<std::string> funcStringAsync(const std::string& paramString) = 0;

    /**
    * Sets the value of the propBool property.
    */
    virtual void setPropBool(bool propBool) = 0;
    /**
    * Gets the value of the propBool property.
    */
    virtual bool getPropBool() const = 0;

    /**
    * Sets the value of the propInt property.
    */
    virtual void setPropInt(int propInt) = 0;
    /**
    * Gets the value of the propInt property.
    */
    virtual int getPropInt() const = 0;

    /**
    * Sets the value of the propInt32 property.
    */
    virtual void setPropInt32(int32_t propInt32) = 0;
    /**
    * Gets the value of the propInt32 property.
    */
    virtual int32_t getPropInt32() const = 0;

    /**
    * Sets the value of the propInt64 property.
    */
    virtual void setPropInt64(int64_t propInt64) = 0;
    /**
    * Gets the value of the propInt64 property.
    */
    virtual int64_t getPropInt64() const = 0;

    /**
    * Sets the value of the propFloat property.
    */
    virtual void setPropFloat(float propFloat) = 0;
    /**
    * Gets the value of the propFloat property.
    */
    virtual float getPropFloat() const = 0;

    /**
    * Sets the value of the propFloat32 property.
    */
    virtual void setPropFloat32(float propFloat32) = 0;
    /**
    * Gets the value of the propFloat32 property.
    */
    virtual float getPropFloat32() const = 0;

    /**
    * Sets the value of the propFloat64 property.
    */
    virtual void setPropFloat64(double propFloat64) = 0;
    /**
    * Gets the value of the propFloat64 property.
    */
    virtual double getPropFloat64() const = 0;

    /**
    * Sets the value of the propString property.
    */
    virtual void setPropString(const std::string& propString) = 0;
    /**
    * Gets the value of the propString property.
    */
    virtual const std::string& getPropString() const = 0;

    /**
    * Access to a publisher, use it to subscribe for SimpleInterface changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for SimpleInterface.
    */
    virtual ISimpleInterfacePublisher& _getPublisher() const = 0;
};


/**
 * The ISimpleInterfaceSubscriber contains functions to allow informing about signals or property changes of the ISimpleInterface implementation.
 * The implementation for ISimpleInterface should provide mechanism for subscription of the ISimpleInterfaceSubscriber clients.
 * See ISimpleInterfacePublisher, which provides facilitation for this purpose.
 * The implementation for ISimpleInterface should call the ISimpleInterfaceSubscriber interface functions on either signal emit or property change.
 * You can use ISimpleInterfaceSubscriber class to implement clients of the ISimpleInterface or the network adapter - see Olink Server and Client example.
 */
class TEST_TB_SIMPLE_EXPORT ISimpleInterfaceSubscriber
{
public:
    virtual ~ISimpleInterfaceSubscriber() = default;
    /**
    * Called by the ISimpleInterfacePublisher when the SimpleInterface emits sigBool, if subscribed for the sigBool.
    * @param paramBool 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigBool(bool paramBool) = 0;
    /**
    * Called by the ISimpleInterfacePublisher when the SimpleInterface emits sigInt, if subscribed for the sigInt.
    * @param paramInt 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigInt(int paramInt) = 0;
    /**
    * Called by the ISimpleInterfacePublisher when the SimpleInterface emits sigInt32, if subscribed for the sigInt32.
    * @param paramInt32 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigInt32(int32_t paramInt32) = 0;
    /**
    * Called by the ISimpleInterfacePublisher when the SimpleInterface emits sigInt64, if subscribed for the sigInt64.
    * @param paramInt64 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigInt64(int64_t paramInt64) = 0;
    /**
    * Called by the ISimpleInterfacePublisher when the SimpleInterface emits sigFloat, if subscribed for the sigFloat.
    * @param paramFloat 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigFloat(float paramFloat) = 0;
    /**
    * Called by the ISimpleInterfacePublisher when the SimpleInterface emits sigFloat32, if subscribed for the sigFloat32.
    * @param paramFloat32 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigFloat32(float paramFloat32) = 0;
    /**
    * Called by the ISimpleInterfacePublisher when the SimpleInterface emits sigFloat64, if subscribed for the sigFloat64.
    * @param paramFloat64 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigFloat64(double paramFloat64) = 0;
    /**
    * Called by the ISimpleInterfacePublisher when the SimpleInterface emits sigString, if subscribed for the sigString.
    * @param paramString 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigString(const std::string& paramString) = 0;
    /**
    * Called by the ISimpleInterfacePublisher when propBool value has changed if subscribed for the propBool change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropBoolChanged(bool propBool) = 0;
    /**
    * Called by the ISimpleInterfacePublisher when propInt value has changed if subscribed for the propInt change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropIntChanged(int propInt) = 0;
    /**
    * Called by the ISimpleInterfacePublisher when propInt32 value has changed if subscribed for the propInt32 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropInt32Changed(int32_t propInt32) = 0;
    /**
    * Called by the ISimpleInterfacePublisher when propInt64 value has changed if subscribed for the propInt64 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropInt64Changed(int64_t propInt64) = 0;
    /**
    * Called by the ISimpleInterfacePublisher when propFloat value has changed if subscribed for the propFloat change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropFloatChanged(float propFloat) = 0;
    /**
    * Called by the ISimpleInterfacePublisher when propFloat32 value has changed if subscribed for the propFloat32 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropFloat32Changed(float propFloat32) = 0;
    /**
    * Called by the ISimpleInterfacePublisher when propFloat64 value has changed if subscribed for the propFloat64 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropFloat64Changed(double propFloat64) = 0;
    /**
    * Called by the ISimpleInterfacePublisher when propString value has changed if subscribed for the propString change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropStringChanged(const std::string& propString) = 0;
};

/** Callback for changes of propBool */
using SimpleInterfacePropBoolPropertyCb = std::function<void(bool propBool)>;
/** Callback for changes of propInt */
using SimpleInterfacePropIntPropertyCb = std::function<void(int propInt)>;
/** Callback for changes of propInt32 */
using SimpleInterfacePropInt32PropertyCb = std::function<void(int32_t propInt32)>;
/** Callback for changes of propInt64 */
using SimpleInterfacePropInt64PropertyCb = std::function<void(int64_t propInt64)>;
/** Callback for changes of propFloat */
using SimpleInterfacePropFloatPropertyCb = std::function<void(float propFloat)>;
/** Callback for changes of propFloat32 */
using SimpleInterfacePropFloat32PropertyCb = std::function<void(float propFloat32)>;
/** Callback for changes of propFloat64 */
using SimpleInterfacePropFloat64PropertyCb = std::function<void(double propFloat64)>;
/** Callback for changes of propString */
using SimpleInterfacePropStringPropertyCb = std::function<void(const std::string& propString)>;
/** Callback for sigBool signal triggers */
using SimpleInterfaceSigBoolSignalCb = std::function<void(bool paramBool)> ;
/** Callback for sigInt signal triggers */
using SimpleInterfaceSigIntSignalCb = std::function<void(int paramInt)> ;
/** Callback for sigInt32 signal triggers */
using SimpleInterfaceSigInt32SignalCb = std::function<void(int32_t paramInt32)> ;
/** Callback for sigInt64 signal triggers */
using SimpleInterfaceSigInt64SignalCb = std::function<void(int64_t paramInt64)> ;
/** Callback for sigFloat signal triggers */
using SimpleInterfaceSigFloatSignalCb = std::function<void(float paramFloat)> ;
/** Callback for sigFloat32 signal triggers */
using SimpleInterfaceSigFloat32SignalCb = std::function<void(float paramFloat32)> ;
/** Callback for sigFloat64 signal triggers */
using SimpleInterfaceSigFloat64SignalCb = std::function<void(double paramFloat64)> ;
/** Callback for sigString signal triggers */
using SimpleInterfaceSigStringSignalCb = std::function<void(const std::string& paramString)> ;


/**
 * The ISimpleInterfacePublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your ISimpleInterface implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a ISimpleInterfaceSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IISimpleInterface on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TB_SIMPLE_EXPORT ISimpleInterfacePublisher
{
public:
    virtual ~ISimpleInterfacePublisher() = default;

    /**
    * Use this function to subscribe for any change of the SimpleInterface.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param ISimpleInterfaceSubscriber which is subscribed in this function to any change of the SimpleInterface.
    */
    virtual void subscribeToAllChanges(ISimpleInterfaceSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the SimpleInterface.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param ISimpleInterfaceSubscriber which subscription for any change of the SimpleInterface is removed.
    */
    virtual void unsubscribeFromAllChanges(ISimpleInterfaceSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for propBool value changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleInterfacePropBoolPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropBoolChanged(SimpleInterfacePropBoolPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propBool property changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropBoolChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propInt value changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleInterfacePropIntPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropIntChanged(SimpleInterfacePropIntPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propInt property changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropIntChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propInt32 value changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleInterfacePropInt32PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropInt32Changed(SimpleInterfacePropInt32PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propInt32 property changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropInt32Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for propInt64 value changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleInterfacePropInt64PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropInt64Changed(SimpleInterfacePropInt64PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propInt64 property changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropInt64Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for propFloat value changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleInterfacePropFloatPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropFloatChanged(SimpleInterfacePropFloatPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propFloat property changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropFloatChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propFloat32 value changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleInterfacePropFloat32PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropFloat32Changed(SimpleInterfacePropFloat32PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propFloat32 property changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropFloat32Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for propFloat64 value changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleInterfacePropFloat64PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropFloat64Changed(SimpleInterfacePropFloat64PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propFloat64 property changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropFloat64Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for propString value changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SimpleInterfacePropStringPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropStringChanged(SimpleInterfacePropStringPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propString property changes.
    * If your subscriber uses subscription with ISimpleInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropStringChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for sigBool signal changes.
    * @param SimpleInterfaceSigBoolSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigBool(SimpleInterfaceSigBoolSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigBool signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigBool(long handleId) = 0;

    /**
    * Use this function to subscribe for sigInt signal changes.
    * @param SimpleInterfaceSigIntSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigInt(SimpleInterfaceSigIntSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigInt signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigInt(long handleId) = 0;

    /**
    * Use this function to subscribe for sigInt32 signal changes.
    * @param SimpleInterfaceSigInt32SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigInt32(SimpleInterfaceSigInt32SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigInt32 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigInt32(long handleId) = 0;

    /**
    * Use this function to subscribe for sigInt64 signal changes.
    * @param SimpleInterfaceSigInt64SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigInt64(SimpleInterfaceSigInt64SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigInt64 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigInt64(long handleId) = 0;

    /**
    * Use this function to subscribe for sigFloat signal changes.
    * @param SimpleInterfaceSigFloatSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigFloat(SimpleInterfaceSigFloatSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigFloat signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigFloat(long handleId) = 0;

    /**
    * Use this function to subscribe for sigFloat32 signal changes.
    * @param SimpleInterfaceSigFloat32SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigFloat32(SimpleInterfaceSigFloat32SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigFloat32 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigFloat32(long handleId) = 0;

    /**
    * Use this function to subscribe for sigFloat64 signal changes.
    * @param SimpleInterfaceSigFloat64SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigFloat64(SimpleInterfaceSigFloat64SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigFloat64 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigFloat64(long handleId) = 0;

    /**
    * Use this function to subscribe for sigString signal changes.
    * @param SimpleInterfaceSigStringSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigString(SimpleInterfaceSigStringSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigString signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigString(long handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when property propBool changes.
    * @param The new value of propBool.
    */
    virtual void publishPropBoolChanged(bool propBool) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when property propInt changes.
    * @param The new value of propInt.
    */
    virtual void publishPropIntChanged(int propInt) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when property propInt32 changes.
    * @param The new value of propInt32.
    */
    virtual void publishPropInt32Changed(int32_t propInt32) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when property propInt64 changes.
    * @param The new value of propInt64.
    */
    virtual void publishPropInt64Changed(int64_t propInt64) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when property propFloat changes.
    * @param The new value of propFloat.
    */
    virtual void publishPropFloatChanged(float propFloat) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when property propFloat32 changes.
    * @param The new value of propFloat32.
    */
    virtual void publishPropFloat32Changed(float propFloat32) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when property propFloat64 changes.
    * @param The new value of propFloat64.
    */
    virtual void publishPropFloat64Changed(double propFloat64) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when property propString changes.
    * @param The new value of propString.
    */
    virtual void publishPropStringChanged(const std::string& propString) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when sigBool is emitted.
    * @param paramBool 
    */
    virtual void publishSigBool(bool paramBool) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when sigInt is emitted.
    * @param paramInt 
    */
    virtual void publishSigInt(int paramInt) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when sigInt32 is emitted.
    * @param paramInt32 
    */
    virtual void publishSigInt32(int32_t paramInt32) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when sigInt64 is emitted.
    * @param paramInt64 
    */
    virtual void publishSigInt64(int64_t paramInt64) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when sigFloat is emitted.
    * @param paramFloat 
    */
    virtual void publishSigFloat(float paramFloat) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when sigFloat32 is emitted.
    * @param paramFloat32 
    */
    virtual void publishSigFloat32(float paramFloat32) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when sigFloat64 is emitted.
    * @param paramFloat64 
    */
    virtual void publishSigFloat64(double paramFloat64) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SimpleInterface implementation when sigString is emitted.
    * @param paramString 
    */
    virtual void publishSigString(const std::string& paramString) const = 0;
};


} // namespace TbSimple
} // namespace Test
