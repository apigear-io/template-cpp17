#pragma once

#include <future>
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/datastructs.api.h"

namespace Test {
namespace TbSimple {

class IEmptyInterfaceSubscriber;
class IEmptyInterfacePublisher;

/**
*
* IEmptyInterface provides an interface for
 *  - methods defined for your EmptyInterface 
 *  - property setters and getters for defined properties
 * The IEmptyInterface also provides an interface to access a publisher IEmptyInterfacePublisher, a class used by IEmptyInterfaceSubscriber clients.
 * The implementation should notify the publisher IEmptyInterfacePublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also IEmptyInterfaceSubscriber, IEmptyInterfacePublisher
 * and the example implementation EmptyInterface  or the
 */
class TEST_TB_SIMPLE_EXPORT IEmptyInterface
{
public:
    virtual ~IEmptyInterface() = default;

    /**
    * Access to a publisher, use it to subscribe for EmptyInterface changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for EmptyInterface.
    */
    virtual IEmptyInterfacePublisher& _getPublisher() const = 0;
};


/**
 * The IEmptyInterfaceSubscriber contains functions to allow informing about signals or property changes of the IEmptyInterface implementation.
 * The implementation for IEmptyInterface should provide mechanism for subscription of the IEmptyInterfaceSubscriber clients.
 * See IEmptyInterfacePublisher, which provides facilitation for this purpose.
 * The implementation for IEmptyInterface should call the IEmptyInterfaceSubscriber interface functions on either signal emit or property change.
 * You can use IEmptyInterfaceSubscriber class to implement clients of the IEmptyInterface or the network adapter - see Olink Server and Client example.
 */
class TEST_TB_SIMPLE_EXPORT IEmptyInterfaceSubscriber
{
public:
    virtual ~IEmptyInterfaceSubscriber() = default;
};



/**
 * The IEmptyInterfacePublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your IEmptyInterface implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a IEmptyInterfaceSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IIEmptyInterface on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TB_SIMPLE_EXPORT IEmptyInterfacePublisher
{
public:
    virtual ~IEmptyInterfacePublisher() = default;

    /**
    * Use this function to subscribe for any change of the EmptyInterface.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param IEmptyInterfaceSubscriber which is subscribed in this function to any change of the EmptyInterface.
    */
    virtual void subscribeToAllChanges(IEmptyInterfaceSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the EmptyInterface.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param IEmptyInterfaceSubscriber which subscription for any change of the EmptyInterface is removed.
    */
    virtual void unsubscribeFromAllChanges(IEmptyInterfaceSubscriber& subscriber) = 0;

};


} // namespace TbSimple
} // namespace Test
