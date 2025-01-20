

#include "testbed1/generated/core/structarrayinterface.threadsafedecorator.h"

using namespace Test::Testbed1;
StructArrayInterfaceThreadSafeDecorator::StructArrayInterfaceThreadSafeDecorator(std::shared_ptr<IStructArrayInterface> impl)
    : m_impl(impl)
{
}
StructBool StructArrayInterfaceThreadSafeDecorator::funcBool(const std::list<StructBool>& paramBool)
{
    return m_impl->funcBool(paramBool);
}

std::future<StructBool> StructArrayInterfaceThreadSafeDecorator::funcBoolAsync(const std::list<StructBool>& paramBool, std::function<void(StructBool)> callback)
{
    return m_impl->funcBoolAsync(paramBool, callback);
}
StructBool StructArrayInterfaceThreadSafeDecorator::funcInt(const std::list<StructInt>& paramInt)
{
    return m_impl->funcInt(paramInt);
}

std::future<StructBool> StructArrayInterfaceThreadSafeDecorator::funcIntAsync(const std::list<StructInt>& paramInt, std::function<void(StructBool)> callback)
{
    return m_impl->funcIntAsync(paramInt, callback);
}
StructBool StructArrayInterfaceThreadSafeDecorator::funcFloat(const std::list<StructFloat>& paramFloat)
{
    return m_impl->funcFloat(paramFloat);
}

std::future<StructBool> StructArrayInterfaceThreadSafeDecorator::funcFloatAsync(const std::list<StructFloat>& paramFloat, std::function<void(StructBool)> callback)
{
    return m_impl->funcFloatAsync(paramFloat, callback);
}
StructBool StructArrayInterfaceThreadSafeDecorator::funcString(const std::list<StructString>& paramString)
{
    return m_impl->funcString(paramString);
}

std::future<StructBool> StructArrayInterfaceThreadSafeDecorator::funcStringAsync(const std::list<StructString>& paramString, std::function<void(StructBool)> callback)
{
    return m_impl->funcStringAsync(paramString, callback);
}
void StructArrayInterfaceThreadSafeDecorator::setPropBool(const std::list<StructBool>& propBool)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propBoolMutex);
    m_impl->setPropBool(propBool);
}

const std::list<StructBool>& StructArrayInterfaceThreadSafeDecorator::getPropBool() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propBoolMutex);
    return m_impl->getPropBool();
}
void StructArrayInterfaceThreadSafeDecorator::setPropInt(const std::list<StructInt>& propInt)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    m_impl->setPropInt(propInt);
}

const std::list<StructInt>& StructArrayInterfaceThreadSafeDecorator::getPropInt() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    return m_impl->getPropInt();
}
void StructArrayInterfaceThreadSafeDecorator::setPropFloat(const std::list<StructFloat>& propFloat)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    m_impl->setPropFloat(propFloat);
}

const std::list<StructFloat>& StructArrayInterfaceThreadSafeDecorator::getPropFloat() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    return m_impl->getPropFloat();
}
void StructArrayInterfaceThreadSafeDecorator::setPropString(const std::list<StructString>& propString)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    m_impl->setPropString(propString);
}

const std::list<StructString>& StructArrayInterfaceThreadSafeDecorator::getPropString() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    return m_impl->getPropString();
}

IStructArrayInterfacePublisher& StructArrayInterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}