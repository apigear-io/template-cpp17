
#pragma once
#include "counter/generated/api/counter.h"
#include "counter/generated/api/common.h"
#include "counter/generated/core/counter.data.h"
#include <memory>

namespace Test {
namespace Counter {

/**
* The Counter implementation.
*/
class TEST_COUNTER_EXPORT Counter : public ICounter
{
public:
    explicit Counter();
    ~Counter();
public:
    void setVector(const Test::CustomTypes::Vector3D& vector) override;
    const Test::CustomTypes::Vector3D& getVector() const override;
    
    void setExternVector(const Eigen::Vector3f& extern_vector) override;
    const Eigen::Vector3f& getExternVector() const override;
    
    void setVectorArray(const std::list<Test::CustomTypes::Vector3D>& vectorArray) override;
    const std::list<Test::CustomTypes::Vector3D>& getVectorArray() const override;
    
    void setExternVectorArray(const std::list<Eigen::Vector3f>& extern_vectorArray) override;
    const std::list<Eigen::Vector3f>& getExternVectorArray() const override;
    
    Eigen::Vector3f increment(const Eigen::Vector3f& vec) override;
    std::future<Eigen::Vector3f> incrementAsync(const Eigen::Vector3f& vec, std::function<void(Eigen::Vector3f)> callback = nullptr) override;
        
    std::list<Eigen::Vector3f> incrementArray(const std::list<Eigen::Vector3f>& vec) override;
    std::future<std::list<Eigen::Vector3f>> incrementArrayAsync(const std::list<Eigen::Vector3f>& vec, std::function<void(std::list<Eigen::Vector3f>)> callback = nullptr) override;
        
    Test::CustomTypes::Vector3D decrement(const Test::CustomTypes::Vector3D& vec) override;
    std::future<Test::CustomTypes::Vector3D> decrementAsync(const Test::CustomTypes::Vector3D& vec, std::function<void(Test::CustomTypes::Vector3D)> callback = nullptr) override;
        
    std::list<Test::CustomTypes::Vector3D> decrementArray(const std::list<Test::CustomTypes::Vector3D>& vec) override;
    std::future<std::list<Test::CustomTypes::Vector3D>> decrementArrayAsync(const std::list<Test::CustomTypes::Vector3D>& vec, std::function<void(std::list<Test::CustomTypes::Vector3D>)> callback = nullptr) override;
        
    /**
    * Access to a publisher, use it to subscribe for Counter changes and signal emission.
    * @return The publisher for Counter.
    */
    ICounterPublisher& _getPublisher() const override;
private:
    /** The publisher for the Counter. */
    std::unique_ptr<ICounterPublisher> m_publisher;
    /** The helper structure to store all the properties for Counter. */
    CounterData m_data;
};
} // namespace Counter
} // namespace Test
