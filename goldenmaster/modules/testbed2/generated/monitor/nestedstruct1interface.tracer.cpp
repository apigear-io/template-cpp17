#include "apigear/tracer/tracer.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"
#include "testbed2/generated/monitor/nestedstruct1interface.tracer.h"

using namespace Test::Testbed2;

NestedStruct1InterfaceTracer::NestedStruct1InterfaceTracer(ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(tracer)
{
}

void NestedStruct1InterfaceTracer::capture_state(INestedStruct1Interface* obj)
{
    nlohmann::json fields_;
    fields_["prop1"] = obj->getProp1();
    m_tracer.state("testbed2.NestedStruct1Interface#_state", fields_);
}

void NestedStruct1InterfaceTracer::trace_funcNoReturnValue(const NestedStruct1& param1)
{
    nlohmann::json fields_;
    fields_["param1"] = param1;
    m_tracer.call("testbed2.NestedStruct1Interface#funcNoReturnValue", fields_);
}

void NestedStruct1InterfaceTracer::trace_funcNoParams()
{
    nlohmann::json fields_;
    m_tracer.call("testbed2.NestedStruct1Interface#funcNoParams", fields_);
}

void NestedStruct1InterfaceTracer::trace_func1(const NestedStruct1& param1)
{
    nlohmann::json fields_;
    fields_["param1"] = param1;
    m_tracer.call("testbed2.NestedStruct1Interface#func1", fields_);
}
void NestedStruct1InterfaceTracer::trace_sig1(const NestedStruct1& param1)
{
    nlohmann::json fields_;
    fields_["param1"] = param1;
    m_tracer.signal("testbed2.NestedStruct1Interface#sig1", fields_);
}