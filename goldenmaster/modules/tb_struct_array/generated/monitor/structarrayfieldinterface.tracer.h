#pragma once

#include "tb_struct_array/generated/api/tb_struct_array.h"

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace TbStructArray {

/**
* A helper class for tracing.
* Builds the trace info with state and operations specific for StructArrayFieldInterface and pass to PocoImpl::Tracer.
*/
class StructArrayFieldInterfaceTracer
{
public:
  /**
  * ctor
  * @param tracer A tracer object to which the information about the state and operations is put.
  */
  StructArrayFieldInterfaceTracer(ApiGear::PocoImpl::Tracer& tracer);
  /** dtor */
  virtual ~StructArrayFieldInterfaceTracer() = default;
  /**
  * Prepares the StructArrayFieldInterface object state in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayFieldInterface object to trace.
  */
  void capture_state(IStructArrayFieldInterface* obj);
  /**
  * Prepares information about the funcMixed call in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayFieldInterface object to trace.
  */
  void trace_funcMixed(const MixedStruct& paramMixed);
  /**
  * Prepares information about the funcStructArray call in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayFieldInterface object to trace.
  */
  void trace_funcStructArray(const StructWithArrayOfStructs& paramPoints);
  /**
  * Prepares information about the sigMixed call in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayFieldInterface object to trace.
  */
  void trace_sigMixed(const MixedStruct& paramMixed);
  /**
  * Prepares information about the sigStructArray call in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayFieldInterface object to trace.
  */
  void trace_sigStructArray(const StructWithArrayOfStructs& paramPoints);
private:
  /**
  * A tracer object to which the information about the state and operations is put.
  */
  ApiGear::PocoImpl::Tracer& m_tracer;
};

} // namespace TbStructArray
} // namespace Test
