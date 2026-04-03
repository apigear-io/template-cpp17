#include "apigear/tracer/tracer.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"
#include "testbed1/generated/monitor/structarrayinterface.tracer.h"

using namespace Test::Testbed1;

StructArrayInterfaceTracer::StructArrayInterfaceTracer(ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(tracer)
{
}

void StructArrayInterfaceTracer::capture_state(IStructArrayInterface* obj)
{
    nlohmann::json fields_;
    fields_["propBool"] = obj->getPropBool();
    fields_["propInt"] = obj->getPropInt();
    fields_["propFloat"] = obj->getPropFloat();
    fields_["propString"] = obj->getPropString();
    fields_["propEnum"] = obj->getPropEnum();
    m_tracer.state("testbed1.StructArrayInterface#_state", fields_);
}

void StructArrayInterfaceTracer::trace_funcBool(const std::list<StructBool>& paramBool)
{
    nlohmann::json fields_;
    fields_["paramBool"] = paramBool;
    m_tracer.call("testbed1.StructArrayInterface#funcBool", fields_);
}

void StructArrayInterfaceTracer::trace_funcInt(const std::list<StructInt>& paramInt)
{
    nlohmann::json fields_;
    fields_["paramInt"] = paramInt;
    m_tracer.call("testbed1.StructArrayInterface#funcInt", fields_);
}

void StructArrayInterfaceTracer::trace_funcFloat(const std::list<StructFloat>& paramFloat)
{
    nlohmann::json fields_;
    fields_["paramFloat"] = paramFloat;
    m_tracer.call("testbed1.StructArrayInterface#funcFloat", fields_);
}

void StructArrayInterfaceTracer::trace_funcString(const std::list<StructString>& paramString)
{
    nlohmann::json fields_;
    fields_["paramString"] = paramString;
    m_tracer.call("testbed1.StructArrayInterface#funcString", fields_);
}

void StructArrayInterfaceTracer::trace_funcEnum(const std::list<Enum0Enum>& paramEnum)
{
    nlohmann::json fields_;
    fields_["paramEnum"] = paramEnum;
    m_tracer.call("testbed1.StructArrayInterface#funcEnum", fields_);
}
void StructArrayInterfaceTracer::trace_sigBool(const std::list<StructBool>& paramBool)
{
    nlohmann::json fields_;
    fields_["paramBool"] = paramBool;
    m_tracer.signal("testbed1.StructArrayInterface#sigBool", fields_);
}
void StructArrayInterfaceTracer::trace_sigInt(const std::list<StructInt>& paramInt)
{
    nlohmann::json fields_;
    fields_["paramInt"] = paramInt;
    m_tracer.signal("testbed1.StructArrayInterface#sigInt", fields_);
}
void StructArrayInterfaceTracer::trace_sigFloat(const std::list<StructFloat>& paramFloat)
{
    nlohmann::json fields_;
    fields_["paramFloat"] = paramFloat;
    m_tracer.signal("testbed1.StructArrayInterface#sigFloat", fields_);
}
void StructArrayInterfaceTracer::trace_sigString(const std::list<StructString>& paramString)
{
    nlohmann::json fields_;
    fields_["paramString"] = paramString;
    m_tracer.signal("testbed1.StructArrayInterface#sigString", fields_);
}
void StructArrayInterfaceTracer::trace_sigEnum(const std::list<Enum0Enum>& paramEnum)
{
    nlohmann::json fields_;
    fields_["paramEnum"] = paramEnum;
    m_tracer.signal("testbed1.StructArrayInterface#sigEnum", fields_);
}