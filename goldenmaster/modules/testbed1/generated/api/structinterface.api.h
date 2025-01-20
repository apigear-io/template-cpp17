#pragma once

#include <future>
#include "testbed1/generated/api/common.h"
#include "testbed1/generated/api/datastructs.api.h"

namespace Test {
namespace Testbed1 {

class IStructInterfaceSubscriber;
class IStructInterfacePublisher;

/**
*
* IStructInterface provides an interface for
 *  - methods defined for your StructInterface 
 *  - property setters and getters for defined properties
 * The IStructInterface also provides an interface to access a publisher IStructInterfacePublisher, a class used by IStructInterfaceSubscriber clients.
 * The implementation should notify the publisher IStructInterfacePublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also IStructInterfaceSubscriber, IStructInterfacePublisher
 * and the example implementation StructInterface  or the
 */
class TEST_TESTBED1_EXPORT IStructInterface
{
public:
    virtual ~IStructInterface() = default;


    virtual StructBool funcBool(const StructBool& paramBool) = 0;
    /**
    * Asynchronous version of funcBool(const StructBool& paramBool)
    * @return Promise of type StructBool which is set once the function has completed
    */
    virtual std::future<StructBool> funcBoolAsync(const StructBool& paramBool, std::function<void(StructBool)> callback = nullptr) = 0;


    virtual StructInt funcInt(const StructInt& paramInt) = 0;
    /**
    * Asynchronous version of funcInt(const StructInt& paramInt)
    * @return Promise of type StructInt which is set once the function has completed
    */
    virtual std::future<StructInt> funcIntAsync(const StructInt& paramInt, std::function<void(StructInt)> callback = nullptr) = 0;


    virtual StructFloat funcFloat(const StructFloat& paramFloat) = 0;
    /**
    * Asynchronous version of funcFloat(const StructFloat& paramFloat)
    * @return Promise of type StructFloat which is set once the function has completed
    */
    virtual std::future<StructFloat> funcFloatAsync(const StructFloat& paramFloat, std::function<void(StructFloat)> callback = nullptr) = 0;


    virtual StructString funcString(const StructString& paramString) = 0;
    /**
    * Asynchronous version of funcString(const StructString& paramString)
    * @return Promise of type StructString which is set once the function has completed
    */
    virtual std::future<StructString> funcStringAsync(const StructString& paramString, std::function<void(StructString)> callback = nullptr) = 0;

    /**
    * Sets the value of the propBool property.
    */
    virtual void setPropBool(const StructBool& propBool) = 0;
    /**
    * Gets the value of the propBool property.
    */
    virtual const StructBool& getPropBool() const = 0;

    /**
    * Sets the value of the propInt property.
    */
    virtual void setPropInt(const StructInt& propInt) = 0;
    /**
    * Gets the value of the propInt property.
    */
    virtual const StructInt& getPropInt() const = 0;

    /**
    * Sets the value of the propFloat property.
    */
    virtual void setPropFloat(const StructFloat& propFloat) = 0;
    /**
    * Gets the value of the propFloat property.
    */
    virtual const StructFloat& getPropFloat() const = 0;

    /**
    * Sets the value of the propString property.
    */
    virtual void setPropString(const StructString& propString) = 0;
    /**
    * Gets the value of the propString property.
    */
    virtual const StructString& getPropString() const = 0;

    /**
    * Access to a publisher, use it to subscribe for StructInterface changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for StructInterface.
    */
    virtual IStructInterfacePublisher& _getPublisher() const = 0;
};


/**
 * The IStructInterfaceSubscriber contains functions to allow informing about signals or property changes of the IStructInterface implementation.
 * The implementation for IStructInterface should provide mechanism for subscription of the IStructInterfaceSubscriber clients.
 * See IStructInterfacePublisher, which provides facilitation for this purpose.
 * The implementation for IStructInterface should call the IStructInterfaceSubscriber interface functions on either signal emit or property change.
 * You can use IStructInterfaceSubscriber class to implement clients of the IStructInterface or the network adapter - see Olink Server and Client example.
 */
class TEST_TESTBED1_EXPORT IStructInterfaceSubscriber
{
public:
    virtual ~IStructInterfaceSubscriber() = default;
    /**
    * Called by the IStructInterfacePublisher when the StructInterface emits sigBool, if subscribed for the sigBool.
    * @param paramBool 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigBool(const StructBool& paramBool) = 0;
    /**
    * Called by the IStructInterfacePublisher when the StructInterface emits sigInt, if subscribed for the sigInt.
    * @param paramInt 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigInt(const StructInt& paramInt) = 0;
    /**
    * Called by the IStructInterfacePublisher when the StructInterface emits sigFloat, if subscribed for the sigFloat.
    * @param paramFloat 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigFloat(const StructFloat& paramFloat) = 0;
    /**
    * Called by the IStructInterfacePublisher when the StructInterface emits sigString, if subscribed for the sigString.
    * @param paramString 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigString(const StructString& paramString) = 0;
    /**
    * Called by the IStructInterfacePublisher when propBool value has changed if subscribed for the propBool change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropBoolChanged(const StructBool& propBool) = 0;
    /**
    * Called by the IStructInterfacePublisher when propInt value has changed if subscribed for the propInt change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropIntChanged(const StructInt& propInt) = 0;
    /**
    * Called by the IStructInterfacePublisher when propFloat value has changed if subscribed for the propFloat change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropFloatChanged(const StructFloat& propFloat) = 0;
    /**
    * Called by the IStructInterfacePublisher when propString value has changed if subscribed for the propString change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropStringChanged(const StructString& propString) = 0;
};

/** Callback for changes of propBool */
using StructInterfacePropBoolPropertyCb = std::function<void(const StructBool& propBool)>;
/** Callback for changes of propInt */
using StructInterfacePropIntPropertyCb = std::function<void(const StructInt& propInt)>;
/** Callback for changes of propFloat */
using StructInterfacePropFloatPropertyCb = std::function<void(const StructFloat& propFloat)>;
/** Callback for changes of propString */
using StructInterfacePropStringPropertyCb = std::function<void(const StructString& propString)>;
/** Callback for sigBool signal triggers */
using StructInterfaceSigBoolSignalCb = std::function<void(const StructBool& paramBool)> ;
/** Callback for sigInt signal triggers */
using StructInterfaceSigIntSignalCb = std::function<void(const StructInt& paramInt)> ;
/** Callback for sigFloat signal triggers */
using StructInterfaceSigFloatSignalCb = std::function<void(const StructFloat& paramFloat)> ;
/** Callback for sigString signal triggers */
using StructInterfaceSigStringSignalCb = std::function<void(const StructString& paramString)> ;


/**
 * The IStructInterfacePublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your IStructInterface implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a IStructInterfaceSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IIStructInterface on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TESTBED1_EXPORT IStructInterfacePublisher
{
public:
    virtual ~IStructInterfacePublisher() = default;

    /**
    * Use this function to subscribe for any change of the StructInterface.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param IStructInterfaceSubscriber which is subscribed in this function to any change of the StructInterface.
    */
    virtual void subscribeToAllChanges(IStructInterfaceSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the StructInterface.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param IStructInterfaceSubscriber which subscription for any change of the StructInterface is removed.
    */
    virtual void unsubscribeFromAllChanges(IStructInterfaceSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for propBool value changes.
    * If your subscriber uses subscription with IStructInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructInterfacePropBoolPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropBoolChanged(StructInterfacePropBoolPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propBool property changes.
    * If your subscriber uses subscription with IStructInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropBoolChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propInt value changes.
    * If your subscriber uses subscription with IStructInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructInterfacePropIntPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropIntChanged(StructInterfacePropIntPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propInt property changes.
    * If your subscriber uses subscription with IStructInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropIntChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propFloat value changes.
    * If your subscriber uses subscription with IStructInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructInterfacePropFloatPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropFloatChanged(StructInterfacePropFloatPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propFloat property changes.
    * If your subscriber uses subscription with IStructInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropFloatChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propString value changes.
    * If your subscriber uses subscription with IStructInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructInterfacePropStringPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropStringChanged(StructInterfacePropStringPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propString property changes.
    * If your subscriber uses subscription with IStructInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropStringChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for sigBool signal changes.
    * @param StructInterfaceSigBoolSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigBool(StructInterfaceSigBoolSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigBool signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigBool(long handleId) = 0;

    /**
    * Use this function to subscribe for sigInt signal changes.
    * @param StructInterfaceSigIntSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigInt(StructInterfaceSigIntSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigInt signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigInt(long handleId) = 0;

    /**
    * Use this function to subscribe for sigFloat signal changes.
    * @param StructInterfaceSigFloatSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigFloat(StructInterfaceSigFloatSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigFloat signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigFloat(long handleId) = 0;

    /**
    * Use this function to subscribe for sigString signal changes.
    * @param StructInterfaceSigStringSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigString(StructInterfaceSigStringSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigString signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigString(long handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructInterface implementation when property propBool changes.
    * @param The new value of propBool.
    */
    virtual void publishPropBoolChanged(const StructBool& propBool) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructInterface implementation when property propInt changes.
    * @param The new value of propInt.
    */
    virtual void publishPropIntChanged(const StructInt& propInt) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructInterface implementation when property propFloat changes.
    * @param The new value of propFloat.
    */
    virtual void publishPropFloatChanged(const StructFloat& propFloat) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructInterface implementation when property propString changes.
    * @param The new value of propString.
    */
    virtual void publishPropStringChanged(const StructString& propString) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the StructInterface implementation when sigBool is emitted.
    * @param paramBool 
    */
    virtual void publishSigBool(const StructBool& paramBool) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the StructInterface implementation when sigInt is emitted.
    * @param paramInt 
    */
    virtual void publishSigInt(const StructInt& paramInt) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the StructInterface implementation when sigFloat is emitted.
    * @param paramFloat 
    */
    virtual void publishSigFloat(const StructFloat& paramFloat) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the StructInterface implementation when sigString is emitted.
    * @param paramString 
    */
    virtual void publishSigString(const StructString& paramString) const = 0;
};


} // namespace Testbed1
} // namespace Test
