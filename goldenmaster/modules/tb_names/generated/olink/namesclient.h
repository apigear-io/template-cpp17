
#pragma once

#include "tb_names/generated/api/common.h"
#include "tb_names/generated/api/tb_names.h"
#include "tb_names/generated/core/names.data.h"

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
namespace TbNames {
namespace olink {
/**
* Adapts the general OLink Client handler to a Nam_Es publisher in a way it provides access 
* to remote Nam_Es services. 
* Sends and receives data over the network with ObjectLink protocol, through the communication node. 
* see https://objectlinkprotocol.net for ObjectLink details.
* see https://github.com/apigear-io/objectlink-core-cpp.git for olink client node - abstraction over the network.
* see Apigear::ObjectLink::OLinkConnection for Olink Client Handler implementation.
*     It provides a network implementation and tools to connect Nam_EsClient to it.
* Use on client side to request changes of the Nam_Es on the server side 
* and to subscribe for the Nam_Es changes.
*/
class TEST_TB_NAMES_EXPORT Nam_EsClient : public INamEs,
    public ApiGear::ObjectLink::IObjectSink
{
public:

    /** ctor */
    explicit Nam_EsClient();
    /** dtor */
    virtual ~Nam_EsClient() = default;
    /**
    * Property getter
    * @return Locally stored locally value for Switch.
    */
    bool getSwitch() const override;
    /**
    * Request setting a property on the Nam_Es service.
    * @param The value to which set request is send for the Switch.
    */
    void setSwitch(bool Switch) override;
    /**
    * Property getter
    * @return Locally stored locally value for SomeProperty.
    */
    int getSomeProperty() const override;
    /**
    * Request setting a property on the Nam_Es service.
    * @param The value to which set request is send for the SomeProperty.
    */
    void setSomeProperty(int SOME_PROPERTY) override;
    /**
    * Property getter
    * @return Locally stored locally value for SomePoperty2.
    */
    int getSomePoperty2() const override;
    /**
    * Request setting a property on the Nam_Es service.
    * @param The value to which set request is send for the SomePoperty2.
    */
    void setSomePoperty2(int Some_Poperty2) override;
    /**
    * Remote call of INamEs::SOME_FUNCTION on the Nam_Es service.
    * Uses SOME_FUNCTIONAsync
    */
    void sOME_FUNCTION(bool SOME_PARAM) override;
    /**
    * Remote call of INamEs::SOME_FUNCTION on the Nam_Es service.
    */
    std::future<void> sOME_FUNCTIONAsync(bool SOME_PARAM) override;
    /**
    * Remote call of INamEs::Some_Function2 on the Nam_Es service.
    * Uses Some_Function2Async
    */
    void some_Function2(bool Some_Param) override;
    /**
    * Remote call of INamEs::Some_Function2 on the Nam_Es service.
    */
    std::future<void> some_Function2Async(bool Some_Param) override;

    /** The publisher to subscribe to. */
    INamEsPublisher& _getPublisher() const override;
    
    /**
    * Informs if the Nam_EsClient is ready to send and receive messages.
    * @return true if Nam_Es is operable, false otherwise.
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
    * @param props Initial values obtained from the Nam_Es service
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
    * @param the data received from Nam_Es service.
    */
    void applyState(const nlohmann::json& fields);
    /**
    * Applies received property value to local state and publishes changes to subscribers.
    * @param propertyName the name of property to be changed.
    * @param value The value for property.
    */
    void applyProperty(const std::string& propertyName, const nlohmann::json& value);
    /**  Updates local value for Switch and informs subscriber about the change*/
    void setSwitchLocal(bool Switch);
    /* Mutex for switch property */
    mutable std::shared_timed_mutex m_switchMutex;
    /**  Updates local value for SomeProperty and informs subscriber about the change*/
    void setSomePropertyLocal(int SOME_PROPERTY);
    /* Mutex for someProperty property */
    mutable std::shared_timed_mutex m_somePropertyMutex;
    /**  Updates local value for SomePoperty2 and informs subscriber about the change*/
    void setSomePoperty2Local(int Some_Poperty2);
    /* Mutex for somePoperty2 property */
    mutable std::shared_timed_mutex m_somePoperty2Mutex;

    /** Local storage for properties values. */
    NamEsData m_data;

    /** 
    * An abstraction layer over the connection with service for the Nam_EsClient.
    * Handles incoming and outgoing messages.
    * Is given when object is linked with the service.
    */
    ApiGear::ObjectLink::IClientNode* m_node = nullptr;

    /** The publisher for Nam_Es */
    std::unique_ptr<INamEsPublisher> m_publisher;
};
} // namespace olink
} // namespace TbNames
} // namespace Test
