#pragma once

#include <future>
#include "testbed2/generated/api/common.h"
#include "testbed2/generated/api/datastructs.api.h"

namespace Test {
namespace Testbed2 {

class INestedStruct2InterfaceSubscriber;
class INestedStruct2InterfacePublisher;

/**
*
* INestedStruct2Interface provides an interface for
 *  - methods defined for your NestedStruct2Interface 
 *  - property setters and getters for defined properties
 * The INestedStruct2Interface also provides an interface to access a publisher INestedStruct2InterfacePublisher, a class used by INestedStruct2InterfaceSubscriber clients.
 * The implementation should notify the publisher INestedStruct2InterfacePublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also INestedStruct2InterfaceSubscriber, INestedStruct2InterfacePublisher
 * and the example implementation NestedStruct2Interface  or the
 */
class TEST_TESTBED2_EXPORT INestedStruct2Interface
{
public:
    virtual ~INestedStruct2Interface() = default;


    virtual NestedStruct1 func1(const NestedStruct1& param1) = 0;
    /**
    * Asynchronous version of func1(const NestedStruct1& param1)
    * @return Promise of type NestedStruct1 which is set once the function has completed
    */
    virtual std::future<NestedStruct1> func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback = nullptr) = 0;


    virtual NestedStruct1 func2(const NestedStruct1& param1, const NestedStruct2& param2) = 0;
    /**
    * Asynchronous version of func2(const NestedStruct1& param1, const NestedStruct2& param2)
    * @return Promise of type NestedStruct1 which is set once the function has completed
    */
    virtual std::future<NestedStruct1> func2Async(const NestedStruct1& param1, const NestedStruct2& param2, std::function<void(NestedStruct1)> callback = nullptr) = 0;

    /**
    * Sets the value of the prop1 property.
    */
    virtual void setProp1(const NestedStruct1& prop1) = 0;
    /**
    * Gets the value of the prop1 property.
    */
    virtual const NestedStruct1& getProp1() const = 0;

    /**
    * Sets the value of the prop2 property.
    */
    virtual void setProp2(const NestedStruct2& prop2) = 0;
    /**
    * Gets the value of the prop2 property.
    */
    virtual const NestedStruct2& getProp2() const = 0;

    /**
    * Access to a publisher, use it to subscribe for NestedStruct2Interface changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for NestedStruct2Interface.
    */
    virtual INestedStruct2InterfacePublisher& _getPublisher() const = 0;
};


/**
 * The INestedStruct2InterfaceSubscriber contains functions to allow informing about signals or property changes of the INestedStruct2Interface implementation.
 * The implementation for INestedStruct2Interface should provide mechanism for subscription of the INestedStruct2InterfaceSubscriber clients.
 * See INestedStruct2InterfacePublisher, which provides facilitation for this purpose.
 * The implementation for INestedStruct2Interface should call the INestedStruct2InterfaceSubscriber interface functions on either signal emit or property change.
 * You can use INestedStruct2InterfaceSubscriber class to implement clients of the INestedStruct2Interface or the network adapter - see Olink Server and Client example.
 */
class TEST_TESTBED2_EXPORT INestedStruct2InterfaceSubscriber
{
public:
    virtual ~INestedStruct2InterfaceSubscriber() = default;
    /**
    * Called by the INestedStruct2InterfacePublisher when the NestedStruct2Interface emits sig1, if subscribed for the sig1.
    * @param param1 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSig1(const NestedStruct1& param1) = 0;
    /**
    * Called by the INestedStruct2InterfacePublisher when the NestedStruct2Interface emits sig2, if subscribed for the sig2.
    * @param param1 
    * @param param2 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSig2(const NestedStruct1& param1, const NestedStruct2& param2) = 0;
    /**
    * Called by the INestedStruct2InterfacePublisher when prop1 value has changed if subscribed for the prop1 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onProp1Changed(const NestedStruct1& prop1) = 0;
    /**
    * Called by the INestedStruct2InterfacePublisher when prop2 value has changed if subscribed for the prop2 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onProp2Changed(const NestedStruct2& prop2) = 0;
};

/** Callback for changes of prop1 */
using NestedStruct2InterfaceProp1PropertyCb = std::function<void(const NestedStruct1& prop1)>;
/** Callback for changes of prop2 */
using NestedStruct2InterfaceProp2PropertyCb = std::function<void(const NestedStruct2& prop2)>;
/** Callback for sig1 signal triggers */
using NestedStruct2InterfaceSig1SignalCb = std::function<void(const NestedStruct1& param1)> ;
/** Callback for sig2 signal triggers */
using NestedStruct2InterfaceSig2SignalCb = std::function<void(const NestedStruct1& param1, const NestedStruct2& param2)> ;


/**
 * The INestedStruct2InterfacePublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your INestedStruct2Interface implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a INestedStruct2InterfaceSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IINestedStruct2Interface on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TESTBED2_EXPORT INestedStruct2InterfacePublisher
{
public:
    virtual ~INestedStruct2InterfacePublisher() = default;

    /**
    * Use this function to subscribe for any change of the NestedStruct2Interface.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param INestedStruct2InterfaceSubscriber which is subscribed in this function to any change of the NestedStruct2Interface.
    */
    virtual void subscribeToAllChanges(INestedStruct2InterfaceSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the NestedStruct2Interface.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param INestedStruct2InterfaceSubscriber which subscription for any change of the NestedStruct2Interface is removed.
    */
    virtual void unsubscribeFromAllChanges(INestedStruct2InterfaceSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for prop1 value changes.
    * If your subscriber uses subscription with INestedStruct2InterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param NestedStruct2InterfaceProp1PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToProp1Changed(NestedStruct2InterfaceProp1PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from prop1 property changes.
    * If your subscriber uses subscription with INestedStruct2InterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromProp1Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for prop2 value changes.
    * If your subscriber uses subscription with INestedStruct2InterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param NestedStruct2InterfaceProp2PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToProp2Changed(NestedStruct2InterfaceProp2PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from prop2 property changes.
    * If your subscriber uses subscription with INestedStruct2InterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromProp2Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for sig1 signal changes.
    * @param NestedStruct2InterfaceSig1SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSig1(NestedStruct2InterfaceSig1SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sig1 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSig1(long handleId) = 0;

    /**
    * Use this function to subscribe for sig2 signal changes.
    * @param NestedStruct2InterfaceSig2SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSig2(NestedStruct2InterfaceSig2SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sig2 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSig2(long handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the NestedStruct2Interface implementation when property prop1 changes.
    * @param The new value of prop1.
    */
    virtual void publishProp1Changed(const NestedStruct1& prop1) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the NestedStruct2Interface implementation when property prop2 changes.
    * @param The new value of prop2.
    */
    virtual void publishProp2Changed(const NestedStruct2& prop2) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the NestedStruct2Interface implementation when sig1 is emitted.
    * @param param1 
    */
    virtual void publishSig1(const NestedStruct1& param1) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the NestedStruct2Interface implementation when sig2 is emitted.
    * @param param1 
    * @param param2 
    */
    virtual void publishSig2(const NestedStruct1& param1, const NestedStruct2& param2) const = 0;
};


} // namespace Testbed2
} // namespace Test
