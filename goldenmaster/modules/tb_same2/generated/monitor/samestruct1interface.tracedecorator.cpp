

#include "tb_same2/generated/monitor/samestruct1interface.tracedecorator.h"
#include "tb_same2/generated/monitor/samestruct1interface.tracer.h"

using namespace Test::TbSame2;
SameStruct1InterfaceTraceDecorator::SameStruct1InterfaceTraceDecorator(ISameStruct1Interface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<SameStruct1InterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
SameStruct1InterfaceTraceDecorator::~SameStruct1InterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<SameStruct1InterfaceTraceDecorator> SameStruct1InterfaceTraceDecorator::connect(ISameStruct1Interface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<SameStruct1InterfaceTraceDecorator>(new SameStruct1InterfaceTraceDecorator(impl, tracer));
}
Struct1 SameStruct1InterfaceTraceDecorator::func1(const Struct1& param1)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1(param1);
}
std::future<Struct1> SameStruct1InterfaceTraceDecorator::func1Async(const Struct1& param1, std::function<void(Struct1)> callback)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1Async(param1, callback);
}
void SameStruct1InterfaceTraceDecorator::setProp1(const Struct1& prop1)
{
    m_impl.setProp1(prop1);
}

const Struct1& SameStruct1InterfaceTraceDecorator::getProp1() const
{
    return m_impl.getProp1();
}
void SameStruct1InterfaceTraceDecorator::onSig1(const Struct1& param1)
{
    m_tracer->trace_sig1(param1);
}

void SameStruct1InterfaceTraceDecorator::onProp1Changed(const Struct1& prop1)
{
    (void) prop1; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



ISameStruct1InterfacePublisher& SameStruct1InterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
