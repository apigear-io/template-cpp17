#pragma once

#include "counter/generated/api/counter.h"
#include "counter/generated/api/common.h"
#include "apigear/mqtt/mqttservice.h"

namespace Test {
namespace Counter {
namespace MQTT {
class TEST_COUNTER_EXPORT CounterService : public ICounterSubscriber
{
public:
    explicit CounterService(std::shared_ptr<ICounter> impl, std::shared_ptr<ApiGear::MQTT::Service> service);
    virtual ~CounterService() override;

    void onConnectionStatusChanged(bool connectionStatus);

private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap();
    void onInvokeIncrement(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onInvokeDecrement(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
    void onVectorChanged(const Test::CustomTypes::Vector3D& vector) override;
    /// @brief requests to set the value for the property Vector coming from the client
    /// @param fields contains the param of the type Test::CustomTypes::Vector3D
    void onSetVector(const std::string& args) const;
    void onExternVectorChanged(const Eigen::Vector3f& extern_vector) override;
    /// @brief requests to set the value for the property ExternVector coming from the client
    /// @param fields contains the param of the type Eigen::Vector3f
    void onSetExternVector(const std::string& args) const;

    std::shared_ptr<ICounter> m_impl;
    std::shared_ptr<ApiGear::MQTT::Service> m_service;
    // id for connection status registration
    int m_connectionStatusRegistrationID;

    /// @brief has all the topics of this service and the corresponding function callbacks
    const std::map<std::string, ApiGear::MQTT::CallbackFunction> m_topics;
};
} // namespace MQTT
} // namespace Counter
} // namespace Test
