

#include "testbed1/generated/monitor/structarray2interface.tracedecorator.h"
#include "testbed1/generated/monitor/structarray2interface.tracer.h"

using namespace Test::Testbed1;
StructArray2InterfaceTraceDecorator::StructArray2InterfaceTraceDecorator(IStructArray2Interface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<StructArray2InterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
StructArray2InterfaceTraceDecorator::~StructArray2InterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<StructArray2InterfaceTraceDecorator> StructArray2InterfaceTraceDecorator::connect(IStructArray2Interface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<StructArray2InterfaceTraceDecorator>(new StructArray2InterfaceTraceDecorator(impl, tracer));
}
std::list<StructBool> StructArray2InterfaceTraceDecorator::funcBool(const StructBoolWithArray& paramBool)
{
    m_tracer->trace_funcBool(paramBool);
    return m_impl.funcBool(paramBool);
}
std::future<std::list<StructBool>> StructArray2InterfaceTraceDecorator::funcBoolAsync(const StructBoolWithArray& paramBool, std::function<void(std::list<StructBool>)> callback)
{
    m_tracer->trace_funcBool(paramBool);
    return m_impl.funcBoolAsync(paramBool, callback);
}
std::list<StructInt> StructArray2InterfaceTraceDecorator::funcInt(const StructIntWithArray& paramInt)
{
    m_tracer->trace_funcInt(paramInt);
    return m_impl.funcInt(paramInt);
}
std::future<std::list<StructInt>> StructArray2InterfaceTraceDecorator::funcIntAsync(const StructIntWithArray& paramInt, std::function<void(std::list<StructInt>)> callback)
{
    m_tracer->trace_funcInt(paramInt);
    return m_impl.funcIntAsync(paramInt, callback);
}
std::list<StructFloat> StructArray2InterfaceTraceDecorator::funcFloat(const StructFloatWithArray& paramFloat)
{
    m_tracer->trace_funcFloat(paramFloat);
    return m_impl.funcFloat(paramFloat);
}
std::future<std::list<StructFloat>> StructArray2InterfaceTraceDecorator::funcFloatAsync(const StructFloatWithArray& paramFloat, std::function<void(std::list<StructFloat>)> callback)
{
    m_tracer->trace_funcFloat(paramFloat);
    return m_impl.funcFloatAsync(paramFloat, callback);
}
std::list<StructString> StructArray2InterfaceTraceDecorator::funcString(const StructStringWithArray& paramString)
{
    m_tracer->trace_funcString(paramString);
    return m_impl.funcString(paramString);
}
std::future<std::list<StructString>> StructArray2InterfaceTraceDecorator::funcStringAsync(const StructStringWithArray& paramString, std::function<void(std::list<StructString>)> callback)
{
    m_tracer->trace_funcString(paramString);
    return m_impl.funcStringAsync(paramString, callback);
}
std::list<Enum0Enum> StructArray2InterfaceTraceDecorator::funcEnum(const StructEnumWithArray& paramEnum)
{
    m_tracer->trace_funcEnum(paramEnum);
    return m_impl.funcEnum(paramEnum);
}
std::future<std::list<Enum0Enum>> StructArray2InterfaceTraceDecorator::funcEnumAsync(const StructEnumWithArray& paramEnum, std::function<void(std::list<Enum0Enum>)> callback)
{
    m_tracer->trace_funcEnum(paramEnum);
    return m_impl.funcEnumAsync(paramEnum, callback);
}
void StructArray2InterfaceTraceDecorator::setPropBool(const StructBoolWithArray& propBool)
{
    m_impl.setPropBool(propBool);
}

const StructBoolWithArray& StructArray2InterfaceTraceDecorator::getPropBool() const
{
    return m_impl.getPropBool();
}
void StructArray2InterfaceTraceDecorator::setPropInt(const StructIntWithArray& propInt)
{
    m_impl.setPropInt(propInt);
}

const StructIntWithArray& StructArray2InterfaceTraceDecorator::getPropInt() const
{
    return m_impl.getPropInt();
}
void StructArray2InterfaceTraceDecorator::setPropFloat(const StructFloatWithArray& propFloat)
{
    m_impl.setPropFloat(propFloat);
}

const StructFloatWithArray& StructArray2InterfaceTraceDecorator::getPropFloat() const
{
    return m_impl.getPropFloat();
}
void StructArray2InterfaceTraceDecorator::setPropString(const StructStringWithArray& propString)
{
    m_impl.setPropString(propString);
}

const StructStringWithArray& StructArray2InterfaceTraceDecorator::getPropString() const
{
    return m_impl.getPropString();
}
void StructArray2InterfaceTraceDecorator::setPropEnum(const StructEnumWithArray& propEnum)
{
    m_impl.setPropEnum(propEnum);
}

const StructEnumWithArray& StructArray2InterfaceTraceDecorator::getPropEnum() const
{
    return m_impl.getPropEnum();
}
void StructArray2InterfaceTraceDecorator::onSigBool(const StructBoolWithArray& paramBool)
{
    m_tracer->trace_sigBool(paramBool);
}

void StructArray2InterfaceTraceDecorator::onSigInt(const StructIntWithArray& paramInt)
{
    m_tracer->trace_sigInt(paramInt);
}

void StructArray2InterfaceTraceDecorator::onSigFloat(const StructFloatWithArray& paramFloat)
{
    m_tracer->trace_sigFloat(paramFloat);
}

void StructArray2InterfaceTraceDecorator::onSigString(const StructStringWithArray& paramString)
{
    m_tracer->trace_sigString(paramString);
}

void StructArray2InterfaceTraceDecorator::onPropBoolChanged(const StructBoolWithArray& propBool)
{
    (void) propBool; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void StructArray2InterfaceTraceDecorator::onPropIntChanged(const StructIntWithArray& propInt)
{
    (void) propInt; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void StructArray2InterfaceTraceDecorator::onPropFloatChanged(const StructFloatWithArray& propFloat)
{
    (void) propFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void StructArray2InterfaceTraceDecorator::onPropStringChanged(const StructStringWithArray& propString)
{
    (void) propString; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void StructArray2InterfaceTraceDecorator::onPropEnumChanged(const StructEnumWithArray& propEnum)
{
    (void) propEnum; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



IStructArray2InterfacePublisher& StructArray2InterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
