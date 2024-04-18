

#include "tb_simple/generated/monitor/simplearrayinterface.tracedecorator.h"
#include "tb_simple/generated/monitor/simplearrayinterface.tracer.h"

using namespace Test::TbSimple;
SimpleArrayInterfaceTraceDecorator::SimpleArrayInterfaceTraceDecorator(ISimpleArrayInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<SimpleArrayInterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
SimpleArrayInterfaceTraceDecorator::~SimpleArrayInterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<SimpleArrayInterfaceTraceDecorator> SimpleArrayInterfaceTraceDecorator::connect(ISimpleArrayInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<SimpleArrayInterfaceTraceDecorator>(new SimpleArrayInterfaceTraceDecorator(impl, tracer));
}
std::list<bool> SimpleArrayInterfaceTraceDecorator::funcBool(const std::list<bool>& paramBool)
{
    m_tracer->trace_funcBool(paramBool);
    return m_impl.funcBool(paramBool);
}
std::future<std::list<bool>> SimpleArrayInterfaceTraceDecorator::funcBoolAsync(const std::list<bool>& paramBool)
{
    m_tracer->trace_funcBool(paramBool);
    return m_impl.funcBoolAsync(paramBool);
}
std::list<int> SimpleArrayInterfaceTraceDecorator::funcInt(const std::list<int>& paramInt)
{
    m_tracer->trace_funcInt(paramInt);
    return m_impl.funcInt(paramInt);
}
std::future<std::list<int>> SimpleArrayInterfaceTraceDecorator::funcIntAsync(const std::list<int>& paramInt)
{
    m_tracer->trace_funcInt(paramInt);
    return m_impl.funcIntAsync(paramInt);
}
std::list<int32_t> SimpleArrayInterfaceTraceDecorator::funcInt32(const std::list<int32_t>& paramInt32)
{
    m_tracer->trace_funcInt32(paramInt32);
    return m_impl.funcInt32(paramInt32);
}
std::future<std::list<int32_t>> SimpleArrayInterfaceTraceDecorator::funcInt32Async(const std::list<int32_t>& paramInt32)
{
    m_tracer->trace_funcInt32(paramInt32);
    return m_impl.funcInt32Async(paramInt32);
}
std::list<int64_t> SimpleArrayInterfaceTraceDecorator::funcInt64(const std::list<int64_t>& paramInt64)
{
    m_tracer->trace_funcInt64(paramInt64);
    return m_impl.funcInt64(paramInt64);
}
std::future<std::list<int64_t>> SimpleArrayInterfaceTraceDecorator::funcInt64Async(const std::list<int64_t>& paramInt64)
{
    m_tracer->trace_funcInt64(paramInt64);
    return m_impl.funcInt64Async(paramInt64);
}
std::list<float> SimpleArrayInterfaceTraceDecorator::funcFloat(const std::list<float>& paramFloat)
{
    m_tracer->trace_funcFloat(paramFloat);
    return m_impl.funcFloat(paramFloat);
}
std::future<std::list<float>> SimpleArrayInterfaceTraceDecorator::funcFloatAsync(const std::list<float>& paramFloat)
{
    m_tracer->trace_funcFloat(paramFloat);
    return m_impl.funcFloatAsync(paramFloat);
}
std::list<float> SimpleArrayInterfaceTraceDecorator::funcFloat32(const std::list<float>& paramFloat32)
{
    m_tracer->trace_funcFloat32(paramFloat32);
    return m_impl.funcFloat32(paramFloat32);
}
std::future<std::list<float>> SimpleArrayInterfaceTraceDecorator::funcFloat32Async(const std::list<float>& paramFloat32)
{
    m_tracer->trace_funcFloat32(paramFloat32);
    return m_impl.funcFloat32Async(paramFloat32);
}
std::list<double> SimpleArrayInterfaceTraceDecorator::funcFloat64(const std::list<double>& paramFloat)
{
    m_tracer->trace_funcFloat64(paramFloat);
    return m_impl.funcFloat64(paramFloat);
}
std::future<std::list<double>> SimpleArrayInterfaceTraceDecorator::funcFloat64Async(const std::list<double>& paramFloat)
{
    m_tracer->trace_funcFloat64(paramFloat);
    return m_impl.funcFloat64Async(paramFloat);
}
std::list<std::string> SimpleArrayInterfaceTraceDecorator::funcString(const std::list<std::string>& paramString)
{
    m_tracer->trace_funcString(paramString);
    return m_impl.funcString(paramString);
}
std::future<std::list<std::string>> SimpleArrayInterfaceTraceDecorator::funcStringAsync(const std::list<std::string>& paramString)
{
    m_tracer->trace_funcString(paramString);
    return m_impl.funcStringAsync(paramString);
}
void SimpleArrayInterfaceTraceDecorator::setPropBool(const std::list<bool>& propBool)
{
    m_impl.setPropBool(propBool);
}

const std::list<bool>& SimpleArrayInterfaceTraceDecorator::getPropBool() const
{
    return m_impl.getPropBool();
}
void SimpleArrayInterfaceTraceDecorator::setPropInt(const std::list<int>& propInt)
{
    m_impl.setPropInt(propInt);
}

const std::list<int>& SimpleArrayInterfaceTraceDecorator::getPropInt() const
{
    return m_impl.getPropInt();
}
void SimpleArrayInterfaceTraceDecorator::setPropInt32(const std::list<int32_t>& propInt32)
{
    m_impl.setPropInt32(propInt32);
}

const std::list<int32_t>& SimpleArrayInterfaceTraceDecorator::getPropInt32() const
{
    return m_impl.getPropInt32();
}
void SimpleArrayInterfaceTraceDecorator::setPropInt64(const std::list<int64_t>& propInt64)
{
    m_impl.setPropInt64(propInt64);
}

const std::list<int64_t>& SimpleArrayInterfaceTraceDecorator::getPropInt64() const
{
    return m_impl.getPropInt64();
}
void SimpleArrayInterfaceTraceDecorator::setPropFloat(const std::list<float>& propFloat)
{
    m_impl.setPropFloat(propFloat);
}

const std::list<float>& SimpleArrayInterfaceTraceDecorator::getPropFloat() const
{
    return m_impl.getPropFloat();
}
void SimpleArrayInterfaceTraceDecorator::setPropFloat32(const std::list<float>& propFloat32)
{
    m_impl.setPropFloat32(propFloat32);
}

const std::list<float>& SimpleArrayInterfaceTraceDecorator::getPropFloat32() const
{
    return m_impl.getPropFloat32();
}
void SimpleArrayInterfaceTraceDecorator::setPropFloat64(const std::list<double>& propFloat64)
{
    m_impl.setPropFloat64(propFloat64);
}

const std::list<double>& SimpleArrayInterfaceTraceDecorator::getPropFloat64() const
{
    return m_impl.getPropFloat64();
}
void SimpleArrayInterfaceTraceDecorator::setPropString(const std::list<std::string>& propString)
{
    m_impl.setPropString(propString);
}

const std::list<std::string>& SimpleArrayInterfaceTraceDecorator::getPropString() const
{
    return m_impl.getPropString();
}

const std::string& SimpleArrayInterfaceTraceDecorator::getPropReadOnlyString() const
{
    return m_impl.getPropReadOnlyString();
}
void SimpleArrayInterfaceTraceDecorator::onSigBool(const std::list<bool>& paramBool)
{
    m_tracer->trace_sigBool(paramBool);
}

void SimpleArrayInterfaceTraceDecorator::onSigInt(const std::list<int>& paramInt)
{
    m_tracer->trace_sigInt(paramInt);
}

void SimpleArrayInterfaceTraceDecorator::onSigInt32(const std::list<int32_t>& paramInt32)
{
    m_tracer->trace_sigInt32(paramInt32);
}

void SimpleArrayInterfaceTraceDecorator::onSigInt64(const std::list<int64_t>& paramInt64)
{
    m_tracer->trace_sigInt64(paramInt64);
}

void SimpleArrayInterfaceTraceDecorator::onSigFloat(const std::list<float>& paramFloat)
{
    m_tracer->trace_sigFloat(paramFloat);
}

void SimpleArrayInterfaceTraceDecorator::onSigFloat32(const std::list<float>& paramFloa32)
{
    m_tracer->trace_sigFloat32(paramFloa32);
}

void SimpleArrayInterfaceTraceDecorator::onSigFloat64(const std::list<double>& paramFloat64)
{
    m_tracer->trace_sigFloat64(paramFloat64);
}

void SimpleArrayInterfaceTraceDecorator::onSigString(const std::list<std::string>& paramString)
{
    m_tracer->trace_sigString(paramString);
}

void SimpleArrayInterfaceTraceDecorator::onPropBoolChanged(const std::list<bool>& propBool)
{
    (void) propBool; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SimpleArrayInterfaceTraceDecorator::onPropIntChanged(const std::list<int>& propInt)
{
    (void) propInt; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SimpleArrayInterfaceTraceDecorator::onPropInt32Changed(const std::list<int32_t>& propInt32)
{
    (void) propInt32; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SimpleArrayInterfaceTraceDecorator::onPropInt64Changed(const std::list<int64_t>& propInt64)
{
    (void) propInt64; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SimpleArrayInterfaceTraceDecorator::onPropFloatChanged(const std::list<float>& propFloat)
{
    (void) propFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SimpleArrayInterfaceTraceDecorator::onPropFloat32Changed(const std::list<float>& propFloat32)
{
    (void) propFloat32; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SimpleArrayInterfaceTraceDecorator::onPropFloat64Changed(const std::list<double>& propFloat64)
{
    (void) propFloat64; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SimpleArrayInterfaceTraceDecorator::onPropStringChanged(const std::list<std::string>& propString)
{
    (void) propString; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SimpleArrayInterfaceTraceDecorator::onPropReadOnlyStringChanged(const std::string& propReadOnlyString)
{
    (void) propReadOnlyString; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



ISimpleArrayInterfacePublisher& SimpleArrayInterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
