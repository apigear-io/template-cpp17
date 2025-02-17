#pragma once

#include <future>
#include "tb_names/generated/api/common.h"
#include "tb_names/generated/api/datastructs.api.h"

namespace Test {
namespace TbNames {

class INamEsSubscriber;
class INamEsPublisher;

/**
*
* INamEs provides an interface for
 *  - methods defined for your Nam_Es 
 *  - property setters and getters for defined properties
 * The INamEs also provides an interface to access a publisher INamEsPublisher, a class used by INamEsSubscriber clients.
 * The implementation should notify the publisher INamEsPublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also INamEsSubscriber, INamEsPublisher
 * and the example implementation Nam_Es  or the
 */
class TEST_TB_NAMES_EXPORT INamEs
{
public:
    virtual ~INamEs() = default;


    virtual void sOME_FUNCTION(bool SOME_PARAM) = 0;
    /**
    * Asynchronous version of SOME_FUNCTION(bool SOME_PARAM)
    * @return Promise of type void which is set once the function has completed
    */
    virtual std::future<void> sOME_FUNCTIONAsync(bool SOME_PARAM) = 0;


    virtual void some_Function2(bool Some_Param) = 0;
    /**
    * Asynchronous version of Some_Function2(bool Some_Param)
    * @return Promise of type void which is set once the function has completed
    */
    virtual std::future<void> some_Function2Async(bool Some_Param) = 0;

    /**
    * Sets the value of the Switch property.
    */
    virtual void setSwitch(bool Switch) = 0;
    /**
    * Gets the value of the Switch property.
    */
    virtual bool getSwitch() const = 0;

    /**
    * Sets the value of the SOME_PROPERTY property.
    */
    virtual void setSomeProperty(int SOME_PROPERTY) = 0;
    /**
    * Gets the value of the SOME_PROPERTY property.
    */
    virtual int getSomeProperty() const = 0;

    /**
    * Sets the value of the Some_Poperty2 property.
    */
    virtual void setSomePoperty2(int Some_Poperty2) = 0;
    /**
    * Gets the value of the Some_Poperty2 property.
    */
    virtual int getSomePoperty2() const = 0;

    /**
    * Sets the value of the enum_property property.
    */
    virtual void setEnumProperty(Enum_With_Under_scoresEnum enum_property) = 0;
    /**
    * Gets the value of the enum_property property.
    */
    virtual Enum_With_Under_scoresEnum getEnumProperty() const = 0;

    /**
    * Access to a publisher, use it to subscribe for Nam_Es changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for Nam_Es.
    */
    virtual INamEsPublisher& _getPublisher() const = 0;
};


/**
 * The INamEsSubscriber contains functions to allow informing about signals or property changes of the INamEs implementation.
 * The implementation for INamEs should provide mechanism for subscription of the INamEsSubscriber clients.
 * See INamEsPublisher, which provides facilitation for this purpose.
 * The implementation for INamEs should call the INamEsSubscriber interface functions on either signal emit or property change.
 * You can use INamEsSubscriber class to implement clients of the INamEs or the network adapter - see Olink Server and Client example.
 */
class TEST_TB_NAMES_EXPORT INamEsSubscriber
{
public:
    virtual ~INamEsSubscriber() = default;
    /**
    * Called by the INamEsPublisher when the Nam_Es emits SOME_SIGNAL, if subscribed for the SOME_SIGNAL.
    * @param SOME_PARAM 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSomeSignal(bool SOME_PARAM) = 0;
    /**
    * Called by the INamEsPublisher when the Nam_Es emits Some_Signal2, if subscribed for the Some_Signal2.
    * @param Some_Param 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSomeSignal2(bool Some_Param) = 0;
    /**
    * Called by the INamEsPublisher when Switch value has changed if subscribed for the Switch change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSwitchChanged(bool Switch) = 0;
    /**
    * Called by the INamEsPublisher when SOME_PROPERTY value has changed if subscribed for the SOME_PROPERTY change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSomePropertyChanged(int SOME_PROPERTY) = 0;
    /**
    * Called by the INamEsPublisher when Some_Poperty2 value has changed if subscribed for the Some_Poperty2 change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSomePoperty2Changed(int Some_Poperty2) = 0;
    /**
    * Called by the INamEsPublisher when enum_property value has changed if subscribed for the enum_property change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onEnumPropertyChanged(Enum_With_Under_scoresEnum enum_property) = 0;
};

/** Callback for changes of Switch */
using NamEsSwitchPropertyCb = std::function<void(bool Switch)>;
/** Callback for changes of SOME_PROPERTY */
using NamEsSomePropertyPropertyCb = std::function<void(int SOME_PROPERTY)>;
/** Callback for changes of Some_Poperty2 */
using NamEsSomePoperty2PropertyCb = std::function<void(int Some_Poperty2)>;
/** Callback for changes of enum_property */
using NamEsEnumPropertyPropertyCb = std::function<void(Enum_With_Under_scoresEnum enum_property)>;
/** Callback for SOME_SIGNAL signal triggers */
using NamEsSomeSignalSignalCb = std::function<void(bool SOME_PARAM)> ;
/** Callback for Some_Signal2 signal triggers */
using NamEsSomeSignal2SignalCb = std::function<void(bool Some_Param)> ;


/**
 * The INamEsPublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your INamEs implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a INamEsSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IINamEs on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TB_NAMES_EXPORT INamEsPublisher
{
public:
    virtual ~INamEsPublisher() = default;

    /**
    * Use this function to subscribe for any change of the Nam_Es.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param INamEsSubscriber which is subscribed in this function to any change of the Nam_Es.
    */
    virtual void subscribeToAllChanges(INamEsSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the Nam_Es.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param INamEsSubscriber which subscription for any change of the Nam_Es is removed.
    */
    virtual void unsubscribeFromAllChanges(INamEsSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for Switch value changes.
    * If your subscriber uses subscription with INamEsSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param NamEsSwitchPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSwitchChanged(NamEsSwitchPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from Switch property changes.
    * If your subscriber uses subscription with INamEsSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSwitchChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for SOME_PROPERTY value changes.
    * If your subscriber uses subscription with INamEsSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param NamEsSomePropertyPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSomePropertyChanged(NamEsSomePropertyPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from SOME_PROPERTY property changes.
    * If your subscriber uses subscription with INamEsSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSomePropertyChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for Some_Poperty2 value changes.
    * If your subscriber uses subscription with INamEsSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param NamEsSomePoperty2PropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSomePoperty2Changed(NamEsSomePoperty2PropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from Some_Poperty2 property changes.
    * If your subscriber uses subscription with INamEsSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSomePoperty2Changed(long handleId) = 0;

    /**
    * Use this function to subscribe for enum_property value changes.
    * If your subscriber uses subscription with INamEsSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param NamEsEnumPropertyPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToEnumPropertyChanged(NamEsEnumPropertyPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from enum_property property changes.
    * If your subscriber uses subscription with INamEsSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromEnumPropertyChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for SOME_SIGNAL signal changes.
    * @param NamEsSomeSignalSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSomeSignal(NamEsSomeSignalSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from SOME_SIGNAL signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSomeSignal(long handleId) = 0;

    /**
    * Use this function to subscribe for Some_Signal2 signal changes.
    * @param NamEsSomeSignal2SignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSomeSignal2(NamEsSomeSignal2SignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from Some_Signal2 signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSomeSignal2(long handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the Nam_Es implementation when property Switch changes.
    * @param The new value of Switch.
    */
    virtual void publishSwitchChanged(bool Switch) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the Nam_Es implementation when property SOME_PROPERTY changes.
    * @param The new value of SOME_PROPERTY.
    */
    virtual void publishSomePropertyChanged(int SOME_PROPERTY) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the Nam_Es implementation when property Some_Poperty2 changes.
    * @param The new value of Some_Poperty2.
    */
    virtual void publishSomePoperty2Changed(int Some_Poperty2) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the Nam_Es implementation when property enum_property changes.
    * @param The new value of enum_property.
    */
    virtual void publishEnumPropertyChanged(Enum_With_Under_scoresEnum enum_property) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the Nam_Es implementation when SOME_SIGNAL is emitted.
    * @param SOME_PARAM 
    */
    virtual void publishSomeSignal(bool SOME_PARAM) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the Nam_Es implementation when Some_Signal2 is emitted.
    * @param Some_Param 
    */
    virtual void publishSomeSignal2(bool Some_Param) const = 0;
};


} // namespace TbNames
} // namespace Test
