
#pragma once

#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/nosignalsinterface.data.h"

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
namespace TbSimple {
namespace olink {
/**
* Adapts the general OLink Client handler to a NoSignalsInterface publisher in a way it provides access 
* to remote NoSignalsInterface services. 
* Sends and receives data over the network with ObjectLink protocol, through the communication node. 
* see https://objectlinkprotocol.net for ObjectLink details.
* see https://github.com/apigear-io/objectlink-core-cpp.git for olink client node - abstraction over the network.
* see Apigear::ObjectLink::OLinkConnection for Olink Client Handler implementation.
*     It provides a network implementation and tools to connect NoSignalsInterfaceClient to it.
* Use on client side to request changes of the NoSignalsInterface on the server side 
* and to subscribe for the NoSignalsInterface changes.
*/
class TEST_TB_SIMPLE_EXPORT NoSignalsInterfaceClient : public INoSignalsInterface,
    public ApiGear::ObjectLink::IObjectSink
{
public:

    /** ctor */
    explicit NoSignalsInterfaceClient();
    /** dtor */
    virtual ~NoSignalsInterfaceClient() = default;
    /**
    * Property getter
    * @return Locally stored locally value for PropBool.
    */
    bool getPropBool() const override;
    /**
    * Request setting a property on the NoSignalsInterface service.
    * @param The value to which set request is send for the PropBool.
    */
    void setPropBool(bool propBool) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropInt.
    */
    int getPropInt() const override;
    /**
    * Request setting a property on the NoSignalsInterface service.
    * @param The value to which set request is send for the PropInt.
    */
    void setPropInt(int propInt) override;
    /**
    * Remote call of INoSignalsInterface::funcVoid on the NoSignalsInterface service.
    * Uses funcVoidAsync
    */
    void funcVoid() override;
    /**
    * Remote call of INoSignalsInterface::funcVoid on the NoSignalsInterface service.
    */
    std::future<void> funcVoidAsync() override;
    /**
    * Remote call of INoSignalsInterface::funcBool on the NoSignalsInterface service.
    * Uses funcBoolAsync
    */
    bool funcBool(bool paramBool) override;
    /**
    * Remote call of INoSignalsInterface::funcBool on the NoSignalsInterface service.
    */
    std::future<bool> funcBoolAsync(bool paramBool) override;

    /** The publisher to subscribe to. */
    INoSignalsInterfacePublisher& _getPublisher() const override;
    
    /**
    * Informs if the NoSignalsInterfaceClient is ready to send and receive messages.
    * @return true if NoSignalsInterface is operable, false otherwise.
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
    * @param props Initial values obtained from the NoSignalsInterface service
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
    * @param the data received from NoSignalsInterface service.
    */
    void applyState(const nlohmann::json& fields);
    /**
    * Applies received property value to local state and publishes changes to subscribers.
    * @param propertyName the name of property to be changed.
    * @param value The value for property.
    */
    void applyProperty(const std::string& propertyName, const nlohmann::json& value);
    /**  Updates local value for PropBool and informs subscriber about the change*/
    void setPropBoolLocal(bool propBool);
    /* Mutex for propBool property */
    mutable std::shared_timed_mutex m_propBoolMutex;
    /**  Updates local value for PropInt and informs subscriber about the change*/
    void setPropIntLocal(int propInt);
    /* Mutex for propInt property */
    mutable std::shared_timed_mutex m_propIntMutex;

    /** Local storage for properties values. */
    NoSignalsInterfaceData m_data;

    /** 
    * An abstraction layer over the connection with service for the NoSignalsInterfaceClient.
    * Handles incoming and outgoing messages.
    * Is given when object is linked with the service.
    */
    ApiGear::ObjectLink::IClientNode* m_node = nullptr;

    /** The publisher for NoSignalsInterface */
    std::unique_ptr<INoSignalsInterfacePublisher> m_publisher;
};
} // namespace olink
} // namespace TbSimple
} // namespace Test
