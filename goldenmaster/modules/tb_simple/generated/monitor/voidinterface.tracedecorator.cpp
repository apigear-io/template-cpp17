

#include "tb_simple/generated/monitor/voidinterface.tracedecorator.h"
#include "tb_simple/generated/monitor/voidinterface.tracer.h"

using namespace Test::TbSimple;
VoidInterfaceTraceDecorator::VoidInterfaceTraceDecorator(IVoidInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<VoidInterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
VoidInterfaceTraceDecorator::~VoidInterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<VoidInterfaceTraceDecorator> VoidInterfaceTraceDecorator::connect(IVoidInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<VoidInterfaceTraceDecorator>(new VoidInterfaceTraceDecorator(impl, tracer));
}
void VoidInterfaceTraceDecorator::funcVoid()
{
    m_tracer->trace_funcVoid();
    return m_impl.funcVoid();
}
std::future<void> VoidInterfaceTraceDecorator::funcVoidAsync( std::function<void(void)> callback)
{
    m_tracer->trace_funcVoid();
    return m_impl.funcVoidAsync( callback);
}
void VoidInterfaceTraceDecorator::onSigVoid()
{
    m_tracer->trace_sigVoid();
}



IVoidInterfacePublisher& VoidInterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
