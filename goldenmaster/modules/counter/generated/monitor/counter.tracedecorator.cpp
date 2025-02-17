

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
std::list<Eigen::Vector3f> CounterTraceDecorator::incrementArray(const std::list<Eigen::Vector3f>& vec)
{
    m_tracer->trace_incrementArray(vec);
    return m_impl.incrementArray(vec);
}
std::future<std::list<Eigen::Vector3f>> CounterTraceDecorator::incrementArrayAsync(const std::list<Eigen::Vector3f>& vec)
{
    m_tracer->trace_incrementArray(vec);
    return m_impl.incrementArrayAsync(vec);
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
std::list<Test::CustomTypes::Vector3D> CounterTraceDecorator::decrementArray(const std::list<Test::CustomTypes::Vector3D>& vec)
{
    m_tracer->trace_decrementArray(vec);
    return m_impl.decrementArray(vec);
}
std::future<std::list<Test::CustomTypes::Vector3D>> CounterTraceDecorator::decrementArrayAsync(const std::list<Test::CustomTypes::Vector3D>& vec)
{
    m_tracer->trace_decrementArray(vec);
    return m_impl.decrementArrayAsync(vec);
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
void CounterTraceDecorator::setVectorArray(const std::list<Test::CustomTypes::Vector3D>& vectorArray)
{
    m_impl.setVectorArray(vectorArray);
}

const std::list<Test::CustomTypes::Vector3D>& CounterTraceDecorator::getVectorArray() const
{
    return m_impl.getVectorArray();
}
void CounterTraceDecorator::setExternVectorArray(const std::list<Eigen::Vector3f>& extern_vectorArray)
{
    m_impl.setExternVectorArray(extern_vectorArray);
}

const std::list<Eigen::Vector3f>& CounterTraceDecorator::getExternVectorArray() const
{
    return m_impl.getExternVectorArray();
}
void CounterTraceDecorator::onValueChanged(const Test::CustomTypes::Vector3D& vector, const Eigen::Vector3f& extern_vector, const std::list<Test::CustomTypes::Vector3D>& vectorArray, const std::list<Eigen::Vector3f>& extern_vectorArray)
{
    m_tracer->trace_valueChanged(vector, extern_vector, vectorArray, extern_vectorArray);
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

void CounterTraceDecorator::onVectorArrayChanged(const std::list<Test::CustomTypes::Vector3D>& vectorArray)
{
    (void) vectorArray; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}

void CounterTraceDecorator::onExternVectorArrayChanged(const std::list<Eigen::Vector3f>& extern_vectorArray)
{
    (void) extern_vectorArray; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}



ICounterPublisher& CounterTraceDecorator::_getPublisher() const
{
    return m_impl._getPublisher();
}
