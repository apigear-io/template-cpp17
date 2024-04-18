
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace TbSimple {

class SimpleArrayInterfaceTracer;

class TEST_TB_SIMPLE_EXPORT SimpleArrayInterfaceTraceDecorator : public ISimpleArrayInterface, public ISimpleArrayInterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The SimpleArrayInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit SimpleArrayInterfaceTraceDecorator(ISimpleArrayInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the SimpleArrayInterfaceTraceDecorator object.
    * @param impl The SimpleArrayInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<SimpleArrayInterfaceTraceDecorator> connect(ISimpleArrayInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~SimpleArrayInterfaceTraceDecorator();

    /** Traces funcBool and forwards call to SimpleArrayInterface implementation. */
    std::list<bool> funcBool(const std::list<bool>& paramBool) override;
    /** Traces funcBool and forwards call to SimpleArrayInterface implementation. */
    std::future<std::list<bool>> funcBoolAsync(const std::list<bool>& paramBool) override;
    
    /** Traces funcInt and forwards call to SimpleArrayInterface implementation. */
    std::list<int> funcInt(const std::list<int>& paramInt) override;
    /** Traces funcInt and forwards call to SimpleArrayInterface implementation. */
    std::future<std::list<int>> funcIntAsync(const std::list<int>& paramInt) override;
    
    /** Traces funcInt32 and forwards call to SimpleArrayInterface implementation. */
    std::list<int32_t> funcInt32(const std::list<int32_t>& paramInt32) override;
    /** Traces funcInt32 and forwards call to SimpleArrayInterface implementation. */
    std::future<std::list<int32_t>> funcInt32Async(const std::list<int32_t>& paramInt32) override;
    
    /** Traces funcInt64 and forwards call to SimpleArrayInterface implementation. */
    std::list<int64_t> funcInt64(const std::list<int64_t>& paramInt64) override;
    /** Traces funcInt64 and forwards call to SimpleArrayInterface implementation. */
    std::future<std::list<int64_t>> funcInt64Async(const std::list<int64_t>& paramInt64) override;
    
    /** Traces funcFloat and forwards call to SimpleArrayInterface implementation. */
    std::list<float> funcFloat(const std::list<float>& paramFloat) override;
    /** Traces funcFloat and forwards call to SimpleArrayInterface implementation. */
    std::future<std::list<float>> funcFloatAsync(const std::list<float>& paramFloat) override;
    
    /** Traces funcFloat32 and forwards call to SimpleArrayInterface implementation. */
    std::list<float> funcFloat32(const std::list<float>& paramFloat32) override;
    /** Traces funcFloat32 and forwards call to SimpleArrayInterface implementation. */
    std::future<std::list<float>> funcFloat32Async(const std::list<float>& paramFloat32) override;
    
    /** Traces funcFloat64 and forwards call to SimpleArrayInterface implementation. */
    std::list<double> funcFloat64(const std::list<double>& paramFloat) override;
    /** Traces funcFloat64 and forwards call to SimpleArrayInterface implementation. */
    std::future<std::list<double>> funcFloat64Async(const std::list<double>& paramFloat) override;
    
    /** Traces funcString and forwards call to SimpleArrayInterface implementation. */
    std::list<std::string> funcString(const std::list<std::string>& paramString) override;
    /** Traces funcString and forwards call to SimpleArrayInterface implementation. */
    std::future<std::list<std::string>> funcStringAsync(const std::list<std::string>& paramString) override;
    
    /** Forwards call to SimpleArrayInterface implementation. */
    void setPropBool(const std::list<bool>& propBool) override;
    /** Forwards call to SimpleArrayInterface implementation. */
    const std::list<bool>& getPropBool() const override;
    
    /** Forwards call to SimpleArrayInterface implementation. */
    void setPropInt(const std::list<int>& propInt) override;
    /** Forwards call to SimpleArrayInterface implementation. */
    const std::list<int>& getPropInt() const override;
    
    /** Forwards call to SimpleArrayInterface implementation. */
    void setPropInt32(const std::list<int32_t>& propInt32) override;
    /** Forwards call to SimpleArrayInterface implementation. */
    const std::list<int32_t>& getPropInt32() const override;
    
    /** Forwards call to SimpleArrayInterface implementation. */
    void setPropInt64(const std::list<int64_t>& propInt64) override;
    /** Forwards call to SimpleArrayInterface implementation. */
    const std::list<int64_t>& getPropInt64() const override;
    
    /** Forwards call to SimpleArrayInterface implementation. */
    void setPropFloat(const std::list<float>& propFloat) override;
    /** Forwards call to SimpleArrayInterface implementation. */
    const std::list<float>& getPropFloat() const override;
    
    /** Forwards call to SimpleArrayInterface implementation. */
    void setPropFloat32(const std::list<float>& propFloat32) override;
    /** Forwards call to SimpleArrayInterface implementation. */
    const std::list<float>& getPropFloat32() const override;
    
    /** Forwards call to SimpleArrayInterface implementation. */
    void setPropFloat64(const std::list<double>& propFloat64) override;
    /** Forwards call to SimpleArrayInterface implementation. */
    const std::list<double>& getPropFloat64() const override;
    
    /** Forwards call to SimpleArrayInterface implementation. */
    void setPropString(const std::list<std::string>& propString) override;
    /** Forwards call to SimpleArrayInterface implementation. */
    const std::list<std::string>& getPropString() const override;
    
    /** Forwards call to SimpleArrayInterface implementation. */
    const std::string& getPropReadOnlyString() const override;
    
    /**
    Traces sigBool emission.
    */
    void onSigBool(const std::list<bool>& paramBool) override;
    /**
    Traces sigInt emission.
    */
    void onSigInt(const std::list<int>& paramInt) override;
    /**
    Traces sigInt32 emission.
    */
    void onSigInt32(const std::list<int32_t>& paramInt32) override;
    /**
    Traces sigInt64 emission.
    */
    void onSigInt64(const std::list<int64_t>& paramInt64) override;
    /**
    Traces sigFloat emission.
    */
    void onSigFloat(const std::list<float>& paramFloat) override;
    /**
    Traces sigFloat32 emission.
    */
    void onSigFloat32(const std::list<float>& paramFloa32) override;
    /**
    Traces sigFloat64 emission.
    */
    void onSigFloat64(const std::list<double>& paramFloat64) override;
    /**
    Traces sigString emission.
    */
    void onSigString(const std::list<std::string>& paramString) override;
    /**
    Traces propBool changed.
    */
    void onPropBoolChanged(const std::list<bool>& propBool) override;
    /**
    Traces propInt changed.
    */
    void onPropIntChanged(const std::list<int>& propInt) override;
    /**
    Traces propInt32 changed.
    */
    void onPropInt32Changed(const std::list<int32_t>& propInt32) override;
    /**
    Traces propInt64 changed.
    */
    void onPropInt64Changed(const std::list<int64_t>& propInt64) override;
    /**
    Traces propFloat changed.
    */
    void onPropFloatChanged(const std::list<float>& propFloat) override;
    /**
    Traces propFloat32 changed.
    */
    void onPropFloat32Changed(const std::list<float>& propFloat32) override;
    /**
    Traces propFloat64 changed.
    */
    void onPropFloat64Changed(const std::list<double>& propFloat64) override;
    /**
    Traces propString changed.
    */
    void onPropStringChanged(const std::list<std::string>& propString) override;
    /**
    Traces propReadOnlyString changed.
    */
    void onPropReadOnlyStringChanged(const std::string& propReadOnlyString) override;

    /**
    * Access to a publisher, use it to subscribe for SimpleArrayInterface changes and signal emission.
    * @return The publisher for SimpleArrayInterface.
    */
    ISimpleArrayInterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given SimpleArrayInterface object. */
    std::unique_ptr<SimpleArrayInterfaceTracer> m_tracer;
    /** The SimpleArrayInterface object which is traced */
    ISimpleArrayInterface& m_impl;
};
} // namespace TbSimple
} // namespace Test
