#pragma once

#include "counter/generated/api/common.h"
#include "counter/generated/api/counter.h"
#include "counter/generated/core/counter.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace Test {
namespace Counter {
namespace Nats {
class TEST_COUNTER_EXPORT CounterClient : public ICounter, public ApiGear::Nats::BaseAdapter,  public std::enable_shared_from_this<CounterClient>
{
protected:
    explicit CounterClient(std::shared_ptr<ApiGear::Nats::Client> client);
public:
    static std::shared_ptr<CounterClient>create(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~CounterClient() override;
    void init();
    const Test::CustomTypes::Vector3D& getVector() const override;
    void setVector(const Test::CustomTypes::Vector3D& vector) override;
    const Eigen::Vector3f& getExternVector() const override;
    void setExternVector(const Eigen::Vector3f& extern_vector) override;
    const std::list<Test::CustomTypes::Vector3D>& getVectorArray() const override;
    void setVectorArray(const std::list<Test::CustomTypes::Vector3D>& vectorArray) override;
    const std::list<Eigen::Vector3f>& getExternVectorArray() const override;
    void setExternVectorArray(const std::list<Eigen::Vector3f>& extern_vectorArray) override;
    Eigen::Vector3f increment(const Eigen::Vector3f& vec) override;
    std::future<Eigen::Vector3f> incrementAsync(const Eigen::Vector3f& vec, std::function<void(Eigen::Vector3f)> callback = nullptr) override;
    std::list<Eigen::Vector3f> incrementArray(const std::list<Eigen::Vector3f>& vec) override;
    std::future<std::list<Eigen::Vector3f>> incrementArrayAsync(const std::list<Eigen::Vector3f>& vec, std::function<void(std::list<Eigen::Vector3f>)> callback = nullptr) override;
    Test::CustomTypes::Vector3D decrement(const Test::CustomTypes::Vector3D& vec) override;
    std::future<Test::CustomTypes::Vector3D> decrementAsync(const Test::CustomTypes::Vector3D& vec, std::function<void(Test::CustomTypes::Vector3D)> callback = nullptr) override;
    std::list<Test::CustomTypes::Vector3D> decrementArray(const std::list<Test::CustomTypes::Vector3D>& vec) override;
    std::future<std::list<Test::CustomTypes::Vector3D>> decrementArrayAsync(const std::list<Test::CustomTypes::Vector3D>& vec, std::function<void(std::list<Test::CustomTypes::Vector3D>)> callback = nullptr) override;
    ICounterPublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::BaseAdapter> getSharedFromDerrived() override;
    void handleAvailable(const std::string& payload);
    void handleInit(const std::string& value);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type Test::CustomTypes::Vector3D
    Test::CustomTypes::Vector3D _to_Vector(const std::string& args);
    /// @brief sets the value for the property Vector coming from the service
    void setVectorLocal(const Test::CustomTypes::Vector3D& vector);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type Eigen::Vector3f
    Eigen::Vector3f _to_ExternVector(const std::string& args);
    /// @brief sets the value for the property ExternVector coming from the service
    void setExternVectorLocal(const Eigen::Vector3f& extern_vector);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::list<Test::CustomTypes::Vector3D>
    std::list<Test::CustomTypes::Vector3D> _to_VectorArray(const std::string& args);
    /// @brief sets the value for the property VectorArray coming from the service
    void setVectorArrayLocal(const std::list<Test::CustomTypes::Vector3D>& vectorArray);
    /// @brief Converts incoming raw message formatted value to a value of property. 
    /// @param args contains the param of the type std::list<Eigen::Vector3f>
    std::list<Eigen::Vector3f> _to_ExternVectorArray(const std::string& args);
    /// @brief sets the value for the property ExternVectorArray coming from the service
    void setExternVectorArrayLocal(const std::list<Eigen::Vector3f>& extern_vectorArray);
    /// @brief publishes the value for the signal ValueChanged coming from the service
    /// @param args contains the param(s) of the type(s) const Test::CustomTypes::Vector3D& vector, const Eigen::Vector3f& extern_vector, const std::list<Test::CustomTypes::Vector3D>& vectorArray, const std::list<Eigen::Vector3f>& extern_vectorArray
    void onValueChanged(const std::string& args) const;
    /** Local storage for properties values. */
    CounterData m_data;
    int32_t m_requestInitCallId = 0;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for Counter */
    std::unique_ptr<ICounterPublisher> m_publisher;
    void onConnected();

};
} // namespace Nats
} // namespace Counter
} // namespace Test
