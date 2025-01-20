#pragma once

#include <future>
#include "testbed2/generated/api/common.h"
#include "testbed2/generated/api/datastructs.api.h"

namespace Test {
namespace Testbed2 {

class INestedStruct1InterfaceSubscriber;
class INestedStruct1InterfacePublisher;

/**
*
* INestedStruct1Interface provides an interface for
 *  - methods defined for your NestedStruct1Interface 
 *  - property setters and getters for defined properties
 * The INestedStruct1Interface also provides an interface to access a publisher INestedStruct1InterfacePublisher, a class used by INestedStruct1InterfaceSubscriber clients.
 * The implementation should notify the publisher INestedStruct1InterfacePublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also INestedStruct1InterfaceSubscriber, INestedStruct1InterfacePublisher
 * and the example implementation NestedStruct1Interface  or the
 */
class TEST_TESTBED2_EXPORT INestedStruct1Interface
{
public:
    virtual ~INestedStruct1Interface() = default;


    virtual NestedStruct1 func1(const NestedStruct1& param1) = 0;
    /**
    * Asynchronous version of func1(const NestedStruct1& param1)
    * @return Promise of type NestedStruct1 which is set once the function has completed
    */
    virtual std::future<NestedStruct1> func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback = nullptr) = 0;

    /**
    * Sets the value of the prop1 property.
    */
    virtual void setProp1(const NestedStruct1& prop1) = 0;
    /**
    * Gets the value of the prop1 property.
    */
    virtual const NestedStruct1& getProp1() const = 0;

    /**
    * Access to a publisher, use it to subscribe for NestedStruct1Interface changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for NestedStruct1Interface.
    */
    virtual INestedStruct1InterfacePublisher& _getPublisher() const = 0;
};


/**
 * The INestedStruct1InterfaceSubscriber contains functions to allow informing about signals or property changes of the INestedStruct1Interface implementation.
 * The implementation for INestedStruct1Interface should provide mechanism for subscription of the INestedStruct1InterfaceSubscriber clients.
 * See INestedStruct1InterfacePublisher, which provides facilitation for this purpose.
 * The implementation for INestedStruct1Interface should call the INestedStruct1InterfaceSubscriber interface functions on either signal emit or property change.
 * You can use INestedStruct1InterfaceSubscriber class to implement clients of the INestedStruct1Interface or the network adapter - see Olink Server and Client example.
 */
class TEST_TESTBED2_EXPORT INestedStruct1InterfaceSubscriber
{
public:
    virtual ~INestedStruct1InterfaceSubscriber() = default;
    /**
    * Called by the INestedStruct1InterfacePublisher when the NestedStruct1Interface emits sig1, if subscribed for the sig1.
    * @param param1 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSig1(const NestedStruct1& param1) = 0;
    /**
    * Called by the INestedStruct1InterfacePublisher when prop1 value has changed if subscribed for the prop1 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onProp1Changed(const NestedStruct1& prop1) = 0;
};

/** Callback for changes of prop1 */
using NestedStruct1InterfaceProp1PropertyCb = std::function<void(const NestedStruct1& prop1)>;
/** Callback for sig1 signal triggers */
using NestedStruct1InterfaceSig1SignalCb = std::function<void(const NestedStruct1& param1)> ;


/**
 * The INestedStruct1InterfacePublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your INestedStruct1Interface implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a INestedStruct1InterfaceSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IINestedStruct1Interface on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TESTBED2_EXPORT INestedStruct1InterfacePublisher
{
public:
    virtual ~INestedStruct1InterfacePublisher() = default;

    /**
    * Use this function to subscribe for any change of the NestedStruct1Interface.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param INestedStruct1InterfaceSubscriber which is subscribed in this function to any change of the NestedStruct1Interface.
    */
    virtual void subscribeToAllChanges(INestedStruct1InterfaceSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the NestedStruct1Interface.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param INestedStruct1InterfaceSubscriber which subscription for any change of the NestedStruct1Interface is removed.
    */
    virtual void unsubscribeFromAllChanges(INestedStruct1InterfaceSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for prop1 value changes.
    * If your subscriber uses subscription with INestedStruct1InterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param NestedStruct1InterfaceProp1PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToProp1Changed(NestedStruct1InterfaceProp1PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from prop1 property changes.
    * If your subscriber uses subscription with INestedStruct1InterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromProp1Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for sig1 signal changes.
    * @param NestedStruct1InterfaceSig1SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSig1(NestedStruct1InterfaceSig1SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sig1 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSig1(long handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the NestedStruct1Interface implementation when property prop1 changes.
    * @param The new value of prop1.
    */
    virtual void publishProp1Changed(const NestedStruct1& prop1) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the NestedStruct1Interface implementation when sig1 is emitted.
    * @param param1 
    */
    virtual void publishSig1(const NestedStruct1& param1) const = 0;
};


} // namespace Testbed2
} // namespace Test
