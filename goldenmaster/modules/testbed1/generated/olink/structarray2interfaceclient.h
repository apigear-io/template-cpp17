
#pragma once

#include "testbed1/generated/api/common.h"
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/core/structarray2interface.data.h"

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
namespace Testbed1 {
namespace olink {
/**
* Adapts the general OLink Client handler to a StructArray2Interface publisher in a way it provides access 
* to remote StructArray2Interface services. 
* Sends and receives data over the network with ObjectLink protocol, through the communication node. 
* see https://objectlinkprotocol.net for ObjectLink details.
* see https://github.com/apigear-io/objectlink-core-cpp.git for olink client node - abstraction over the network.
* see Apigear::ObjectLink::OLinkConnection for Olink Client Handler implementation.
*     It provides a network implementation and tools to connect StructArray2InterfaceClient to it.
* Use on client side to request changes of the StructArray2Interface on the server side
* and to subscribe for the StructArray2Interface changes.
*
* @note Threading: property-change and signal callbacks arrive on the OLink network thread.
* Properties are individually guarded by shared_timed_mutex (concurrent reads allowed,
* exclusive writes). Operation calls are not synchronized by this adapter.
*/
class TEST_TESTBED1_EXPORT StructArray2InterfaceClient : public IStructArray2Interface,
    public ApiGear::ObjectLink::IObjectSink
{
public:

    /** ctor */
    explicit StructArray2InterfaceClient();
    /** dtor */
    virtual ~StructArray2InterfaceClient() = default;
    /**
    * Property getter
    * @return Locally stored locally value for PropBool.
    */
    const StructBoolWithArray& getPropBool() const override;
    /**
    * Request setting a property on the StructArray2Interface service.
    * @param The value to which set request is send for the PropBool.
    */
    void setPropBool(const StructBoolWithArray& propBool) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropInt.
    */
    const StructIntWithArray& getPropInt() const override;
    /**
    * Request setting a property on the StructArray2Interface service.
    * @param The value to which set request is send for the PropInt.
    */
    void setPropInt(const StructIntWithArray& propInt) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropFloat.
    */
    const StructFloatWithArray& getPropFloat() const override;
    /**
    * Request setting a property on the StructArray2Interface service.
    * @param The value to which set request is send for the PropFloat.
    */
    void setPropFloat(const StructFloatWithArray& propFloat) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropString.
    */
    const StructStringWithArray& getPropString() const override;
    /**
    * Request setting a property on the StructArray2Interface service.
    * @param The value to which set request is send for the PropString.
    */
    void setPropString(const StructStringWithArray& propString) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropEnum.
    */
    const StructEnumWithArray& getPropEnum() const override;
    /**
    * Request setting a property on the StructArray2Interface service.
    * @param The value to which set request is send for the PropEnum.
    */
    void setPropEnum(const StructEnumWithArray& propEnum) override;
    /**
    * Remote call of IStructArray2Interface::funcBool on the StructArray2Interface service.
    * Uses funcBoolAsync
    */
    std::list<StructBool> funcBool(const StructBoolWithArray& paramBool) override;
    /**
    * Remote call of IStructArray2Interface::funcBool on the StructArray2Interface service.
    */
    std::future<std::list<StructBool>> funcBoolAsync(const StructBoolWithArray& paramBool, std::function<void(std::list<StructBool>)> callback = nullptr) override;
    /**
    * Remote call of IStructArray2Interface::funcInt on the StructArray2Interface service.
    * Uses funcIntAsync
    */
    std::list<StructInt> funcInt(const StructIntWithArray& paramInt) override;
    /**
    * Remote call of IStructArray2Interface::funcInt on the StructArray2Interface service.
    */
    std::future<std::list<StructInt>> funcIntAsync(const StructIntWithArray& paramInt, std::function<void(std::list<StructInt>)> callback = nullptr) override;
    /**
    * Remote call of IStructArray2Interface::funcFloat on the StructArray2Interface service.
    * Uses funcFloatAsync
    */
    std::list<StructFloat> funcFloat(const StructFloatWithArray& paramFloat) override;
    /**
    * Remote call of IStructArray2Interface::funcFloat on the StructArray2Interface service.
    */
    std::future<std::list<StructFloat>> funcFloatAsync(const StructFloatWithArray& paramFloat, std::function<void(std::list<StructFloat>)> callback = nullptr) override;
    /**
    * Remote call of IStructArray2Interface::funcString on the StructArray2Interface service.
    * Uses funcStringAsync
    */
    std::list<StructString> funcString(const StructStringWithArray& paramString) override;
    /**
    * Remote call of IStructArray2Interface::funcString on the StructArray2Interface service.
    */
    std::future<std::list<StructString>> funcStringAsync(const StructStringWithArray& paramString, std::function<void(std::list<StructString>)> callback = nullptr) override;
    /**
    * Remote call of IStructArray2Interface::funcEnum on the StructArray2Interface service.
    * Uses funcEnumAsync
    */
    std::list<Enum0Enum> funcEnum(const StructEnumWithArray& paramEnum) override;
    /**
    * Remote call of IStructArray2Interface::funcEnum on the StructArray2Interface service.
    */
    std::future<std::list<Enum0Enum>> funcEnumAsync(const StructEnumWithArray& paramEnum, std::function<void(std::list<Enum0Enum>)> callback = nullptr) override;

    /** The publisher to subscribe to. */
    IStructArray2InterfacePublisher& _getPublisher() const override;
    
    /**
    * Informs if the StructArray2InterfaceClient is ready to send and receive messages.
    * @return true if StructArray2Interface is operable, false otherwise.
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
    * @param props Initial values obtained from the StructArray2Interface service
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
    * @param the data received from StructArray2Interface service.
    */
    void applyState(const nlohmann::json& fields);
    /**
    * Applies received property value to local state and publishes changes to subscribers.
    * @param propertyName the name of property to be changed.
    * @param value The value for property.
    */
    void applyProperty(const std::string& propertyName, const nlohmann::json& value);
    /**  Updates local value for PropBool and informs subscriber about the change*/
    void setPropBoolLocal(const StructBoolWithArray& propBool);
    /* Mutex for propBool property */
    mutable std::shared_timed_mutex m_propBoolMutex;
    /**  Updates local value for PropInt and informs subscriber about the change*/
    void setPropIntLocal(const StructIntWithArray& propInt);
    /* Mutex for propInt property */
    mutable std::shared_timed_mutex m_propIntMutex;
    /**  Updates local value for PropFloat and informs subscriber about the change*/
    void setPropFloatLocal(const StructFloatWithArray& propFloat);
    /* Mutex for propFloat property */
    mutable std::shared_timed_mutex m_propFloatMutex;
    /**  Updates local value for PropString and informs subscriber about the change*/
    void setPropStringLocal(const StructStringWithArray& propString);
    /* Mutex for propString property */
    mutable std::shared_timed_mutex m_propStringMutex;
    /**  Updates local value for PropEnum and informs subscriber about the change*/
    void setPropEnumLocal(const StructEnumWithArray& propEnum);
    /* Mutex for propEnum property */
    mutable std::shared_timed_mutex m_propEnumMutex;

    /** Local storage for properties values. */
    StructArray2InterfaceData m_data;

    /** 
    * An abstraction layer over the connection with service for the StructArray2InterfaceClient.
    * Handles incoming and outgoing messages.
    * Is given when object is linked with the service.
    */
    ApiGear::ObjectLink::IClientNode* m_node = nullptr;

    /** The publisher for StructArray2Interface */
    std::unique_ptr<IStructArray2InterfacePublisher> m_publisher;
};
} // namespace olink
} // namespace Testbed1
} // namespace Test
