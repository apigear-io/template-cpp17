
#pragma once
#include "counter/generated/api/counter.h"
#include "counter/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace Counter {

/** 
* @brief The CounterThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the Counter interface.
* @see Counter
*
\code{.cpp}
using namespace Test::Counter;

std::unique_ptr<ICounter> testCounter = std::make_unique<CounterThreadSafeDecorator>(std::make_shared<Counter>());

// Thread safe access
auto vector = testCounter->getVector();
testCounter->setVector(Test::CustomTypes::Vector3D());
auto externVector = testCounter->getExternVector();
testCounter->setExternVector(Eigen::Vector3f(0,0,0));
auto vectorArray = testCounter->getVectorArray();
testCounter->setVectorArray(std::list<Test::CustomTypes::Vector3D>());
auto externVectorArray = testCounter->getExternVectorArray();
testCounter->setExternVectorArray(std::list<Eigen::Vector3f>());
\endcode
*/
class TEST_COUNTER_EXPORT CounterThreadSafeDecorator : public ICounter
{
public:
    /** 
    * ctor
    * @param impl The Counter object to make thread safe.
    */
    explicit CounterThreadSafeDecorator(std::shared_ptr<ICounter> impl);

    /** 
    * Forwards call to Counter implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    Eigen::Vector3f increment(const Eigen::Vector3f& vec) override;
    /** 
    * Forwards call to Counter implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<Eigen::Vector3f> incrementAsync(const Eigen::Vector3f& vec, std::function<void(Eigen::Vector3f)> callback = nullptr) override;

    /** 
    * Forwards call to Counter implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::list<Eigen::Vector3f> incrementArray(const std::list<Eigen::Vector3f>& vec) override;
    /** 
    * Forwards call to Counter implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<std::list<Eigen::Vector3f>> incrementArrayAsync(const std::list<Eigen::Vector3f>& vec, std::function<void(std::list<Eigen::Vector3f>)> callback = nullptr) override;

    /** 
    * Forwards call to Counter implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    Test::CustomTypes::Vector3D decrement(const Test::CustomTypes::Vector3D& vec) override;
    /** 
    * Forwards call to Counter implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<Test::CustomTypes::Vector3D> decrementAsync(const Test::CustomTypes::Vector3D& vec, std::function<void(Test::CustomTypes::Vector3D)> callback = nullptr) override;

    /** 
    * Forwards call to Counter implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::list<Test::CustomTypes::Vector3D> decrementArray(const std::list<Test::CustomTypes::Vector3D>& vec) override;
    /** 
    * Forwards call to Counter implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<std::list<Test::CustomTypes::Vector3D>> decrementArrayAsync(const std::list<Test::CustomTypes::Vector3D>& vec, std::function<void(std::list<Test::CustomTypes::Vector3D>)> callback = nullptr) override;

    /** Guards and forwards call to Counter implementation. */
    void setVector(const Test::CustomTypes::Vector3D& vector) override;
    /** Guards and forwards call to Counter implementation. */
    const Test::CustomTypes::Vector3D& getVector() const override;

    /** Guards and forwards call to Counter implementation. */
    void setExternVector(const Eigen::Vector3f& extern_vector) override;
    /** Guards and forwards call to Counter implementation. */
    const Eigen::Vector3f& getExternVector() const override;

    /** Guards and forwards call to Counter implementation. */
    void setVectorArray(const std::list<Test::CustomTypes::Vector3D>& vectorArray) override;
    /** Guards and forwards call to Counter implementation. */
    const std::list<Test::CustomTypes::Vector3D>& getVectorArray() const override;

    /** Guards and forwards call to Counter implementation. */
    void setExternVectorArray(const std::list<Eigen::Vector3f>& extern_vectorArray) override;
    /** Guards and forwards call to Counter implementation. */
    const std::list<Eigen::Vector3f>& getExternVectorArray() const override;

    /**
    * Access to a publisher, use it to subscribe for Counter changes and signal emission.
    * This call is thread safe.
    * @return The publisher for Counter.
    */
    ICounterPublisher& _getPublisher() const override;
private:
    /** The Counter object which is guarded */
    std::shared_ptr<ICounter> m_impl;
    // Mutex for vector property
    mutable std::shared_timed_mutex m_vectorMutex;
    // Mutex for externVector property
    mutable std::shared_timed_mutex m_externVectorMutex;
    // Mutex for vectorArray property
    mutable std::shared_timed_mutex m_vectorArrayMutex;
    // Mutex for externVectorArray property
    mutable std::shared_timed_mutex m_externVectorArrayMutex;
};
} // namespace Counter
} // namespace Test
