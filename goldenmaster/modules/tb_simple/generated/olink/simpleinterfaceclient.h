
#pragma once

#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/simpleinterface.data.h"

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
* Adapts the general OLink Client handler to a SimpleInterface publisher in a way it provides access 
* to remote SimpleInterface services. 
* Sends and receives data over the network with ObjectLink protocol, through the communication node. 
* see https://objectlinkprotocol.net for ObjectLink details.
* see https://github.com/apigear-io/objectlink-core-cpp.git for olink client node - abstraction over the network.
* see Apigear::ObjectLink::OLinkConnection for Olink Client Handler implementation.
*     It provides a network implementation and tools to connect SimpleInterfaceClient to it.
* Use on client side to request changes of the SimpleInterface on the server side 
* and to subscribe for the SimpleInterface changes.
*/
class TEST_TB_SIMPLE_EXPORT SimpleInterfaceClient : public ISimpleInterface,
    public ApiGear::ObjectLink::IObjectSink
{
public:

    /** ctor */
    explicit SimpleInterfaceClient();
    /** dtor */
    virtual ~SimpleInterfaceClient() = default;
    /**
    * Property getter
    * @return Locally stored locally value for PropBool.
    */
    bool getPropBool() const override;
    /**
    * Request setting a property on the SimpleInterface service.
    * @param The value to which set request is send for the PropBool.
    */
    void setPropBool(bool propBool) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropInt.
    */
    int getPropInt() const override;
    /**
    * Request setting a property on the SimpleInterface service.
    * @param The value to which set request is send for the PropInt.
    */
    void setPropInt(int propInt) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropInt32.
    */
    int32_t getPropInt32() const override;
    /**
    * Request setting a property on the SimpleInterface service.
    * @param The value to which set request is send for the PropInt32.
    */
    void setPropInt32(int32_t propInt32) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropInt64.
    */
    int64_t getPropInt64() const override;
    /**
    * Request setting a property on the SimpleInterface service.
    * @param The value to which set request is send for the PropInt64.
    */
    void setPropInt64(int64_t propInt64) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropFloat.
    */
    float getPropFloat() const override;
    /**
    * Request setting a property on the SimpleInterface service.
    * @param The value to which set request is send for the PropFloat.
    */
    void setPropFloat(float propFloat) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropFloat32.
    */
    float getPropFloat32() const override;
    /**
    * Request setting a property on the SimpleInterface service.
    * @param The value to which set request is send for the PropFloat32.
    */
    void setPropFloat32(float propFloat32) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropFloat64.
    */
    double getPropFloat64() const override;
    /**
    * Request setting a property on the SimpleInterface service.
    * @param The value to which set request is send for the PropFloat64.
    */
    void setPropFloat64(double propFloat64) override;
    /**
    * Property getter
    * @return Locally stored locally value for PropString.
    */
    const std::string& getPropString() const override;
    /**
    * Request setting a property on the SimpleInterface service.
    * @param The value to which set request is send for the PropString.
    */
    void setPropString(const std::string& propString) override;
    /**
    * Remote call of ISimpleInterface::funcNoReturnValue on the SimpleInterface service.
    * Uses funcNoReturnValueAsync
    */
    void funcNoReturnValue(bool paramBool) override;
    /**
    * Remote call of ISimpleInterface::funcNoReturnValue on the SimpleInterface service.
    */
    std::future<void> funcNoReturnValueAsync(bool paramBool) override;
    /**
    * Remote call of ISimpleInterface::funcBool on the SimpleInterface service.
    * Uses funcBoolAsync
    */
    bool funcBool(bool paramBool) override;
    /**
    * Remote call of ISimpleInterface::funcBool on the SimpleInterface service.
    */
    std::future<bool> funcBoolAsync(bool paramBool) override;
    /**
    * Remote call of ISimpleInterface::funcInt on the SimpleInterface service.
    * Uses funcIntAsync
    */
    int funcInt(int paramInt) override;
    /**
    * Remote call of ISimpleInterface::funcInt on the SimpleInterface service.
    */
    std::future<int> funcIntAsync(int paramInt) override;
    /**
    * Remote call of ISimpleInterface::funcInt32 on the SimpleInterface service.
    * Uses funcInt32Async
    */
    int32_t funcInt32(int32_t paramInt32) override;
    /**
    * Remote call of ISimpleInterface::funcInt32 on the SimpleInterface service.
    */
    std::future<int32_t> funcInt32Async(int32_t paramInt32) override;
    /**
    * Remote call of ISimpleInterface::funcInt64 on the SimpleInterface service.
    * Uses funcInt64Async
    */
    int64_t funcInt64(int64_t paramInt64) override;
    /**
    * Remote call of ISimpleInterface::funcInt64 on the SimpleInterface service.
    */
    std::future<int64_t> funcInt64Async(int64_t paramInt64) override;
    /**
    * Remote call of ISimpleInterface::funcFloat on the SimpleInterface service.
    * Uses funcFloatAsync
    */
    float funcFloat(float paramFloat) override;
    /**
    * Remote call of ISimpleInterface::funcFloat on the SimpleInterface service.
    */
    std::future<float> funcFloatAsync(float paramFloat) override;
    /**
    * Remote call of ISimpleInterface::funcFloat32 on the SimpleInterface service.
    * Uses funcFloat32Async
    */
    float funcFloat32(float paramFloat32) override;
    /**
    * Remote call of ISimpleInterface::funcFloat32 on the SimpleInterface service.
    */
    std::future<float> funcFloat32Async(float paramFloat32) override;
    /**
    * Remote call of ISimpleInterface::funcFloat64 on the SimpleInterface service.
    * Uses funcFloat64Async
    */
    double funcFloat64(double paramFloat) override;
    /**
    * Remote call of ISimpleInterface::funcFloat64 on the SimpleInterface service.
    */
    std::future<double> funcFloat64Async(double paramFloat) override;
    /**
    * Remote call of ISimpleInterface::funcString on the SimpleInterface service.
    * Uses funcStringAsync
    */
    std::string funcString(const std::string& paramString) override;
    /**
    * Remote call of ISimpleInterface::funcString on the SimpleInterface service.
    */
    std::future<std::string> funcStringAsync(const std::string& paramString) override;

    /** The publisher to subscribe to. */
    ISimpleInterfacePublisher& _getPublisher() const override;
    
    /**
    * Informs if the SimpleInterfaceClient is ready to send and receive messages.
    * @return true if SimpleInterface is operable, false otherwise.
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
    * @param props Initial values obtained from the SimpleInterface service
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
    * @param the data received from SimpleInterface service.
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
    /**  Updates local value for PropInt32 and informs subscriber about the change*/
    void setPropInt32Local(int32_t propInt32);
    /* Mutex for propInt32 property */
    mutable std::shared_timed_mutex m_propInt32Mutex;
    /**  Updates local value for PropInt64 and informs subscriber about the change*/
    void setPropInt64Local(int64_t propInt64);
    /* Mutex for propInt64 property */
    mutable std::shared_timed_mutex m_propInt64Mutex;
    /**  Updates local value for PropFloat and informs subscriber about the change*/
    void setPropFloatLocal(float propFloat);
    /* Mutex for propFloat property */
    mutable std::shared_timed_mutex m_propFloatMutex;
    /**  Updates local value for PropFloat32 and informs subscriber about the change*/
    void setPropFloat32Local(float propFloat32);
    /* Mutex for propFloat32 property */
    mutable std::shared_timed_mutex m_propFloat32Mutex;
    /**  Updates local value for PropFloat64 and informs subscriber about the change*/
    void setPropFloat64Local(double propFloat64);
    /* Mutex for propFloat64 property */
    mutable std::shared_timed_mutex m_propFloat64Mutex;
    /**  Updates local value for PropString and informs subscriber about the change*/
    void setPropStringLocal(const std::string& propString);
    /* Mutex for propString property */
    mutable std::shared_timed_mutex m_propStringMutex;

    /** Local storage for properties values. */
    SimpleInterfaceData m_data;

    /** 
    * An abstraction layer over the connection with service for the SimpleInterfaceClient.
    * Handles incoming and outgoing messages.
    * Is given when object is linked with the service.
    */
    ApiGear::ObjectLink::IClientNode* m_node = nullptr;

    /** The publisher for SimpleInterface */
    std::unique_ptr<ISimpleInterfacePublisher> m_publisher;
};
} // namespace olink
} // namespace TbSimple
} // namespace Test
