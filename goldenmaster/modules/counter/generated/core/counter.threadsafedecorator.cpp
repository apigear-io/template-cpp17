

#include "counter/generated/core/counter.threadsafedecorator.h"

using namespace Test::Counter;
CounterThreadSafeDecorator::CounterThreadSafeDecorator(std::shared_ptr<ICounter> impl)
    : m_impl(impl)
{
}
Eigen::Vector3f CounterThreadSafeDecorator::increment(const Eigen::Vector3f& vec)
{
    return m_impl->increment(vec);
}

std::future<Eigen::Vector3f> CounterThreadSafeDecorator::incrementAsync(const Eigen::Vector3f& vec)
{
    return m_impl->incrementAsync(vec);
}
Test::CustomTypes::Vector3D CounterThreadSafeDecorator::decrement(const Test::CustomTypes::Vector3D& vec)
{
    return m_impl->decrement(vec);
}

std::future<Test::CustomTypes::Vector3D> CounterThreadSafeDecorator::decrementAsync(const Test::CustomTypes::Vector3D& vec)
{
    return m_impl->decrementAsync(vec);
}
void CounterThreadSafeDecorator::setVector(const Test::CustomTypes::Vector3D& vector)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_vectorMutex);
    m_impl->setVector(vector);
}

const Test::CustomTypes::Vector3D& CounterThreadSafeDecorator::getVector() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_vectorMutex);
    return m_impl->getVector();
}
void CounterThreadSafeDecorator::setExternVector(const Eigen::Vector3f& extern_vector)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_externVectorMutex);
    m_impl->setExternVector(extern_vector);
}

const Eigen::Vector3f& CounterThreadSafeDecorator::getExternVector() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_externVectorMutex);
    return m_impl->getExternVector();
}

ICounterPublisher& CounterThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}