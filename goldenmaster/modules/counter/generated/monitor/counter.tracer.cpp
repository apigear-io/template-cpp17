#include "apigear/tracer/tracer.h"
#include "counter/generated/core/counter.json.adapter.h"
#include "custom_types/generated/core/custom_types.json.adapter.h"
#include "extern_types/generated/core/extern_types.json.adapter.h"
#include "counter/generated/monitor/counter.tracer.h"

using namespace Test::Counter;

CounterTracer::CounterTracer(ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(tracer)
{
}

void CounterTracer::capture_state(ICounter* obj)
{
    nlohmann::json fields_;
    fields_["vector"] = obj->getVector();
    fields_["extern_vector"] = obj->getExternVector();
    m_tracer.state("counter.Counter#_state", fields_);
}

void CounterTracer::trace_increment(const Eigen::Vector3f& vec)
{
    nlohmann::json fields_;
    fields_["vec"] = vec;
    m_tracer.call("counter.Counter#increment", fields_);
}

void CounterTracer::trace_decrement(const Test::CustomTypes::Vector3D& vec)
{
    nlohmann::json fields_;
    fields_["vec"] = vec;
    m_tracer.call("counter.Counter#decrement", fields_);
}