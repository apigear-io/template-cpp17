#pragma once

#include <future>
#include "counter/generated/api/common.h"
#include "counter/generated/api/datastructs.api.h"
#include "custom_types/generated/api/datastructs.api.h"
#include "extern_types/generated/api/datastructs.api.h"

namespace Test {
namespace Counter {

class ICounterSubscriber;
class ICounterPublisher;

/**
*
* ICounter provides an interface for
 *  - methods defined for your Counter 
 *  - property setters and getters for defined properties
 * The ICounter also provides an interface to access a publisher ICounterPublisher, a class used by ICounterSubscriber clients.
 * The implementation should notify the publisher ICounterPublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also ICounterSubscriber, ICounterPublisher
 * and the example implementation Counter  or the
 */
class TEST_COUNTER_EXPORT ICounter
{
public:
    virtual ~ICounter() = default;


    virtual Eigen::Vector3f increment(const Eigen::Vector3f& vec) = 0;
    /**
    * Asynchronous version of increment(const Eigen::Vector3f& vec)
    * @return Promise of type Eigen::Vector3f which is set once the function has completed
    */
    virtual std::future<Eigen::Vector3f> incrementAsync(const Eigen::Vector3f& vec) = 0;


    virtual Test::CustomTypes::Vector3D decrement(const Test::CustomTypes::Vector3D& vec) = 0;
    /**
    * Asynchronous version of decrement(const Test::CustomTypes::Vector3D& vec)
    * @return Promise of type Test::CustomTypes::Vector3D which is set once the function has completed
    */
    virtual std::future<Test::CustomTypes::Vector3D> decrementAsync(const Test::CustomTypes::Vector3D& vec) = 0;

    /**
    * Sets the value of the vector property.
    */
    virtual void setVector(const Test::CustomTypes::Vector3D& vector) = 0;
    /**
    * Gets the value of the vector property.
    */
    virtual const Test::CustomTypes::Vector3D& getVector() const = 0;

    /**
    * Sets the value of the extern_vector property.
    */
    virtual void setExternVector(const Eigen::Vector3f& extern_vector) = 0;
    /**
    * Gets the value of the extern_vector property.
    */
    virtual const Eigen::Vector3f& getExternVector() const = 0;

    /**
    * Access to a publisher, use it to subscribe for Counter changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for Counter.
    */
    virtual ICounterPublisher& _getPublisher() const = 0;
};


/**
 * The ICounterSubscriber contains functions to allow informing about signals or property changes of the ICounter implementation.
 * The implementation for ICounter should provide mechanism for subscription of the ICounterSubscriber clients.
 * See ICounterPublisher, which provides facilitation for this purpose.
 * The implementation for ICounter should call the ICounterSubscriber interface functions on either signal emit or property change.
 * You can use ICounterSubscriber class to implement clients of the ICounter or the network adapter - see Olink Server and Client example.
 */
class TEST_COUNTER_EXPORT ICounterSubscriber
{
public:
    virtual ~ICounterSubscriber() = default;
    /**
    * Called by the ICounterPublisher when vector value has changed if subscribed for the vector change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onVectorChanged(const Test::CustomTypes::Vector3D& vector) = 0;
    /**
    * Called by the ICounterPublisher when extern_vector value has changed if subscribed for the extern_vector change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onExternVectorChanged(const Eigen::Vector3f& extern_vector) = 0;
};

/** Callback for changes of vector */
using CounterVectorPropertyCb = std::function<void(const Test::CustomTypes::Vector3D& vector)>;
/** Callback for changes of extern_vector */
using CounterExternVectorPropertyCb = std::function<void(const Eigen::Vector3f& extern_vector)>;


/**
 * The ICounterPublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your ICounter implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a ICounterSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IICounter on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_COUNTER_EXPORT ICounterPublisher
{
public:
    virtual ~ICounterPublisher() = default;

    /**
    * Use this function to subscribe for any change of the Counter.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param ICounterSubscriber which is subscribed in this function to any change of the Counter.
    */
    virtual void subscribeToAllChanges(ICounterSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the Counter.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param ICounterSubscriber which subscription for any change of the Counter is removed.
    */
    virtual void unsubscribeFromAllChanges(ICounterSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for vector value changes.
    * If your subscriber uses subscription with ICounterSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param CounterVectorPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToVectorChanged(CounterVectorPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from vector property changes.
    * If your subscriber uses subscription with ICounterSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromVectorChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for extern_vector value changes.
    * If your subscriber uses subscription with ICounterSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param CounterExternVectorPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToExternVectorChanged(CounterExternVectorPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from extern_vector property changes.
    * If your subscriber uses subscription with ICounterSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromExternVectorChanged(long handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the Counter implementation when property vector changes.
    * @param The new value of vector.
    */
    virtual void publishVectorChanged(const Test::CustomTypes::Vector3D& vector) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the Counter implementation when property extern_vector changes.
    * @param The new value of extern_vector.
    */
    virtual void publishExternVectorChanged(const Eigen::Vector3f& extern_vector) const = 0;
};


} // namespace Counter
} // namespace Test
