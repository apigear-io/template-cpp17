

#include "tb_simple/generated/core/simplearrayinterface.threadsafedecorator.h"

using namespace Test::TbSimple;
SimpleArrayInterfaceThreadSafeDecorator::SimpleArrayInterfaceThreadSafeDecorator(std::shared_ptr<ISimpleArrayInterface> impl)
    : m_impl(impl)
{
}
std::list<bool> SimpleArrayInterfaceThreadSafeDecorator::funcBool(const std::list<bool>& paramBool)
{
    return m_impl->funcBool(paramBool);
}

std::future<std::list<bool>> SimpleArrayInterfaceThreadSafeDecorator::funcBoolAsync(const std::list<bool>& paramBool)
{
    return m_impl->funcBoolAsync(paramBool);
}
std::list<int> SimpleArrayInterfaceThreadSafeDecorator::funcInt(const std::list<int>& paramInt)
{
    return m_impl->funcInt(paramInt);
}

std::future<std::list<int>> SimpleArrayInterfaceThreadSafeDecorator::funcIntAsync(const std::list<int>& paramInt)
{
    return m_impl->funcIntAsync(paramInt);
}
std::list<int32_t> SimpleArrayInterfaceThreadSafeDecorator::funcInt32(const std::list<int32_t>& paramInt32)
{
    return m_impl->funcInt32(paramInt32);
}

std::future<std::list<int32_t>> SimpleArrayInterfaceThreadSafeDecorator::funcInt32Async(const std::list<int32_t>& paramInt32)
{
    return m_impl->funcInt32Async(paramInt32);
}
std::list<int64_t> SimpleArrayInterfaceThreadSafeDecorator::funcInt64(const std::list<int64_t>& paramInt64)
{
    return m_impl->funcInt64(paramInt64);
}

std::future<std::list<int64_t>> SimpleArrayInterfaceThreadSafeDecorator::funcInt64Async(const std::list<int64_t>& paramInt64)
{
    return m_impl->funcInt64Async(paramInt64);
}
std::list<float> SimpleArrayInterfaceThreadSafeDecorator::funcFloat(const std::list<float>& paramFloat)
{
    return m_impl->funcFloat(paramFloat);
}

std::future<std::list<float>> SimpleArrayInterfaceThreadSafeDecorator::funcFloatAsync(const std::list<float>& paramFloat)
{
    return m_impl->funcFloatAsync(paramFloat);
}
std::list<float> SimpleArrayInterfaceThreadSafeDecorator::funcFloat32(const std::list<float>& paramFloat32)
{
    return m_impl->funcFloat32(paramFloat32);
}

std::future<std::list<float>> SimpleArrayInterfaceThreadSafeDecorator::funcFloat32Async(const std::list<float>& paramFloat32)
{
    return m_impl->funcFloat32Async(paramFloat32);
}
std::list<double> SimpleArrayInterfaceThreadSafeDecorator::funcFloat64(const std::list<double>& paramFloat)
{
    return m_impl->funcFloat64(paramFloat);
}

std::future<std::list<double>> SimpleArrayInterfaceThreadSafeDecorator::funcFloat64Async(const std::list<double>& paramFloat)
{
    return m_impl->funcFloat64Async(paramFloat);
}
std::list<std::string> SimpleArrayInterfaceThreadSafeDecorator::funcString(const std::list<std::string>& paramString)
{
    return m_impl->funcString(paramString);
}

std::future<std::list<std::string>> SimpleArrayInterfaceThreadSafeDecorator::funcStringAsync(const std::list<std::string>& paramString)
{
    return m_impl->funcStringAsync(paramString);
}
void SimpleArrayInterfaceThreadSafeDecorator::setPropBool(const std::list<bool>& propBool)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propBoolMutex);
    m_impl->setPropBool(propBool);
}

const std::list<bool>& SimpleArrayInterfaceThreadSafeDecorator::getPropBool() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propBoolMutex);
    return m_impl->getPropBool();
}
void SimpleArrayInterfaceThreadSafeDecorator::setPropInt(const std::list<int>& propInt)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    m_impl->setPropInt(propInt);
}

const std::list<int>& SimpleArrayInterfaceThreadSafeDecorator::getPropInt() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    return m_impl->getPropInt();
}
void SimpleArrayInterfaceThreadSafeDecorator::setPropInt32(const std::list<int32_t>& propInt32)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propInt32Mutex);
    m_impl->setPropInt32(propInt32);
}

const std::list<int32_t>& SimpleArrayInterfaceThreadSafeDecorator::getPropInt32() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propInt32Mutex);
    return m_impl->getPropInt32();
}
void SimpleArrayInterfaceThreadSafeDecorator::setPropInt64(const std::list<int64_t>& propInt64)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propInt64Mutex);
    m_impl->setPropInt64(propInt64);
}

const std::list<int64_t>& SimpleArrayInterfaceThreadSafeDecorator::getPropInt64() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propInt64Mutex);
    return m_impl->getPropInt64();
}
void SimpleArrayInterfaceThreadSafeDecorator::setPropFloat(const std::list<float>& propFloat)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    m_impl->setPropFloat(propFloat);
}

const std::list<float>& SimpleArrayInterfaceThreadSafeDecorator::getPropFloat() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    return m_impl->getPropFloat();
}
void SimpleArrayInterfaceThreadSafeDecorator::setPropFloat32(const std::list<float>& propFloat32)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloat32Mutex);
    m_impl->setPropFloat32(propFloat32);
}

const std::list<float>& SimpleArrayInterfaceThreadSafeDecorator::getPropFloat32() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloat32Mutex);
    return m_impl->getPropFloat32();
}
void SimpleArrayInterfaceThreadSafeDecorator::setPropFloat64(const std::list<double>& propFloat64)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloat64Mutex);
    m_impl->setPropFloat64(propFloat64);
}

const std::list<double>& SimpleArrayInterfaceThreadSafeDecorator::getPropFloat64() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloat64Mutex);
    return m_impl->getPropFloat64();
}
void SimpleArrayInterfaceThreadSafeDecorator::setPropString(const std::list<std::string>& propString)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    m_impl->setPropString(propString);
}

const std::list<std::string>& SimpleArrayInterfaceThreadSafeDecorator::getPropString() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    return m_impl->getPropString();
}

const std::string& SimpleArrayInterfaceThreadSafeDecorator::getPropReadOnlyString() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propReadOnlyStringMutex);
    return m_impl->getPropReadOnlyString();
}

ISimpleArrayInterfacePublisher& SimpleArrayInterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}