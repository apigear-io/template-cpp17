
#pragma once
#include "tb_same1/generated/api/tb_same1.h"
#include "tb_same1/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace TbSame1 {

class SameStruct2InterfaceTracer;

class TEST_TB_SAME1_EXPORT SameStruct2InterfaceTraceDecorator : public ISameStruct2Interface, public ISameStruct2InterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The SameStruct2Interface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit SameStruct2InterfaceTraceDecorator(ISameStruct2Interface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the SameStruct2InterfaceTraceDecorator object.
    * @param impl The SameStruct2Interface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<SameStruct2InterfaceTraceDecorator> connect(ISameStruct2Interface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~SameStruct2InterfaceTraceDecorator();

    /** Traces func1 and forwards call to SameStruct2Interface implementation. */
    Struct1 func1(const Struct1& param1) override;
    /** Traces func1 and forwards call to SameStruct2Interface implementation. */
    std::future<Struct1> func1Async(const Struct1& param1, std::function<void(Struct1)> callback = nullptr) override;
    
    /** Traces func2 and forwards call to SameStruct2Interface implementation. */
    Struct1 func2(const Struct1& param1, const Struct2& param2) override;
    /** Traces func2 and forwards call to SameStruct2Interface implementation. */
    std::future<Struct1> func2Async(const Struct1& param1, const Struct2& param2, std::function<void(Struct1)> callback = nullptr) override;
    
    /** Forwards call to SameStruct2Interface implementation. */
    void setProp1(const Struct2& prop1) override;
    /** Forwards call to SameStruct2Interface implementation. */
    const Struct2& getProp1() const override;
    
    /** Forwards call to SameStruct2Interface implementation. */
    void setProp2(const Struct2& prop2) override;
    /** Forwards call to SameStruct2Interface implementation. */
    const Struct2& getProp2() const override;
    
    /**
    Traces sig1 emission.
    */
    void onSig1(const Struct1& param1) override;
    /**
    Traces sig2 emission.
    */
    void onSig2(const Struct1& param1, const Struct2& param2) override;
    /**
    Traces prop1 changed.
    */
    void onProp1Changed(const Struct2& prop1) override;
    /**
    Traces prop2 changed.
    */
    void onProp2Changed(const Struct2& prop2) override;

    /**
    * Access to a publisher, use it to subscribe for SameStruct2Interface changes and signal emission.
    * @return The publisher for SameStruct2Interface.
    */
    ISameStruct2InterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given SameStruct2Interface object. */
    std::unique_ptr<SameStruct2InterfaceTracer> m_tracer;
    /** The SameStruct2Interface object which is traced */
    ISameStruct2Interface& m_impl;
};
} // namespace TbSame1
} // namespace Test
