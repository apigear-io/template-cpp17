

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
std::list<Eigen::Vector3f> CounterThreadSafeDecorator::incrementArray(const std::list<Eigen::Vector3f>& vec)
{
    return m_impl->incrementArray(vec);
}

std::future<std::list<Eigen::Vector3f>> CounterThreadSafeDecorator::incrementArrayAsync(const std::list<Eigen::Vector3f>& vec)
{
    return m_impl->incrementArrayAsync(vec);
}
Test::CustomTypes::Vector3D CounterThreadSafeDecorator::decrement(const Test::CustomTypes::Vector3D& vec)
{
    return m_impl->decrement(vec);
}

std::future<Test::CustomTypes::Vector3D> CounterThreadSafeDecorator::decrementAsync(const Test::CustomTypes::Vector3D& vec)
{
    return m_impl->decrementAsync(vec);
}
std::list<Test::CustomTypes::Vector3D> CounterThreadSafeDecorator::decrementArray(const std::list<Test::CustomTypes::Vector3D>& vec)
{
    return m_impl->decrementArray(vec);
}

std::future<std::list<Test::CustomTypes::Vector3D>> CounterThreadSafeDecorator::decrementArrayAsync(const std::list<Test::CustomTypes::Vector3D>& vec)
{
    return m_impl->decrementArrayAsync(vec);
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
void CounterThreadSafeDecorator::setVectorArray(const std::list<Test::CustomTypes::Vector3D>& vectorArray)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_vectorArrayMutex);
    m_impl->setVectorArray(vectorArray);
}

const std::list<Test::CustomTypes::Vector3D>& CounterThreadSafeDecorator::getVectorArray() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_vectorArrayMutex);
    return m_impl->getVectorArray();
}
void CounterThreadSafeDecorator::setExternVectorArray(const std::list<Eigen::Vector3f>& extern_vectorArray)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_externVectorArrayMutex);
    m_impl->setExternVectorArray(extern_vectorArray);
}

const std::list<Eigen::Vector3f>& CounterThreadSafeDecorator::getExternVectorArray() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_externVectorArrayMutex);
    return m_impl->getExternVectorArray();
}

ICounterPublisher& CounterThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}