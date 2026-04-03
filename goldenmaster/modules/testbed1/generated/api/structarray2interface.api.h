#pragma once

#include <cstdint>
#include <future>
#include "testbed1/generated/api/common.h"
#include "testbed1/generated/api/datastructs.api.h"

namespace Test {
namespace Testbed1 {

class IStructArray2InterfaceSubscriber;
class IStructArray2InterfacePublisher;

/**
*
* IStructArray2Interface provides an interface for
 *  - methods defined for your StructArray2Interface 
 *  - property setters and getters for defined properties
 * The IStructArray2Interface also provides an interface to access a publisher IStructArray2InterfacePublisher, a class used by IStructArray2InterfaceSubscriber clients.
 * The implementation should notify the publisher IStructArray2InterfacePublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also IStructArray2InterfaceSubscriber, IStructArray2InterfacePublisher
 * and the example implementation StructArray2Interface  or the
 */
class TEST_TESTBED1_EXPORT IStructArray2Interface
{
public:
    virtual ~IStructArray2Interface() = default;


    virtual std::list<StructBool> funcBool(const StructBoolWithArray& paramBool) = 0;
    /**
    * Asynchronous version of funcBool(const StructBoolWithArray& paramBool)
    * @return Promise of type std::list<StructBool> which is set once the function has completed
    */
    virtual std::future<std::list<StructBool>> funcBoolAsync(const StructBoolWithArray& paramBool, std::function<void(std::list<StructBool>)> callback = nullptr) = 0;


    virtual std::list<StructInt> funcInt(const StructIntWithArray& paramInt) = 0;
    /**
    * Asynchronous version of funcInt(const StructIntWithArray& paramInt)
    * @return Promise of type std::list<StructInt> which is set once the function has completed
    */
    virtual std::future<std::list<StructInt>> funcIntAsync(const StructIntWithArray& paramInt, std::function<void(std::list<StructInt>)> callback = nullptr) = 0;


    virtual std::list<StructFloat> funcFloat(const StructFloatWithArray& paramFloat) = 0;
    /**
    * Asynchronous version of funcFloat(const StructFloatWithArray& paramFloat)
    * @return Promise of type std::list<StructFloat> which is set once the function has completed
    */
    virtual std::future<std::list<StructFloat>> funcFloatAsync(const StructFloatWithArray& paramFloat, std::function<void(std::list<StructFloat>)> callback = nullptr) = 0;


    virtual std::list<StructString> funcString(const StructStringWithArray& paramString) = 0;
    /**
    * Asynchronous version of funcString(const StructStringWithArray& paramString)
    * @return Promise of type std::list<StructString> which is set once the function has completed
    */
    virtual std::future<std::list<StructString>> funcStringAsync(const StructStringWithArray& paramString, std::function<void(std::list<StructString>)> callback = nullptr) = 0;


    virtual std::list<Enum0Enum> funcEnum(const StructEnumWithArray& paramEnum) = 0;
    /**
    * Asynchronous version of funcEnum(const StructEnumWithArray& paramEnum)
    * @return Promise of type std::list<Enum0Enum> which is set once the function has completed
    */
    virtual std::future<std::list<Enum0Enum>> funcEnumAsync(const StructEnumWithArray& paramEnum, std::function<void(std::list<Enum0Enum>)> callback = nullptr) = 0;

    /**
    * Sets the value of the propBool property.
    */
    virtual void setPropBool(const StructBoolWithArray& propBool) = 0;
    /**
    * Gets the value of the propBool property.
    */
    virtual const StructBoolWithArray& getPropBool() const = 0;

    /**
    * Sets the value of the propInt property.
    */
    virtual void setPropInt(const StructIntWithArray& propInt) = 0;
    /**
    * Gets the value of the propInt property.
    */
    virtual const StructIntWithArray& getPropInt() const = 0;

    /**
    * Sets the value of the propFloat property.
    */
    virtual void setPropFloat(const StructFloatWithArray& propFloat) = 0;
    /**
    * Gets the value of the propFloat property.
    */
    virtual const StructFloatWithArray& getPropFloat() const = 0;

    /**
    * Sets the value of the propString property.
    */
    virtual void setPropString(const StructStringWithArray& propString) = 0;
    /**
    * Gets the value of the propString property.
    */
    virtual const StructStringWithArray& getPropString() const = 0;

    /**
    * Sets the value of the propEnum property.
    */
    virtual void setPropEnum(const StructEnumWithArray& propEnum) = 0;
    /**
    * Gets the value of the propEnum property.
    */
    virtual const StructEnumWithArray& getPropEnum() const = 0;

    /**
    * Access to a publisher, use it to subscribe for StructArray2Interface changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for StructArray2Interface.
    */
    virtual IStructArray2InterfacePublisher& _getPublisher() const = 0;
};


/**
 * The IStructArray2InterfaceSubscriber contains functions to allow informing about signals or property changes of the IStructArray2Interface implementation.
 * The implementation for IStructArray2Interface should provide mechanism for subscription of the IStructArray2InterfaceSubscriber clients.
 * See IStructArray2InterfacePublisher, which provides facilitation for this purpose.
 * The implementation for IStructArray2Interface should call the IStructArray2InterfaceSubscriber interface functions on either signal emit or property change.
 * You can use IStructArray2InterfaceSubscriber class to implement clients of the IStructArray2Interface or the network adapter - see Olink Server and Client example.
 */
class TEST_TESTBED1_EXPORT IStructArray2InterfaceSubscriber
{
public:
    virtual ~IStructArray2InterfaceSubscriber() = default;
    /**
    * Called by the IStructArray2InterfacePublisher when the StructArray2Interface emits sigBool, if subscribed for the sigBool.
    * @param paramBool 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigBool(const StructBoolWithArray& paramBool) = 0;
    /**
    * Called by the IStructArray2InterfacePublisher when the StructArray2Interface emits sigInt, if subscribed for the sigInt.
    * @param paramInt 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigInt(const StructIntWithArray& paramInt) = 0;
    /**
    * Called by the IStructArray2InterfacePublisher when the StructArray2Interface emits sigFloat, if subscribed for the sigFloat.
    * @param paramFloat 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigFloat(const StructFloatWithArray& paramFloat) = 0;
    /**
    * Called by the IStructArray2InterfacePublisher when the StructArray2Interface emits sigString, if subscribed for the sigString.
    * @param paramString 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigString(const StructStringWithArray& paramString) = 0;
    /**
    * Called by the IStructArray2InterfacePublisher when propBool value has changed if subscribed for the propBool change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropBoolChanged(const StructBoolWithArray& propBool) = 0;
    /**
    * Called by the IStructArray2InterfacePublisher when propInt value has changed if subscribed for the propInt change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropIntChanged(const StructIntWithArray& propInt) = 0;
    /**
    * Called by the IStructArray2InterfacePublisher when propFloat value has changed if subscribed for the propFloat change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropFloatChanged(const StructFloatWithArray& propFloat) = 0;
    /**
    * Called by the IStructArray2InterfacePublisher when propString value has changed if subscribed for the propString change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropStringChanged(const StructStringWithArray& propString) = 0;
    /**
    * Called by the IStructArray2InterfacePublisher when propEnum value has changed if subscribed for the propEnum change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropEnumChanged(const StructEnumWithArray& propEnum) = 0;
};

/** Callback for changes of propBool */
using StructArray2InterfacePropBoolPropertyCb = std::function<void(const StructBoolWithArray& propBool)>;
/** Callback for changes of propInt */
using StructArray2InterfacePropIntPropertyCb = std::function<void(const StructIntWithArray& propInt)>;
/** Callback for changes of propFloat */
using StructArray2InterfacePropFloatPropertyCb = std::function<void(const StructFloatWithArray& propFloat)>;
/** Callback for changes of propString */
using StructArray2InterfacePropStringPropertyCb = std::function<void(const StructStringWithArray& propString)>;
/** Callback for changes of propEnum */
using StructArray2InterfacePropEnumPropertyCb = std::function<void(const StructEnumWithArray& propEnum)>;
/** Callback for sigBool signal triggers */
using StructArray2InterfaceSigBoolSignalCb = std::function<void(const StructBoolWithArray& paramBool)> ;
/** Callback for sigInt signal triggers */
using StructArray2InterfaceSigIntSignalCb = std::function<void(const StructIntWithArray& paramInt)> ;
/** Callback for sigFloat signal triggers */
using StructArray2InterfaceSigFloatSignalCb = std::function<void(const StructFloatWithArray& paramFloat)> ;
/** Callback for sigString signal triggers */
using StructArray2InterfaceSigStringSignalCb = std::function<void(const StructStringWithArray& paramString)> ;


/**
 * The IStructArray2InterfacePublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your IStructArray2Interface implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a IStructArray2InterfaceSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IIStructArray2Interface on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TESTBED1_EXPORT IStructArray2InterfacePublisher
{
public:
    virtual ~IStructArray2InterfacePublisher() = default;

    /**
    * Use this function to subscribe for any change of the StructArray2Interface.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param IStructArray2InterfaceSubscriber which is subscribed in this function to any change of the StructArray2Interface.
    */
    virtual void subscribeToAllChanges(IStructArray2InterfaceSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the StructArray2Interface.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param IStructArray2InterfaceSubscriber which subscription for any change of the StructArray2Interface is removed.
    */
    virtual void unsubscribeFromAllChanges(IStructArray2InterfaceSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for propBool value changes.
    * If your subscriber uses subscription with IStructArray2InterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructArray2InterfacePropBoolPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToPropBoolChanged(StructArray2InterfacePropBoolPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propBool property changes.
    * If your subscriber uses subscription with IStructArray2InterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropBoolChanged(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for propInt value changes.
    * If your subscriber uses subscription with IStructArray2InterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructArray2InterfacePropIntPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToPropIntChanged(StructArray2InterfacePropIntPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propInt property changes.
    * If your subscriber uses subscription with IStructArray2InterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropIntChanged(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for propFloat value changes.
    * If your subscriber uses subscription with IStructArray2InterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructArray2InterfacePropFloatPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToPropFloatChanged(StructArray2InterfacePropFloatPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propFloat property changes.
    * If your subscriber uses subscription with IStructArray2InterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropFloatChanged(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for propString value changes.
    * If your subscriber uses subscription with IStructArray2InterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructArray2InterfacePropStringPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToPropStringChanged(StructArray2InterfacePropStringPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propString property changes.
    * If your subscriber uses subscription with IStructArray2InterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropStringChanged(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for propEnum value changes.
    * If your subscriber uses subscription with IStructArray2InterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructArray2InterfacePropEnumPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToPropEnumChanged(StructArray2InterfacePropEnumPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propEnum property changes.
    * If your subscriber uses subscription with IStructArray2InterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropEnumChanged(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for sigBool signal changes.
    * @param StructArray2InterfaceSigBoolSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToSigBool(StructArray2InterfaceSigBoolSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigBool signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigBool(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for sigInt signal changes.
    * @param StructArray2InterfaceSigIntSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToSigInt(StructArray2InterfaceSigIntSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigInt signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigInt(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for sigFloat signal changes.
    * @param StructArray2InterfaceSigFloatSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToSigFloat(StructArray2InterfaceSigFloatSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigFloat signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigFloat(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for sigString signal changes.
    * @param StructArray2InterfaceSigStringSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToSigString(StructArray2InterfaceSigStringSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigString signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigString(uint64_t handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructArray2Interface implementation when property propBool changes.
    * @param The new value of propBool.
    */
    virtual void publishPropBoolChanged(const StructBoolWithArray& propBool) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructArray2Interface implementation when property propInt changes.
    * @param The new value of propInt.
    */
    virtual void publishPropIntChanged(const StructIntWithArray& propInt) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructArray2Interface implementation when property propFloat changes.
    * @param The new value of propFloat.
    */
    virtual void publishPropFloatChanged(const StructFloatWithArray& propFloat) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructArray2Interface implementation when property propString changes.
    * @param The new value of propString.
    */
    virtual void publishPropStringChanged(const StructStringWithArray& propString) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructArray2Interface implementation when property propEnum changes.
    * @param The new value of propEnum.
    */
    virtual void publishPropEnumChanged(const StructEnumWithArray& propEnum) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the StructArray2Interface implementation when sigBool is emitted.
    * @param paramBool 
    */
    virtual void publishSigBool(const StructBoolWithArray& paramBool) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the StructArray2Interface implementation when sigInt is emitted.
    * @param paramInt 
    */
    virtual void publishSigInt(const StructIntWithArray& paramInt) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the StructArray2Interface implementation when sigFloat is emitted.
    * @param paramFloat 
    */
    virtual void publishSigFloat(const StructFloatWithArray& paramFloat) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the StructArray2Interface implementation when sigString is emitted.
    * @param paramString 
    */
    virtual void publishSigString(const StructStringWithArray& paramString) const = 0;
};


} // namespace Testbed1
} // namespace Test
