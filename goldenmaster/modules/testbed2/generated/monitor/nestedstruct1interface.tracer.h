#pragma once

#include "testbed2/generated/api/testbed2.h"

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace Testbed2 {

/**
* A helper class for tracing.
* Builds the trace info with state and operations specific for NestedStruct1Interface and pass to PocoImpl::Tracer.
*/
class NestedStruct1InterfaceTracer
{
public:
  /**
  * ctor
  * @param tracer A tracer object to which the information about the state and operations is put.
  */
  NestedStruct1InterfaceTracer(ApiGear::PocoImpl::Tracer& tracer);
  /** dtor */
  virtual ~NestedStruct1InterfaceTracer() = default;
  /**
  * Prepares the NestedStruct1Interface object state in a nlohmann::json format and puts to a tracer.
  * @param The NestedStruct1Interface object to trace.
  */
  void capture_state(INestedStruct1Interface* obj);
  /**
  * Prepares information about the funcNoReturnValue call in a nlohmann::json format and puts to a tracer.
  * @param The NestedStruct1Interface object to trace.
  */
  void trace_funcNoReturnValue(const NestedStruct1& param1);
  /**
  * Prepares information about the funcNoParams call in a nlohmann::json format and puts to a tracer.
  * @param The NestedStruct1Interface object to trace.
  */
  void trace_funcNoParams();
  /**
  * Prepares information about the func1 call in a nlohmann::json format and puts to a tracer.
  * @param The NestedStruct1Interface object to trace.
  */
  void trace_func1(const NestedStruct1& param1);
  /**
  * Prepares information about the sig1 call in a nlohmann::json format and puts to a tracer.
  * @param The NestedStruct1Interface object to trace.
  */
  void trace_sig1(const NestedStruct1& param1);
private:
  /**
  * A tracer object to which the information about the state and operations is put.
  */
  ApiGear::PocoImpl::Tracer& m_tracer;
};

} // namespace Testbed2
} // namespace Test
