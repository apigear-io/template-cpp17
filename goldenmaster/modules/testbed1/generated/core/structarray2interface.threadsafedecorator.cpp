

#include "testbed1/generated/core/structarray2interface.threadsafedecorator.h"

using namespace Test::Testbed1;
StructArray2InterfaceThreadSafeDecorator::StructArray2InterfaceThreadSafeDecorator(std::shared_ptr<IStructArray2Interface> impl)
    : m_impl(impl)
{
}
std::list<StructBool> StructArray2InterfaceThreadSafeDecorator::funcBool(const StructBoolWithArray& paramBool)
{
    return m_impl->funcBool(paramBool);
}

std::future<std::list<StructBool>> StructArray2InterfaceThreadSafeDecorator::funcBoolAsync(const StructBoolWithArray& paramBool, std::function<void(std::list<StructBool>)> callback)
{
    return m_impl->funcBoolAsync(paramBool, callback);
}
std::list<StructInt> StructArray2InterfaceThreadSafeDecorator::funcInt(const StructIntWithArray& paramInt)
{
    return m_impl->funcInt(paramInt);
}

std::future<std::list<StructInt>> StructArray2InterfaceThreadSafeDecorator::funcIntAsync(const StructIntWithArray& paramInt, std::function<void(std::list<StructInt>)> callback)
{
    return m_impl->funcIntAsync(paramInt, callback);
}
std::list<StructFloat> StructArray2InterfaceThreadSafeDecorator::funcFloat(const StructFloatWithArray& paramFloat)
{
    return m_impl->funcFloat(paramFloat);
}

std::future<std::list<StructFloat>> StructArray2InterfaceThreadSafeDecorator::funcFloatAsync(const StructFloatWithArray& paramFloat, std::function<void(std::list<StructFloat>)> callback)
{
    return m_impl->funcFloatAsync(paramFloat, callback);
}
std::list<StructString> StructArray2InterfaceThreadSafeDecorator::funcString(const StructStringWithArray& paramString)
{
    return m_impl->funcString(paramString);
}

std::future<std::list<StructString>> StructArray2InterfaceThreadSafeDecorator::funcStringAsync(const StructStringWithArray& paramString, std::function<void(std::list<StructString>)> callback)
{
    return m_impl->funcStringAsync(paramString, callback);
}
std::list<Enum0Enum> StructArray2InterfaceThreadSafeDecorator::funcEnum(const StructEnumWithArray& paramEnum)
{
    return m_impl->funcEnum(paramEnum);
}

std::future<std::list<Enum0Enum>> StructArray2InterfaceThreadSafeDecorator::funcEnumAsync(const StructEnumWithArray& paramEnum, std::function<void(std::list<Enum0Enum>)> callback)
{
    return m_impl->funcEnumAsync(paramEnum, callback);
}
void StructArray2InterfaceThreadSafeDecorator::setPropBool(const StructBoolWithArray& propBool)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propBoolMutex);
    m_impl->setPropBool(propBool);
}

const StructBoolWithArray& StructArray2InterfaceThreadSafeDecorator::getPropBool() const
{
    // WARNING: The returned reference is only valid while the internal lock is held.
    // Callers should copy the result immediately: auto val = decorator->getXxx();
    // Do NOT store the reference: const auto& ref = decorator->getXxx(); // UNSAFE
    std::shared_lock<std::shared_timed_mutex> lock(m_propBoolMutex);
    return m_impl->getPropBool();
}
void StructArray2InterfaceThreadSafeDecorator::setPropInt(const StructIntWithArray& propInt)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    m_impl->setPropInt(propInt);
}

const StructIntWithArray& StructArray2InterfaceThreadSafeDecorator::getPropInt() const
{
    // WARNING: The returned reference is only valid while the internal lock is held.
    // Callers should copy the result immediately: auto val = decorator->getXxx();
    // Do NOT store the reference: const auto& ref = decorator->getXxx(); // UNSAFE
    std::shared_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    return m_impl->getPropInt();
}
void StructArray2InterfaceThreadSafeDecorator::setPropFloat(const StructFloatWithArray& propFloat)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    m_impl->setPropFloat(propFloat);
}

const StructFloatWithArray& StructArray2InterfaceThreadSafeDecorator::getPropFloat() const
{
    // WARNING: The returned reference is only valid while the internal lock is held.
    // Callers should copy the result immediately: auto val = decorator->getXxx();
    // Do NOT store the reference: const auto& ref = decorator->getXxx(); // UNSAFE
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    return m_impl->getPropFloat();
}
void StructArray2InterfaceThreadSafeDecorator::setPropString(const StructStringWithArray& propString)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    m_impl->setPropString(propString);
}

const StructStringWithArray& StructArray2InterfaceThreadSafeDecorator::getPropString() const
{
    // WARNING: The returned reference is only valid while the internal lock is held.
    // Callers should copy the result immediately: auto val = decorator->getXxx();
    // Do NOT store the reference: const auto& ref = decorator->getXxx(); // UNSAFE
    std::shared_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    return m_impl->getPropString();
}
void StructArray2InterfaceThreadSafeDecorator::setPropEnum(const StructEnumWithArray& propEnum)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propEnumMutex);
    m_impl->setPropEnum(propEnum);
}

const StructEnumWithArray& StructArray2InterfaceThreadSafeDecorator::getPropEnum() const
{
    // WARNING: The returned reference is only valid while the internal lock is held.
    // Callers should copy the result immediately: auto val = decorator->getXxx();
    // Do NOT store the reference: const auto& ref = decorator->getXxx(); // UNSAFE
    std::shared_lock<std::shared_timed_mutex> lock(m_propEnumMutex);
    return m_impl->getPropEnum();
}

IStructArray2InterfacePublisher& StructArray2InterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}