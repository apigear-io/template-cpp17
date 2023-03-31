
#pragma once

#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/nooperationsinterface.data.h"

#include "apigear/olink/iolinkconnector.h"
#include "apigear/utilities/logger.h"
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
* Adapts the general OLink Client handler to a NoOperationsInterface publisher in a way it provides access 
* to remote NoOperationsInterface services. 
* Sends and receives data over the network with ObjectLink protocol, through the communication node. 
* see https://objectlinkprotocol.net for ObjectLink details.
* see https://github.com/apigear-io/objectlink-core-cpp.git for olink client node - abstraction over the network.
* see Apigear::ObjectLink::OLinkConnection for Olink Client Handler implementation.
*     It provides a network implementation and tools to connect NoOperationsInterfaceClient to it.
* Use on client side to request changes of the NoOperationsInterface on the server side 
* and to subscribe for the NoOperationsInterface changes.
*/
class TEST_TB_SIMPLE_EXPORT NoOperationsInterfaceClient : public INoOperationsInterface,
    public ApiGear::ObjectLink::IObjectSink
{
public:

    /** ctor */
    explicit NoOperationsInterfaceClient();
    /** dtor */
    virtual ~NoOperationsInterfaceClient() = default;
    /**
    * Property getter
    * @return Locally stored locally value for PropBool.
    */
    bool getPropBool() const override;
    /**
    * Request setting a property on the NoOperationsInterface service.
    * @param The value to which set request is send for the PropBool.
    */
    void setPropBool(bool propBool) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropInt.
    */
    int getPropInt() const override;
    /**
    * Request setting a property on the NoOperationsInterface service.
    * @param The value to which set request is send for the PropInt.
    */
    void setPropInt(int propInt) override;

    /** The publisher to subscribe to. */
    INoOperationsInterfacePublisher& _getPublisher() const override;
    
    /**
    * Informs if the NoOperationsInterfaceClient is ready to send and receive messages.
    * @return true if NoOperationsInterface is operable, false otherwise.
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
    * @param props Initial values obtained from the NoOperationsInterface service
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
    * @param the data received from NoOperationsInterface service.
    */
    void applyState(const nlohmann::json& fields);
    /**  Updates local value for PropBool and informs subscriber about the change*/
    void setPropBoolLocal(bool propBool);
    /**  Updates local value for PropInt and informs subscriber about the change*/
    void setPropIntLocal(int propInt);

    /** Local storage for properties values. */
    NoOperationsInterfaceData m_data;

    /** 
    * An abstraction layer over the connection with service for the NoOperationsInterfaceClient.
    * Handles incoming and outgoing messages.
    * Is given when object is linked with the service.
    */
    ApiGear::ObjectLink::IClientNode* m_node = nullptr;

    /** The publisher for NoOperationsInterface */
    std::unique_ptr<INoOperationsInterfacePublisher> m_publisher;

    /** The logger */
    std::unique_ptr<ApiGear::Utilities::Logger> m_logger;
};
} // namespace olink
} // namespace TbSimple
} // namespace Test
