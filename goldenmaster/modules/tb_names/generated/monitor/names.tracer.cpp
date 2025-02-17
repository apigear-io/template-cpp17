#include "apigear/tracer/tracer.h"
#include "tb_names/generated/core/tb_names.json.adapter.h"
#include "tb_names/generated/monitor/names.tracer.h"

using namespace Test::TbNames;

Nam_EsTracer::Nam_EsTracer(ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(tracer)
{
}

void Nam_EsTracer::capture_state(INamEs* obj)
{
    nlohmann::json fields_;
    fields_["Switch"] = obj->getSwitch();
    fields_["SOME_PROPERTY"] = obj->getSomeProperty();
    fields_["Some_Poperty2"] = obj->getSomePoperty2();
    fields_["enum_property"] = obj->getEnumProperty();
    m_tracer.state("tb.names.Nam_Es#_state", fields_);
}

void Nam_EsTracer::trace_SOME_FUNCTION(bool SOME_PARAM)
{
    nlohmann::json fields_;
    fields_["SOME_PARAM"] = SOME_PARAM;
    m_tracer.call("tb.names.Nam_Es#SOME_FUNCTION", fields_);
}

void Nam_EsTracer::trace_Some_Function2(bool Some_Param)
{
    nlohmann::json fields_;
    fields_["Some_Param"] = Some_Param;
    m_tracer.call("tb.names.Nam_Es#Some_Function2", fields_);
}
void Nam_EsTracer::trace_SOME_SIGNAL(bool SOME_PARAM)
{
    nlohmann::json fields_;
    fields_["SOME_PARAM"] = SOME_PARAM;
    m_tracer.signal("tb.names.Nam_Es#SOME_SIGNAL", fields_);
}
void Nam_EsTracer::trace_Some_Signal2(bool Some_Param)
{
    nlohmann::json fields_;
    fields_["Some_Param"] = Some_Param;
    m_tracer.signal("tb.names.Nam_Es#Some_Signal2", fields_);
}