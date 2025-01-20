#pragma once

#include <future>
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/datastructs.api.h"

namespace Test {
namespace TbSimple {

class INoSignalsInterfaceSubscriber;
class INoSignalsInterfacePublisher;

/**
*
* INoSignalsInterface provides an interface for
 *  - methods defined for your NoSignalsInterface 
 *  - property setters and getters for defined properties
 * The INoSignalsInterface also provides an interface to access a publisher INoSignalsInterfacePublisher, a class used by INoSignalsInterfaceSubscriber clients.
 * The implementation should notify the publisher INoSignalsInterfacePublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also INoSignalsInterfaceSubscriber, INoSignalsInterfacePublisher
 * and the example implementation NoSignalsInterface  or the
 */
class TEST_TB_SIMPLE_EXPORT INoSignalsInterface
{
public:
    virtual ~INoSignalsInterface() = default;


    virtual void funcVoid() = 0;
    /**
    * Asynchronous version of funcVoid()
    * @return Promise of type void which is set once the function has completed
    */
    virtual std::future<void> funcVoidAsync( std::function<void(void)> callback = nullptr) = 0;


    virtual bool funcBool(bool paramBool) = 0;
    /**
    * Asynchronous version of funcBool(bool paramBool)
    * @return Promise of type bool which is set once the function has completed
    */
    virtual std::future<bool> funcBoolAsync(bool paramBool, std::function<void(bool)> callback = nullptr) = 0;

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
    * Access to a publisher, use it to subscribe for NoSignalsInterface changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for NoSignalsInterface.
    */
    virtual INoSignalsInterfacePublisher& _getPublisher() const = 0;
};


/**
 * The INoSignalsInterfaceSubscriber contains functions to allow informing about signals or property changes of the INoSignalsInterface implementation.
 * The implementation for INoSignalsInterface should provide mechanism for subscription of the INoSignalsInterfaceSubscriber clients.
 * See INoSignalsInterfacePublisher, which provides facilitation for this purpose.
 * The implementation for INoSignalsInterface should call the INoSignalsInterfaceSubscriber interface functions on either signal emit or property change.
 * You can use INoSignalsInterfaceSubscriber class to implement clients of the INoSignalsInterface or the network adapter - see Olink Server and Client example.
 */
class TEST_TB_SIMPLE_EXPORT INoSignalsInterfaceSubscriber
{
public:
    virtual ~INoSignalsInterfaceSubscriber() = default;
    /**
    * Called by the INoSignalsInterfacePublisher when propBool value has changed if subscribed for the propBool change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropBoolChanged(bool propBool) = 0;
    /**
    * Called by the INoSignalsInterfacePublisher when propInt value has changed if subscribed for the propInt change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropIntChanged(int propInt) = 0;
};

/** Callback for changes of propBool */
using NoSignalsInterfacePropBoolPropertyCb = std::function<void(bool propBool)>;
/** Callback for changes of propInt */
using NoSignalsInterfacePropIntPropertyCb = std::function<void(int propInt)>;


/**
 * The INoSignalsInterfacePublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your INoSignalsInterface implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a INoSignalsInterfaceSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IINoSignalsInterface on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TB_SIMPLE_EXPORT INoSignalsInterfacePublisher
{
public:
    virtual ~INoSignalsInterfacePublisher() = default;

    /**
    * Use this function to subscribe for any change of the NoSignalsInterface.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param INoSignalsInterfaceSubscriber which is subscribed in this function to any change of the NoSignalsInterface.
    */
    virtual void subscribeToAllChanges(INoSignalsInterfaceSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the NoSignalsInterface.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param INoSignalsInterfaceSubscriber which subscription for any change of the NoSignalsInterface is removed.
    */
    virtual void unsubscribeFromAllChanges(INoSignalsInterfaceSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for propBool value changes.
    * If your subscriber uses subscription with INoSignalsInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param NoSignalsInterfacePropBoolPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropBoolChanged(NoSignalsInterfacePropBoolPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propBool property changes.
    * If your subscriber uses subscription with INoSignalsInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropBoolChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propInt value changes.
    * If your subscriber uses subscription with INoSignalsInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param NoSignalsInterfacePropIntPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropIntChanged(NoSignalsInterfacePropIntPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propInt property changes.
    * If your subscriber uses subscription with INoSignalsInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropIntChanged(long handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the NoSignalsInterface implementation when property propBool changes.
    * @param The new value of propBool.
    */
    virtual void publishPropBoolChanged(bool propBool) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the NoSignalsInterface implementation when property propInt changes.
    * @param The new value of propInt.
    */
    virtual void publishPropIntChanged(int propInt) const = 0;
};


} // namespace TbSimple
} // namespace Test
