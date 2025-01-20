#pragma once

#include <future>
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/datastructs.api.h"

namespace Test {
namespace TbSimple {

class INoPropertiesInterfaceSubscriber;
class INoPropertiesInterfacePublisher;

/**
*
* INoPropertiesInterface provides an interface for
 *  - methods defined for your NoPropertiesInterface 
 *  - property setters and getters for defined properties
 * The INoPropertiesInterface also provides an interface to access a publisher INoPropertiesInterfacePublisher, a class used by INoPropertiesInterfaceSubscriber clients.
 * The implementation should notify the publisher INoPropertiesInterfacePublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also INoPropertiesInterfaceSubscriber, INoPropertiesInterfacePublisher
 * and the example implementation NoPropertiesInterface  or the
 */
class TEST_TB_SIMPLE_EXPORT INoPropertiesInterface
{
public:
    virtual ~INoPropertiesInterface() = default;


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
    * Access to a publisher, use it to subscribe for NoPropertiesInterface changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for NoPropertiesInterface.
    */
    virtual INoPropertiesInterfacePublisher& _getPublisher() const = 0;
};


/**
 * The INoPropertiesInterfaceSubscriber contains functions to allow informing about signals or property changes of the INoPropertiesInterface implementation.
 * The implementation for INoPropertiesInterface should provide mechanism for subscription of the INoPropertiesInterfaceSubscriber clients.
 * See INoPropertiesInterfacePublisher, which provides facilitation for this purpose.
 * The implementation for INoPropertiesInterface should call the INoPropertiesInterfaceSubscriber interface functions on either signal emit or property change.
 * You can use INoPropertiesInterfaceSubscriber class to implement clients of the INoPropertiesInterface or the network adapter - see Olink Server and Client example.
 */
class TEST_TB_SIMPLE_EXPORT INoPropertiesInterfaceSubscriber
{
public:
    virtual ~INoPropertiesInterfaceSubscriber() = default;
    /**
    * Called by the INoPropertiesInterfacePublisher when the NoPropertiesInterface emits sigVoid, if subscribed for the sigVoid.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigVoid() = 0;
    /**
    * Called by the INoPropertiesInterfacePublisher when the NoPropertiesInterface emits sigBool, if subscribed for the sigBool.
    * @param paramBool 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigBool(bool paramBool) = 0;
};

/** Callback for sigVoid signal triggers */
using NoPropertiesInterfaceSigVoidSignalCb = std::function<void()> ;
/** Callback for sigBool signal triggers */
using NoPropertiesInterfaceSigBoolSignalCb = std::function<void(bool paramBool)> ;


/**
 * The INoPropertiesInterfacePublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your INoPropertiesInterface implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a INoPropertiesInterfaceSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IINoPropertiesInterface on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TB_SIMPLE_EXPORT INoPropertiesInterfacePublisher
{
public:
    virtual ~INoPropertiesInterfacePublisher() = default;

    /**
    * Use this function to subscribe for any change of the NoPropertiesInterface.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param INoPropertiesInterfaceSubscriber which is subscribed in this function to any change of the NoPropertiesInterface.
    */
    virtual void subscribeToAllChanges(INoPropertiesInterfaceSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the NoPropertiesInterface.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param INoPropertiesInterfaceSubscriber which subscription for any change of the NoPropertiesInterface is removed.
    */
    virtual void unsubscribeFromAllChanges(INoPropertiesInterfaceSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for sigVoid signal changes.
    * @param NoPropertiesInterfaceSigVoidSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigVoid(NoPropertiesInterfaceSigVoidSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigVoid signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigVoid(long handleId) = 0;

    /**
    * Use this function to subscribe for sigBool signal changes.
    * @param NoPropertiesInterfaceSigBoolSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigBool(NoPropertiesInterfaceSigBoolSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigBool signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigBool(long handleId) = 0;

    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the NoPropertiesInterface implementation when sigVoid is emitted.
    */
    virtual void publishSigVoid() const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the NoPropertiesInterface implementation when sigBool is emitted.
    * @param paramBool 
    */
    virtual void publishSigBool(bool paramBool) const = 0;
};


} // namespace TbSimple
} // namespace Test
