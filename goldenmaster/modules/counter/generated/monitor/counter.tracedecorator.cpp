

#include "counter/generated/monitor/counter.tracedecorator.h"
#include "counter/generated/monitor/counter.tracer.h"

using namespace Test::Counter;
CounterTraceDecorator::CounterTraceDecorator(ICounter& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<CounterTracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
CounterTraceDecorator::~CounterTraceDecorator()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<CounterTraceDecorator> CounterTraceDecorator::connect(ICounter& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<CounterTraceDecorator>(new CounterTraceDecorator(impl, tracer));
}
Eigen::Vector3f CounterTraceDecorator::increment(const Eigen::Vector3f& vec)
{
    m_tracer->trace_increment(vec);
    return m_impl.increment(vec);
}
std::future<Eigen::Vector3f> CounterTraceDecorator::incrementAsync(const Eigen::Vector3f& vec)
{
    m_tracer->trace_increment(vec);
    return m_impl.incrementAsync(vec);
}
Test::CustomTypes::Vector3D CounterTraceDecorator::decrement(const Test::CustomTypes::Vector3D& vec)
{
    m_tracer->trace_decrement(vec);
    return m_impl.decrement(vec);
}
std::future<Test::CustomTypes::Vector3D> CounterTraceDecorator::decrementAsync(const Test::CustomTypes::Vector3D& vec)
{
    m_tracer->trace_decrement(vec);
    return m_impl.decrementAsync(vec);
}
void CounterTraceDecorator::setVector(const Test::CustomTypes::Vector3D& vector)
{
    m_impl.setVector(vector);
}

const Test::CustomTypes::Vector3D& CounterTraceDecorator::getVector() const
{
    return m_impl.getVector();
}
void CounterTraceDecorator::setExternVector(const Eigen::Vector3f& extern_vector)
{
    m_impl.setExternVector(extern_vector);
}

const Eigen::Vector3f& CounterTraceDecorator::getExternVector() const
{
    return m_impl.getExternVector();
}
void CounterTraceDecorator::onVectorChanged(const Test::CustomTypes::Vector3D& vector)
{
    (void) vector; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void CounterTraceDecorator::onExternVectorChanged(const Eigen::Vector3f& extern_vector)
{
    (void) extern_vector; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



ICounterPublisher& CounterTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
