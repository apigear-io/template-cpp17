

#include "tb_same2/generated/monitor/sameenum2interface.tracedecorator.h"
#include "tb_same2/generated/monitor/sameenum2interface.tracer.h"

using namespace Test::TbSame2;
SameEnum2InterfaceTraceDecorator::SameEnum2InterfaceTraceDecorator(ISameEnum2Interface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<SameEnum2InterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
SameEnum2InterfaceTraceDecorator::~SameEnum2InterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<SameEnum2InterfaceTraceDecorator> SameEnum2InterfaceTraceDecorator::connect(ISameEnum2Interface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<SameEnum2InterfaceTraceDecorator>(new SameEnum2InterfaceTraceDecorator(impl, tracer));
}
Enum1Enum SameEnum2InterfaceTraceDecorator::func1(Enum1Enum param1)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1(param1);
}
std::future<Enum1Enum> SameEnum2InterfaceTraceDecorator::func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1Async(param1, callback);
}
Enum1Enum SameEnum2InterfaceTraceDecorator::func2(Enum1Enum param1, Enum2Enum param2)
{
    m_tracer->trace_func2(param1, param2);
    return m_impl.func2(param1, param2);
}
std::future<Enum1Enum> SameEnum2InterfaceTraceDecorator::func2Async(Enum1Enum param1, Enum2Enum param2, std::function<void(Enum1Enum)> callback)
{
    m_tracer->trace_func2(param1, param2);
    return m_impl.func2Async(param1, param2, callback);
}
void SameEnum2InterfaceTraceDecorator::setProp1(Enum1Enum prop1)
{
    m_impl.setProp1(prop1);
}

Enum1Enum SameEnum2InterfaceTraceDecorator::getProp1() const
{
    return m_impl.getProp1();
}
void SameEnum2InterfaceTraceDecorator::setProp2(Enum2Enum prop2)
{
    m_impl.setProp2(prop2);
}

Enum2Enum SameEnum2InterfaceTraceDecorator::getProp2() const
{
    return m_impl.getProp2();
}
void SameEnum2InterfaceTraceDecorator::onSig1(Enum1Enum param1)
{
    m_tracer->trace_sig1(param1);
}

void SameEnum2InterfaceTraceDecorator::onSig2(Enum1Enum param1, Enum2Enum param2)
{
    m_tracer->trace_sig2(param1, param2);
}

void SameEnum2InterfaceTraceDecorator::onProp1Changed(Enum1Enum prop1)
{
    (void) prop1; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SameEnum2InterfaceTraceDecorator::onProp2Changed(Enum2Enum prop2)
{
    (void) prop2; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



ISameEnum2InterfacePublisher& SameEnum2InterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
