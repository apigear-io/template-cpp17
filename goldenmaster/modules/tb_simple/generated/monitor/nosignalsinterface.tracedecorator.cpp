

#include "tb_simple/generated/monitor/nosignalsinterface.tracedecorator.h"
#include "tb_simple/generated/monitor/nosignalsinterface.tracer.h"

using namespace Test::TbSimple;
NoSignalsInterfaceTraceDecorator::NoSignalsInterfaceTraceDecorator(INoSignalsInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<NoSignalsInterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
NoSignalsInterfaceTraceDecorator::~NoSignalsInterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<NoSignalsInterfaceTraceDecorator> NoSignalsInterfaceTraceDecorator::connect(INoSignalsInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<NoSignalsInterfaceTraceDecorator>(new NoSignalsInterfaceTraceDecorator(impl, tracer));
}
void NoSignalsInterfaceTraceDecorator::funcVoid()
{
    m_tracer->trace_funcVoid();
    return m_impl.funcVoid();
}
std::future<void> NoSignalsInterfaceTraceDecorator::funcVoidAsync( std::function<void(void)> callback)
{
    m_tracer->trace_funcVoid();
    return m_impl.funcVoidAsync( callback);
}
bool NoSignalsInterfaceTraceDecorator::funcBool(bool paramBool)
{
    m_tracer->trace_funcBool(paramBool);
    return m_impl.funcBool(paramBool);
}
std::future<bool> NoSignalsInterfaceTraceDecorator::funcBoolAsync(bool paramBool, std::function<void(bool)> callback)
{
    m_tracer->trace_funcBool(paramBool);
    return m_impl.funcBoolAsync(paramBool, callback);
}
void NoSignalsInterfaceTraceDecorator::setPropBool(bool propBool)
{
    m_impl.setPropBool(propBool);
}

bool NoSignalsInterfaceTraceDecorator::getPropBool() const
{
    return m_impl.getPropBool();
}
void NoSignalsInterfaceTraceDecorator::setPropInt(int propInt)
{
    m_impl.setPropInt(propInt);
}

int NoSignalsInterfaceTraceDecorator::getPropInt() const
{
    return m_impl.getPropInt();
}
void NoSignalsInterfaceTraceDecorator::onPropBoolChanged(bool propBool)
{
    (void) propBool; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void NoSignalsInterfaceTraceDecorator::onPropIntChanged(int propInt)
{
    (void) propInt; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



INoSignalsInterfacePublisher& NoSignalsInterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
