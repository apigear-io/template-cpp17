
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace TbSimple {

class VoidInterfaceTracer;

class TEST_TB_SIMPLE_EXPORT VoidInterfaceTraceDecorator : public IVoidInterface, public IVoidInterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The VoidInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit VoidInterfaceTraceDecorator(IVoidInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the VoidInterfaceTraceDecorator object.
    * @param impl The VoidInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<VoidInterfaceTraceDecorator> connect(IVoidInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~VoidInterfaceTraceDecorator();

    /** Traces funcVoid and forwards call to VoidInterface implementation. */
    void funcVoid() override;
    /** Traces funcVoid and forwards call to VoidInterface implementation. */
    std::future<void> funcVoidAsync( std::function<void(void)> callback = nullptr) override;
    
    /**
    Traces sigVoid emission.
    */
    void onSigVoid() override;

    /**
    * Access to a publisher, use it to subscribe for VoidInterface changes and signal emission.
    * @return The publisher for VoidInterface.
    */
    IVoidInterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given VoidInterface object. */
    std::unique_ptr<VoidInterfaceTracer> m_tracer;
    /** The VoidInterface object which is traced */
    IVoidInterface& m_impl;
};
} // namespace TbSimple
} // namespace Test
