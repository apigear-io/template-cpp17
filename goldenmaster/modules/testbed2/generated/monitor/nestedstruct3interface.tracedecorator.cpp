

#include "testbed2/generated/monitor/nestedstruct3interface.tracedecorator.h"
#include "testbed2/generated/monitor/nestedstruct3interface.tracer.h"

using namespace Test::Testbed2;
NestedStruct3InterfaceTraceDecorator::NestedStruct3InterfaceTraceDecorator(INestedStruct3Interface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<NestedStruct3InterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
NestedStruct3InterfaceTraceDecorator::~NestedStruct3InterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<NestedStruct3InterfaceTraceDecorator> NestedStruct3InterfaceTraceDecorator::connect(INestedStruct3Interface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<NestedStruct3InterfaceTraceDecorator>(new NestedStruct3InterfaceTraceDecorator(impl, tracer));
}
NestedStruct1 NestedStruct3InterfaceTraceDecorator::func1(const NestedStruct1& param1)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1(param1);
}
std::future<NestedStruct1> NestedStruct3InterfaceTraceDecorator::func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1Async(param1, callback);
}
NestedStruct1 NestedStruct3InterfaceTraceDecorator::func2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    m_tracer->trace_func2(param1, param2);
    return m_impl.func2(param1, param2);
}
std::future<NestedStruct1> NestedStruct3InterfaceTraceDecorator::func2Async(const NestedStruct1& param1, const NestedStruct2& param2, std::function<void(NestedStruct1)> callback)
{
    m_tracer->trace_func2(param1, param2);
    return m_impl.func2Async(param1, param2, callback);
}
NestedStruct1 NestedStruct3InterfaceTraceDecorator::func3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3)
{
    m_tracer->trace_func3(param1, param2, param3);
    return m_impl.func3(param1, param2, param3);
}
std::future<NestedStruct1> NestedStruct3InterfaceTraceDecorator::func3Async(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3, std::function<void(NestedStruct1)> callback)
{
    m_tracer->trace_func3(param1, param2, param3);
    return m_impl.func3Async(param1, param2, param3, callback);
}
void NestedStruct3InterfaceTraceDecorator::setProp1(const NestedStruct1& prop1)
{
    m_impl.setProp1(prop1);
}

const NestedStruct1& NestedStruct3InterfaceTraceDecorator::getProp1() const
{
    return m_impl.getProp1();
}
void NestedStruct3InterfaceTraceDecorator::setProp2(const NestedStruct2& prop2)
{
    m_impl.setProp2(prop2);
}

const NestedStruct2& NestedStruct3InterfaceTraceDecorator::getProp2() const
{
    return m_impl.getProp2();
}
void NestedStruct3InterfaceTraceDecorator::setProp3(const NestedStruct3& prop3)
{
    m_impl.setProp3(prop3);
}

const NestedStruct3& NestedStruct3InterfaceTraceDecorator::getProp3() const
{
    return m_impl.getProp3();
}
void NestedStruct3InterfaceTraceDecorator::onSig1(const NestedStruct1& param1)
{
    m_tracer->trace_sig1(param1);
}

void NestedStruct3InterfaceTraceDecorator::onSig2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    m_tracer->trace_sig2(param1, param2);
}

void NestedStruct3InterfaceTraceDecorator::onSig3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3)
{
    m_tracer->trace_sig3(param1, param2, param3);
}

void NestedStruct3InterfaceTraceDecorator::onProp1Changed(const NestedStruct1& prop1)
{
    (void) prop1; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void NestedStruct3InterfaceTraceDecorator::onProp2Changed(const NestedStruct2& prop2)
{
    (void) prop2; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void NestedStruct3InterfaceTraceDecorator::onProp3Changed(const NestedStruct3& prop3)
{
    (void) prop3; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



INestedStruct3InterfacePublisher& NestedStruct3InterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
