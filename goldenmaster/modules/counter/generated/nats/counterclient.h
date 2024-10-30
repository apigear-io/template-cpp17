#pragma once

#include <future>
#include "counter/generated/api/common.h"
#include "counter/generated/api/counter.h"
#include "counter/generated/core/counter.data.h"
#include "apigear/nats/natsclient.h"

namespace Test {
namespace Counter {
namespace Nats {
class TEST_COUNTER_EXPORT CounterClient : public ICounter
{
public:
    explicit CounterClient(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~CounterClient() override;
    const Test::CustomTypes::Vector3D& getVector() const override;
    void setVector(const Test::CustomTypes::Vector3D& vector) override;
    const Eigen::Vector3f& getExternVector() const override;
    void setExternVector(const Eigen::Vector3f& extern_vector) override;
    const std::list<Test::CustomTypes::Vector3D>& getVectorArray() const override;
    void setVectorArray(const std::list<Test::CustomTypes::Vector3D>& vectorArray) override;
    const std::list<Eigen::Vector3f>& getExternVectorArray() const override;
    void setExternVectorArray(const std::list<Eigen::Vector3f>& extern_vectorArray) override;
    Eigen::Vector3f increment(const Eigen::Vector3f& vec) override;
    std::future<Eigen::Vector3f> incrementAsync(const Eigen::Vector3f& vec) override;
    std::list<Eigen::Vector3f> incrementArray(const std::list<Eigen::Vector3f>& vec) override;
    std::future<std::list<Eigen::Vector3f>> incrementArrayAsync(const std::list<Eigen::Vector3f>& vec) override;
    Test::CustomTypes::Vector3D decrement(const Test::CustomTypes::Vector3D& vec) override;
    std::future<Test::CustomTypes::Vector3D> decrementAsync(const Test::CustomTypes::Vector3D& vec) override;
    std::list<Test::CustomTypes::Vector3D> decrementArray(const std::list<Test::CustomTypes::Vector3D>& vec) override;
    std::future<std::list<Test::CustomTypes::Vector3D>> decrementArrayAsync(const std::list<Test::CustomTypes::Vector3D>& vec) override;
    ICounterPublisher& _getPublisher() const override;
private:
    /// @brief sets the value for the property Vector coming from the service
    /// @param args contains the param of the type Test::CustomTypes::Vector3D
    void setVectorLocal(const std::string& args);
    /// @brief sets the value for the property ExternVector coming from the service
    /// @param args contains the param of the type Eigen::Vector3f
    void setExternVectorLocal(const std::string& args);
    /// @brief sets the value for the property VectorArray coming from the service
    /// @param args contains the param of the type std::list<Test::CustomTypes::Vector3D>
    void setVectorArrayLocal(const std::string& args);
    /// @brief sets the value for the property ExternVectorArray coming from the service
    /// @param args contains the param of the type std::list<Eigen::Vector3f>
    void setExternVectorArrayLocal(const std::string& args);
    /// @brief publishes the value for the signal ValueChanged coming from the service
    /// @param args contains the param(s) of the type(s) const Test::CustomTypes::Vector3D& vector, const Eigen::Vector3f& extern_vector, const std::list<Test::CustomTypes::Vector3D>& vectorArray, const std::list<Eigen::Vector3f>& extern_vectorArray
    void onValueChanged(const std::string& args) const;
    /** Local storage for properties values. */
    CounterData m_data;
    std::shared_ptr<ApiGear::Nats::Client> m_client;

    /** The publisher for Counter */
    std::unique_ptr<ICounterPublisher> m_publisher;

};
} // namespace Nats
} // namespace Counter
} // namespace Test
