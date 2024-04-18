
#pragma once

#include "tb_same2/generated/api/common.h"
#include "tb_same2/generated/api/tb_same2.h"
#include "tb_same2/generated/core/sameenum1interface.data.h"

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
namespace TbSame2 {
namespace olink {
/**
* Adapts the general OLink Client handler to a SameEnum1Interface publisher in a way it provides access 
* to remote SameEnum1Interface services. 
* Sends and receives data over the network with ObjectLink protocol, through the communication node. 
* see https://objectlinkprotocol.net for ObjectLink details.
* see https://github.com/apigear-io/objectlink-core-cpp.git for olink client node - abstraction over the network.
* see Apigear::ObjectLink::OLinkConnection for Olink Client Handler implementation.
*     It provides a network implementation and tools to connect SameEnum1InterfaceClient to it.
* Use on client side to request changes of the SameEnum1Interface on the server side 
* and to subscribe for the SameEnum1Interface changes.
*/
class TEST_TB_SAME2_EXPORT SameEnum1InterfaceClient : public ISameEnum1Interface,
    public ApiGear::ObjectLink::IObjectSink
{
public:

    /** ctor */
    explicit SameEnum1InterfaceClient();
    /** dtor */
    virtual ~SameEnum1InterfaceClient() = default;
    /**
    * Property getter
    * @return Locally stored locally value for Prop1.
    */
    Enum1Enum getProp1() const override;
    /**
    * Request setting a property on the SameEnum1Interface service.
    * @param The value to which set request is send for the Prop1.
    */
    void setProp1(Enum1Enum prop1) override;
    /**
    * Remote call of ISameEnum1Interface::func1 on the SameEnum1Interface service.
    * Uses func1Async
    */
    Enum1Enum func1(Enum1Enum param1) override;
    /**
    * Remote call of ISameEnum1Interface::func1 on the SameEnum1Interface service.
    */
    std::future<Enum1Enum> func1Async(Enum1Enum param1) override;

    /** The publisher to subscribe to. */
    ISameEnum1InterfacePublisher& _getPublisher() const override;
    
    /**
    * Informs if the SameEnum1InterfaceClient is ready to send and receive messages.
    * @return true if SameEnum1Interface is operable, false otherwise.
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
    * @param props Initial values obtained from the SameEnum1Interface service
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
    * @param the data received from SameEnum1Interface service.
    */
    void applyState(const nlohmann::json& fields);
    /**
    * Applies received property value to local state and publishes changes to subscribers.
    * @param propertyName the name of property to be changed.
    * @param value The value for property.
    */
    void applyProperty(const std::string& propertyName, const nlohmann::json& value);
    /**  Updates local value for Prop1 and informs subscriber about the change*/
    void setProp1Local(Enum1Enum prop1);
    /* Mutex for prop1 property */
    mutable std::shared_timed_mutex m_prop1Mutex;

    /** Local storage for properties values. */
    SameEnum1InterfaceData m_data;

    /** 
    * An abstraction layer over the connection with service for the SameEnum1InterfaceClient.
    * Handles incoming and outgoing messages.
    * Is given when object is linked with the service.
    */
    ApiGear::ObjectLink::IClientNode* m_node = nullptr;

    /** The publisher for SameEnum1Interface */
    std::unique_ptr<ISameEnum1InterfacePublisher> m_publisher;
};
} // namespace olink
} // namespace TbSame2
} // namespace Test
