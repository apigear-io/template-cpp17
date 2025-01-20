#pragma once

#include <future>
#include "testbed1/generated/api/common.h"
#include "testbed1/generated/api/datastructs.api.h"

namespace Test {
namespace Testbed1 {

class IStructArrayInterfaceSubscriber;
class IStructArrayInterfacePublisher;

/**
*
* IStructArrayInterface provides an interface for
 *  - methods defined for your StructArrayInterface 
 *  - property setters and getters for defined properties
 * The IStructArrayInterface also provides an interface to access a publisher IStructArrayInterfacePublisher, a class used by IStructArrayInterfaceSubscriber clients.
 * The implementation should notify the publisher IStructArrayInterfacePublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also IStructArrayInterfaceSubscriber, IStructArrayInterfacePublisher
 * and the example implementation StructArrayInterface  or the
 */
class TEST_TESTBED1_EXPORT IStructArrayInterface
{
public:
    virtual ~IStructArrayInterface() = default;


    virtual StructBool funcBool(const std::list<StructBool>& paramBool) = 0;
    /**
    * Asynchronous version of funcBool(const std::list<StructBool>& paramBool)
    * @return Promise of type StructBool which is set once the function has completed
    */
    virtual std::future<StructBool> funcBoolAsync(const std::list<StructBool>& paramBool, std::function<void(StructBool)> callback = nullptr) = 0;


    virtual StructBool funcInt(const std::list<StructInt>& paramInt) = 0;
    /**
    * Asynchronous version of funcInt(const std::list<StructInt>& paramInt)
    * @return Promise of type StructBool which is set once the function has completed
    */
    virtual std::future<StructBool> funcIntAsync(const std::list<StructInt>& paramInt, std::function<void(StructBool)> callback = nullptr) = 0;


    virtual StructBool funcFloat(const std::list<StructFloat>& paramFloat) = 0;
    /**
    * Asynchronous version of funcFloat(const std::list<StructFloat>& paramFloat)
    * @return Promise of type StructBool which is set once the function has completed
    */
    virtual std::future<StructBool> funcFloatAsync(const std::list<StructFloat>& paramFloat, std::function<void(StructBool)> callback = nullptr) = 0;


    virtual StructBool funcString(const std::list<StructString>& paramString) = 0;
    /**
    * Asynchronous version of funcString(const std::list<StructString>& paramString)
    * @return Promise of type StructBool which is set once the function has completed
    */
    virtual std::future<StructBool> funcStringAsync(const std::list<StructString>& paramString, std::function<void(StructBool)> callback = nullptr) = 0;

    /**
    * Sets the value of the propBool property.
    */
    virtual void setPropBool(const std::list<StructBool>& propBool) = 0;
    /**
    * Gets the value of the propBool property.
    */
    virtual const std::list<StructBool>& getPropBool() const = 0;

    /**
    * Sets the value of the propInt property.
    */
    virtual void setPropInt(const std::list<StructInt>& propInt) = 0;
    /**
    * Gets the value of the propInt property.
    */
    virtual const std::list<StructInt>& getPropInt() const = 0;

    /**
    * Sets the value of the propFloat property.
    */
    virtual void setPropFloat(const std::list<StructFloat>& propFloat) = 0;
    /**
    * Gets the value of the propFloat property.
    */
    virtual const std::list<StructFloat>& getPropFloat() const = 0;

    /**
    * Sets the value of the propString property.
    */
    virtual void setPropString(const std::list<StructString>& propString) = 0;
    /**
    * Gets the value of the propString property.
    */
    virtual const std::list<StructString>& getPropString() const = 0;

    /**
    * Access to a publisher, use it to subscribe for StructArrayInterface changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for StructArrayInterface.
    */
    virtual IStructArrayInterfacePublisher& _getPublisher() const = 0;
};


/**
 * The IStructArrayInterfaceSubscriber contains functions to allow informing about signals or property changes of the IStructArrayInterface implementation.
 * The implementation for IStructArrayInterface should provide mechanism for subscription of the IStructArrayInterfaceSubscriber clients.
 * See IStructArrayInterfacePublisher, which provides facilitation for this purpose.
 * The implementation for IStructArrayInterface should call the IStructArrayInterfaceSubscriber interface functions on either signal emit or property change.
 * You can use IStructArrayInterfaceSubscriber class to implement clients of the IStructArrayInterface or the network adapter - see Olink Server and Client example.
 */
class TEST_TESTBED1_EXPORT IStructArrayInterfaceSubscriber
{
public:
    virtual ~IStructArrayInterfaceSubscriber() = default;
    /**
    * Called by the IStructArrayInterfacePublisher when the StructArrayInterface emits sigBool, if subscribed for the sigBool.
    * @param paramBool 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigBool(const std::list<StructBool>& paramBool) = 0;
    /**
    * Called by the IStructArrayInterfacePublisher when the StructArrayInterface emits sigInt, if subscribed for the sigInt.
    * @param paramInt 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigInt(const std::list<StructInt>& paramInt) = 0;
    /**
    * Called by the IStructArrayInterfacePublisher when the StructArrayInterface emits sigFloat, if subscribed for the sigFloat.
    * @param paramFloat 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigFloat(const std::list<StructFloat>& paramFloat) = 0;
    /**
    * Called by the IStructArrayInterfacePublisher when the StructArrayInterface emits sigString, if subscribed for the sigString.
    * @param paramString 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigString(const std::list<StructString>& paramString) = 0;
    /**
    * Called by the IStructArrayInterfacePublisher when propBool value has changed if subscribed for the propBool change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropBoolChanged(const std::list<StructBool>& propBool) = 0;
    /**
    * Called by the IStructArrayInterfacePublisher when propInt value has changed if subscribed for the propInt change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropIntChanged(const std::list<StructInt>& propInt) = 0;
    /**
    * Called by the IStructArrayInterfacePublisher when propFloat value has changed if subscribed for the propFloat change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropFloatChanged(const std::list<StructFloat>& propFloat) = 0;
    /**
    * Called by the IStructArrayInterfacePublisher when propString value has changed if subscribed for the propString change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropStringChanged(const std::list<StructString>& propString) = 0;
};

/** Callback for changes of propBool */
using StructArrayInterfacePropBoolPropertyCb = std::function<void(const std::list<StructBool>& propBool)>;
/** Callback for changes of propInt */
using StructArrayInterfacePropIntPropertyCb = std::function<void(const std::list<StructInt>& propInt)>;
/** Callback for changes of propFloat */
using StructArrayInterfacePropFloatPropertyCb = std::function<void(const std::list<StructFloat>& propFloat)>;
/** Callback for changes of propString */
using StructArrayInterfacePropStringPropertyCb = std::function<void(const std::list<StructString>& propString)>;
/** Callback for sigBool signal triggers */
using StructArrayInterfaceSigBoolSignalCb = std::function<void(const std::list<StructBool>& paramBool)> ;
/** Callback for sigInt signal triggers */
using StructArrayInterfaceSigIntSignalCb = std::function<void(const std::list<StructInt>& paramInt)> ;
/** Callback for sigFloat signal triggers */
using StructArrayInterfaceSigFloatSignalCb = std::function<void(const std::list<StructFloat>& paramFloat)> ;
/** Callback for sigString signal triggers */
using StructArrayInterfaceSigStringSignalCb = std::function<void(const std::list<StructString>& paramString)> ;


/**
 * The IStructArrayInterfacePublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your IStructArrayInterface implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a IStructArrayInterfaceSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IIStructArrayInterface on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TESTBED1_EXPORT IStructArrayInterfacePublisher
{
public:
    virtual ~IStructArrayInterfacePublisher() = default;

    /**
    * Use this function to subscribe for any change of the StructArrayInterface.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param IStructArrayInterfaceSubscriber which is subscribed in this function to any change of the StructArrayInterface.
    */
    virtual void subscribeToAllChanges(IStructArrayInterfaceSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the StructArrayInterface.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param IStructArrayInterfaceSubscriber which subscription for any change of the StructArrayInterface is removed.
    */
    virtual void unsubscribeFromAllChanges(IStructArrayInterfaceSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for propBool value changes.
    * If your subscriber uses subscription with IStructArrayInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructArrayInterfacePropBoolPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropBoolChanged(StructArrayInterfacePropBoolPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propBool property changes.
    * If your subscriber uses subscription with IStructArrayInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropBoolChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propInt value changes.
    * If your subscriber uses subscription with IStructArrayInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructArrayInterfacePropIntPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropIntChanged(StructArrayInterfacePropIntPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propInt property changes.
    * If your subscriber uses subscription with IStructArrayInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropIntChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propFloat value changes.
    * If your subscriber uses subscription with IStructArrayInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructArrayInterfacePropFloatPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropFloatChanged(StructArrayInterfacePropFloatPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propFloat property changes.
    * If your subscriber uses subscription with IStructArrayInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropFloatChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propString value changes.
    * If your subscriber uses subscription with IStructArrayInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructArrayInterfacePropStringPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropStringChanged(StructArrayInterfacePropStringPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propString property changes.
    * If your subscriber uses subscription with IStructArrayInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropStringChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for sigBool signal changes.
    * @param StructArrayInterfaceSigBoolSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigBool(StructArrayInterfaceSigBoolSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigBool signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigBool(long handleId) = 0;

    /**
    * Use this function to subscribe for sigInt signal changes.
    * @param StructArrayInterfaceSigIntSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigInt(StructArrayInterfaceSigIntSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigInt signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigInt(long handleId) = 0;

    /**
    * Use this function to subscribe for sigFloat signal changes.
    * @param StructArrayInterfaceSigFloatSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigFloat(StructArrayInterfaceSigFloatSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigFloat signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigFloat(long handleId) = 0;

    /**
    * Use this function to subscribe for sigString signal changes.
    * @param StructArrayInterfaceSigStringSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigString(StructArrayInterfaceSigStringSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigString signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigString(long handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructArrayInterface implementation when property propBool changes.
    * @param The new value of propBool.
    */
    virtual void publishPropBoolChanged(const std::list<StructBool>& propBool) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructArrayInterface implementation when property propInt changes.
    * @param The new value of propInt.
    */
    virtual void publishPropIntChanged(const std::list<StructInt>& propInt) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructArrayInterface implementation when property propFloat changes.
    * @param The new value of propFloat.
    */
    virtual void publishPropFloatChanged(const std::list<StructFloat>& propFloat) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructArrayInterface implementation when property propString changes.
    * @param The new value of propString.
    */
    virtual void publishPropStringChanged(const std::list<StructString>& propString) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the StructArrayInterface implementation when sigBool is emitted.
    * @param paramBool 
    */
    virtual void publishSigBool(const std::list<StructBool>& paramBool) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the StructArrayInterface implementation when sigInt is emitted.
    * @param paramInt 
    */
    virtual void publishSigInt(const std::list<StructInt>& paramInt) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the StructArrayInterface implementation when sigFloat is emitted.
    * @param paramFloat 
    */
    virtual void publishSigFloat(const std::list<StructFloat>& paramFloat) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the StructArrayInterface implementation when sigString is emitted.
    * @param paramString 
    */
    virtual void publishSigString(const std::list<StructString>& paramString) const = 0;
};


} // namespace Testbed1
} // namespace Test
