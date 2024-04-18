#include "apigear/tracer/tracer.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include "tb_simple/generated/monitor/simplearrayinterface.tracer.h"

using namespace Test::TbSimple;

SimpleArrayInterfaceTracer::SimpleArrayInterfaceTracer(ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(tracer)
{
}

void SimpleArrayInterfaceTracer::capture_state(ISimpleArrayInterface* obj)
{
    nlohmann::json fields_;
    fields_["propBool"] = obj->getPropBool();
    fields_["propInt"] = obj->getPropInt();
    fields_["propInt32"] = obj->getPropInt32();
    fields_["propInt64"] = obj->getPropInt64();
    fields_["propFloat"] = obj->getPropFloat();
    fields_["propFloat32"] = obj->getPropFloat32();
    fields_["propFloat64"] = obj->getPropFloat64();
    fields_["propString"] = obj->getPropString();
    fields_["propReadOnlyString"] = obj->getPropReadOnlyString();
    m_tracer.state("tb.simple.SimpleArrayInterface#_state", fields_);
}

void SimpleArrayInterfaceTracer::trace_funcBool(const std::list<bool>& paramBool)
{
    nlohmann::json fields_;
    fields_["paramBool"] = paramBool;
    m_tracer.call("tb.simple.SimpleArrayInterface#funcBool", fields_);
}

void SimpleArrayInterfaceTracer::trace_funcInt(const std::list<int>& paramInt)
{
    nlohmann::json fields_;
    fields_["paramInt"] = paramInt;
    m_tracer.call("tb.simple.SimpleArrayInterface#funcInt", fields_);
}

void SimpleArrayInterfaceTracer::trace_funcInt32(const std::list<int32_t>& paramInt32)
{
    nlohmann::json fields_;
    fields_["paramInt32"] = paramInt32;
    m_tracer.call("tb.simple.SimpleArrayInterface#funcInt32", fields_);
}

void SimpleArrayInterfaceTracer::trace_funcInt64(const std::list<int64_t>& paramInt64)
{
    nlohmann::json fields_;
    fields_["paramInt64"] = paramInt64;
    m_tracer.call("tb.simple.SimpleArrayInterface#funcInt64", fields_);
}

void SimpleArrayInterfaceTracer::trace_funcFloat(const std::list<float>& paramFloat)
{
    nlohmann::json fields_;
    fields_["paramFloat"] = paramFloat;
    m_tracer.call("tb.simple.SimpleArrayInterface#funcFloat", fields_);
}

void SimpleArrayInterfaceTracer::trace_funcFloat32(const std::list<float>& paramFloat32)
{
    nlohmann::json fields_;
    fields_["paramFloat32"] = paramFloat32;
    m_tracer.call("tb.simple.SimpleArrayInterface#funcFloat32", fields_);
}

void SimpleArrayInterfaceTracer::trace_funcFloat64(const std::list<double>& paramFloat)
{
    nlohmann::json fields_;
    fields_["paramFloat"] = paramFloat;
    m_tracer.call("tb.simple.SimpleArrayInterface#funcFloat64", fields_);
}

void SimpleArrayInterfaceTracer::trace_funcString(const std::list<std::string>& paramString)
{
    nlohmann::json fields_;
    fields_["paramString"] = paramString;
    m_tracer.call("tb.simple.SimpleArrayInterface#funcString", fields_);
}
void SimpleArrayInterfaceTracer::trace_sigBool(const std::list<bool>& paramBool)
{
    nlohmann::json fields_;
    fields_["paramBool"] = paramBool;
    m_tracer.signal("tb.simple.SimpleArrayInterface#sigBool", fields_);
}
void SimpleArrayInterfaceTracer::trace_sigInt(const std::list<int>& paramInt)
{
    nlohmann::json fields_;
    fields_["paramInt"] = paramInt;
    m_tracer.signal("tb.simple.SimpleArrayInterface#sigInt", fields_);
}
void SimpleArrayInterfaceTracer::trace_sigInt32(const std::list<int32_t>& paramInt32)
{
    nlohmann::json fields_;
    fields_["paramInt32"] = paramInt32;
    m_tracer.signal("tb.simple.SimpleArrayInterface#sigInt32", fields_);
}
void SimpleArrayInterfaceTracer::trace_sigInt64(const std::list<int64_t>& paramInt64)
{
    nlohmann::json fields_;
    fields_["paramInt64"] = paramInt64;
    m_tracer.signal("tb.simple.SimpleArrayInterface#sigInt64", fields_);
}
void SimpleArrayInterfaceTracer::trace_sigFloat(const std::list<float>& paramFloat)
{
    nlohmann::json fields_;
    fields_["paramFloat"] = paramFloat;
    m_tracer.signal("tb.simple.SimpleArrayInterface#sigFloat", fields_);
}
void SimpleArrayInterfaceTracer::trace_sigFloat32(const std::list<float>& paramFloa32)
{
    nlohmann::json fields_;
    fields_["paramFloa32"] = paramFloa32;
    m_tracer.signal("tb.simple.SimpleArrayInterface#sigFloat32", fields_);
}
void SimpleArrayInterfaceTracer::trace_sigFloat64(const std::list<double>& paramFloat64)
{
    nlohmann::json fields_;
    fields_["paramFloat64"] = paramFloat64;
    m_tracer.signal("tb.simple.SimpleArrayInterface#sigFloat64", fields_);
}
void SimpleArrayInterfaceTracer::trace_sigString(const std::list<std::string>& paramString)
{
    nlohmann::json fields_;
    fields_["paramString"] = paramString;
    m_tracer.signal("tb.simple.SimpleArrayInterface#sigString", fields_);
}