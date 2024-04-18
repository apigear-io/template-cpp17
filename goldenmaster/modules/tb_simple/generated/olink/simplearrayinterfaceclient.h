
#pragma once

#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/simplearrayinterface.data.h"

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
* Adapts the general OLink Client handler to a SimpleArrayInterface publisher in a way it provides access 
* to remote SimpleArrayInterface services. 
* Sends and receives data over the network with ObjectLink protocol, through the communication node. 
* see https://objectlinkprotocol.net for ObjectLink details.
* see https://github.com/apigear-io/objectlink-core-cpp.git for olink client node - abstraction over the network.
* see Apigear::ObjectLink::OLinkConnection for Olink Client Handler implementation.
*     It provides a network implementation and tools to connect SimpleArrayInterfaceClient to it.
* Use on client side to request changes of the SimpleArrayInterface on the server side 
* and to subscribe for the SimpleArrayInterface changes.
*/
class TEST_TB_SIMPLE_EXPORT SimpleArrayInterfaceClient : public ISimpleArrayInterface,
    public ApiGear::ObjectLink::IObjectSink
{
public:

    /** ctor */
    explicit SimpleArrayInterfaceClient();
    /** dtor */
    virtual ~SimpleArrayInterfaceClient() = default;
    /**
    * Property getter
    * @return Locally stored locally value for PropBool.
    */
    const std::list<bool>& getPropBool() const override;
    /**
    * Request setting a property on the SimpleArrayInterface service.
    * @param The value to which set request is send for the PropBool.
    */
    void setPropBool(const std::list<bool>& propBool) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropInt.
    */
    const std::list<int>& getPropInt() const override;
    /**
    * Request setting a property on the SimpleArrayInterface service.
    * @param The value to which set request is send for the PropInt.
    */
    void setPropInt(const std::list<int>& propInt) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropInt32.
    */
    const std::list<int32_t>& getPropInt32() const override;
    /**
    * Request setting a property on the SimpleArrayInterface service.
    * @param The value to which set request is send for the PropInt32.
    */
    void setPropInt32(const std::list<int32_t>& propInt32) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropInt64.
    */
    const std::list<int64_t>& getPropInt64() const override;
    /**
    * Request setting a property on the SimpleArrayInterface service.
    * @param The value to which set request is send for the PropInt64.
    */
    void setPropInt64(const std::list<int64_t>& propInt64) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropFloat.
    */
    const std::list<float>& getPropFloat() const override;
    /**
    * Request setting a property on the SimpleArrayInterface service.
    * @param The value to which set request is send for the PropFloat.
    */
    void setPropFloat(const std::list<float>& propFloat) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropFloat32.
    */
    const std::list<float>& getPropFloat32() const override;
    /**
    * Request setting a property on the SimpleArrayInterface service.
    * @param The value to which set request is send for the PropFloat32.
    */
    void setPropFloat32(const std::list<float>& propFloat32) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropFloat64.
    */
    const std::list<double>& getPropFloat64() const override;
    /**
    * Request setting a property on the SimpleArrayInterface service.
    * @param The value to which set request is send for the PropFloat64.
    */
    void setPropFloat64(const std::list<double>& propFloat64) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropString.
    */
    const std::list<std::string>& getPropString() const override;
    /**
    * Request setting a property on the SimpleArrayInterface service.
    * @param The value to which set request is send for the PropString.
    */
    void setPropString(const std::list<std::string>& propString) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropReadOnlyString.
    */
    const std::string& getPropReadOnlyString() const override;
    /**
    * Remote call of ISimpleArrayInterface::funcBool on the SimpleArrayInterface service.
    * Uses funcBoolAsync
    */
    std::list<bool> funcBool(const std::list<bool>& paramBool) override;
    /**
    * Remote call of ISimpleArrayInterface::funcBool on the SimpleArrayInterface service.
    */
    std::future<std::list<bool>> funcBoolAsync(const std::list<bool>& paramBool) override;
    /**
    * Remote call of ISimpleArrayInterface::funcInt on the SimpleArrayInterface service.
    * Uses funcIntAsync
    */
    std::list<int> funcInt(const std::list<int>& paramInt) override;
    /**
    * Remote call of ISimpleArrayInterface::funcInt on the SimpleArrayInterface service.
    */
    std::future<std::list<int>> funcIntAsync(const std::list<int>& paramInt) override;
    /**
    * Remote call of ISimpleArrayInterface::funcInt32 on the SimpleArrayInterface service.
    * Uses funcInt32Async
    */
    std::list<int32_t> funcInt32(const std::list<int32_t>& paramInt32) override;
    /**
    * Remote call of ISimpleArrayInterface::funcInt32 on the SimpleArrayInterface service.
    */
    std::future<std::list<int32_t>> funcInt32Async(const std::list<int32_t>& paramInt32) override;
    /**
    * Remote call of ISimpleArrayInterface::funcInt64 on the SimpleArrayInterface service.
    * Uses funcInt64Async
    */
    std::list<int64_t> funcInt64(const std::list<int64_t>& paramInt64) override;
    /**
    * Remote call of ISimpleArrayInterface::funcInt64 on the SimpleArrayInterface service.
    */
    std::future<std::list<int64_t>> funcInt64Async(const std::list<int64_t>& paramInt64) override;
    /**
    * Remote call of ISimpleArrayInterface::funcFloat on the SimpleArrayInterface service.
    * Uses funcFloatAsync
    */
    std::list<float> funcFloat(const std::list<float>& paramFloat) override;
    /**
    * Remote call of ISimpleArrayInterface::funcFloat on the SimpleArrayInterface service.
    */
    std::future<std::list<float>> funcFloatAsync(const std::list<float>& paramFloat) override;
    /**
    * Remote call of ISimpleArrayInterface::funcFloat32 on the SimpleArrayInterface service.
    * Uses funcFloat32Async
    */
    std::list<float> funcFloat32(const std::list<float>& paramFloat32) override;
    /**
    * Remote call of ISimpleArrayInterface::funcFloat32 on the SimpleArrayInterface service.
    */
    std::future<std::list<float>> funcFloat32Async(const std::list<float>& paramFloat32) override;
    /**
    * Remote call of ISimpleArrayInterface::funcFloat64 on the SimpleArrayInterface service.
    * Uses funcFloat64Async
    */
    std::list<double> funcFloat64(const std::list<double>& paramFloat) override;
    /**
    * Remote call of ISimpleArrayInterface::funcFloat64 on the SimpleArrayInterface service.
    */
    std::future<std::list<double>> funcFloat64Async(const std::list<double>& paramFloat) override;
    /**
    * Remote call of ISimpleArrayInterface::funcString on the SimpleArrayInterface service.
    * Uses funcStringAsync
    */
    std::list<std::string> funcString(const std::list<std::string>& paramString) override;
    /**
    * Remote call of ISimpleArrayInterface::funcString on the SimpleArrayInterface service.
    */
    std::future<std::list<std::string>> funcStringAsync(const std::list<std::string>& paramString) override;

    /** The publisher to subscribe to. */
    ISimpleArrayInterfacePublisher& _getPublisher() const override;
    
    /**
    * Informs if the SimpleArrayInterfaceClient is ready to send and receive messages.
    * @return true if SimpleArrayInterface is operable, false otherwise.
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
    * @param props Initial values obtained from the SimpleArrayInterface service
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
    * @param the data received from SimpleArrayInterface service.
    */
    void applyState(const nlohmann::json& fields);
    /**
    * Applies received property value to local state and publishes changes to subscribers.
    * @param propertyName the name of property to be changed.
    * @param value The value for property.
    */
    void applyProperty(const std::string& propertyName, const nlohmann::json& value);
    /**  Updates local value for PropBool and informs subscriber about the change*/
    void setPropBoolLocal(const std::list<bool>& propBool);
    /* Mutex for propBool property */
    mutable std::shared_timed_mutex m_propBoolMutex;
    /**  Updates local value for PropInt and informs subscriber about the change*/
    void setPropIntLocal(const std::list<int>& propInt);
    /* Mutex for propInt property */
    mutable std::shared_timed_mutex m_propIntMutex;
    /**  Updates local value for PropInt32 and informs subscriber about the change*/
    void setPropInt32Local(const std::list<int32_t>& propInt32);
    /* Mutex for propInt32 property */
    mutable std::shared_timed_mutex m_propInt32Mutex;
    /**  Updates local value for PropInt64 and informs subscriber about the change*/
    void setPropInt64Local(const std::list<int64_t>& propInt64);
    /* Mutex for propInt64 property */
    mutable std::shared_timed_mutex m_propInt64Mutex;
    /**  Updates local value for PropFloat and informs subscriber about the change*/
    void setPropFloatLocal(const std::list<float>& propFloat);
    /* Mutex for propFloat property */
    mutable std::shared_timed_mutex m_propFloatMutex;
    /**  Updates local value for PropFloat32 and informs subscriber about the change*/
    void setPropFloat32Local(const std::list<float>& propFloat32);
    /* Mutex for propFloat32 property */
    mutable std::shared_timed_mutex m_propFloat32Mutex;
    /**  Updates local value for PropFloat64 and informs subscriber about the change*/
    void setPropFloat64Local(const std::list<double>& propFloat64);
    /* Mutex for propFloat64 property */
    mutable std::shared_timed_mutex m_propFloat64Mutex;
    /**  Updates local value for PropString and informs subscriber about the change*/
    void setPropStringLocal(const std::list<std::string>& propString);
    /* Mutex for propString property */
    mutable std::shared_timed_mutex m_propStringMutex;
    /**  Updates local value for PropReadOnlyString and informs subscriber about the change*/
    void setPropReadOnlyStringLocal(const std::string& propReadOnlyString);
    /* Mutex for propReadOnlyString property */
    mutable std::shared_timed_mutex m_propReadOnlyStringMutex;

    /** Local storage for properties values. */
    SimpleArrayInterfaceData m_data;

    /** 
    * An abstraction layer over the connection with service for the SimpleArrayInterfaceClient.
    * Handles incoming and outgoing messages.
    * Is given when object is linked with the service.
    */
    ApiGear::ObjectLink::IClientNode* m_node = nullptr;

    /** The publisher for SimpleArrayInterface */
    std::unique_ptr<ISimpleArrayInterfacePublisher> m_publisher;
};
} // namespace olink
} // namespace TbSimple
} // namespace Test
