#pragma once

#include <future>
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/datastructs.api.h"

namespace Test {
namespace TbSimple {

class IVoidInterfaceSubscriber;
class IVoidInterfacePublisher;

/**
*
* IVoidInterface provides an interface for
 *  - methods defined for your VoidInterface 
 *  - property setters and getters for defined properties
 * The IVoidInterface also provides an interface to access a publisher IVoidInterfacePublisher, a class used by IVoidInterfaceSubscriber clients.
 * The implementation should notify the publisher IVoidInterfacePublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also IVoidInterfaceSubscriber, IVoidInterfacePublisher
 * and the example implementation VoidInterface  or the
 */
class TEST_TB_SIMPLE_EXPORT IVoidInterface
{
public:
    virtual ~IVoidInterface() = default;


    virtual void funcVoid() = 0;
    /**
    * Asynchronous version of funcVoid()
    * @return Promise of type void which is set once the function has completed
    */
    virtual std::future<void> funcVoidAsync( std::function<void(void)> callback = nullptr) = 0;

    /**
    * Access to a publisher, use it to subscribe for VoidInterface changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for VoidInterface.
    */
    virtual IVoidInterfacePublisher& _getPublisher() const = 0;
};


/**
 * The IVoidInterfaceSubscriber contains functions to allow informing about signals or property changes of the IVoidInterface implementation.
 * The implementation for IVoidInterface should provide mechanism for subscription of the IVoidInterfaceSubscriber clients.
 * See IVoidInterfacePublisher, which provides facilitation for this purpose.
 * The implementation for IVoidInterface should call the IVoidInterfaceSubscriber interface functions on either signal emit or property change.
 * You can use IVoidInterfaceSubscriber class to implement clients of the IVoidInterface or the network adapter - see Olink Server and Client example.
 */
class TEST_TB_SIMPLE_EXPORT IVoidInterfaceSubscriber
{
public:
    virtual ~IVoidInterfaceSubscriber() = default;
    /**
    * Called by the IVoidInterfacePublisher when the VoidInterface emits sigVoid, if subscribed for the sigVoid.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigVoid() = 0;
};

/** Callback for sigVoid signal triggers */
using VoidInterfaceSigVoidSignalCb = std::function<void()> ;


/**
 * The IVoidInterfacePublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your IVoidInterface implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a IVoidInterfaceSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IIVoidInterface on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TB_SIMPLE_EXPORT IVoidInterfacePublisher
{
public:
    virtual ~IVoidInterfacePublisher() = default;

    /**
    * Use this function to subscribe for any change of the VoidInterface.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param IVoidInterfaceSubscriber which is subscribed in this function to any change of the VoidInterface.
    */
    virtual void subscribeToAllChanges(IVoidInterfaceSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the VoidInterface.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param IVoidInterfaceSubscriber which subscription for any change of the VoidInterface is removed.
    */
    virtual void unsubscribeFromAllChanges(IVoidInterfaceSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for sigVoid signal changes.
    * @param VoidInterfaceSigVoidSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigVoid(VoidInterfaceSigVoidSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigVoid signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigVoid(long handleId) = 0;

    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the VoidInterface implementation when sigVoid is emitted.
    */
    virtual void publishSigVoid() const = 0;
};


} // namespace TbSimple
} // namespace Test
