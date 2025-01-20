#pragma once

#include <future>
#include "tb_same1/generated/api/common.h"
#include "tb_same1/generated/api/datastructs.api.h"

namespace Test {
namespace TbSame1 {

class ISameEnum2InterfaceSubscriber;
class ISameEnum2InterfacePublisher;

/**
*
* ISameEnum2Interface provides an interface for
 *  - methods defined for your SameEnum2Interface 
 *  - property setters and getters for defined properties
 * The ISameEnum2Interface also provides an interface to access a publisher ISameEnum2InterfacePublisher, a class used by ISameEnum2InterfaceSubscriber clients.
 * The implementation should notify the publisher ISameEnum2InterfacePublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also ISameEnum2InterfaceSubscriber, ISameEnum2InterfacePublisher
 * and the example implementation SameEnum2Interface  or the
 */
class TEST_TB_SAME1_EXPORT ISameEnum2Interface
{
public:
    virtual ~ISameEnum2Interface() = default;


    virtual Enum1Enum func1(Enum1Enum param1) = 0;
    /**
    * Asynchronous version of func1(Enum1Enum param1)
    * @return Promise of type Enum1Enum which is set once the function has completed
    */
    virtual std::future<Enum1Enum> func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback = nullptr) = 0;


    virtual Enum1Enum func2(Enum1Enum param1, Enum2Enum param2) = 0;
    /**
    * Asynchronous version of func2(Enum1Enum param1, Enum2Enum param2)
    * @return Promise of type Enum1Enum which is set once the function has completed
    */
    virtual std::future<Enum1Enum> func2Async(Enum1Enum param1, Enum2Enum param2, std::function<void(Enum1Enum)> callback = nullptr) = 0;

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
    * Access to a publisher, use it to subscribe for SameEnum2Interface changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for SameEnum2Interface.
    */
    virtual ISameEnum2InterfacePublisher& _getPublisher() const = 0;
};


/**
 * The ISameEnum2InterfaceSubscriber contains functions to allow informing about signals or property changes of the ISameEnum2Interface implementation.
 * The implementation for ISameEnum2Interface should provide mechanism for subscription of the ISameEnum2InterfaceSubscriber clients.
 * See ISameEnum2InterfacePublisher, which provides facilitation for this purpose.
 * The implementation for ISameEnum2Interface should call the ISameEnum2InterfaceSubscriber interface functions on either signal emit or property change.
 * You can use ISameEnum2InterfaceSubscriber class to implement clients of the ISameEnum2Interface or the network adapter - see Olink Server and Client example.
 */
class TEST_TB_SAME1_EXPORT ISameEnum2InterfaceSubscriber
{
public:
    virtual ~ISameEnum2InterfaceSubscriber() = default;
    /**
    * Called by the ISameEnum2InterfacePublisher when the SameEnum2Interface emits sig1, if subscribed for the sig1.
    * @param param1 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSig1(Enum1Enum param1) = 0;
    /**
    * Called by the ISameEnum2InterfacePublisher when the SameEnum2Interface emits sig2, if subscribed for the sig2.
    * @param param1 
    * @param param2 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSig2(Enum1Enum param1, Enum2Enum param2) = 0;
    /**
    * Called by the ISameEnum2InterfacePublisher when prop1 value has changed if subscribed for the prop1 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onProp1Changed(Enum1Enum prop1) = 0;
    /**
    * Called by the ISameEnum2InterfacePublisher when prop2 value has changed if subscribed for the prop2 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onProp2Changed(Enum2Enum prop2) = 0;
};

/** Callback for changes of prop1 */
using SameEnum2InterfaceProp1PropertyCb = std::function<void(Enum1Enum prop1)>;
/** Callback for changes of prop2 */
using SameEnum2InterfaceProp2PropertyCb = std::function<void(Enum2Enum prop2)>;
/** Callback for sig1 signal triggers */
using SameEnum2InterfaceSig1SignalCb = std::function<void(Enum1Enum param1)> ;
/** Callback for sig2 signal triggers */
using SameEnum2InterfaceSig2SignalCb = std::function<void(Enum1Enum param1, Enum2Enum param2)> ;


/**
 * The ISameEnum2InterfacePublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your ISameEnum2Interface implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a ISameEnum2InterfaceSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IISameEnum2Interface on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TB_SAME1_EXPORT ISameEnum2InterfacePublisher
{
public:
    virtual ~ISameEnum2InterfacePublisher() = default;

    /**
    * Use this function to subscribe for any change of the SameEnum2Interface.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param ISameEnum2InterfaceSubscriber which is subscribed in this function to any change of the SameEnum2Interface.
    */
    virtual void subscribeToAllChanges(ISameEnum2InterfaceSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the SameEnum2Interface.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param ISameEnum2InterfaceSubscriber which subscription for any change of the SameEnum2Interface is removed.
    */
    virtual void unsubscribeFromAllChanges(ISameEnum2InterfaceSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for prop1 value changes.
    * If your subscriber uses subscription with ISameEnum2InterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SameEnum2InterfaceProp1PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToProp1Changed(SameEnum2InterfaceProp1PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from prop1 property changes.
    * If your subscriber uses subscription with ISameEnum2InterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromProp1Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for prop2 value changes.
    * If your subscriber uses subscription with ISameEnum2InterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param SameEnum2InterfaceProp2PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToProp2Changed(SameEnum2InterfaceProp2PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from prop2 property changes.
    * If your subscriber uses subscription with ISameEnum2InterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromProp2Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for sig1 signal changes.
    * @param SameEnum2InterfaceSig1SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSig1(SameEnum2InterfaceSig1SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sig1 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSig1(long handleId) = 0;

    /**
    * Use this function to subscribe for sig2 signal changes.
    * @param SameEnum2InterfaceSig2SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSig2(SameEnum2InterfaceSig2SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sig2 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSig2(long handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SameEnum2Interface implementation when property prop1 changes.
    * @param The new value of prop1.
    */
    virtual void publishProp1Changed(Enum1Enum prop1) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the SameEnum2Interface implementation when property prop2 changes.
    * @param The new value of prop2.
    */
    virtual void publishProp2Changed(Enum2Enum prop2) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SameEnum2Interface implementation when sig1 is emitted.
    * @param param1 
    */
    virtual void publishSig1(Enum1Enum param1) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the SameEnum2Interface implementation when sig2 is emitted.
    * @param param1 
    * @param param2 
    */
    virtual void publishSig2(Enum1Enum param1, Enum2Enum param2) const = 0;
};


} // namespace TbSame1
} // namespace Test
