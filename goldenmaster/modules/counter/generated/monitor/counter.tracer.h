#pragma once

#include "counter/generated/api/counter.h"

namespace ApiGear { namespace PocoImpl { class Tracer; } }

namespace Test {
namespace Counter {

/**
* A helper class for tracing.
* Builds the trace info with state and operations specific for Counter and pass to PocoImpl::Tracer.
*/
class CounterTracer
{
public:
  /**
  * ctor
  * @param tracer A tracer object to which the information about the state and operations is put.
  */
  CounterTracer(ApiGear::PocoImpl::Tracer& tracer);
  /** dtor */
  virtual ~CounterTracer() = default;
  /**
  * Prepares the Counter object state in a nlohmann::json format and puts to a tracer.
  * @param The Counter object to trace.
  */
  void capture_state(ICounter* obj);
  /**
  * Prepares information about the increment call in a nlohmann::json format and puts to a tracer.
  * @param The Counter object to trace.
  */
  void trace_increment(const Eigen::Vector3f& vec);
  /**
  * Prepares information about the decrement call in a nlohmann::json format and puts to a tracer.
  * @param The Counter object to trace.
  */
  void trace_decrement(const Test::CustomTypes::Vector3D& vec);
private:
  /**
  * A tracer object to which the information about the state and operations is put.
  */
  ApiGear::PocoImpl::Tracer& m_tracer;
};

} // namespace Counter
} // namespace Test
