#pragma once

#include "testbed1/generated/api/testbed1.h"

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace Testbed1 {

/**
* A helper class for tracing.
* Builds the trace info with state and operations specific for StructArrayInterface and pass to PocoImpl::Tracer.
*/
class StructArrayInterfaceTracer
{
public:
  /**
  * ctor
  * @param tracer A tracer object to which the information about the state and operations is put.
  */
  StructArrayInterfaceTracer(ApiGear::PocoImpl::Tracer& tracer);
  /** dtor */
  virtual ~StructArrayInterfaceTracer() = default;
  /**
  * Prepares the StructArrayInterface object state in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayInterface object to trace.
  */
  void capture_state(IStructArrayInterface* obj);
  /**
  * Prepares information about the funcBool call in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayInterface object to trace.
  */
  void trace_funcBool(const std::list<StructBool>& paramBool);
  /**
  * Prepares information about the funcInt call in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayInterface object to trace.
  */
  void trace_funcInt(const std::list<StructInt>& paramInt);
  /**
  * Prepares information about the funcFloat call in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayInterface object to trace.
  */
  void trace_funcFloat(const std::list<StructFloat>& paramFloat);
  /**
  * Prepares information about the funcString call in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayInterface object to trace.
  */
  void trace_funcString(const std::list<StructString>& paramString);
  /**
  * Prepares information about the funcEnum call in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayInterface object to trace.
  */
  void trace_funcEnum(const std::list<Enum0Enum>& paramEnum);
  /**
  * Prepares information about the sigBool call in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayInterface object to trace.
  */
  void trace_sigBool(const std::list<StructBool>& paramBool);
  /**
  * Prepares information about the sigInt call in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayInterface object to trace.
  */
  void trace_sigInt(const std::list<StructInt>& paramInt);
  /**
  * Prepares information about the sigFloat call in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayInterface object to trace.
  */
  void trace_sigFloat(const std::list<StructFloat>& paramFloat);
  /**
  * Prepares information about the sigString call in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayInterface object to trace.
  */
  void trace_sigString(const std::list<StructString>& paramString);
  /**
  * Prepares information about the sigEnum call in a nlohmann::json format and puts to a tracer.
  * @param The StructArrayInterface object to trace.
  */
  void trace_sigEnum(const std::list<Enum0Enum>& paramEnum);
private:
  /**
  * A tracer object to which the information about the state and operations is put.
  */
  ApiGear::PocoImpl::Tracer& m_tracer;
};

} // namespace Testbed1
} // namespace Test
