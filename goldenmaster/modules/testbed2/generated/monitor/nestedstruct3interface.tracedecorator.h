
#pragma once
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace Testbed2 {

class NestedStruct3InterfaceTracer;

class TEST_TESTBED2_EXPORT NestedStruct3InterfaceTraceDecorator : public INestedStruct3Interface, public INestedStruct3InterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The NestedStruct3Interface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit NestedStruct3InterfaceTraceDecorator(INestedStruct3Interface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the NestedStruct3InterfaceTraceDecorator object.
    * @param impl The NestedStruct3Interface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<NestedStruct3InterfaceTraceDecorator> connect(INestedStruct3Interface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~NestedStruct3InterfaceTraceDecorator();

    /** Traces func1 and forwards call to NestedStruct3Interface implementation. */
    NestedStruct1 func1(const NestedStruct1& param1) override;
    /** Traces func1 and forwards call to NestedStruct3Interface implementation. */
    std::future<NestedStruct1> func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback = nullptr) override;
    
    /** Traces func2 and forwards call to NestedStruct3Interface implementation. */
    NestedStruct1 func2(const NestedStruct1& param1, const NestedStruct2& param2) override;
    /** Traces func2 and forwards call to NestedStruct3Interface implementation. */
    std::future<NestedStruct1> func2Async(const NestedStruct1& param1, const NestedStruct2& param2, std::function<void(NestedStruct1)> callback = nullptr) override;
    
    /** Traces func3 and forwards call to NestedStruct3Interface implementation. */
    NestedStruct1 func3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3) override;
    /** Traces func3 and forwards call to NestedStruct3Interface implementation. */
    std::future<NestedStruct1> func3Async(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3, std::function<void(NestedStruct1)> callback = nullptr) override;
    
    /** Forwards call to NestedStruct3Interface implementation. */
    void setProp1(const NestedStruct1& prop1) override;
    /** Forwards call to NestedStruct3Interface implementation. */
    const NestedStruct1& getProp1() const override;
    
    /** Forwards call to NestedStruct3Interface implementation. */
    void setProp2(const NestedStruct2& prop2) override;
    /** Forwards call to NestedStruct3Interface implementation. */
    const NestedStruct2& getProp2() const override;
    
    /** Forwards call to NestedStruct3Interface implementation. */
    void setProp3(const NestedStruct3& prop3) override;
    /** Forwards call to NestedStruct3Interface implementation. */
    const NestedStruct3& getProp3() const override;
    
    /**
    Traces sig1 emission.
    */
    void onSig1(const NestedStruct1& param1) override;
    /**
    Traces sig2 emission.
    */
    void onSig2(const NestedStruct1& param1, const NestedStruct2& param2) override;
    /**
    Traces sig3 emission.
    */
    void onSig3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3) override;
    /**
    Traces prop1 changed.
    */
    void onProp1Changed(const NestedStruct1& prop1) override;
    /**
    Traces prop2 changed.
    */
    void onProp2Changed(const NestedStruct2& prop2) override;
    /**
    Traces prop3 changed.
    */
    void onProp3Changed(const NestedStruct3& prop3) override;

    /**
    * Access to a publisher, use it to subscribe for NestedStruct3Interface changes and signal emission.
    * @return The publisher for NestedStruct3Interface.
    */
    INestedStruct3InterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given NestedStruct3Interface object. */
    std::unique_ptr<NestedStruct3InterfaceTracer> m_tracer;
    /** The NestedStruct3Interface object which is traced */
    INestedStruct3Interface& m_impl;
};
} // namespace Testbed2
} // namespace Test
