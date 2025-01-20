
#pragma once
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace Testbed1 {

class StructArrayInterfaceTracer;

class TEST_TESTBED1_EXPORT StructArrayInterfaceTraceDecorator : public IStructArrayInterface, public IStructArrayInterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The StructArrayInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit StructArrayInterfaceTraceDecorator(IStructArrayInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the StructArrayInterfaceTraceDecorator object.
    * @param impl The StructArrayInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<StructArrayInterfaceTraceDecorator> connect(IStructArrayInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~StructArrayInterfaceTraceDecorator();

    /** Traces funcBool and forwards call to StructArrayInterface implementation. */
    StructBool funcBool(const std::list<StructBool>& paramBool) override;
    /** Traces funcBool and forwards call to StructArrayInterface implementation. */
    std::future<StructBool> funcBoolAsync(const std::list<StructBool>& paramBool, std::function<void(StructBool)> callback = nullptr) override;
    
    /** Traces funcInt and forwards call to StructArrayInterface implementation. */
    StructBool funcInt(const std::list<StructInt>& paramInt) override;
    /** Traces funcInt and forwards call to StructArrayInterface implementation. */
    std::future<StructBool> funcIntAsync(const std::list<StructInt>& paramInt, std::function<void(StructBool)> callback = nullptr) override;
    
    /** Traces funcFloat and forwards call to StructArrayInterface implementation. */
    StructBool funcFloat(const std::list<StructFloat>& paramFloat) override;
    /** Traces funcFloat and forwards call to StructArrayInterface implementation. */
    std::future<StructBool> funcFloatAsync(const std::list<StructFloat>& paramFloat, std::function<void(StructBool)> callback = nullptr) override;
    
    /** Traces funcString and forwards call to StructArrayInterface implementation. */
    StructBool funcString(const std::list<StructString>& paramString) override;
    /** Traces funcString and forwards call to StructArrayInterface implementation. */
    std::future<StructBool> funcStringAsync(const std::list<StructString>& paramString, std::function<void(StructBool)> callback = nullptr) override;
    
    /** Forwards call to StructArrayInterface implementation. */
    void setPropBool(const std::list<StructBool>& propBool) override;
    /** Forwards call to StructArrayInterface implementation. */
    const std::list<StructBool>& getPropBool() const override;
    
    /** Forwards call to StructArrayInterface implementation. */
    void setPropInt(const std::list<StructInt>& propInt) override;
    /** Forwards call to StructArrayInterface implementation. */
    const std::list<StructInt>& getPropInt() const override;
    
    /** Forwards call to StructArrayInterface implementation. */
    void setPropFloat(const std::list<StructFloat>& propFloat) override;
    /** Forwards call to StructArrayInterface implementation. */
    const std::list<StructFloat>& getPropFloat() const override;
    
    /** Forwards call to StructArrayInterface implementation. */
    void setPropString(const std::list<StructString>& propString) override;
    /** Forwards call to StructArrayInterface implementation. */
    const std::list<StructString>& getPropString() const override;
    
    /**
    Traces sigBool emission.
    */
    void onSigBool(const std::list<StructBool>& paramBool) override;
    /**
    Traces sigInt emission.
    */
    void onSigInt(const std::list<StructInt>& paramInt) override;
    /**
    Traces sigFloat emission.
    */
    void onSigFloat(const std::list<StructFloat>& paramFloat) override;
    /**
    Traces sigString emission.
    */
    void onSigString(const std::list<StructString>& paramString) override;
    /**
    Traces propBool changed.
    */
    void onPropBoolChanged(const std::list<StructBool>& propBool) override;
    /**
    Traces propInt changed.
    */
    void onPropIntChanged(const std::list<StructInt>& propInt) override;
    /**
    Traces propFloat changed.
    */
    void onPropFloatChanged(const std::list<StructFloat>& propFloat) override;
    /**
    Traces propString changed.
    */
    void onPropStringChanged(const std::list<StructString>& propString) override;

    /**
    * Access to a publisher, use it to subscribe for StructArrayInterface changes and signal emission.
    * @return The publisher for StructArrayInterface.
    */
    IStructArrayInterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given StructArrayInterface object. */
    std::unique_ptr<StructArrayInterfaceTracer> m_tracer;
    /** The StructArrayInterface object which is traced */
    IStructArrayInterface& m_impl;
};
} // namespace Testbed1
} // namespace Test
