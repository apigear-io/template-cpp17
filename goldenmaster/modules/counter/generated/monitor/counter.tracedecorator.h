
#pragma once
#include "counter/generated/api/counter.h"
#include "counter/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace Counter {

class CounterTracer;

class TEST_COUNTER_EXPORT CounterTraceDecorator : public ICounter, public ICounterSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The Counter object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit CounterTraceDecorator(ICounter& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the CounterTraceDecorator object.
    * @param impl The Counter object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<CounterTraceDecorator> connect(ICounter& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~CounterTraceDecorator();

    /** Traces increment and forwards call to Counter implementation. */
    Eigen::Vector3f increment(const Eigen::Vector3f& vec) override;
    /** Traces increment and forwards call to Counter implementation. */
    std::future<Eigen::Vector3f> incrementAsync(const Eigen::Vector3f& vec, std::function<void(Eigen::Vector3f)> callback = nullptr) override;
    
    /** Traces incrementArray and forwards call to Counter implementation. */
    std::list<Eigen::Vector3f> incrementArray(const std::list<Eigen::Vector3f>& vec) override;
    /** Traces incrementArray and forwards call to Counter implementation. */
    std::future<std::list<Eigen::Vector3f>> incrementArrayAsync(const std::list<Eigen::Vector3f>& vec, std::function<void(std::list<Eigen::Vector3f>)> callback = nullptr) override;
    
    /** Traces decrement and forwards call to Counter implementation. */
    Test::CustomTypes::Vector3D decrement(const Test::CustomTypes::Vector3D& vec) override;
    /** Traces decrement and forwards call to Counter implementation. */
    std::future<Test::CustomTypes::Vector3D> decrementAsync(const Test::CustomTypes::Vector3D& vec, std::function<void(Test::CustomTypes::Vector3D)> callback = nullptr) override;
    
    /** Traces decrementArray and forwards call to Counter implementation. */
    std::list<Test::CustomTypes::Vector3D> decrementArray(const std::list<Test::CustomTypes::Vector3D>& vec) override;
    /** Traces decrementArray and forwards call to Counter implementation. */
    std::future<std::list<Test::CustomTypes::Vector3D>> decrementArrayAsync(const std::list<Test::CustomTypes::Vector3D>& vec, std::function<void(std::list<Test::CustomTypes::Vector3D>)> callback = nullptr) override;
    
    /** Forwards call to Counter implementation. */
    void setVector(const Test::CustomTypes::Vector3D& vector) override;
    /** Forwards call to Counter implementation. */
    const Test::CustomTypes::Vector3D& getVector() const override;
    
    /** Forwards call to Counter implementation. */
    void setExternVector(const Eigen::Vector3f& extern_vector) override;
    /** Forwards call to Counter implementation. */
    const Eigen::Vector3f& getExternVector() const override;
    
    /** Forwards call to Counter implementation. */
    void setVectorArray(const std::list<Test::CustomTypes::Vector3D>& vectorArray) override;
    /** Forwards call to Counter implementation. */
    const std::list<Test::CustomTypes::Vector3D>& getVectorArray() const override;
    
    /** Forwards call to Counter implementation. */
    void setExternVectorArray(const std::list<Eigen::Vector3f>& extern_vectorArray) override;
    /** Forwards call to Counter implementation. */
    const std::list<Eigen::Vector3f>& getExternVectorArray() const override;
    
    /**
    Traces valueChanged emission.
    */
    void onValueChanged(const Test::CustomTypes::Vector3D& vector, const Eigen::Vector3f& extern_vector, const std::list<Test::CustomTypes::Vector3D>& vectorArray, const std::list<Eigen::Vector3f>& extern_vectorArray) override;
    /**
    Traces vector changed.
    */
    void onVectorChanged(const Test::CustomTypes::Vector3D& vector) override;
    /**
    Traces extern_vector changed.
    */
    void onExternVectorChanged(const Eigen::Vector3f& extern_vector) override;
    /**
    Traces vectorArray changed.
    */
    void onVectorArrayChanged(const std::list<Test::CustomTypes::Vector3D>& vectorArray) override;
    /**
    Traces extern_vectorArray changed.
    */
    void onExternVectorArrayChanged(const std::list<Eigen::Vector3f>& extern_vectorArray) override;

    /**
    * Access to a publisher, use it to subscribe for Counter changes and signal emission.
    * @return The publisher for Counter.
    */
    ICounterPublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given Counter object. */
    std::unique_ptr<CounterTracer> m_tracer;
    /** The Counter object which is traced */
    ICounter& m_impl;
};
} // namespace Counter
} // namespace Test
