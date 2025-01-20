
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace TbSimple {

class SimpleInterfaceTracer;

class TEST_TB_SIMPLE_EXPORT SimpleInterfaceTraceDecorator : public ISimpleInterface, public ISimpleInterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The SimpleInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit SimpleInterfaceTraceDecorator(ISimpleInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the SimpleInterfaceTraceDecorator object.
    * @param impl The SimpleInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<SimpleInterfaceTraceDecorator> connect(ISimpleInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~SimpleInterfaceTraceDecorator();

    /** Traces funcNoReturnValue and forwards call to SimpleInterface implementation. */
    void funcNoReturnValue(bool paramBool) override;
    /** Traces funcNoReturnValue and forwards call to SimpleInterface implementation. */
    std::future<void> funcNoReturnValueAsync(bool paramBool, std::function<void(void)> callback = nullptr) override;
    
    /** Traces funcBool and forwards call to SimpleInterface implementation. */
    bool funcBool(bool paramBool) override;
    /** Traces funcBool and forwards call to SimpleInterface implementation. */
    std::future<bool> funcBoolAsync(bool paramBool, std::function<void(bool)> callback = nullptr) override;
    
    /** Traces funcInt and forwards call to SimpleInterface implementation. */
    int funcInt(int paramInt) override;
    /** Traces funcInt and forwards call to SimpleInterface implementation. */
    std::future<int> funcIntAsync(int paramInt, std::function<void(int)> callback = nullptr) override;
    
    /** Traces funcInt32 and forwards call to SimpleInterface implementation. */
    int32_t funcInt32(int32_t paramInt32) override;
    /** Traces funcInt32 and forwards call to SimpleInterface implementation. */
    std::future<int32_t> funcInt32Async(int32_t paramInt32, std::function<void(int32_t)> callback = nullptr) override;
    
    /** Traces funcInt64 and forwards call to SimpleInterface implementation. */
    int64_t funcInt64(int64_t paramInt64) override;
    /** Traces funcInt64 and forwards call to SimpleInterface implementation. */
    std::future<int64_t> funcInt64Async(int64_t paramInt64, std::function<void(int64_t)> callback = nullptr) override;
    
    /** Traces funcFloat and forwards call to SimpleInterface implementation. */
    float funcFloat(float paramFloat) override;
    /** Traces funcFloat and forwards call to SimpleInterface implementation. */
    std::future<float> funcFloatAsync(float paramFloat, std::function<void(float)> callback = nullptr) override;
    
    /** Traces funcFloat32 and forwards call to SimpleInterface implementation. */
    float funcFloat32(float paramFloat32) override;
    /** Traces funcFloat32 and forwards call to SimpleInterface implementation. */
    std::future<float> funcFloat32Async(float paramFloat32, std::function<void(float)> callback = nullptr) override;
    
    /** Traces funcFloat64 and forwards call to SimpleInterface implementation. */
    double funcFloat64(double paramFloat) override;
    /** Traces funcFloat64 and forwards call to SimpleInterface implementation. */
    std::future<double> funcFloat64Async(double paramFloat, std::function<void(double)> callback = nullptr) override;
    
    /** Traces funcString and forwards call to SimpleInterface implementation. */
    std::string funcString(const std::string& paramString) override;
    /** Traces funcString and forwards call to SimpleInterface implementation. */
    std::future<std::string> funcStringAsync(const std::string& paramString, std::function<void(std::string)> callback = nullptr) override;
    
    /** Forwards call to SimpleInterface implementation. */
    void setPropBool(bool propBool) override;
    /** Forwards call to SimpleInterface implementation. */
    bool getPropBool() const override;
    
    /** Forwards call to SimpleInterface implementation. */
    void setPropInt(int propInt) override;
    /** Forwards call to SimpleInterface implementation. */
    int getPropInt() const override;
    
    /** Forwards call to SimpleInterface implementation. */
    void setPropInt32(int32_t propInt32) override;
    /** Forwards call to SimpleInterface implementation. */
    int32_t getPropInt32() const override;
    
    /** Forwards call to SimpleInterface implementation. */
    void setPropInt64(int64_t propInt64) override;
    /** Forwards call to SimpleInterface implementation. */
    int64_t getPropInt64() const override;
    
    /** Forwards call to SimpleInterface implementation. */
    void setPropFloat(float propFloat) override;
    /** Forwards call to SimpleInterface implementation. */
    float getPropFloat() const override;
    
    /** Forwards call to SimpleInterface implementation. */
    void setPropFloat32(float propFloat32) override;
    /** Forwards call to SimpleInterface implementation. */
    float getPropFloat32() const override;
    
    /** Forwards call to SimpleInterface implementation. */
    void setPropFloat64(double propFloat64) override;
    /** Forwards call to SimpleInterface implementation. */
    double getPropFloat64() const override;
    
    /** Forwards call to SimpleInterface implementation. */
    void setPropString(const std::string& propString) override;
    /** Forwards call to SimpleInterface implementation. */
    const std::string& getPropString() const override;
    
    /**
    Traces sigBool emission.
    */
    void onSigBool(bool paramBool) override;
    /**
    Traces sigInt emission.
    */
    void onSigInt(int paramInt) override;
    /**
    Traces sigInt32 emission.
    */
    void onSigInt32(int32_t paramInt32) override;
    /**
    Traces sigInt64 emission.
    */
    void onSigInt64(int64_t paramInt64) override;
    /**
    Traces sigFloat emission.
    */
    void onSigFloat(float paramFloat) override;
    /**
    Traces sigFloat32 emission.
    */
    void onSigFloat32(float paramFloa32) override;
    /**
    Traces sigFloat64 emission.
    */
    void onSigFloat64(double paramFloat64) override;
    /**
    Traces sigString emission.
    */
    void onSigString(const std::string& paramString) override;
    /**
    Traces propBool changed.
    */
    void onPropBoolChanged(bool propBool) override;
    /**
    Traces propInt changed.
    */
    void onPropIntChanged(int propInt) override;
    /**
    Traces propInt32 changed.
    */
    void onPropInt32Changed(int32_t propInt32) override;
    /**
    Traces propInt64 changed.
    */
    void onPropInt64Changed(int64_t propInt64) override;
    /**
    Traces propFloat changed.
    */
    void onPropFloatChanged(float propFloat) override;
    /**
    Traces propFloat32 changed.
    */
    void onPropFloat32Changed(float propFloat32) override;
    /**
    Traces propFloat64 changed.
    */
    void onPropFloat64Changed(double propFloat64) override;
    /**
    Traces propString changed.
    */
    void onPropStringChanged(const std::string& propString) override;

    /**
    * Access to a publisher, use it to subscribe for SimpleInterface changes and signal emission.
    * @return The publisher for SimpleInterface.
    */
    ISimpleInterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given SimpleInterface object. */
    std::unique_ptr<SimpleInterfaceTracer> m_tracer;
    /** The SimpleInterface object which is traced */
    ISimpleInterface& m_impl;
};
} // namespace TbSimple
} // namespace Test
