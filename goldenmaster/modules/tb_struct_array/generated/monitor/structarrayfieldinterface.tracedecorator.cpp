

#include "tb_struct_array/generated/monitor/structarrayfieldinterface.tracedecorator.h"
#include "tb_struct_array/generated/monitor/structarrayfieldinterface.tracer.h"

using namespace Test::TbStructArray;
StructArrayFieldInterfaceTraceDecorator::StructArrayFieldInterfaceTraceDecorator(IStructArrayFieldInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<StructArrayFieldInterfaceTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
StructArrayFieldInterfaceTraceDecorator::~StructArrayFieldInterfaceTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<StructArrayFieldInterfaceTraceDecorator> StructArrayFieldInterfaceTraceDecorator::connect(IStructArrayFieldInterface& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<StructArrayFieldInterfaceTraceDecorator>(new StructArrayFieldInterfaceTraceDecorator(impl, tracer));
}
MixedStruct StructArrayFieldInterfaceTraceDecorator::funcMixed(const MixedStruct& paramMixed)
{
    m_tracer->trace_funcMixed(paramMixed);
    return m_impl.funcMixed(paramMixed);
}
std::future<MixedStruct> StructArrayFieldInterfaceTraceDecorator::funcMixedAsync(const MixedStruct& paramMixed, std::function<void(MixedStruct)> callback)
{
    m_tracer->trace_funcMixed(paramMixed);
    return m_impl.funcMixedAsync(paramMixed, callback);
}
StructWithArrayOfStructs StructArrayFieldInterfaceTraceDecorator::funcStructArray(const StructWithArrayOfStructs& paramPoints)
{
    m_tracer->trace_funcStructArray(paramPoints);
    return m_impl.funcStructArray(paramPoints);
}
std::future<StructWithArrayOfStructs> StructArrayFieldInterfaceTraceDecorator::funcStructArrayAsync(const StructWithArrayOfStructs& paramPoints, std::function<void(StructWithArrayOfStructs)> callback)
{
    m_tracer->trace_funcStructArray(paramPoints);
    return m_impl.funcStructArrayAsync(paramPoints, callback);
}
void StructArrayFieldInterfaceTraceDecorator::setPropStructArray(const StructWithArrayOfStructs& propStructArray)
{
    m_impl.setPropStructArray(propStructArray);
}

const StructWithArrayOfStructs& StructArrayFieldInterfaceTraceDecorator::getPropStructArray() const
{
    return m_impl.getPropStructArray();
}
void StructArrayFieldInterfaceTraceDecorator::setPropEnumArray(const StructWithArrayOfEnums& propEnumArray)
{
    m_impl.setPropEnumArray(propEnumArray);
}

const StructWithArrayOfEnums& StructArrayFieldInterfaceTraceDecorator::getPropEnumArray() const
{
    return m_impl.getPropEnumArray();
}
void StructArrayFieldInterfaceTraceDecorator::setPropIntArray(const StructWithArrayOfInts& propIntArray)
{
    m_impl.setPropIntArray(propIntArray);
}

const StructWithArrayOfInts& StructArrayFieldInterfaceTraceDecorator::getPropIntArray() const
{
    return m_impl.getPropIntArray();
}
void StructArrayFieldInterfaceTraceDecorator::setPropMixed(const MixedStruct& propMixed)
{
    m_impl.setPropMixed(propMixed);
}

const MixedStruct& StructArrayFieldInterfaceTraceDecorator::getPropMixed() const
{
    return m_impl.getPropMixed();
}
void StructArrayFieldInterfaceTraceDecorator::onSigMixed(const MixedStruct& paramMixed)
{
    m_tracer->trace_sigMixed(paramMixed);
}

void StructArrayFieldInterfaceTraceDecorator::onSigStructArray(const StructWithArrayOfStructs& paramPoints)
{
    m_tracer->trace_sigStructArray(paramPoints);
}

void StructArrayFieldInterfaceTraceDecorator::onPropStructArrayChanged(const StructWithArrayOfStructs& propStructArray)
{
    (void) propStructArray; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void StructArrayFieldInterfaceTraceDecorator::onPropEnumArrayChanged(const StructWithArrayOfEnums& propEnumArray)
{
    (void) propEnumArray; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void StructArrayFieldInterfaceTraceDecorator::onPropIntArrayChanged(const StructWithArrayOfInts& propIntArray)
{
    (void) propIntArray; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void StructArrayFieldInterfaceTraceDecorator::onPropMixedChanged(const MixedStruct& propMixed)
{
    (void) propMixed; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



IStructArrayFieldInterfacePublisher& StructArrayFieldInterfaceTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
