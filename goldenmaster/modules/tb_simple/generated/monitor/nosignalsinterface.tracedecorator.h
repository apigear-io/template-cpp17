
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace TbSimple {

class NoSignalsInterfaceTracer;

class TEST_TB_SIMPLE_EXPORT NoSignalsInterfaceTraceDecorator : public INoSignalsInterface, public INoSignalsInterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The NoSignalsInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit NoSignalsInterfaceTraceDecorator(INoSignalsInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the NoSignalsInterfaceTraceDecorator object.
    * @param impl The NoSignalsInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<NoSignalsInterfaceTraceDecorator> connect(INoSignalsInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~NoSignalsInterfaceTraceDecorator();

    /** Traces funcVoid and forwards call to NoSignalsInterface implementation. */
    void funcVoid() override;
    /** Traces funcVoid and forwards call to NoSignalsInterface implementation. */
    std::future<void> funcVoidAsync( std::function<void(void)> callback = nullptr) override;
    
    /** Traces funcBool and forwards call to NoSignalsInterface implementation. */
    bool funcBool(bool paramBool) override;
    /** Traces funcBool and forwards call to NoSignalsInterface implementation. */
    std::future<bool> funcBoolAsync(bool paramBool, std::function<void(bool)> callback = nullptr) override;
    
    /** Forwards call to NoSignalsInterface implementation. */
    void setPropBool(bool propBool) override;
    /** Forwards call to NoSignalsInterface implementation. */
    bool getPropBool() const override;
    
    /** Forwards call to NoSignalsInterface implementation. */
    void setPropInt(int propInt) override;
    /** Forwards call to NoSignalsInterface implementation. */
    int getPropInt() const override;
    
    /**
    Traces propBool changed.
    */
    void onPropBoolChanged(bool propBool) override;
    /**
    Traces propInt changed.
    */
    void onPropIntChanged(int propInt) override;

    /**
    * Access to a publisher, use it to subscribe for NoSignalsInterface changes and signal emission.
    * @return The publisher for NoSignalsInterface.
    */
    INoSignalsInterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given NoSignalsInterface object. */
    std::unique_ptr<NoSignalsInterfaceTracer> m_tracer;
    /** The NoSignalsInterface object which is traced */
    INoSignalsInterface& m_impl;
};
} // namespace TbSimple
} // namespace Test
