

#include "testbed2/generated/monitor/nestedstruct2interface.tracedecorator.h"
#include "testbed2/generated/monitor/nestedstruct2interface.tracer.h"

using namespace Test::Testbed2;
NestedStruct2InterfaceTraceDecorator::NestedStruct2InterfaceTraceDecorator(INestedStruct2Interface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<NestedStruct2InterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
NestedStruct2InterfaceTraceDecorator::~NestedStruct2InterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<NestedStruct2InterfaceTraceDecorator> NestedStruct2InterfaceTraceDecorator::connect(INestedStruct2Interface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<NestedStruct2InterfaceTraceDecorator>(new NestedStruct2InterfaceTraceDecorator(impl, tracer));
}
NestedStruct1 NestedStruct2InterfaceTraceDecorator::func1(const NestedStruct1& param1)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1(param1);
}
std::future<NestedStruct1> NestedStruct2InterfaceTraceDecorator::func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1Async(param1, callback);
}
NestedStruct1 NestedStruct2InterfaceTraceDecorator::func2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    m_tracer->trace_func2(param1, param2);
    return m_impl.func2(param1, param2);
}
std::future<NestedStruct1> NestedStruct2InterfaceTraceDecorator::func2Async(const NestedStruct1& param1, const NestedStruct2& param2, std::function<void(NestedStruct1)> callback)
{
    m_tracer->trace_func2(param1, param2);
    return m_impl.func2Async(param1, param2, callback);
}
void NestedStruct2InterfaceTraceDecorator::setProp1(const NestedStruct1& prop1)
{
    m_impl.setProp1(prop1);
}

const NestedStruct1& NestedStruct2InterfaceTraceDecorator::getProp1() const
{
    return m_impl.getProp1();
}
void NestedStruct2InterfaceTraceDecorator::setProp2(const NestedStruct2& prop2)
{
    m_impl.setProp2(prop2);
}

const NestedStruct2& NestedStruct2InterfaceTraceDecorator::getProp2() const
{
    return m_impl.getProp2();
}
void NestedStruct2InterfaceTraceDecorator::onSig1(const NestedStruct1& param1)
{
    m_tracer->trace_sig1(param1);
}

void NestedStruct2InterfaceTraceDecorator::onSig2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    m_tracer->trace_sig2(param1, param2);
}

void NestedStruct2InterfaceTraceDecorator::onProp1Changed(const NestedStruct1& prop1)
{
    (void) prop1; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void NestedStruct2InterfaceTraceDecorator::onProp2Changed(const NestedStruct2& prop2)
{
    (void) prop2; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



INestedStruct2InterfacePublisher& NestedStruct2InterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
