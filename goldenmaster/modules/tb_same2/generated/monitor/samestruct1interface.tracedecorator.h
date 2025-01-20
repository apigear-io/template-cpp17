
#pragma once
#include "tb_same2/generated/api/tb_same2.h"
#include "tb_same2/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace TbSame2 {

class SameStruct1InterfaceTracer;

class TEST_TB_SAME2_EXPORT SameStruct1InterfaceTraceDecorator : public ISameStruct1Interface, public ISameStruct1InterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The SameStruct1Interface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit SameStruct1InterfaceTraceDecorator(ISameStruct1Interface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the SameStruct1InterfaceTraceDecorator object.
    * @param impl The SameStruct1Interface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<SameStruct1InterfaceTraceDecorator> connect(ISameStruct1Interface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~SameStruct1InterfaceTraceDecorator();

    /** Traces func1 and forwards call to SameStruct1Interface implementation. */
    Struct1 func1(const Struct1& param1) override;
    /** Traces func1 and forwards call to SameStruct1Interface implementation. */
    std::future<Struct1> func1Async(const Struct1& param1, std::function<void(Struct1)> callback = nullptr) override;
    
    /** Forwards call to SameStruct1Interface implementation. */
    void setProp1(const Struct1& prop1) override;
    /** Forwards call to SameStruct1Interface implementation. */
    const Struct1& getProp1() const override;
    
    /**
    Traces sig1 emission.
    */
    void onSig1(const Struct1& param1) override;
    /**
    Traces prop1 changed.
    */
    void onProp1Changed(const Struct1& prop1) override;

    /**
    * Access to a publisher, use it to subscribe for SameStruct1Interface changes and signal emission.
    * @return The publisher for SameStruct1Interface.
    */
    ISameStruct1InterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given SameStruct1Interface object. */
    std::unique_ptr<SameStruct1InterfaceTracer> m_tracer;
    /** The SameStruct1Interface object which is traced */
    ISameStruct1Interface& m_impl;
};
} // namespace TbSame2
} // namespace Test
