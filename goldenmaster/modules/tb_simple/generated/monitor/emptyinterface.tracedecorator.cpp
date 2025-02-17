

#include "tb_simple/generated/monitor/emptyinterface.tracedecorator.h"
#include "tb_simple/generated/monitor/emptyinterface.tracer.h"

using namespace Test::TbSimple;
EmptyInterfaceTraceDecorator::EmptyInterfaceTraceDecorator(IEmptyInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<EmptyInterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
EmptyInterfaceTraceDecorator::~EmptyInterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<EmptyInterfaceTraceDecorator> EmptyInterfaceTraceDecorator::connect(IEmptyInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<EmptyInterfaceTraceDecorator>(new EmptyInterfaceTraceDecorator(impl, tracer));
}


IEmptyInterfacePublisher& EmptyInterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
