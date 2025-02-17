
#pragma once
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace Testbed1 {

class StructInterfaceTracer;

class TEST_TESTBED1_EXPORT StructInterfaceTraceDecorator : public IStructInterface, public IStructInterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The StructInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit StructInterfaceTraceDecorator(IStructInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the StructInterfaceTraceDecorator object.
    * @param impl The StructInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<StructInterfaceTraceDecorator> connect(IStructInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~StructInterfaceTraceDecorator();

    /** Traces funcBool and forwards call to StructInterface implementation. */
    StructBool funcBool(const StructBool& paramBool) override;
    /** Traces funcBool and forwards call to StructInterface implementation. */
    std::future<StructBool> funcBoolAsync(const StructBool& paramBool) override;
    
    /** Traces funcInt and forwards call to StructInterface implementation. */
    StructInt funcInt(const StructInt& paramInt) override;
    /** Traces funcInt and forwards call to StructInterface implementation. */
    std::future<StructInt> funcIntAsync(const StructInt& paramInt) override;
    
    /** Traces funcFloat and forwards call to StructInterface implementation. */
    StructFloat funcFloat(const StructFloat& paramFloat) override;
    /** Traces funcFloat and forwards call to StructInterface implementation. */
    std::future<StructFloat> funcFloatAsync(const StructFloat& paramFloat) override;
    
    /** Traces funcString and forwards call to StructInterface implementation. */
    StructString funcString(const StructString& paramString) override;
    /** Traces funcString and forwards call to StructInterface implementation. */
    std::future<StructString> funcStringAsync(const StructString& paramString) override;
    
    /** Forwards call to StructInterface implementation. */
    void setPropBool(const StructBool& propBool) override;
    /** Forwards call to StructInterface implementation. */
    const StructBool& getPropBool() const override;
    
    /** Forwards call to StructInterface implementation. */
    void setPropInt(const StructInt& propInt) override;
    /** Forwards call to StructInterface implementation. */
    const StructInt& getPropInt() const override;
    
    /** Forwards call to StructInterface implementation. */
    void setPropFloat(const StructFloat& propFloat) override;
    /** Forwards call to StructInterface implementation. */
    const StructFloat& getPropFloat() const override;
    
    /** Forwards call to StructInterface implementation. */
    void setPropString(const StructString& propString) override;
    /** Forwards call to StructInterface implementation. */
    const StructString& getPropString() const override;
    
    /**
    Traces sigBool emission.
    */
    void onSigBool(const StructBool& paramBool) override;
    /**
    Traces sigInt emission.
    */
    void onSigInt(const StructInt& paramInt) override;
    /**
    Traces sigFloat emission.
    */
    void onSigFloat(const StructFloat& paramFloat) override;
    /**
    Traces sigString emission.
    */
    void onSigString(const StructString& paramString) override;
    /**
    Traces propBool changed.
    */
    void onPropBoolChanged(const StructBool& propBool) override;
    /**
    Traces propInt changed.
    */
    void onPropIntChanged(const StructInt& propInt) override;
    /**
    Traces propFloat changed.
    */
    void onPropFloatChanged(const StructFloat& propFloat) override;
    /**
    Traces propString changed.
    */
    void onPropStringChanged(const StructString& propString) override;

    /**
    * Access to a publisher, use it to subscribe for StructInterface changes and signal emission.
    * @return The publisher for StructInterface.
    */
    IStructInterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given StructInterface object. */
    std::unique_ptr<StructInterfaceTracer> m_tracer;
    /** The StructInterface object which is traced */
    IStructInterface& m_impl;
};
} // namespace Testbed1
} // namespace Test
