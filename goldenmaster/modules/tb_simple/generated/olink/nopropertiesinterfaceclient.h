
#pragma once

#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/nopropertiesinterface.data.h"

#include "olink/iobjectsink.h"

#include <future>
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
* Adapts the general OLink Client handler to a NoPropertiesInterface publisher in a way it provides access 
* to remote NoPropertiesInterface services. 
* Sends and receives data over the network with ObjectLink protocol, through the communication node. 
* see https://objectlinkprotocol.net for ObjectLink details.
* see https://github.com/apigear-io/objectlink-core-cpp.git for olink client node - abstraction over the network.
* see Apigear::ObjectLink::OLinkConnection for Olink Client Handler implementation.
*     It provides a network implementation and tools to connect NoPropertiesInterfaceClient to it.
* Use on client side to request changes of the NoPropertiesInterface on the server side 
* and to subscribe for the NoPropertiesInterface changes.
*/
class TEST_TB_SIMPLE_EXPORT NoPropertiesInterfaceClient : public INoPropertiesInterface,
    public ApiGear::ObjectLink::IObjectSink
{
public:

    /** ctor */
    explicit NoPropertiesInterfaceClient();
    /** dtor */
    virtual ~NoPropertiesInterfaceClient() = default;
    /**
    * Remote call of INoPropertiesInterface::funcVoid on the NoPropertiesInterface service.
    * Uses funcVoidAsync
    */
    void funcVoid() override;
    /**
    * Remote call of INoPropertiesInterface::funcVoid on the NoPropertiesInterface service.
    */
    std::future<void> funcVoidAsync( std::function<void(void)> callback = nullptr) override;
    /**
    * Remote call of INoPropertiesInterface::funcBool on the NoPropertiesInterface service.
    * Uses funcBoolAsync
    */
    bool funcBool(bool paramBool) override;
    /**
    * Remote call of INoPropertiesInterface::funcBool on the NoPropertiesInterface service.
    */
    std::future<bool> funcBoolAsync(bool paramBool, std::function<void(bool)> callback = nullptr) override;

    /** The publisher to subscribe to. */
    INoPropertiesInterfacePublisher& _getPublisher() const override;
    
    /**
    * Informs if the NoPropertiesInterfaceClient is ready to send and receive messages.
    * @return true if NoPropertiesInterface is operable, false otherwise.
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
    * @param props Initial values obtained from the NoPropertiesInterface service
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
    * @param the data received from NoPropertiesInterface service.
    */
    void applyState(const nlohmann::json& fields);
    /**
    * Applies received property value to local state and publishes changes to subscribers.
    * @param propertyName the name of property to be changed.
    * @param value The value for property.
    */
    void applyProperty(const std::string& propertyName, const nlohmann::json& value);

    /** 
    * An abstraction layer over the connection with service for the NoPropertiesInterfaceClient.
    * Handles incoming and outgoing messages.
    * Is given when object is linked with the service.
    */
    ApiGear::ObjectLink::IClientNode* m_node = nullptr;

    /** The publisher for NoPropertiesInterface */
    std::unique_ptr<INoPropertiesInterfacePublisher> m_publisher;
};
} // namespace olink
} // namespace TbSimple
} // namespace Test
