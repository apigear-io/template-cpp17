#include "apigear/tracer/tracer.h"
#include "tb_struct_array/generated/core/tb_struct_array.json.adapter.h"
#include "tb_struct_array/generated/monitor/structarrayfieldinterface.tracer.h"

using namespace Test::TbStructArray;

StructArrayFieldInterfaceTracer::StructArrayFieldInterfaceTracer(ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(tracer)
{
}

void StructArrayFieldInterfaceTracer::capture_state(IStructArrayFieldInterface* obj)
{
    nlohmann::json fields_;
    fields_["propStructArray"] = obj->getPropStructArray();
    fields_["propEnumArray"] = obj->getPropEnumArray();
    fields_["propIntArray"] = obj->getPropIntArray();
    fields_["propMixed"] = obj->getPropMixed();
    m_tracer.state("tb.struct.array.StructArrayFieldInterface#_state", fields_);
}

void StructArrayFieldInterfaceTracer::trace_funcMixed(const MixedStruct& paramMixed)
{
    nlohmann::json fields_;
    fields_["paramMixed"] = paramMixed;
    m_tracer.call("tb.struct.array.StructArrayFieldInterface#funcMixed", fields_);
}

void StructArrayFieldInterfaceTracer::trace_funcStructArray(const StructWithArrayOfStructs& paramPoints)
{
    nlohmann::json fields_;
    fields_["paramPoints"] = paramPoints;
    m_tracer.call("tb.struct.array.StructArrayFieldInterface#funcStructArray", fields_);
}
void StructArrayFieldInterfaceTracer::trace_sigMixed(const MixedStruct& paramMixed)
{
    nlohmann::json fields_;
    fields_["paramMixed"] = paramMixed;
    m_tracer.signal("tb.struct.array.StructArrayFieldInterface#sigMixed", fields_);
}
void StructArrayFieldInterfaceTracer::trace_sigStructArray(const StructWithArrayOfStructs& paramPoints)
{
    nlohmann::json fields_;
    fields_["paramPoints"] = paramPoints;
    m_tracer.signal("tb.struct.array.StructArrayFieldInterface#sigStructArray", fields_);
}