

#include "tb_simple/generated/monitor/nopropertiesinterface.tracedecorator.h"
#include "tb_simple/generated/monitor/nopropertiesinterface.tracer.h"

using namespace Test::TbSimple;
NoPropertiesInterfaceTraceDecorator::NoPropertiesInterfaceTraceDecorator(INoPropertiesInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<NoPropertiesInterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
NoPropertiesInterfaceTraceDecorator::~NoPropertiesInterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<NoPropertiesInterfaceTraceDecorator> NoPropertiesInterfaceTraceDecorator::connect(INoPropertiesInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<NoPropertiesInterfaceTraceDecorator>(new NoPropertiesInterfaceTraceDecorator(impl, tracer));
}
void NoPropertiesInterfaceTraceDecorator::funcVoid()
{
    m_tracer->trace_funcVoid();
    return m_impl.funcVoid();
}
std::future<void> NoPropertiesInterfaceTraceDecorator::funcVoidAsync( std::function<void(void)> callback)
{
    m_tracer->trace_funcVoid();
    return m_impl.funcVoidAsync( callback);
}
bool NoPropertiesInterfaceTraceDecorator::funcBool(bool paramBool)
{
    m_tracer->trace_funcBool(paramBool);
    return m_impl.funcBool(paramBool);
}
std::future<bool> NoPropertiesInterfaceTraceDecorator::funcBoolAsync(bool paramBool, std::function<void(bool)> callback)
{
    m_tracer->trace_funcBool(paramBool);
    return m_impl.funcBoolAsync(paramBool, callback);
}
void NoPropertiesInterfaceTraceDecorator::onSigVoid()
{
    m_tracer->trace_sigVoid();
}

void NoPropertiesInterfaceTraceDecorator::onSigBool(bool paramBool)
{
    m_tracer->trace_sigBool(paramBool);
}



INoPropertiesInterfacePublisher& NoPropertiesInterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
