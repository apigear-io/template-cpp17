#pragma once

#include "tb_simple/generated/api/tb_simple.h"

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace TbSimple {

/**
* A helper class for tracing.
* Builds the trace info with state and operations specific for EmptyInterface and pass to PocoImpl::Tracer.
*/
class EmptyInterfaceTracer
{
public:
  /**
  * ctor
  * @param tracer A tracer object to which the information about the state and operations is put.
  */
  EmptyInterfaceTracer(ApiGear::PocoImpl::Tracer& tracer);
  /** dtor */
  virtual ~EmptyInterfaceTracer() = default;
  /**
  * Prepares the EmptyInterface object state in a nlohmann::json format and puts to a tracer.
  * @param The EmptyInterface object to trace.
  */
  void capture_state(IEmptyInterface* obj);
private:
  /**
  * A tracer object to which the information about the state and operations is put.
  */
  ApiGear::PocoImpl::Tracer& m_tracer;
};

} // namespace TbSimple
} // namespace Test
