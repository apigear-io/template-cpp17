

#include "tb_same1/generated/monitor/sameenum1interface.tracedecorator.h"
#include "tb_same1/generated/monitor/sameenum1interface.tracer.h"

using namespace Test::TbSame1;
SameEnum1InterfaceTraceDecorator::SameEnum1InterfaceTraceDecorator(ISameEnum1Interface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<SameEnum1InterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
SameEnum1InterfaceTraceDecorator::~SameEnum1InterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<SameEnum1InterfaceTraceDecorator> SameEnum1InterfaceTraceDecorator::connect(ISameEnum1Interface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<SameEnum1InterfaceTraceDecorator>(new SameEnum1InterfaceTraceDecorator(impl, tracer));
}
Enum1Enum SameEnum1InterfaceTraceDecorator::func1(Enum1Enum param1)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1(param1);
}
std::future<Enum1Enum> SameEnum1InterfaceTraceDecorator::func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1Async(param1, callback);
}
void SameEnum1InterfaceTraceDecorator::setProp1(Enum1Enum prop1)
{
    m_impl.setProp1(prop1);
}

Enum1Enum SameEnum1InterfaceTraceDecorator::getProp1() const
{
    return m_impl.getProp1();
}
void SameEnum1InterfaceTraceDecorator::onSig1(Enum1Enum param1)
{
    m_tracer->trace_sig1(param1);
}

void SameEnum1InterfaceTraceDecorator::onProp1Changed(Enum1Enum prop1)
{
    (void) prop1; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



ISameEnum1InterfacePublisher& SameEnum1InterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
