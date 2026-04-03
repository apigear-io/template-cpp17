
#pragma once

#include "tb_struct_array/generated/api/common.h"
#include "tb_struct_array/generated/api/tb_struct_array.h"
#include "tb_struct_array/generated/core/structarrayfieldinterface.data.h"

THIRD_PARTY_INCLUDES_START
#include "olink/iobjectsink.h"
THIRD_PARTY_INCLUDES_END

#include <future>
#include <shared_mutex>
#include <memory>

namespace ApiGear{
namespace ObjectLink{
class IClientNode;
}
}

namespace Test {
namespace TbStructArray {
namespace olink {
/**
* Adapts the general OLink Client handler to a StructArrayFieldInterface publisher in a way it provides access 
* to remote StructArrayFieldInterface services. 
* Sends and receives data over the network with ObjectLink protocol, through the communication node. 
* see https://objectlinkprotocol.net for ObjectLink details.
* see https://github.com/apigear-io/objectlink-core-cpp.git for olink client node - abstraction over the network.
* see Apigear::ObjectLink::OLinkConnection for Olink Client Handler implementation.
*     It provides a network implementation and tools to connect StructArrayFieldInterfaceClient to it.
* Use on client side to request changes of the StructArrayFieldInterface on the server side
* and to subscribe for the StructArrayFieldInterface changes.
*
* @note Threading: property-change and signal callbacks arrive on the OLink network thread.
* Properties are individually guarded by shared_timed_mutex (concurrent reads allowed,
* exclusive writes). Operation calls are not synchronized by this adapter.
*/
class TEST_TB_STRUCT_ARRAY_EXPORT StructArrayFieldInterfaceClient : public IStructArrayFieldInterface,
    public ApiGear::ObjectLink::IObjectSink
{
public:

    /** ctor */
    explicit StructArrayFieldInterfaceClient();
    /** dtor */
    virtual ~StructArrayFieldInterfaceClient() = default;
    /**
    * Property getter
    * @return Locally stored locally value for PropStructArray.
    */
    const StructWithArrayOfStructs& getPropStructArray() const override;
    /**
    * Request setting a property on the StructArrayFieldInterface service.
    * @param The value to which set request is send for the PropStructArray.
    */
    void setPropStructArray(const StructWithArrayOfStructs& propStructArray) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropEnumArray.
    */
    const StructWithArrayOfEnums& getPropEnumArray() const override;
    /**
    * Request setting a property on the StructArrayFieldInterface service.
    * @param The value to which set request is send for the PropEnumArray.
    */
    void setPropEnumArray(const StructWithArrayOfEnums& propEnumArray) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropIntArray.
    */
    const StructWithArrayOfInts& getPropIntArray() const override;
    /**
    * Request setting a property on the StructArrayFieldInterface service.
    * @param The value to which set request is send for the PropIntArray.
    */
    void setPropIntArray(const StructWithArrayOfInts& propIntArray) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropMixed.
    */
    const MixedStruct& getPropMixed() const override;
    /**
    * Request setting a property on the StructArrayFieldInterface service.
    * @param The value to which set request is send for the PropMixed.
    */
    void setPropMixed(const MixedStruct& propMixed) override;
    /**
    * Remote call of IStructArrayFieldInterface::funcMixed on the StructArrayFieldInterface service.
    * Uses funcMixedAsync
    */
    MixedStruct funcMixed(const MixedStruct& paramMixed) override;
    /**
    * Remote call of IStructArrayFieldInterface::funcMixed on the StructArrayFieldInterface service.
    */
    std::future<MixedStruct> funcMixedAsync(const MixedStruct& paramMixed, std::function<void(MixedStruct)> callback = nullptr) override;
    /**
    * Remote call of IStructArrayFieldInterface::funcStructArray on the StructArrayFieldInterface service.
    * Uses funcStructArrayAsync
    */
    StructWithArrayOfStructs funcStructArray(const StructWithArrayOfStructs& paramPoints) override;
    /**
    * Remote call of IStructArrayFieldInterface::funcStructArray on the StructArrayFieldInterface service.
    */
    std::future<StructWithArrayOfStructs> funcStructArrayAsync(const StructWithArrayOfStructs& paramPoints, std::function<void(StructWithArrayOfStructs)> callback = nullptr) override;

    /** The publisher to subscribe to. */
    IStructArrayFieldInterfacePublisher& _getPublisher() const override;
    
    /**
    * Informs if the StructArrayFieldInterfaceClient is ready to send and receive messages.
    * @return true if StructArrayFieldInterface is operable, false otherwise.
    */
    bool isReady() const;

    /**
    * The name of the object for which this sink is created, object on server side has to have the same name.
    * It serves as an identifier for the client registry, it has to be unique for the pair sink object - client node.
    * Passed in the olink messages as an object identifier.
    */
    std::string olinkObjectName() override;
    
    /**
    * Information about signal emission on a server side to all subscribers.
    * @param signalId Unique identifier for the signal emitted from object.
    * @param args The arguments for the signal.
    */
    void olinkOnSignal(const std::string& signalId, const nlohmann::json& args) override;
    
    /**
    * Applies the information about the property changed on server side.
    * @param propertyId Unique identifier of a changed property in object .
    * @param value The value of the property.
    */
    void olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value) override;
    
    /** Informs this object sink that connection was is established.
    * @param interfaceId The name of the object for which link was established.
    * @param props Initial values obtained from the StructArrayFieldInterface service
    * @param the initialized link endpoint for this sink.
    */
    void olinkOnInit(const std::string& interfaceId, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node) override;
    /**
    * Informs this object source that the link was disconnected and cannot be used anymore.
    */
    void olinkOnRelease() override;

private:
    /**
    * Applies received data to local state and publishes changes to subscribers.
    * @param the data received from StructArrayFieldInterface service.
    */
    void applyState(const nlohmann::json& fields);
    /**
    * Applies received property value to local state and publishes changes to subscribers.
    * @param propertyName the name of property to be changed.
    * @param value The value for property.
    */
    void applyProperty(const std::string& propertyName, const nlohmann::json& value);
    /**  Updates local value for PropStructArray and informs subscriber about the change*/
    void setPropStructArrayLocal(const StructWithArrayOfStructs& propStructArray);
    /* Mutex for propStructArray property */
    mutable std::shared_timed_mutex m_propStructArrayMutex;
    /**  Updates local value for PropEnumArray and informs subscriber about the change*/
    void setPropEnumArrayLocal(const StructWithArrayOfEnums& propEnumArray);
    /* Mutex for propEnumArray property */
    mutable std::shared_timed_mutex m_propEnumArrayMutex;
    /**  Updates local value for PropIntArray and informs subscriber about the change*/
    void setPropIntArrayLocal(const StructWithArrayOfInts& propIntArray);
    /* Mutex for propIntArray property */
    mutable std::shared_timed_mutex m_propIntArrayMutex;
    /**  Updates local value for PropMixed and informs subscriber about the change*/
    void setPropMixedLocal(const MixedStruct& propMixed);
    /* Mutex for propMixed property */
    mutable std::shared_timed_mutex m_propMixedMutex;

    /** Local storage for properties values. */
    StructArrayFieldInterfaceData m_data;

    /** 
    * An abstraction layer over the connection with service for the StructArrayFieldInterfaceClient.
    * Handles incoming and outgoing messages.
    * Is given when object is linked with the service.
    */
    ApiGear::ObjectLink::IClientNode* m_node = nullptr;

    /** The publisher for StructArrayFieldInterface */
    std::unique_ptr<IStructArrayFieldInterfacePublisher> m_publisher;
};
} // namespace olink
} // namespace TbStructArray
} // namespace Test
