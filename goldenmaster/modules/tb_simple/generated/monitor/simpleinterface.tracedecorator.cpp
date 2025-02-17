

#include "tb_simple/generated/monitor/simpleinterface.tracedecorator.h"
#include "tb_simple/generated/monitor/simpleinterface.tracer.h"

using namespace Test::TbSimple;
SimpleInterfaceTraceDecorator::SimpleInterfaceTraceDecorator(ISimpleInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<SimpleInterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
SimpleInterfaceTraceDecorator::~SimpleInterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<SimpleInterfaceTraceDecorator> SimpleInterfaceTraceDecorator::connect(ISimpleInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<SimpleInterfaceTraceDecorator>(new SimpleInterfaceTraceDecorator(impl, tracer));
}
void SimpleInterfaceTraceDecorator::funcNoReturnValue(bool paramBool)
{
    m_tracer->trace_funcNoReturnValue(paramBool);
    return m_impl.funcNoReturnValue(paramBool);
}
std::future<void> SimpleInterfaceTraceDecorator::funcNoReturnValueAsync(bool paramBool)
{
    m_tracer->trace_funcNoReturnValue(paramBool);
    return m_impl.funcNoReturnValueAsync(paramBool);
}
bool SimpleInterfaceTraceDecorator::funcBool(bool paramBool)
{
    m_tracer->trace_funcBool(paramBool);
    return m_impl.funcBool(paramBool);
}
std::future<bool> SimpleInterfaceTraceDecorator::funcBoolAsync(bool paramBool)
{
    m_tracer->trace_funcBool(paramBool);
    return m_impl.funcBoolAsync(paramBool);
}
int SimpleInterfaceTraceDecorator::funcInt(int paramInt)
{
    m_tracer->trace_funcInt(paramInt);
    return m_impl.funcInt(paramInt);
}
std::future<int> SimpleInterfaceTraceDecorator::funcIntAsync(int paramInt)
{
    m_tracer->trace_funcInt(paramInt);
    return m_impl.funcIntAsync(paramInt);
}
int32_t SimpleInterfaceTraceDecorator::funcInt32(int32_t paramInt32)
{
    m_tracer->trace_funcInt32(paramInt32);
    return m_impl.funcInt32(paramInt32);
}
std::future<int32_t> SimpleInterfaceTraceDecorator::funcInt32Async(int32_t paramInt32)
{
    m_tracer->trace_funcInt32(paramInt32);
    return m_impl.funcInt32Async(paramInt32);
}
int64_t SimpleInterfaceTraceDecorator::funcInt64(int64_t paramInt64)
{
    m_tracer->trace_funcInt64(paramInt64);
    return m_impl.funcInt64(paramInt64);
}
std::future<int64_t> SimpleInterfaceTraceDecorator::funcInt64Async(int64_t paramInt64)
{
    m_tracer->trace_funcInt64(paramInt64);
    return m_impl.funcInt64Async(paramInt64);
}
float SimpleInterfaceTraceDecorator::funcFloat(float paramFloat)
{
    m_tracer->trace_funcFloat(paramFloat);
    return m_impl.funcFloat(paramFloat);
}
std::future<float> SimpleInterfaceTraceDecorator::funcFloatAsync(float paramFloat)
{
    m_tracer->trace_funcFloat(paramFloat);
    return m_impl.funcFloatAsync(paramFloat);
}
float SimpleInterfaceTraceDecorator::funcFloat32(float paramFloat32)
{
    m_tracer->trace_funcFloat32(paramFloat32);
    return m_impl.funcFloat32(paramFloat32);
}
std::future<float> SimpleInterfaceTraceDecorator::funcFloat32Async(float paramFloat32)
{
    m_tracer->trace_funcFloat32(paramFloat32);
    return m_impl.funcFloat32Async(paramFloat32);
}
double SimpleInterfaceTraceDecorator::funcFloat64(double paramFloat)
{
    m_tracer->trace_funcFloat64(paramFloat);
    return m_impl.funcFloat64(paramFloat);
}
std::future<double> SimpleInterfaceTraceDecorator::funcFloat64Async(double paramFloat)
{
    m_tracer->trace_funcFloat64(paramFloat);
    return m_impl.funcFloat64Async(paramFloat);
}
std::string SimpleInterfaceTraceDecorator::funcString(const std::string& paramString)
{
    m_tracer->trace_funcString(paramString);
    return m_impl.funcString(paramString);
}
std::future<std::string> SimpleInterfaceTraceDecorator::funcStringAsync(const std::string& paramString)
{
    m_tracer->trace_funcString(paramString);
    return m_impl.funcStringAsync(paramString);
}
void SimpleInterfaceTraceDecorator::setPropBool(bool propBool)
{
    m_impl.setPropBool(propBool);
}

bool SimpleInterfaceTraceDecorator::getPropBool() const
{
    return m_impl.getPropBool();
}
void SimpleInterfaceTraceDecorator::setPropInt(int propInt)
{
    m_impl.setPropInt(propInt);
}

int SimpleInterfaceTraceDecorator::getPropInt() const
{
    return m_impl.getPropInt();
}
void SimpleInterfaceTraceDecorator::setPropInt32(int32_t propInt32)
{
    m_impl.setPropInt32(propInt32);
}

int32_t SimpleInterfaceTraceDecorator::getPropInt32() const
{
    return m_impl.getPropInt32();
}
void SimpleInterfaceTraceDecorator::setPropInt64(int64_t propInt64)
{
    m_impl.setPropInt64(propInt64);
}

int64_t SimpleInterfaceTraceDecorator::getPropInt64() const
{
    return m_impl.getPropInt64();
}
void SimpleInterfaceTraceDecorator::setPropFloat(float propFloat)
{
    m_impl.setPropFloat(propFloat);
}

float SimpleInterfaceTraceDecorator::getPropFloat() const
{
    return m_impl.getPropFloat();
}
void SimpleInterfaceTraceDecorator::setPropFloat32(float propFloat32)
{
    m_impl.setPropFloat32(propFloat32);
}

float SimpleInterfaceTraceDecorator::getPropFloat32() const
{
    return m_impl.getPropFloat32();
}
void SimpleInterfaceTraceDecorator::setPropFloat64(double propFloat64)
{
    m_impl.setPropFloat64(propFloat64);
}

double SimpleInterfaceTraceDecorator::getPropFloat64() const
{
    return m_impl.getPropFloat64();
}
void SimpleInterfaceTraceDecorator::setPropString(const std::string& propString)
{
    m_impl.setPropString(propString);
}

const std::string& SimpleInterfaceTraceDecorator::getPropString() const
{
    return m_impl.getPropString();
}
void SimpleInterfaceTraceDecorator::onSigBool(bool paramBool)
{
    m_tracer->trace_sigBool(paramBool);
}

void SimpleInterfaceTraceDecorator::onSigInt(int paramInt)
{
    m_tracer->trace_sigInt(paramInt);
}

void SimpleInterfaceTraceDecorator::onSigInt32(int32_t paramInt32)
{
    m_tracer->trace_sigInt32(paramInt32);
}

void SimpleInterfaceTraceDecorator::onSigInt64(int64_t paramInt64)
{
    m_tracer->trace_sigInt64(paramInt64);
}

void SimpleInterfaceTraceDecorator::onSigFloat(float paramFloat)
{
    m_tracer->trace_sigFloat(paramFloat);
}

void SimpleInterfaceTraceDecorator::onSigFloat32(float paramFloat32)
{
    m_tracer->trace_sigFloat32(paramFloat32);
}

void SimpleInterfaceTraceDecorator::onSigFloat64(double paramFloat64)
{
    m_tracer->trace_sigFloat64(paramFloat64);
}

void SimpleInterfaceTraceDecorator::onSigString(const std::string& paramString)
{
    m_tracer->trace_sigString(paramString);
}

void SimpleInterfaceTraceDecorator::onPropBoolChanged(bool propBool)
{
    (void) propBool; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SimpleInterfaceTraceDecorator::onPropIntChanged(int propInt)
{
    (void) propInt; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SimpleInterfaceTraceDecorator::onPropInt32Changed(int32_t propInt32)
{
    (void) propInt32; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SimpleInterfaceTraceDecorator::onPropInt64Changed(int64_t propInt64)
{
    (void) propInt64; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SimpleInterfaceTraceDecorator::onPropFloatChanged(float propFloat)
{
    (void) propFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SimpleInterfaceTraceDecorator::onPropFloat32Changed(float propFloat32)
{
    (void) propFloat32; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SimpleInterfaceTraceDecorator::onPropFloat64Changed(double propFloat64)
{
    (void) propFloat64; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void SimpleInterfaceTraceDecorator::onPropStringChanged(const std::string& propString)
{
    (void) propString; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



ISimpleInterfacePublisher& SimpleInterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
