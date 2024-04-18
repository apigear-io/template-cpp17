
#pragma once

#include "tb_same1/generated/api/common.h"
#include "tb_same1/generated/api/tb_same1.h"
#include "tb_same1/generated/core/sameenum2interface.data.h"

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
namespace TbSame1 {
namespace olink {
/**
* Adapts the general OLink Client handler to a SameEnum2Interface publisher in a way it provides access 
* to remote SameEnum2Interface services. 
* Sends and receives data over the network with ObjectLink protocol, through the communication node. 
* see https://objectlinkprotocol.net for ObjectLink details.
* see https://github.com/apigear-io/objectlink-core-cpp.git for olink client node - abstraction over the network.
* see Apigear::ObjectLink::OLinkConnection for Olink Client Handler implementation.
*     It provides a network implementation and tools to connect SameEnum2InterfaceClient to it.
* Use on client side to request changes of the SameEnum2Interface on the server side 
* and to subscribe for the SameEnum2Interface changes.
*/
class TEST_TB_SAME1_EXPORT SameEnum2InterfaceClient : public ISameEnum2Interface,
    public ApiGear::ObjectLink::IObjectSink
{
public:

    /** ctor */
    explicit SameEnum2InterfaceClient();
    /** dtor */
    virtual ~SameEnum2InterfaceClient() = default;
    /**
    * Property getter
    * @return Locally stored locally value for Prop1.
    */
    Enum1Enum getProp1() const override;
    /**
    * Request setting a property on the SameEnum2Interface service.
    * @param The value to which set request is send for the Prop1.
    */
    void setProp1(Enum1Enum prop1) override;
    /**
    * Property getter
    * @return Locally stored locally value for Prop2.
    */
    Enum2Enum getProp2() const override;
    /**
    * Request setting a property on the SameEnum2Interface service.
    * @param The value to which set request is send for the Prop2.
    */
    void setProp2(Enum2Enum prop2) override;
    /**
    * Remote call of ISameEnum2Interface::func1 on the SameEnum2Interface service.
    * Uses func1Async
    */
    Enum1Enum func1(Enum1Enum param1) override;
    /**
    * Remote call of ISameEnum2Interface::func1 on the SameEnum2Interface service.
    */
    std::future<Enum1Enum> func1Async(Enum1Enum param1) override;
    /**
    * Remote call of ISameEnum2Interface::func2 on the SameEnum2Interface service.
    * Uses func2Async
    */
    Enum1Enum func2(Enum1Enum param1, Enum2Enum param2) override;
    /**
    * Remote call of ISameEnum2Interface::func2 on the SameEnum2Interface service.
    */
    std::future<Enum1Enum> func2Async(Enum1Enum param1, Enum2Enum param2) override;

    /** The publisher to subscribe to. */
    ISameEnum2InterfacePublisher& _getPublisher() const override;
    
    /**
    * Informs if the SameEnum2InterfaceClient is ready to send and receive messages.
    * @return true if SameEnum2Interface is operable, false otherwise.
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
    * @param props Initial values obtained from the SameEnum2Interface service
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
    * @param the data received from SameEnum2Interface service.
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
    /**  Updates local value for Prop2 and informs subscriber about the change*/
    void setProp2Local(Enum2Enum prop2);
    /* Mutex for prop2 property */
    mutable std::shared_timed_mutex m_prop2Mutex;

    /** Local storage for properties values. */
    SameEnum2InterfaceData m_data;

    /** 
    * An abstraction layer over the connection with service for the SameEnum2InterfaceClient.
    * Handles incoming and outgoing messages.
    * Is given when object is linked with the service.
    */
    ApiGear::ObjectLink::IClientNode* m_node = nullptr;

    /** The publisher for SameEnum2Interface */
    std::unique_ptr<ISameEnum2InterfacePublisher> m_publisher;
};
} // namespace olink
} // namespace TbSame1
} // namespace Test
