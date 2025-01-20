

#include "tb_same1/generated/monitor/samestruct2interface.tracedecorator.h"
#include "tb_same1/generated/monitor/samestruct2interface.tracer.h"

using namespace Test::TbSame1;
SameStruct2InterfaceTraceDecorator::SameStruct2InterfaceTraceDecorator(ISameStruct2Interface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<SameStruct2InterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
SameStruct2InterfaceTraceDecorator::~SameStruct2InterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<SameStruct2InterfaceTraceDecorator> SameStruct2InterfaceTraceDecorator::connect(ISameStruct2Interface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<SameStruct2InterfaceTraceDecorator>(new SameStruct2InterfaceTraceDecorator(impl, tracer));
}
Struct1 SameStruct2InterfaceTraceDecorator::func1(const Struct1& param1)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1(param1);
}
std::future<Struct1> SameStruct2InterfaceTraceDecorator::func1Async(const Struct1& param1, std::function<void(Struct1)> callback)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1Async(param1, callback);
}
Struct1 SameStruct2InterfaceTraceDecorator::func2(const Struct1& param1, const Struct2& param2)
{
    m_tracer->trace_func2(param1, param2);
    return m_impl.func2(param1, param2);
}
std::future<Struct1> SameStruct2InterfaceTraceDecorator::func2Async(const Struct1& param1, const Struct2& param2, std::function<void(Struct1)> callback)
{
    m_tracer->trace_func2(param1, param2);
    return m_impl.func2Async(param1, param2, callback);
}
void SameStruct2InterfaceTraceDecorator::setProp1(const Struct2& prop1)
{
    m_impl.setProp1(prop1);
}

const Struct2& SameStruct2InterfaceTraceDecorator::getProp1() const
{
    return m_impl.getProp1();
}
void SameStruct2InterfaceTraceDecorator::setProp2(const Struct2& prop2)
{
    m_impl.setProp2(prop2);
}

const Struct2& SameStruct2InterfaceTraceDecorator::getProp2() const
{
    return m_impl.getProp2();
}
void SameStruct2InterfaceTraceDecorator::onSig1(const Struct1& param1)
{
    m_tracer->trace_sig1(param1);
}

void SameStruct2InterfaceTraceDecorator::onSig2(const Struct1& param1, const Struct2& param2)
{
    m_tracer->trace_sig2(param1, param2);
}

void SameStruct2InterfaceTraceDecorator::onProp1Changed(const Struct2& prop1)
{
    (void) prop1; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SameStruct2InterfaceTraceDecorator::onProp2Changed(const Struct2& prop2)
{
    (void) prop2; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



ISameStruct2InterfacePublisher& SameStruct2InterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
