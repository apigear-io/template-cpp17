
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include <memory>

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace TbSimple {

class EmptyInterfaceTracer;

class TEST_TB_SIMPLE_EXPORT EmptyInterfaceTraceDecorator : public IEmptyInterface, public IEmptyInterfaceSubscriber
{
protected:
    /** 
    * ctor
    * Subscribes for signal emission.
    * @param impl The EmptyInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    explicit EmptyInterfaceTraceDecorator(IEmptyInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
public:
    /** 
    * Use this function to get the EmptyInterfaceTraceDecorator object.
    * @param impl The EmptyInterface object to trace.
    * @param tracer A Poco tracer to which traces are put, wrapped with relevant object info.
    */
    static std::unique_ptr<EmptyInterfaceTraceDecorator> connect(IEmptyInterface& impl, ApiGear::PocoImpl::Tracer& tracer);
    /**
    * dtor
    * Unsubscribes from signal emission.
    */
    virtual ~EmptyInterfaceTraceDecorator();


    /**
    * Access to a publisher, use it to subscribe for EmptyInterface changes and signal emission.
    * @return The publisher for EmptyInterface.
    */
    IEmptyInterfacePublisher& _getPublisher() const override;
private:
    /** A tracer that provides the traces for given EmptyInterface object. */
    std::unique_ptr<EmptyInterfaceTracer> m_tracer;
    /** The EmptyInterface object which is traced */
    IEmptyInterface& m_impl;
};
} // namespace TbSimple
} // namespace Test
