

#include "testbed1/generated/monitor/structarrayinterface.tracedecorator.h"
#include "testbed1/generated/monitor/structarrayinterface.tracer.h"

using namespace Test::Testbed1;
StructArrayInterfaceTraceDecorator::StructArrayInterfaceTraceDecorator(IStructArrayInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<StructArrayInterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
StructArrayInterfaceTraceDecorator::~StructArrayInterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<StructArrayInterfaceTraceDecorator> StructArrayInterfaceTraceDecorator::connect(IStructArrayInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<StructArrayInterfaceTraceDecorator>(new StructArrayInterfaceTraceDecorator(impl, tracer));
}
std::list<StructBool> StructArrayInterfaceTraceDecorator::funcBool(const std::list<StructBool>& paramBool)
{
    m_tracer->trace_funcBool(paramBool);
    return m_impl.funcBool(paramBool);
}
std::future<std::list<StructBool>> StructArrayInterfaceTraceDecorator::funcBoolAsync(const std::list<StructBool>& paramBool, std::function<void(std::list<StructBool>)> callback)
{
    m_tracer->trace_funcBool(paramBool);
    return m_impl.funcBoolAsync(paramBool, callback);
}
std::list<StructInt> StructArrayInterfaceTraceDecorator::funcInt(const std::list<StructInt>& paramInt)
{
    m_tracer->trace_funcInt(paramInt);
    return m_impl.funcInt(paramInt);
}
std::future<std::list<StructInt>> StructArrayInterfaceTraceDecorator::funcIntAsync(const std::list<StructInt>& paramInt, std::function<void(std::list<StructInt>)> callback)
{
    m_tracer->trace_funcInt(paramInt);
    return m_impl.funcIntAsync(paramInt, callback);
}
std::list<StructFloat> StructArrayInterfaceTraceDecorator::funcFloat(const std::list<StructFloat>& paramFloat)
{
    m_tracer->trace_funcFloat(paramFloat);
    return m_impl.funcFloat(paramFloat);
}
std::future<std::list<StructFloat>> StructArrayInterfaceTraceDecorator::funcFloatAsync(const std::list<StructFloat>& paramFloat, std::function<void(std::list<StructFloat>)> callback)
{
    m_tracer->trace_funcFloat(paramFloat);
    return m_impl.funcFloatAsync(paramFloat, callback);
}
std::list<StructString> StructArrayInterfaceTraceDecorator::funcString(const std::list<StructString>& paramString)
{
    m_tracer->trace_funcString(paramString);
    return m_impl.funcString(paramString);
}
std::future<std::list<StructString>> StructArrayInterfaceTraceDecorator::funcStringAsync(const std::list<StructString>& paramString, std::function<void(std::list<StructString>)> callback)
{
    m_tracer->trace_funcString(paramString);
    return m_impl.funcStringAsync(paramString, callback);
}
void StructArrayInterfaceTraceDecorator::setPropBool(const std::list<StructBool>& propBool)
{
    m_impl.setPropBool(propBool);
}

const std::list<StructBool>& StructArrayInterfaceTraceDecorator::getPropBool() const
{
    return m_impl.getPropBool();
}
void StructArrayInterfaceTraceDecorator::setPropInt(const std::list<StructInt>& propInt)
{
    m_impl.setPropInt(propInt);
}

const std::list<StructInt>& StructArrayInterfaceTraceDecorator::getPropInt() const
{
    return m_impl.getPropInt();
}
void StructArrayInterfaceTraceDecorator::setPropFloat(const std::list<StructFloat>& propFloat)
{
    m_impl.setPropFloat(propFloat);
}

const std::list<StructFloat>& StructArrayInterfaceTraceDecorator::getPropFloat() const
{
    return m_impl.getPropFloat();
}
void StructArrayInterfaceTraceDecorator::setPropString(const std::list<StructString>& propString)
{
    m_impl.setPropString(propString);
}

const std::list<StructString>& StructArrayInterfaceTraceDecorator::getPropString() const
{
    return m_impl.getPropString();
}
void StructArrayInterfaceTraceDecorator::onSigBool(const std::list<StructBool>& paramBool)
{
    m_tracer->trace_sigBool(paramBool);
}

void StructArrayInterfaceTraceDecorator::onSigInt(const std::list<StructInt>& paramInt)
{
    m_tracer->trace_sigInt(paramInt);
}

void StructArrayInterfaceTraceDecorator::onSigFloat(const std::list<StructFloat>& paramFloat)
{
    m_tracer->trace_sigFloat(paramFloat);
}

void StructArrayInterfaceTraceDecorator::onSigString(const std::list<StructString>& paramString)
{
    m_tracer->trace_sigString(paramString);
}

void StructArrayInterfaceTraceDecorator::onPropBoolChanged(const std::list<StructBool>& propBool)
{
    (void) propBool; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void StructArrayInterfaceTraceDecorator::onPropIntChanged(const std::list<StructInt>& propInt)
{
    (void) propInt; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void StructArrayInterfaceTraceDecorator::onPropFloatChanged(const std::list<StructFloat>& propFloat)
{
    (void) propFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void StructArrayInterfaceTraceDecorator::onPropStringChanged(const std::list<StructString>& propString)
{
    (void) propString; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



IStructArrayInterfacePublisher& StructArrayInterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
