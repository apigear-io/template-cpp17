
#pragma once

#include "counter/generated/api/common.h"
#include "counter/generated/api/counter.h"
#include "counter/generated/core/counter.data.h"

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
namespace Counter {
namespace olink {
/**
* Adapts the general OLink Client handler to a Counter publisher in a way it provides access 
* to remote Counter services. 
* Sends and receives data over the network with ObjectLink protocol, through the communication node. 
* see https://objectlinkprotocol.net for ObjectLink details.
* see https://github.com/apigear-io/objectlink-core-cpp.git for olink client node - abstraction over the network.
* see Apigear::ObjectLink::OLinkConnection for Olink Client Handler implementation.
*     It provides a network implementation and tools to connect CounterClient to it.
* Use on client side to request changes of the Counter on the server side 
* and to subscribe for the Counter changes.
*/
class TEST_COUNTER_EXPORT CounterClient : public ICounter,
    public ApiGear::ObjectLink::IObjectSink
{
public:

    /** ctor */
    explicit CounterClient();
    /** dtor */
    virtual ~CounterClient() = default;
    /**
    * Property getter
    * @return Locally stored locally value for Vector.
    */
    const Test::CustomTypes::Vector3D& getVector() const override;
    /**
    * Request setting a property on the Counter service.
    * @param The value to which set request is send for the Vector.
    */
    void setVector(const Test::CustomTypes::Vector3D& vector) override;
    /**
    * Property getter
    * @return Locally stored locally value for ExternVector.
    */
    const Eigen::Vector3f& getExternVector() const override;
    /**
    * Request setting a property on the Counter service.
    * @param The value to which set request is send for the ExternVector.
    */
    void setExternVector(const Eigen::Vector3f& extern_vector) override;
    /**
    * Remote call of ICounter::increment on the Counter service.
    * Uses incrementAsync
    */
    Eigen::Vector3f increment(const Eigen::Vector3f& vec) override;
    /**
    * Remote call of ICounter::increment on the Counter service.
    */
    std::future<Eigen::Vector3f> incrementAsync(const Eigen::Vector3f& vec) override;
    /**
    * Remote call of ICounter::decrement on the Counter service.
    * Uses decrementAsync
    */
    Test::CustomTypes::Vector3D decrement(const Test::CustomTypes::Vector3D& vec) override;
    /**
    * Remote call of ICounter::decrement on the Counter service.
    */
    std::future<Test::CustomTypes::Vector3D> decrementAsync(const Test::CustomTypes::Vector3D& vec) override;

    /** The publisher to subscribe to. */
    ICounterPublisher& _getPublisher() const override;
    
    /**
    * Informs if the CounterClient is ready to send and receive messages.
    * @return true if Counter is operable, false otherwise.
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
    * @param props Initial values obtained from the Counter service
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
    * @param the data received from Counter service.
    */
    void applyState(const nlohmann::json& fields);
    /**
    * Applies received property value to local state and publishes changes to subscribers.
    * @param propertyName the name of property to be changed.
    * @param value The value for property.
    */
    void applyProperty(const std::string& propertyName, const nlohmann::json& value);
    /**  Updates local value for Vector and informs subscriber about the change*/
    void setVectorLocal(const Test::CustomTypes::Vector3D& vector);
    /* Mutex for vector property */
    mutable std::shared_timed_mutex m_vectorMutex;
    /**  Updates local value for ExternVector and informs subscriber about the change*/
    void setExternVectorLocal(const Eigen::Vector3f& extern_vector);
    /* Mutex for externVector property */
    mutable std::shared_timed_mutex m_externVectorMutex;

    /** Local storage for properties values. */
    CounterData m_data;

    /** 
    * An abstraction layer over the connection with service for the CounterClient.
    * Handles incoming and outgoing messages.
    * Is given when object is linked with the service.
    */
    ApiGear::ObjectLink::IClientNode* m_node = nullptr;

    /** The publisher for Counter */
    std::unique_ptr<ICounterPublisher> m_publisher;
};
} // namespace olink
} // namespace Counter
} // namespace Test
