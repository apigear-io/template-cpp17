#pragma once

#include "testbed1/generated/api/testbed1.h"

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace Testbed1 {

/**
* A helper class for tracing.
* Builds the trace info with state and operations specific for StructArray2Interface and pass to PocoImpl::Tracer.
*/
class StructArray2InterfaceTracer
{
public:
  /**
  * ctor
  * @param tracer A tracer object to which the information about the state and operations is put.
  */
  StructArray2InterfaceTracer(ApiGear::PocoImpl::Tracer& tracer);
  /** dtor */
  virtual ~StructArray2InterfaceTracer() = default;
  /**
  * Prepares the StructArray2Interface object state in a nlohmann::json format and puts to a tracer.
  * @param The StructArray2Interface object to trace.
  */
  void capture_state(IStructArray2Interface* obj);
  /**
  * Prepares information about the funcBool call in a nlohmann::json format and puts to a tracer.
  * @param The StructArray2Interface object to trace.
  */
  void trace_funcBool(const StructBoolWithArray& paramBool);
  /**
  * Prepares information about the funcInt call in a nlohmann::json format and puts to a tracer.
  * @param The StructArray2Interface object to trace.
  */
  void trace_funcInt(const StructIntWithArray& paramInt);
  /**
  * Prepares information about the funcFloat call in a nlohmann::json format and puts to a tracer.
  * @param The StructArray2Interface object to trace.
  */
  void trace_funcFloat(const StructFloatWithArray& paramFloat);
  /**
  * Prepares information about the funcString call in a nlohmann::json format and puts to a tracer.
  * @param The StructArray2Interface object to trace.
  */
  void trace_funcString(const StructStringWithArray& paramString);
  /**
  * Prepares information about the funcEnum call in a nlohmann::json format and puts to a tracer.
  * @param The StructArray2Interface object to trace.
  */
  void trace_funcEnum(const StructEnumWithArray& paramEnum);
  /**
  * Prepares information about the sigBool call in a nlohmann::json format and puts to a tracer.
  * @param The StructArray2Interface object to trace.
  */
  void trace_sigBool(const StructBoolWithArray& paramBool);
  /**
  * Prepares information about the sigInt call in a nlohmann::json format and puts to a tracer.
  * @param The StructArray2Interface object to trace.
  */
  void trace_sigInt(const StructIntWithArray& paramInt);
  /**
  * Prepares information about the sigFloat call in a nlohmann::json format and puts to a tracer.
  * @param The StructArray2Interface object to trace.
  */
  void trace_sigFloat(const StructFloatWithArray& paramFloat);
  /**
  * Prepares information about the sigString call in a nlohmann::json format and puts to a tracer.
  * @param The StructArray2Interface object to trace.
  */
  void trace_sigString(const StructStringWithArray& paramString);
private:
  /**
  * A tracer object to which the information about the state and operations is put.
  */
  ApiGear::PocoImpl::Tracer& m_tracer;
};

} // namespace Testbed1
} // namespace Test
