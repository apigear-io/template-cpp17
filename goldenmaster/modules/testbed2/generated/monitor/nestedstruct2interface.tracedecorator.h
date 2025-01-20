
#pragma once
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace Testbed2 {

class NestedStruct2InterfaceTracer;

class TEST_TESTBED2_EXPORT NestedStruct2InterfaceTraceDecorator : public INestedStruct2Interface, public INestedStruct2InterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The NestedStruct2Interface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit NestedStruct2InterfaceTraceDecorator(INestedStruct2Interface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the NestedStruct2InterfaceTraceDecorator object.
    * @param impl The NestedStruct2Interface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<NestedStruct2InterfaceTraceDecorator> connect(INestedStruct2Interface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~NestedStruct2InterfaceTraceDecorator();

    /** Traces func1 and forwards call to NestedStruct2Interface implementation. */
    NestedStruct1 func1(const NestedStruct1& param1) override;
    /** Traces func1 and forwards call to NestedStruct2Interface implementation. */
    std::future<NestedStruct1> func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback = nullptr) override;
    
    /** Traces func2 and forwards call to NestedStruct2Interface implementation. */
    NestedStruct1 func2(const NestedStruct1& param1, const NestedStruct2& param2) override;
    /** Traces func2 and forwards call to NestedStruct2Interface implementation. */
    std::future<NestedStruct1> func2Async(const NestedStruct1& param1, const NestedStruct2& param2, std::function<void(NestedStruct1)> callback = nullptr) override;
    
    /** Forwards call to NestedStruct2Interface implementation. */
    void setProp1(const NestedStruct1& prop1) override;
    /** Forwards call to NestedStruct2Interface implementation. */
    const NestedStruct1& getProp1() const override;
    
    /** Forwards call to NestedStruct2Interface implementation. */
    void setProp2(const NestedStruct2& prop2) override;
    /** Forwards call to NestedStruct2Interface implementation. */
    const NestedStruct2& getProp2() const override;
    
    /**
    Traces sig1 emission.
    */
    void onSig1(const NestedStruct1& param1) override;
    /**
    Traces sig2 emission.
    */
    void onSig2(const NestedStruct1& param1, const NestedStruct2& param2) override;
    /**
    Traces prop1 changed.
    */
    void onProp1Changed(const NestedStruct1& prop1) override;
    /**
    Traces prop2 changed.
    */
    void onProp2Changed(const NestedStruct2& prop2) override;

    /**
    * Access to a publisher, use it to subscribe for NestedStruct2Interface changes and signal emission.
    * @return The publisher for NestedStruct2Interface.
    */
    INestedStruct2InterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given NestedStruct2Interface object. */
    std::unique_ptr<NestedStruct2InterfaceTracer> m_tracer;
    /** The NestedStruct2Interface object which is traced */
    INestedStruct2Interface& m_impl;
};
} // namespace Testbed2
} // namespace Test
