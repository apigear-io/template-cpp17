#include "apigear/tracer/tracer.h"
#include "tb_simple/generated/core/tb_simple.json.adapter.h"
#include "tb_simple/generated/monitor/emptyinterface.tracer.h"

using namespace Test::TbSimple;

EmptyInterfaceTracer::EmptyInterfaceTracer(ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(tracer)
{
}

void EmptyInterfaceTracer::capture_state(IEmptyInterface* obj)
{
    nlohmann::json fields_;
    (void) obj;
    m_tracer.state("tb.simple.EmptyInterface#_state", fields_);
}