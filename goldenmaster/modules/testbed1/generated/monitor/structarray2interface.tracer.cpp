#include "apigear/tracer/tracer.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include "testbed1/generated/monitor/structarray2interface.tracer.h"

using namespace Test::Testbed1;

StructArray2InterfaceTracer::StructArray2InterfaceTracer(ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(tracer)
{
}

void StructArray2InterfaceTracer::capture_state(IStructArray2Interface* obj)
{
    nlohmann::json fields_;
    fields_["propBool"] = obj->getPropBool();
    fields_["propInt"] = obj->getPropInt();
    fields_["propFloat"] = obj->getPropFloat();
    fields_["propString"] = obj->getPropString();
    fields_["propEnum"] = obj->getPropEnum();
    m_tracer.state("testbed1.StructArray2Interface#_state", fields_);
}

void StructArray2InterfaceTracer::trace_funcBool(const StructBoolWithArray& paramBool)
{
    nlohmann::json fields_;
    fields_["paramBool"] = paramBool;
    m_tracer.call("testbed1.StructArray2Interface#funcBool", fields_);
}

void StructArray2InterfaceTracer::trace_funcInt(const StructIntWithArray& paramInt)
{
    nlohmann::json fields_;
    fields_["paramInt"] = paramInt;
    m_tracer.call("testbed1.StructArray2Interface#funcInt", fields_);
}

void StructArray2InterfaceTracer::trace_funcFloat(const StructFloatWithArray& paramFloat)
{
    nlohmann::json fields_;
    fields_["paramFloat"] = paramFloat;
    m_tracer.call("testbed1.StructArray2Interface#funcFloat", fields_);
}

void StructArray2InterfaceTracer::trace_funcString(const StructStringWithArray& paramString)
{
    nlohmann::json fields_;
    fields_["paramString"] = paramString;
    m_tracer.call("testbed1.StructArray2Interface#funcString", fields_);
}

void StructArray2InterfaceTracer::trace_funcEnum(const StructEnumWithArray& paramEnum)
{
    nlohmann::json fields_;
    fields_["paramEnum"] = paramEnum;
    m_tracer.call("testbed1.StructArray2Interface#funcEnum", fields_);
}
void StructArray2InterfaceTracer::trace_sigBool(const StructBoolWithArray& paramBool)
{
    nlohmann::json fields_;
    fields_["paramBool"] = paramBool;
    m_tracer.signal("testbed1.StructArray2Interface#sigBool", fields_);
}
void StructArray2InterfaceTracer::trace_sigInt(const StructIntWithArray& paramInt)
{
    nlohmann::json fields_;
    fields_["paramInt"] = paramInt;
    m_tracer.signal("testbed1.StructArray2Interface#sigInt", fields_);
}
void StructArray2InterfaceTracer::trace_sigFloat(const StructFloatWithArray& paramFloat)
{
    nlohmann::json fields_;
    fields_["paramFloat"] = paramFloat;
    m_tracer.signal("testbed1.StructArray2Interface#sigFloat", fields_);
}
void StructArray2InterfaceTracer::trace_sigString(const StructStringWithArray& paramString)
{
    nlohmann::json fields_;
    fields_["paramString"] = paramString;
    m_tracer.signal("testbed1.StructArray2Interface#sigString", fields_);
}