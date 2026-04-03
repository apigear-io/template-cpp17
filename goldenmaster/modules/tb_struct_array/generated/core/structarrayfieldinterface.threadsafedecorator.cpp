

#include "tb_struct_array/generated/core/structarrayfieldinterface.threadsafedecorator.h"

using namespace Test::TbStructArray;
StructArrayFieldInterfaceThreadSafeDecorator::StructArrayFieldInterfaceThreadSafeDecorator(std::shared_ptr<IStructArrayFieldInterface> impl)
    : m_impl(impl)
{
}
MixedStruct StructArrayFieldInterfaceThreadSafeDecorator::funcMixed(const MixedStruct& paramMixed)
{
    return m_impl->funcMixed(paramMixed);
}

std::future<MixedStruct> StructArrayFieldInterfaceThreadSafeDecorator::funcMixedAsync(const MixedStruct& paramMixed, std::function<void(MixedStruct)> callback)
{
    return m_impl->funcMixedAsync(paramMixed, callback);
}
StructWithArrayOfStructs StructArrayFieldInterfaceThreadSafeDecorator::funcStructArray(const StructWithArrayOfStructs& paramPoints)
{
    return m_impl->funcStructArray(paramPoints);
}

std::future<StructWithArrayOfStructs> StructArrayFieldInterfaceThreadSafeDecorator::funcStructArrayAsync(const StructWithArrayOfStructs& paramPoints, std::function<void(StructWithArrayOfStructs)> callback)
{
    return m_impl->funcStructArrayAsync(paramPoints, callback);
}
void StructArrayFieldInterfaceThreadSafeDecorator::setPropStructArray(const StructWithArrayOfStructs& propStructArray)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propStructArrayMutex);
    m_impl->setPropStructArray(propStructArray);
}

const StructWithArrayOfStructs& StructArrayFieldInterfaceThreadSafeDecorator::getPropStructArray() const
{
    // WARNING: The returned reference is only valid while the internal lock is held.
    // Callers should copy the result immediately: auto val = decorator->getXxx();
    // Do NOT store the reference: const auto& ref = decorator->getXxx(); // UNSAFE
    std::shared_lock<std::shared_timed_mutex> lock(m_propStructArrayMutex);
    return m_impl->getPropStructArray();
}
void StructArrayFieldInterfaceThreadSafeDecorator::setPropEnumArray(const StructWithArrayOfEnums& propEnumArray)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propEnumArrayMutex);
    m_impl->setPropEnumArray(propEnumArray);
}

const StructWithArrayOfEnums& StructArrayFieldInterfaceThreadSafeDecorator::getPropEnumArray() const
{
    // WARNING: The returned reference is only valid while the internal lock is held.
    // Callers should copy the result immediately: auto val = decorator->getXxx();
    // Do NOT store the reference: const auto& ref = decorator->getXxx(); // UNSAFE
    std::shared_lock<std::shared_timed_mutex> lock(m_propEnumArrayMutex);
    return m_impl->getPropEnumArray();
}
void StructArrayFieldInterfaceThreadSafeDecorator::setPropIntArray(const StructWithArrayOfInts& propIntArray)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propIntArrayMutex);
    m_impl->setPropIntArray(propIntArray);
}

const StructWithArrayOfInts& StructArrayFieldInterfaceThreadSafeDecorator::getPropIntArray() const
{
    // WARNING: The returned reference is only valid while the internal lock is held.
    // Callers should copy the result immediately: auto val = decorator->getXxx();
    // Do NOT store the reference: const auto& ref = decorator->getXxx(); // UNSAFE
    std::shared_lock<std::shared_timed_mutex> lock(m_propIntArrayMutex);
    return m_impl->getPropIntArray();
}
void StructArrayFieldInterfaceThreadSafeDecorator::setPropMixed(const MixedStruct& propMixed)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propMixedMutex);
    m_impl->setPropMixed(propMixed);
}

const MixedStruct& StructArrayFieldInterfaceThreadSafeDecorator::getPropMixed() const
{
    // WARNING: The returned reference is only valid while the internal lock is held.
    // Callers should copy the result immediately: auto val = decorator->getXxx();
    // Do NOT store the reference: const auto& ref = decorator->getXxx(); // UNSAFE
    std::shared_lock<std::shared_timed_mutex> lock(m_propMixedMutex);
    return m_impl->getPropMixed();
}

IStructArrayFieldInterfacePublisher& StructArrayFieldInterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}