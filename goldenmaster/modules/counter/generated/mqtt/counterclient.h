#pragma once

#include <future>
#include "counter/generated/api/common.h"
#include "counter/generated/api/counter.h"
#include "counter/generated/core/counter.data.h"
#include "apigear/mqtt/mqttclient.h"

namespace Test {
namespace Counter {
namespace MQTT {
class TEST_COUNTER_EXPORT CounterClient : public ICounter
{
public:
    explicit CounterClient(std::shared_ptr<ApiGear::MQTT::Client> client);
    virtual ~CounterClient() override;
    const Test::CustomTypes::Vector3D& getVector() const override;
    void setVector(const Test::CustomTypes::Vector3D& vector) override;
    const Eigen::Vector3f& getExternVector() const override;
    void setExternVector(const Eigen::Vector3f& extern_vector) override;
    Eigen::Vector3f increment(const Eigen::Vector3f& vec) override;
    std::future<Eigen::Vector3f> incrementAsync(const Eigen::Vector3f& vec) override;
    Test::CustomTypes::Vector3D decrement(const Test::CustomTypes::Vector3D& vec) override;
    std::future<Test::CustomTypes::Vector3D> decrementAsync(const Test::CustomTypes::Vector3D& vec) override;
    ICounterPublisher& _getPublisher() const override;

    bool isReady() const;

    void onInvokeReply(const std::string& args, const std::string& correlationData);

    void onConnectionStatusChanged(bool connectionStatus);
private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap(const std::string&clientId);
    /// @brief sets the value for the property Vector coming from the service
    /// @param args contains the param of the type Test::CustomTypes::Vector3D
    void setVectorLocal(const std::string& args);
    /// @brief sets the value for the property ExternVector coming from the service
    /// @param args contains the param of the type Eigen::Vector3f
    void setExternVectorLocal(const std::string& args);

    bool m_isReady;
    /** Local storage for properties values. */
    CounterData m_data;
    std::shared_ptr<ApiGear::MQTT::Client> m_client;

    /** The publisher for Counter */
    std::unique_ptr<ICounterPublisher> m_publisher;

    /**
     * @brief register a response handler for an operation invocation
     * 
     * @param handler function to be called on return
     * @return int unique id of the call
     */
    int registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler);
    std::mutex m_responseHandlerMutex;
    std::map<int, ApiGear::MQTT::InvokeReplyFunc> m_responseHandlerMap;

    /// @brief has all the topics of this client and the corresponding function callbacks
    const std::map<std::string, ApiGear::MQTT::CallbackFunction> m_topics;
    // id for connection status registration
    int m_connectionStatusRegistrationID;
};
} // namespace MQTT
} // namespace Counter
} // namespace Test
