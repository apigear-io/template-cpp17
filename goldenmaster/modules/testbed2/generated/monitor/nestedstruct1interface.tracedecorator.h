
#pragma once
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace Testbed2 {

class NestedStruct1InterfaceTracer;

class TEST_TESTBED2_EXPORT NestedStruct1InterfaceTraceDecorator : public INestedStruct1Interface, public INestedStruct1InterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The NestedStruct1Interface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit NestedStruct1InterfaceTraceDecorator(INestedStruct1Interface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the NestedStruct1InterfaceTraceDecorator object.
    * @param impl The NestedStruct1Interface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<NestedStruct1InterfaceTraceDecorator> connect(INestedStruct1Interface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~NestedStruct1InterfaceTraceDecorator();

    /** Traces func1 and forwards call to NestedStruct1Interface implementation. */
    NestedStruct1 func1(const NestedStruct1& param1) override;
    /** Traces func1 and forwards call to NestedStruct1Interface implementation. */
    std::future<NestedStruct1> func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback = nullptr) override;
    
    /** Forwards call to NestedStruct1Interface implementation. */
    void setProp1(const NestedStruct1& prop1) override;
    /** Forwards call to NestedStruct1Interface implementation. */
    const NestedStruct1& getProp1() const override;
    
    /**
    Traces sig1 emission.
    */
    void onSig1(const NestedStruct1& param1) override;
    /**
    Traces prop1 changed.
    */
    void onProp1Changed(const NestedStruct1& prop1) override;

    /**
    * Access to a publisher, use it to subscribe for NestedStruct1Interface changes and signal emission.
    * @return The publisher for NestedStruct1Interface.
    */
    INestedStruct1InterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given NestedStruct1Interface object. */
    std::unique_ptr<NestedStruct1InterfaceTracer> m_tracer;
    /** The NestedStruct1Interface object which is traced */
    INestedStruct1Interface& m_impl;
};
} // namespace Testbed2
} // namespace Test
