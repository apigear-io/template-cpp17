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
    fields_["vectorArray"] = obj->getVectorArray();
    fields_["extern_vectorArray"] = obj->getExternVectorArray();
    m_tracer.state("counter.Counter#_state", fields_);
}

void CounterTracer::trace_increment(const Eigen::Vector3f& vec)
{
    nlohmann::json fields_;
    fields_["vec"] = vec;
    m_tracer.call("counter.Counter#increment", fields_);
}

void CounterTracer::trace_incrementArray(const std::list<Eigen::Vector3f>& vec)
{
    nlohmann::json fields_;
    fields_["vec"] = vec;
    m_tracer.call("counter.Counter#incrementArray", fields_);
}

void CounterTracer::trace_decrement(const Test::CustomTypes::Vector3D& vec)
{
    nlohmann::json fields_;
    fields_["vec"] = vec;
    m_tracer.call("counter.Counter#decrement", fields_);
}

void CounterTracer::trace_decrementArray(const std::list<Test::CustomTypes::Vector3D>& vec)
{
    nlohmann::json fields_;
    fields_["vec"] = vec;
    m_tracer.call("counter.Counter#decrementArray", fields_);
}
void CounterTracer::trace_valueChanged(const Test::CustomTypes::Vector3D& vector, const Eigen::Vector3f& extern_vector, const std::list<Test::CustomTypes::Vector3D>& vectorArray, const std::list<Eigen::Vector3f>& extern_vectorArray)
{
    nlohmann::json fields_;
    fields_["vector"] = vector;
    fields_["extern_vector"] = extern_vector;
    fields_["vectorArray"] = vectorArray;
    fields_["extern_vectorArray"] = extern_vectorArray;
    m_tracer.signal("counter.Counter#valueChanged", fields_);
}