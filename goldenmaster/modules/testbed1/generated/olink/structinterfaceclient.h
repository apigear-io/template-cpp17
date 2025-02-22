
#pragma once

#include "testbed1/generated/api/common.h"
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/core/structinterface.data.h"

#include "olink/iobjectsink.h"

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
* Adapts the general OLink Client handler to a StructInterface publisher in a way it provides access 
* to remote StructInterface services. 
* Sends and receives data over the network with ObjectLink protocol, through the communication node. 
* see https://objectlinkprotocol.net for ObjectLink details.
* see https://github.com/apigear-io/objectlink-core-cpp.git for olink client node - abstraction over the network.
* see Apigear::ObjectLink::OLinkConnection for Olink Client Handler implementation.
*     It provides a network implementation and tools to connect StructInterfaceClient to it.
* Use on client side to request changes of the StructInterface on the server side 
* and to subscribe for the StructInterface changes.
*/
class TEST_TESTBED1_EXPORT StructInterfaceClient : public IStructInterface,
    public ApiGear::ObjectLink::IObjectSink
{
public:

    /** ctor */
    explicit StructInterfaceClient();
    /** dtor */
    virtual ~StructInterfaceClient() = default;
    /**
    * Property getter
    * @return Locally stored locally value for PropBool.
    */
    const StructBool& getPropBool() const override;
    /**
    * Request setting a property on the StructInterface service.
    * @param The value to which set request is send for the PropBool.
    */
    void setPropBool(const StructBool& propBool) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropInt.
    */
    const StructInt& getPropInt() const override;
    /**
    * Request setting a property on the StructInterface service.
    * @param The value to which set request is send for the PropInt.
    */
    void setPropInt(const StructInt& propInt) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropFloat.
    */
    const StructFloat& getPropFloat() const override;
    /**
    * Request setting a property on the StructInterface service.
    * @param The value to which set request is send for the PropFloat.
    */
    void setPropFloat(const StructFloat& propFloat) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropString.
    */
    const StructString& getPropString() const override;
    /**
    * Request setting a property on the StructInterface service.
    * @param The value to which set request is send for the PropString.
    */
    void setPropString(const StructString& propString) override;
    /**
    * Remote call of IStructInterface::funcBool on the StructInterface service.
    * Uses funcBoolAsync
    */
    StructBool funcBool(const StructBool& paramBool) override;
    /**
    * Remote call of IStructInterface::funcBool on the StructInterface service.
    */
    std::future<StructBool> funcBoolAsync(const StructBool& paramBool, std::function<void(StructBool)> callback = nullptr) override;
    /**
    * Remote call of IStructInterface::funcInt on the StructInterface service.
    * Uses funcIntAsync
    */
    StructInt funcInt(const StructInt& paramInt) override;
    /**
    * Remote call of IStructInterface::funcInt on the StructInterface service.
    */
    std::future<StructInt> funcIntAsync(const StructInt& paramInt, std::function<void(StructInt)> callback = nullptr) override;
    /**
    * Remote call of IStructInterface::funcFloat on the StructInterface service.
    * Uses funcFloatAsync
    */
    StructFloat funcFloat(const StructFloat& paramFloat) override;
    /**
    * Remote call of IStructInterface::funcFloat on the StructInterface service.
    */
    std::future<StructFloat> funcFloatAsync(const StructFloat& paramFloat, std::function<void(StructFloat)> callback = nullptr) override;
    /**
    * Remote call of IStructInterface::funcString on the StructInterface service.
    * Uses funcStringAsync
    */
    StructString funcString(const StructString& paramString) override;
    /**
    * Remote call of IStructInterface::funcString on the StructInterface service.
    */
    std::future<StructString> funcStringAsync(const StructString& paramString, std::function<void(StructString)> callback = nullptr) override;

    /** The publisher to subscribe to. */
    IStructInterfacePublisher& _getPublisher() const override;
    
    /**
    * Informs if the StructInterfaceClient is ready to send and receive messages.
    * @return true if StructInterface is operable, false otherwise.
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
    * @param props Initial values obtained from the StructInterface service
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
    * @param the data received from StructInterface service.
    */
    void applyState(const nlohmann::json& fields);
    /**
    * Applies received property value to local state and publishes changes to subscribers.
    * @param propertyName the name of property to be changed.
    * @param value The value for property.
    */
    void applyProperty(const std::string& propertyName, const nlohmann::json& value);
    /**  Updates local value for PropBool and informs subscriber about the change*/
    void setPropBoolLocal(const StructBool& propBool);
    /* Mutex for propBool property */
    mutable std::shared_timed_mutex m_propBoolMutex;
    /**  Updates local value for PropInt and informs subscriber about the change*/
    void setPropIntLocal(const StructInt& propInt);
    /* Mutex for propInt property */
    mutable std::shared_timed_mutex m_propIntMutex;
    /**  Updates local value for PropFloat and informs subscriber about the change*/
    void setPropFloatLocal(const StructFloat& propFloat);
    /* Mutex for propFloat property */
    mutable std::shared_timed_mutex m_propFloatMutex;
    /**  Updates local value for PropString and informs subscriber about the change*/
    void setPropStringLocal(const StructString& propString);
    /* Mutex for propString property */
    mutable std::shared_timed_mutex m_propStringMutex;

    /** Local storage for properties values. */
    StructInterfaceData m_data;

    /** 
    * An abstraction layer over the connection with service for the StructInterfaceClient.
    * Handles incoming and outgoing messages.
    * Is given when object is linked with the service.
    */
    ApiGear::ObjectLink::IClientNode* m_node = nullptr;

    /** The publisher for StructInterface */
    std::unique_ptr<IStructInterfacePublisher> m_publisher;
};
} // namespace olink
} // namespace Testbed1
} // namespace Test
