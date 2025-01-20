#pragma once

#include <future>
#include "tb_enum/generated/api/common.h"
#include "tb_enum/generated/api/datastructs.api.h"

namespace Test {
namespace TbEnum {

class IEnumInterfaceSubscriber;
class IEnumInterfacePublisher;

/**
*
* IEnumInterface provides an interface for
 *  - methods defined for your EnumInterface 
 *  - property setters and getters for defined properties
 * The IEnumInterface also provides an interface to access a publisher IEnumInterfacePublisher, a class used by IEnumInterfaceSubscriber clients.
 * The implementation should notify the publisher IEnumInterfacePublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also IEnumInterfaceSubscriber, IEnumInterfacePublisher
 * and the example implementation EnumInterface  or the
 */
class TEST_TB_ENUM_EXPORT IEnumInterface
{
public:
    virtual ~IEnumInterface() = default;


    virtual Enum0Enum func0(Enum0Enum param0) = 0;
    /**
    * Asynchronous version of func0(Enum0Enum param0)
    * @return Promise of type Enum0Enum which is set once the function has completed
    */
    virtual std::future<Enum0Enum> func0Async(Enum0Enum param0, std::function<void(Enum0Enum)> callback = nullptr) = 0;


    virtual Enum1Enum func1(Enum1Enum param1) = 0;
    /**
    * Asynchronous version of func1(Enum1Enum param1)
    * @return Promise of type Enum1Enum which is set once the function has completed
    */
    virtual std::future<Enum1Enum> func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback = nullptr) = 0;


    virtual Enum2Enum func2(Enum2Enum param2) = 0;
    /**
    * Asynchronous version of func2(Enum2Enum param2)
    * @return Promise of type Enum2Enum which is set once the function has completed
    */
    virtual std::future<Enum2Enum> func2Async(Enum2Enum param2, std::function<void(Enum2Enum)> callback = nullptr) = 0;


    virtual Enum3Enum func3(Enum3Enum param3) = 0;
    /**
    * Asynchronous version of func3(Enum3Enum param3)
    * @return Promise of type Enum3Enum which is set once the function has completed
    */
    virtual std::future<Enum3Enum> func3Async(Enum3Enum param3, std::function<void(Enum3Enum)> callback = nullptr) = 0;

    /**
    * Sets the value of the prop0 property.
    */
    virtual void setProp0(Enum0Enum prop0) = 0;
    /**
    * Gets the value of the prop0 property.
    */
    virtual Enum0Enum getProp0() const = 0;

    /**
    * Sets the value of the prop1 property.
    */
    virtual void setProp1(Enum1Enum prop1) = 0;
    /**
    * Gets the value of the prop1 property.
    */
    virtual Enum1Enum getProp1() const = 0;

    /**
    * Sets the value of the prop2 property.
    */
    virtual void setProp2(Enum2Enum prop2) = 0;
    /**
    * Gets the value of the prop2 property.
    */
    virtual Enum2Enum getProp2() const = 0;

    /**
    * Sets the value of the prop3 property.
    */
    virtual void setProp3(Enum3Enum prop3) = 0;
    /**
    * Gets the value of the prop3 property.
    */
    virtual Enum3Enum getProp3() const = 0;

    /**
    * Access to a publisher, use it to subscribe for EnumInterface changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for EnumInterface.
    */
    virtual IEnumInterfacePublisher& _getPublisher() const = 0;
};


/**
 * The IEnumInterfaceSubscriber contains functions to allow informing about signals or property changes of the IEnumInterface implementation.
 * The implementation for IEnumInterface should provide mechanism for subscription of the IEnumInterfaceSubscriber clients.
 * See IEnumInterfacePublisher, which provides facilitation for this purpose.
 * The implementation for IEnumInterface should call the IEnumInterfaceSubscriber interface functions on either signal emit or property change.
 * You can use IEnumInterfaceSubscriber class to implement clients of the IEnumInterface or the network adapter - see Olink Server and Client example.
 */
class TEST_TB_ENUM_EXPORT IEnumInterfaceSubscriber
{
public:
    virtual ~IEnumInterfaceSubscriber() = default;
    /**
    * Called by the IEnumInterfacePublisher when the EnumInterface emits sig0, if subscribed for the sig0.
    * @param param0 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSig0(Enum0Enum param0) = 0;
    /**
    * Called by the IEnumInterfacePublisher when the EnumInterface emits sig1, if subscribed for the sig1.
    * @param param1 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSig1(Enum1Enum param1) = 0;
    /**
    * Called by the IEnumInterfacePublisher when the EnumInterface emits sig2, if subscribed for the sig2.
    * @param param2 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSig2(Enum2Enum param2) = 0;
    /**
    * Called by the IEnumInterfacePublisher when the EnumInterface emits sig3, if subscribed for the sig3.
    * @param param3 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSig3(Enum3Enum param3) = 0;
    /**
    * Called by the IEnumInterfacePublisher when prop0 value has changed if subscribed for the prop0 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onProp0Changed(Enum0Enum prop0) = 0;
    /**
    * Called by the IEnumInterfacePublisher when prop1 value has changed if subscribed for the prop1 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onProp1Changed(Enum1Enum prop1) = 0;
    /**
    * Called by the IEnumInterfacePublisher when prop2 value has changed if subscribed for the prop2 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onProp2Changed(Enum2Enum prop2) = 0;
    /**
    * Called by the IEnumInterfacePublisher when prop3 value has changed if subscribed for the prop3 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onProp3Changed(Enum3Enum prop3) = 0;
};

/** Callback for changes of prop0 */
using EnumInterfaceProp0PropertyCb = std::function<void(Enum0Enum prop0)>;
/** Callback for changes of prop1 */
using EnumInterfaceProp1PropertyCb = std::function<void(Enum1Enum prop1)>;
/** Callback for changes of prop2 */
using EnumInterfaceProp2PropertyCb = std::function<void(Enum2Enum prop2)>;
/** Callback for changes of prop3 */
using EnumInterfaceProp3PropertyCb = std::function<void(Enum3Enum prop3)>;
/** Callback for sig0 signal triggers */
using EnumInterfaceSig0SignalCb = std::function<void(Enum0Enum param0)> ;
/** Callback for sig1 signal triggers */
using EnumInterfaceSig1SignalCb = std::function<void(Enum1Enum param1)> ;
/** Callback for sig2 signal triggers */
using EnumInterfaceSig2SignalCb = std::function<void(Enum2Enum param2)> ;
/** Callback for sig3 signal triggers */
using EnumInterfaceSig3SignalCb = std::function<void(Enum3Enum param3)> ;


/**
 * The IEnumInterfacePublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your IEnumInterface implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a IEnumInterfaceSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IIEnumInterface on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TB_ENUM_EXPORT IEnumInterfacePublisher
{
public:
    virtual ~IEnumInterfacePublisher() = default;

    /**
    * Use this function to subscribe for any change of the EnumInterface.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param IEnumInterfaceSubscriber which is subscribed in this function to any change of the EnumInterface.
    */
    virtual void subscribeToAllChanges(IEnumInterfaceSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the EnumInterface.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param IEnumInterfaceSubscriber which subscription for any change of the EnumInterface is removed.
    */
    virtual void unsubscribeFromAllChanges(IEnumInterfaceSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for prop0 value changes.
    * If your subscriber uses subscription with IEnumInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param EnumInterfaceProp0PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToProp0Changed(EnumInterfaceProp0PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from prop0 property changes.
    * If your subscriber uses subscription with IEnumInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromProp0Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for prop1 value changes.
    * If your subscriber uses subscription with IEnumInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param EnumInterfaceProp1PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToProp1Changed(EnumInterfaceProp1PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from prop1 property changes.
    * If your subscriber uses subscription with IEnumInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromProp1Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for prop2 value changes.
    * If your subscriber uses subscription with IEnumInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param EnumInterfaceProp2PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToProp2Changed(EnumInterfaceProp2PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from prop2 property changes.
    * If your subscriber uses subscription with IEnumInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromProp2Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for prop3 value changes.
    * If your subscriber uses subscription with IEnumInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param EnumInterfaceProp3PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToProp3Changed(EnumInterfaceProp3PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from prop3 property changes.
    * If your subscriber uses subscription with IEnumInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromProp3Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for sig0 signal changes.
    * @param EnumInterfaceSig0SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSig0(EnumInterfaceSig0SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sig0 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSig0(long handleId) = 0;

    /**
    * Use this function to subscribe for sig1 signal changes.
    * @param EnumInterfaceSig1SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSig1(EnumInterfaceSig1SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sig1 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSig1(long handleId) = 0;

    /**
    * Use this function to subscribe for sig2 signal changes.
    * @param EnumInterfaceSig2SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSig2(EnumInterfaceSig2SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sig2 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSig2(long handleId) = 0;

    /**
    * Use this function to subscribe for sig3 signal changes.
    * @param EnumInterfaceSig3SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSig3(EnumInterfaceSig3SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sig3 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSig3(long handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the EnumInterface implementation when property prop0 changes.
    * @param The new value of prop0.
    */
    virtual void publishProp0Changed(Enum0Enum prop0) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the EnumInterface implementation when property prop1 changes.
    * @param The new value of prop1.
    */
    virtual void publishProp1Changed(Enum1Enum prop1) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the EnumInterface implementation when property prop2 changes.
    * @param The new value of prop2.
    */
    virtual void publishProp2Changed(Enum2Enum prop2) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the EnumInterface implementation when property prop3 changes.
    * @param The new value of prop3.
    */
    virtual void publishProp3Changed(Enum3Enum prop3) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the EnumInterface implementation when sig0 is emitted.
    * @param param0 
    */
    virtual void publishSig0(Enum0Enum param0) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the EnumInterface implementation when sig1 is emitted.
    * @param param1 
    */
    virtual void publishSig1(Enum1Enum param1) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the EnumInterface implementation when sig2 is emitted.
    * @param param2 
    */
    virtual void publishSig2(Enum2Enum param2) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the EnumInterface implementation when sig3 is emitted.
    * @param param3 
    */
    virtual void publishSig3(Enum3Enum param3) const = 0;
};


} // namespace TbEnum
} // namespace Test
