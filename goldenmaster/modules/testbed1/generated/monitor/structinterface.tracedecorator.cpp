

#include "testbed1/generated/monitor/structinterface.tracedecorator.h"
#include "testbed1/generated/monitor/structinterface.tracer.h"

using namespace Test::Testbed1;
StructInterfaceTraceDecorator::StructInterfaceTraceDecorator(IStructInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<StructInterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
StructInterfaceTraceDecorator::~StructInterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<StructInterfaceTraceDecorator> StructInterfaceTraceDecorator::connect(IStructInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<StructInterfaceTraceDecorator>(new StructInterfaceTraceDecorator(impl, tracer));
}
StructBool StructInterfaceTraceDecorator::funcBool(const StructBool& paramBool)
{
    m_tracer->trace_funcBool(paramBool);
    return m_impl.funcBool(paramBool);
}
std::future<StructBool> StructInterfaceTraceDecorator::funcBoolAsync(const StructBool& paramBool, std::function<void(StructBool)> callback)
{
    m_tracer->trace_funcBool(paramBool);
    return m_impl.funcBoolAsync(paramBool, callback);
}
StructBool StructInterfaceTraceDecorator::funcInt(const StructInt& paramInt)
{
    m_tracer->trace_funcInt(paramInt);
    return m_impl.funcInt(paramInt);
}
std::future<StructBool> StructInterfaceTraceDecorator::funcIntAsync(const StructInt& paramInt, std::function<void(StructBool)> callback)
{
    m_tracer->trace_funcInt(paramInt);
    return m_impl.funcIntAsync(paramInt, callback);
}
StructFloat StructInterfaceTraceDecorator::funcFloat(const StructFloat& paramFloat)
{
    m_tracer->trace_funcFloat(paramFloat);
    return m_impl.funcFloat(paramFloat);
}
std::future<StructFloat> StructInterfaceTraceDecorator::funcFloatAsync(const StructFloat& paramFloat, std::function<void(StructFloat)> callback)
{
    m_tracer->trace_funcFloat(paramFloat);
    return m_impl.funcFloatAsync(paramFloat, callback);
}
StructString StructInterfaceTraceDecorator::funcString(const StructString& paramString)
{
    m_tracer->trace_funcString(paramString);
    return m_impl.funcString(paramString);
}
std::future<StructString> StructInterfaceTraceDecorator::funcStringAsync(const StructString& paramString, std::function<void(StructString)> callback)
{
    m_tracer->trace_funcString(paramString);
    return m_impl.funcStringAsync(paramString, callback);
}
void StructInterfaceTraceDecorator::setPropBool(const StructBool& propBool)
{
    m_impl.setPropBool(propBool);
}

const StructBool& StructInterfaceTraceDecorator::getPropBool() const
{
    return m_impl.getPropBool();
}
void StructInterfaceTraceDecorator::setPropInt(const StructInt& propInt)
{
    m_impl.setPropInt(propInt);
}

const StructInt& StructInterfaceTraceDecorator::getPropInt() const
{
    return m_impl.getPropInt();
}
void StructInterfaceTraceDecorator::setPropFloat(const StructFloat& propFloat)
{
    m_impl.setPropFloat(propFloat);
}

const StructFloat& StructInterfaceTraceDecorator::getPropFloat() const
{
    return m_impl.getPropFloat();
}
void StructInterfaceTraceDecorator::setPropString(const StructString& propString)
{
    m_impl.setPropString(propString);
}

const StructString& StructInterfaceTraceDecorator::getPropString() const
{
    return m_impl.getPropString();
}
void StructInterfaceTraceDecorator::onSigBool(const StructBool& paramBool)
{
    m_tracer->trace_sigBool(paramBool);
}

void StructInterfaceTraceDecorator::onSigInt(const StructInt& paramInt)
{
    m_tracer->trace_sigInt(paramInt);
}

void StructInterfaceTraceDecorator::onSigFloat(const StructFloat& paramFloat)
{
    m_tracer->trace_sigFloat(paramFloat);
}

void StructInterfaceTraceDecorator::onSigString(const StructString& paramString)
{
    m_tracer->trace_sigString(paramString);
}

void StructInterfaceTraceDecorator::onPropBoolChanged(const StructBool& propBool)
{
    (void) propBool; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void StructInterfaceTraceDecorator::onPropIntChanged(const StructInt& propInt)
{
    (void) propInt; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void StructInterfaceTraceDecorator::onPropFloatChanged(const StructFloat& propFloat)
{
    (void) propFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void StructInterfaceTraceDecorator::onPropStringChanged(const StructString& propString)
{
    (void) propString; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



IStructInterfacePublisher& StructInterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
