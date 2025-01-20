
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace TbSimple {

class NoPropertiesInterfaceTracer;

class TEST_TB_SIMPLE_EXPORT NoPropertiesInterfaceTraceDecorator : public INoPropertiesInterface, public INoPropertiesInterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The NoPropertiesInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit NoPropertiesInterfaceTraceDecorator(INoPropertiesInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the NoPropertiesInterfaceTraceDecorator object.
    * @param impl The NoPropertiesInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<NoPropertiesInterfaceTraceDecorator> connect(INoPropertiesInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~NoPropertiesInterfaceTraceDecorator();

    /** Traces funcVoid and forwards call to NoPropertiesInterface implementation. */
    void funcVoid() override;
    /** Traces funcVoid and forwards call to NoPropertiesInterface implementation. */
    std::future<void> funcVoidAsync( std::function<void(void)> callback = nullptr) override;
    
    /** Traces funcBool and forwards call to NoPropertiesInterface implementation. */
    bool funcBool(bool paramBool) override;
    /** Traces funcBool and forwards call to NoPropertiesInterface implementation. */
    std::future<bool> funcBoolAsync(bool paramBool, std::function<void(bool)> callback = nullptr) override;
    
    /**
    Traces sigVoid emission.
    */
    void onSigVoid() override;
    /**
    Traces sigBool emission.
    */
    void onSigBool(bool paramBool) override;

    /**
    * Access to a publisher, use it to subscribe for NoPropertiesInterface changes and signal emission.
    * @return The publisher for NoPropertiesInterface.
    */
    INoPropertiesInterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given NoPropertiesInterface object. */
    std::unique_ptr<NoPropertiesInterfaceTracer> m_tracer;
    /** The NoPropertiesInterface object which is traced */
    INoPropertiesInterface& m_impl;
};
} // namespace TbSimple
} // namespace Test
