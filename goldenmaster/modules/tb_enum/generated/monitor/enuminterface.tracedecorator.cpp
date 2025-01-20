

#include "tb_enum/generated/monitor/enuminterface.tracedecorator.h"
#include "tb_enum/generated/monitor/enuminterface.tracer.h"

using namespace Test::TbEnum;
EnumInterfaceTraceDecorator::EnumInterfaceTraceDecorator(IEnumInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<EnumInterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
EnumInterfaceTraceDecorator::~EnumInterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<EnumInterfaceTraceDecorator> EnumInterfaceTraceDecorator::connect(IEnumInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<EnumInterfaceTraceDecorator>(new EnumInterfaceTraceDecorator(impl, tracer));
}
Enum0Enum EnumInterfaceTraceDecorator::func0(Enum0Enum param0)
{
    m_tracer->trace_func0(param0);
    return m_impl.func0(param0);
}
std::future<Enum0Enum> EnumInterfaceTraceDecorator::func0Async(Enum0Enum param0, std::function<void(Enum0Enum)> callback)
{
    m_tracer->trace_func0(param0);
    return m_impl.func0Async(param0, callback);
}
Enum1Enum EnumInterfaceTraceDecorator::func1(Enum1Enum param1)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1(param1);
}
std::future<Enum1Enum> EnumInterfaceTraceDecorator::func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback)
{
    m_tracer->trace_func1(param1);
    return m_impl.func1Async(param1, callback);
}
Enum2Enum EnumInterfaceTraceDecorator::func2(Enum2Enum param2)
{
    m_tracer->trace_func2(param2);
    return m_impl.func2(param2);
}
std::future<Enum2Enum> EnumInterfaceTraceDecorator::func2Async(Enum2Enum param2, std::function<void(Enum2Enum)> callback)
{
    m_tracer->trace_func2(param2);
    return m_impl.func2Async(param2, callback);
}
Enum3Enum EnumInterfaceTraceDecorator::func3(Enum3Enum param3)
{
    m_tracer->trace_func3(param3);
    return m_impl.func3(param3);
}
std::future<Enum3Enum> EnumInterfaceTraceDecorator::func3Async(Enum3Enum param3, std::function<void(Enum3Enum)> callback)
{
    m_tracer->trace_func3(param3);
    return m_impl.func3Async(param3, callback);
}
void EnumInterfaceTraceDecorator::setProp0(Enum0Enum prop0)
{
    m_impl.setProp0(prop0);
}

Enum0Enum EnumInterfaceTraceDecorator::getProp0() const
{
    return m_impl.getProp0();
}
void EnumInterfaceTraceDecorator::setProp1(Enum1Enum prop1)
{
    m_impl.setProp1(prop1);
}

Enum1Enum EnumInterfaceTraceDecorator::getProp1() const
{
    return m_impl.getProp1();
}
void EnumInterfaceTraceDecorator::setProp2(Enum2Enum prop2)
{
    m_impl.setProp2(prop2);
}

Enum2Enum EnumInterfaceTraceDecorator::getProp2() const
{
    return m_impl.getProp2();
}
void EnumInterfaceTraceDecorator::setProp3(Enum3Enum prop3)
{
    m_impl.setProp3(prop3);
}

Enum3Enum EnumInterfaceTraceDecorator::getProp3() const
{
    return m_impl.getProp3();
}
void EnumInterfaceTraceDecorator::onSig0(Enum0Enum param0)
{
    m_tracer->trace_sig0(param0);
}

void EnumInterfaceTraceDecorator::onSig1(Enum1Enum param1)
{
    m_tracer->trace_sig1(param1);
}

void EnumInterfaceTraceDecorator::onSig2(Enum2Enum param2)
{
    m_tracer->trace_sig2(param2);
}

void EnumInterfaceTraceDecorator::onSig3(Enum3Enum param3)
{
    m_tracer->trace_sig3(param3);
}

void EnumInterfaceTraceDecorator::onProp0Changed(Enum0Enum prop0)
{
    (void) prop0; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void EnumInterfaceTraceDecorator::onProp1Changed(Enum1Enum prop1)
{
    (void) prop1; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void EnumInterfaceTraceDecorator::onProp2Changed(Enum2Enum prop2)
{
    (void) prop2; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void EnumInterfaceTraceDecorator::onProp3Changed(Enum3Enum prop3)
{
    (void) prop3; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



IEnumInterfacePublisher& EnumInterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
