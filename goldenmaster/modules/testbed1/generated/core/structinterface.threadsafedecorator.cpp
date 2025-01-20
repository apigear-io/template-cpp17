

#include "testbed1/generated/core/structinterface.threadsafedecorator.h"

using namespace Test::Testbed1;
StructInterfaceThreadSafeDecorator::StructInterfaceThreadSafeDecorator(std::shared_ptr<IStructInterface> impl)
    : m_impl(impl)
{
}
StructBool StructInterfaceThreadSafeDecorator::funcBool(const StructBool& paramBool)
{
    return m_impl->funcBool(paramBool);
}

std::future<StructBool> StructInterfaceThreadSafeDecorator::funcBoolAsync(const StructBool& paramBool, std::function<void(StructBool)> callback)
{
    return m_impl->funcBoolAsync(paramBool, callback);
}
StructBool StructInterfaceThreadSafeDecorator::funcInt(const StructInt& paramInt)
{
    return m_impl->funcInt(paramInt);
}

std::future<StructBool> StructInterfaceThreadSafeDecorator::funcIntAsync(const StructInt& paramInt, std::function<void(StructBool)> callback)
{
    return m_impl->funcIntAsync(paramInt, callback);
}
StructFloat StructInterfaceThreadSafeDecorator::funcFloat(const StructFloat& paramFloat)
{
    return m_impl->funcFloat(paramFloat);
}

std::future<StructFloat> StructInterfaceThreadSafeDecorator::funcFloatAsync(const StructFloat& paramFloat, std::function<void(StructFloat)> callback)
{
    return m_impl->funcFloatAsync(paramFloat, callback);
}
StructString StructInterfaceThreadSafeDecorator::funcString(const StructString& paramString)
{
    return m_impl->funcString(paramString);
}

std::future<StructString> StructInterfaceThreadSafeDecorator::funcStringAsync(const StructString& paramString, std::function<void(StructString)> callback)
{
    return m_impl->funcStringAsync(paramString, callback);
}
void StructInterfaceThreadSafeDecorator::setPropBool(const StructBool& propBool)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propBoolMutex);
    m_impl->setPropBool(propBool);
}

const StructBool& StructInterfaceThreadSafeDecorator::getPropBool() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propBoolMutex);
    return m_impl->getPropBool();
}
void StructInterfaceThreadSafeDecorator::setPropInt(const StructInt& propInt)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    m_impl->setPropInt(propInt);
}

const StructInt& StructInterfaceThreadSafeDecorator::getPropInt() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    return m_impl->getPropInt();
}
void StructInterfaceThreadSafeDecorator::setPropFloat(const StructFloat& propFloat)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    m_impl->setPropFloat(propFloat);
}

const StructFloat& StructInterfaceThreadSafeDecorator::getPropFloat() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    return m_impl->getPropFloat();
}
void StructInterfaceThreadSafeDecorator::setPropString(const StructString& propString)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    m_impl->setPropString(propString);
}

const StructString& StructInterfaceThreadSafeDecorator::getPropString() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    return m_impl->getPropString();
}

IStructInterfacePublisher& StructInterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}