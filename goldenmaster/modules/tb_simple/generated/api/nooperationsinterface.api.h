#pragma once

#include <cstdint>
#include <future>
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/datastructs.api.h"

namespace Test {
namespace TbSimple {

class INoOperationsInterfaceSubscriber;
class INoOperationsInterfacePublisher;

/**
*
* INoOperationsInterface provides an interface for
 *  - methods defined for your NoOperationsInterface 
 *  - property setters and getters for defined properties
 * The INoOperationsInterface also provides an interface to access a publisher INoOperationsInterfacePublisher, a class used by INoOperationsInterfaceSubscriber clients.
 * The implementation should notify the publisher INoOperationsInterfacePublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also INoOperationsInterfaceSubscriber, INoOperationsInterfacePublisher
 * and the example implementation NoOperationsInterface  or the
 */
class TEST_TB_SIMPLE_EXPORT INoOperationsInterface
{
public:
    virtual ~INoOperationsInterface() = default;

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
    * Access to a publisher, use it to subscribe for NoOperationsInterface changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for NoOperationsInterface.
    */
    virtual INoOperationsInterfacePublisher& _getPublisher() const = 0;
};


/**
 * The INoOperationsInterfaceSubscriber contains functions to allow informing about signals or property changes of the INoOperationsInterface implementation.
 * The implementation for INoOperationsInterface should provide mechanism for subscription of the INoOperationsInterfaceSubscriber clients.
 * See INoOperationsInterfacePublisher, which provides facilitation for this purpose.
 * The implementation for INoOperationsInterface should call the INoOperationsInterfaceSubscriber interface functions on either signal emit or property change.
 * You can use INoOperationsInterfaceSubscriber class to implement clients of the INoOperationsInterface or the network adapter - see Olink Server and Client example.
 */
class TEST_TB_SIMPLE_EXPORT INoOperationsInterfaceSubscriber
{
public:
    virtual ~INoOperationsInterfaceSubscriber() = default;
    /**
    * Called by the INoOperationsInterfacePublisher when the NoOperationsInterface emits sigVoid, if subscribed for the sigVoid.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigVoid() = 0;
    /**
    * Called by the INoOperationsInterfacePublisher when the NoOperationsInterface emits sigBool, if subscribed for the sigBool.
    * @param paramBool 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigBool(bool paramBool) = 0;
    /**
    * Called by the INoOperationsInterfacePublisher when propBool value has changed if subscribed for the propBool change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropBoolChanged(bool propBool) = 0;
    /**
    * Called by the INoOperationsInterfacePublisher when propInt value has changed if subscribed for the propInt change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropIntChanged(int propInt) = 0;
};

/** Callback for changes of propBool */
using NoOperationsInterfacePropBoolPropertyCb = std::function<void(bool propBool)>;
/** Callback for changes of propInt */
using NoOperationsInterfacePropIntPropertyCb = std::function<void(int propInt)>;
/** Callback for sigVoid signal triggers */
using NoOperationsInterfaceSigVoidSignalCb = std::function<void()> ;
/** Callback for sigBool signal triggers */
using NoOperationsInterfaceSigBoolSignalCb = std::function<void(bool paramBool)> ;


/**
 * The INoOperationsInterfacePublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your INoOperationsInterface implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a INoOperationsInterfaceSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IINoOperationsInterface on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TB_SIMPLE_EXPORT INoOperationsInterfacePublisher
{
public:
    virtual ~INoOperationsInterfacePublisher() = default;

    /**
    * Use this function to subscribe for any change of the NoOperationsInterface.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param INoOperationsInterfaceSubscriber which is subscribed in this function to any change of the NoOperationsInterface.
    */
    virtual void subscribeToAllChanges(INoOperationsInterfaceSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the NoOperationsInterface.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param INoOperationsInterfaceSubscriber which subscription for any change of the NoOperationsInterface is removed.
    */
    virtual void unsubscribeFromAllChanges(INoOperationsInterfaceSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for propBool value changes.
    * If your subscriber uses subscription with INoOperationsInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param NoOperationsInterfacePropBoolPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToPropBoolChanged(NoOperationsInterfacePropBoolPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propBool property changes.
    * If your subscriber uses subscription with INoOperationsInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropBoolChanged(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for propInt value changes.
    * If your subscriber uses subscription with INoOperationsInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param NoOperationsInterfacePropIntPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToPropIntChanged(NoOperationsInterfacePropIntPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propInt property changes.
    * If your subscriber uses subscription with INoOperationsInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropIntChanged(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for sigVoid signal changes.
    * @param NoOperationsInterfaceSigVoidSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToSigVoid(NoOperationsInterfaceSigVoidSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigVoid signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigVoid(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for sigBool signal changes.
    * @param NoOperationsInterfaceSigBoolSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToSigBool(NoOperationsInterfaceSigBoolSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigBool signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigBool(uint64_t handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the NoOperationsInterface implementation when property propBool changes.
    * @param The new value of propBool.
    */
    virtual void publishPropBoolChanged(bool propBool) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the NoOperationsInterface implementation when property propInt changes.
    * @param The new value of propInt.
    */
    virtual void publishPropIntChanged(int propInt) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the NoOperationsInterface implementation when sigVoid is emitted.
    */
    virtual void publishSigVoid() const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the NoOperationsInterface implementation when sigBool is emitted.
    * @param paramBool 
    */
    virtual void publishSigBool(bool paramBool) const = 0;
};


} // namespace TbSimple
} // namespace Test
