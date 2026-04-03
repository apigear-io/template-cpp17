
#pragma once
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace Testbed1 {

class StructArray2InterfaceTracer;

class TEST_TESTBED1_EXPORT StructArray2InterfaceTraceDecorator : public IStructArray2Interface, public IStructArray2InterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The StructArray2Interface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit StructArray2InterfaceTraceDecorator(IStructArray2Interface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the StructArray2InterfaceTraceDecorator object.
    * @param impl The StructArray2Interface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<StructArray2InterfaceTraceDecorator> connect(IStructArray2Interface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~StructArray2InterfaceTraceDecorator();

    /** Traces funcBool and forwards call to StructArray2Interface implementation. */
    std::list<StructBool> funcBool(const StructBoolWithArray& paramBool) override;
    /** Traces funcBool and forwards call to StructArray2Interface implementation. */
    std::future<std::list<StructBool>> funcBoolAsync(const StructBoolWithArray& paramBool, std::function<void(std::list<StructBool>)> callback = nullptr) override;
    
    /** Traces funcInt and forwards call to StructArray2Interface implementation. */
    std::list<StructInt> funcInt(const StructIntWithArray& paramInt) override;
    /** Traces funcInt and forwards call to StructArray2Interface implementation. */
    std::future<std::list<StructInt>> funcIntAsync(const StructIntWithArray& paramInt, std::function<void(std::list<StructInt>)> callback = nullptr) override;
    
    /** Traces funcFloat and forwards call to StructArray2Interface implementation. */
    std::list<StructFloat> funcFloat(const StructFloatWithArray& paramFloat) override;
    /** Traces funcFloat and forwards call to StructArray2Interface implementation. */
    std::future<std::list<StructFloat>> funcFloatAsync(const StructFloatWithArray& paramFloat, std::function<void(std::list<StructFloat>)> callback = nullptr) override;
    
    /** Traces funcString and forwards call to StructArray2Interface implementation. */
    std::list<StructString> funcString(const StructStringWithArray& paramString) override;
    /** Traces funcString and forwards call to StructArray2Interface implementation. */
    std::future<std::list<StructString>> funcStringAsync(const StructStringWithArray& paramString, std::function<void(std::list<StructString>)> callback = nullptr) override;
    
    /** Traces funcEnum and forwards call to StructArray2Interface implementation. */
    std::list<Enum0Enum> funcEnum(const StructEnumWithArray& paramEnum) override;
    /** Traces funcEnum and forwards call to StructArray2Interface implementation. */
    std::future<std::list<Enum0Enum>> funcEnumAsync(const StructEnumWithArray& paramEnum, std::function<void(std::list<Enum0Enum>)> callback = nullptr) override;
    
    /** Forwards call to StructArray2Interface implementation. */
    void setPropBool(const StructBoolWithArray& propBool) override;
    /** Forwards call to StructArray2Interface implementation. */
    const StructBoolWithArray& getPropBool() const override;
    
    /** Forwards call to StructArray2Interface implementation. */
    void setPropInt(const StructIntWithArray& propInt) override;
    /** Forwards call to StructArray2Interface implementation. */
    const StructIntWithArray& getPropInt() const override;
    
    /** Forwards call to StructArray2Interface implementation. */
    void setPropFloat(const StructFloatWithArray& propFloat) override;
    /** Forwards call to StructArray2Interface implementation. */
    const StructFloatWithArray& getPropFloat() const override;
    
    /** Forwards call to StructArray2Interface implementation. */
    void setPropString(const StructStringWithArray& propString) override;
    /** Forwards call to StructArray2Interface implementation. */
    const StructStringWithArray& getPropString() const override;
    
    /** Forwards call to StructArray2Interface implementation. */
    void setPropEnum(const StructEnumWithArray& propEnum) override;
    /** Forwards call to StructArray2Interface implementation. */
    const StructEnumWithArray& getPropEnum() const override;
    
    /**
    Traces sigBool emission.
    */
    void onSigBool(const StructBoolWithArray& paramBool) override;
    /**
    Traces sigInt emission.
    */
    void onSigInt(const StructIntWithArray& paramInt) override;
    /**
    Traces sigFloat emission.
    */
    void onSigFloat(const StructFloatWithArray& paramFloat) override;
    /**
    Traces sigString emission.
    */
    void onSigString(const StructStringWithArray& paramString) override;
    /**
    Traces propBool changed.
    */
    void onPropBoolChanged(const StructBoolWithArray& propBool) override;
    /**
    Traces propInt changed.
    */
    void onPropIntChanged(const StructIntWithArray& propInt) override;
    /**
    Traces propFloat changed.
    */
    void onPropFloatChanged(const StructFloatWithArray& propFloat) override;
    /**
    Traces propString changed.
    */
    void onPropStringChanged(const StructStringWithArray& propString) override;
    /**
    Traces propEnum changed.
    */
    void onPropEnumChanged(const StructEnumWithArray& propEnum) override;

    /**
    * Access to a publisher, use it to subscribe for StructArray2Interface changes and signal emission.
    * @return The publisher for StructArray2Interface.
    */
    IStructArray2InterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given StructArray2Interface object. */
    std::unique_ptr<StructArray2InterfaceTracer> m_tracer;
    /** The StructArray2Interface object which is traced */
    IStructArray2Interface& m_impl;
};
} // namespace Testbed1
} // namespace Test
