
#pragma once

#include "testbed2/generated/api/common.h"
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/core/nestedstruct3interface.data.h"

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
namespace Testbed2 {
namespace olink {
/**
* Adapts the general OLink Client handler to a NestedStruct3Interface publisher in a way it provides access 
* to remote NestedStruct3Interface services. 
* Sends and receives data over the network with ObjectLink protocol, through the communication node. 
* see https://objectlinkprotocol.net for ObjectLink details.
* see https://github.com/apigear-io/objectlink-core-cpp.git for olink client node - abstraction over the network.
* see Apigear::ObjectLink::OLinkConnection for Olink Client Handler implementation.
*     It provides a network implementation and tools to connect NestedStruct3InterfaceClient to it.
* Use on client side to request changes of the NestedStruct3Interface on the server side 
* and to subscribe for the NestedStruct3Interface changes.
*/
class TEST_TESTBED2_EXPORT NestedStruct3InterfaceClient : public INestedStruct3Interface,
    public ApiGear::ObjectLink::IObjectSink
{
public:

    /** ctor */
    explicit NestedStruct3InterfaceClient();
    /** dtor */
    virtual ~NestedStruct3InterfaceClient() = default;
    /**
    * Property getter
    * @return Locally stored locally value for Prop1.
    */
    const NestedStruct1& getProp1() const override;
    /**
    * Request setting a property on the NestedStruct3Interface service.
    * @param The value to which set request is send for the Prop1.
    */
    void setProp1(const NestedStruct1& prop1) override;
    /**
    * Property getter
    * @return Locally stored locally value for Prop2.
    */
    const NestedStruct2& getProp2() const override;
    /**
    * Request setting a property on the NestedStruct3Interface service.
    * @param The value to which set request is send for the Prop2.
    */
    void setProp2(const NestedStruct2& prop2) override;
    /**
    * Property getter
    * @return Locally stored locally value for Prop3.
    */
    const NestedStruct3& getProp3() const override;
    /**
    * Request setting a property on the NestedStruct3Interface service.
    * @param The value to which set request is send for the Prop3.
    */
    void setProp3(const NestedStruct3& prop3) override;
    /**
    * Remote call of INestedStruct3Interface::func1 on the NestedStruct3Interface service.
    * Uses func1Async
    */
    NestedStruct1 func1(const NestedStruct1& param1) override;
    /**
    * Remote call of INestedStruct3Interface::func1 on the NestedStruct3Interface service.
    */
    std::future<NestedStruct1> func1Async(const NestedStruct1& param1) override;
    /**
    * Remote call of INestedStruct3Interface::func2 on the NestedStruct3Interface service.
    * Uses func2Async
    */
    NestedStruct1 func2(const NestedStruct1& param1, const NestedStruct2& param2) override;
    /**
    * Remote call of INestedStruct3Interface::func2 on the NestedStruct3Interface service.
    */
    std::future<NestedStruct1> func2Async(const NestedStruct1& param1, const NestedStruct2& param2) override;
    /**
    * Remote call of INestedStruct3Interface::func3 on the NestedStruct3Interface service.
    * Uses func3Async
    */
    NestedStruct1 func3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3) override;
    /**
    * Remote call of INestedStruct3Interface::func3 on the NestedStruct3Interface service.
    */
    std::future<NestedStruct1> func3Async(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3) override;

    /** The publisher to subscribe to. */
    INestedStruct3InterfacePublisher& _getPublisher() const override;
    
    /**
    * Informs if the NestedStruct3InterfaceClient is ready to send and receive messages.
    * @return true if NestedStruct3Interface is operable, false otherwise.
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
    * @param props Initial values obtained from the NestedStruct3Interface service
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
    * @param the data received from NestedStruct3Interface service.
    */
    void applyState(const nlohmann::json& fields);
    /**
    * Applies received property value to local state and publishes changes to subscribers.
    * @param propertyName the name of property to be changed.
    * @param value The value for property.
    */
    void applyProperty(const std::string& propertyName, const nlohmann::json& value);
    /**  Updates local value for Prop1 and informs subscriber about the change*/
    void setProp1Local(const NestedStruct1& prop1);
    /* Mutex for prop1 property */
    mutable std::shared_timed_mutex m_prop1Mutex;
    /**  Updates local value for Prop2 and informs subscriber about the change*/
    void setProp2Local(const NestedStruct2& prop2);
    /* Mutex for prop2 property */
    mutable std::shared_timed_mutex m_prop2Mutex;
    /**  Updates local value for Prop3 and informs subscriber about the change*/
    void setProp3Local(const NestedStruct3& prop3);
    /* Mutex for prop3 property */
    mutable std::shared_timed_mutex m_prop3Mutex;

    /** Local storage for properties values. */
    NestedStruct3InterfaceData m_data;

    /** 
    * An abstraction layer over the connection with service for the NestedStruct3InterfaceClient.
    * Handles incoming and outgoing messages.
    * Is given when object is linked with the service.
    */
    ApiGear::ObjectLink::IClientNode* m_node = nullptr;

    /** The publisher for NestedStruct3Interface */
    std::unique_ptr<INestedStruct3InterfacePublisher> m_publisher;
};
} // namespace olink
} // namespace Testbed2
} // namespace Test
