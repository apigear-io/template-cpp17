#pragma once

#include <cstdint>
#include <future>
#include "tb_struct_array/generated/api/common.h"
#include "tb_struct_array/generated/api/datastructs.api.h"

namespace Test {
namespace TbStructArray {

class IStructArrayFieldInterfaceSubscriber;
class IStructArrayFieldInterfacePublisher;

/**
*
* IStructArrayFieldInterface provides an interface for
 *  - methods defined for your StructArrayFieldInterface 
 *  - property setters and getters for defined properties
 * The IStructArrayFieldInterface also provides an interface to access a publisher IStructArrayFieldInterfacePublisher, a class used by IStructArrayFieldInterfaceSubscriber clients.
 * The implementation should notify the publisher IStructArrayFieldInterfacePublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also IStructArrayFieldInterfaceSubscriber, IStructArrayFieldInterfacePublisher
 * and the example implementation StructArrayFieldInterface  or the
 */
class TEST_TB_STRUCT_ARRAY_EXPORT IStructArrayFieldInterface
{
public:
    virtual ~IStructArrayFieldInterface() = default;


    virtual MixedStruct funcMixed(const MixedStruct& paramMixed) = 0;
    /**
    * Asynchronous version of funcMixed(const MixedStruct& paramMixed)
    * @return Promise of type MixedStruct which is set once the function has completed
    */
    virtual std::future<MixedStruct> funcMixedAsync(const MixedStruct& paramMixed, std::function<void(MixedStruct)> callback = nullptr) = 0;


    virtual StructWithArrayOfStructs funcStructArray(const StructWithArrayOfStructs& paramPoints) = 0;
    /**
    * Asynchronous version of funcStructArray(const StructWithArrayOfStructs& paramPoints)
    * @return Promise of type StructWithArrayOfStructs which is set once the function has completed
    */
    virtual std::future<StructWithArrayOfStructs> funcStructArrayAsync(const StructWithArrayOfStructs& paramPoints, std::function<void(StructWithArrayOfStructs)> callback = nullptr) = 0;

    /**
    * Sets the value of the propStructArray property.
    */
    virtual void setPropStructArray(const StructWithArrayOfStructs& propStructArray) = 0;
    /**
    * Gets the value of the propStructArray property.
    */
    virtual const StructWithArrayOfStructs& getPropStructArray() const = 0;

    /**
    * Sets the value of the propEnumArray property.
    */
    virtual void setPropEnumArray(const StructWithArrayOfEnums& propEnumArray) = 0;
    /**
    * Gets the value of the propEnumArray property.
    */
    virtual const StructWithArrayOfEnums& getPropEnumArray() const = 0;

    /**
    * Sets the value of the propIntArray property.
    */
    virtual void setPropIntArray(const StructWithArrayOfInts& propIntArray) = 0;
    /**
    * Gets the value of the propIntArray property.
    */
    virtual const StructWithArrayOfInts& getPropIntArray() const = 0;

    /**
    * Sets the value of the propMixed property.
    */
    virtual void setPropMixed(const MixedStruct& propMixed) = 0;
    /**
    * Gets the value of the propMixed property.
    */
    virtual const MixedStruct& getPropMixed() const = 0;

    /**
    * Access to a publisher, use it to subscribe for StructArrayFieldInterface changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for StructArrayFieldInterface.
    */
    virtual IStructArrayFieldInterfacePublisher& _getPublisher() const = 0;
};


/**
 * The IStructArrayFieldInterfaceSubscriber contains functions to allow informing about signals or property changes of the IStructArrayFieldInterface implementation.
 * The implementation for IStructArrayFieldInterface should provide mechanism for subscription of the IStructArrayFieldInterfaceSubscriber clients.
 * See IStructArrayFieldInterfacePublisher, which provides facilitation for this purpose.
 * The implementation for IStructArrayFieldInterface should call the IStructArrayFieldInterfaceSubscriber interface functions on either signal emit or property change.
 * You can use IStructArrayFieldInterfaceSubscriber class to implement clients of the IStructArrayFieldInterface or the network adapter - see Olink Server and Client example.
 */
class TEST_TB_STRUCT_ARRAY_EXPORT IStructArrayFieldInterfaceSubscriber
{
public:
    virtual ~IStructArrayFieldInterfaceSubscriber() = default;
    /**
    * Called by the IStructArrayFieldInterfacePublisher when the StructArrayFieldInterface emits sigMixed, if subscribed for the sigMixed.
    * @param paramMixed 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigMixed(const MixedStruct& paramMixed) = 0;
    /**
    * Called by the IStructArrayFieldInterfacePublisher when the StructArrayFieldInterface emits sigStructArray, if subscribed for the sigStructArray.
    * @param paramPoints 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigStructArray(const StructWithArrayOfStructs& paramPoints) = 0;
    /**
    * Called by the IStructArrayFieldInterfacePublisher when propStructArray value has changed if subscribed for the propStructArray change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropStructArrayChanged(const StructWithArrayOfStructs& propStructArray) = 0;
    /**
    * Called by the IStructArrayFieldInterfacePublisher when propEnumArray value has changed if subscribed for the propEnumArray change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropEnumArrayChanged(const StructWithArrayOfEnums& propEnumArray) = 0;
    /**
    * Called by the IStructArrayFieldInterfacePublisher when propIntArray value has changed if subscribed for the propIntArray change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropIntArrayChanged(const StructWithArrayOfInts& propIntArray) = 0;
    /**
    * Called by the IStructArrayFieldInterfacePublisher when propMixed value has changed if subscribed for the propMixed change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropMixedChanged(const MixedStruct& propMixed) = 0;
};

/** Callback for changes of propStructArray */
using StructArrayFieldInterfacePropStructArrayPropertyCb = std::function<void(const StructWithArrayOfStructs& propStructArray)>;
/** Callback for changes of propEnumArray */
using StructArrayFieldInterfacePropEnumArrayPropertyCb = std::function<void(const StructWithArrayOfEnums& propEnumArray)>;
/** Callback for changes of propIntArray */
using StructArrayFieldInterfacePropIntArrayPropertyCb = std::function<void(const StructWithArrayOfInts& propIntArray)>;
/** Callback for changes of propMixed */
using StructArrayFieldInterfacePropMixedPropertyCb = std::function<void(const MixedStruct& propMixed)>;
/** Callback for sigMixed signal triggers */
using StructArrayFieldInterfaceSigMixedSignalCb = std::function<void(const MixedStruct& paramMixed)> ;
/** Callback for sigStructArray signal triggers */
using StructArrayFieldInterfaceSigStructArraySignalCb = std::function<void(const StructWithArrayOfStructs& paramPoints)> ;


/**
 * The IStructArrayFieldInterfacePublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your IStructArrayFieldInterface implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a IStructArrayFieldInterfaceSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IIStructArrayFieldInterface on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class TEST_TB_STRUCT_ARRAY_EXPORT IStructArrayFieldInterfacePublisher
{
public:
    virtual ~IStructArrayFieldInterfacePublisher() = default;

    /**
    * Use this function to subscribe for any change of the StructArrayFieldInterface.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param IStructArrayFieldInterfaceSubscriber which is subscribed in this function to any change of the StructArrayFieldInterface.
    */
    virtual void subscribeToAllChanges(IStructArrayFieldInterfaceSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the StructArrayFieldInterface.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param IStructArrayFieldInterfaceSubscriber which subscription for any change of the StructArrayFieldInterface is removed.
    */
    virtual void unsubscribeFromAllChanges(IStructArrayFieldInterfaceSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for propStructArray value changes.
    * If your subscriber uses subscription with IStructArrayFieldInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructArrayFieldInterfacePropStructArrayPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToPropStructArrayChanged(StructArrayFieldInterfacePropStructArrayPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propStructArray property changes.
    * If your subscriber uses subscription with IStructArrayFieldInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropStructArrayChanged(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for propEnumArray value changes.
    * If your subscriber uses subscription with IStructArrayFieldInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructArrayFieldInterfacePropEnumArrayPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToPropEnumArrayChanged(StructArrayFieldInterfacePropEnumArrayPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propEnumArray property changes.
    * If your subscriber uses subscription with IStructArrayFieldInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropEnumArrayChanged(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for propIntArray value changes.
    * If your subscriber uses subscription with IStructArrayFieldInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructArrayFieldInterfacePropIntArrayPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToPropIntArrayChanged(StructArrayFieldInterfacePropIntArrayPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propIntArray property changes.
    * If your subscriber uses subscription with IStructArrayFieldInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropIntArrayChanged(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for propMixed value changes.
    * If your subscriber uses subscription with IStructArrayFieldInterfaceSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param StructArrayFieldInterfacePropMixedPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToPropMixedChanged(StructArrayFieldInterfacePropMixedPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propMixed property changes.
    * If your subscriber uses subscription with IStructArrayFieldInterfaceSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropMixedChanged(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for sigMixed signal changes.
    * @param StructArrayFieldInterfaceSigMixedSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToSigMixed(StructArrayFieldInterfaceSigMixedSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigMixed signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigMixed(uint64_t handleId) = 0;

    /**
    * Use this function to subscribe for sigStructArray signal changes.
    * @param StructArrayFieldInterfaceSigStructArraySignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual uint64_t subscribeToSigStructArray(StructArrayFieldInterfaceSigStructArraySignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigStructArray signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigStructArray(uint64_t handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructArrayFieldInterface implementation when property propStructArray changes.
    * @param The new value of propStructArray.
    */
    virtual void publishPropStructArrayChanged(const StructWithArrayOfStructs& propStructArray) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructArrayFieldInterface implementation when property propEnumArray changes.
    * @param The new value of propEnumArray.
    */
    virtual void publishPropEnumArrayChanged(const StructWithArrayOfEnums& propEnumArray) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructArrayFieldInterface implementation when property propIntArray changes.
    * @param The new value of propIntArray.
    */
    virtual void publishPropIntArrayChanged(const StructWithArrayOfInts& propIntArray) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the StructArrayFieldInterface implementation when property propMixed changes.
    * @param The new value of propMixed.
    */
    virtual void publishPropMixedChanged(const MixedStruct& propMixed) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the StructArrayFieldInterface implementation when sigMixed is emitted.
    * @param paramMixed 
    */
    virtual void publishSigMixed(const MixedStruct& paramMixed) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the StructArrayFieldInterface implementation when sigStructArray is emitted.
    * @param paramPoints 
    */
    virtual void publishSigStructArray(const StructWithArrayOfStructs& paramPoints) const = 0;
};


} // namespace TbStructArray
} // namespace Test
