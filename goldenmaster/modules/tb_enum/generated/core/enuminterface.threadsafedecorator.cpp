

#include "tb_enum/generated/core/enuminterface.threadsafedecorator.h"

using namespace Test::TbEnum;
EnumInterfaceThreadSafeDecorator::EnumInterfaceThreadSafeDecorator(std::shared_ptr<IEnumInterface> impl)
    : m_impl(impl)
{
}
Enum0Enum EnumInterfaceThreadSafeDecorator::func0(Enum0Enum param0)
{
    return m_impl->func0(param0);
}

std::future<Enum0Enum> EnumInterfaceThreadSafeDecorator::func0Async(Enum0Enum param0, std::function<void(Enum0Enum)> callback)
{
    return m_impl->func0Async(param0, callback);
}
Enum1Enum EnumInterfaceThreadSafeDecorator::func1(Enum1Enum param1)
{
    return m_impl->func1(param1);
}

std::future<Enum1Enum> EnumInterfaceThreadSafeDecorator::func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback)
{
    return m_impl->func1Async(param1, callback);
}
Enum2Enum EnumInterfaceThreadSafeDecorator::func2(Enum2Enum param2)
{
    return m_impl->func2(param2);
}

std::future<Enum2Enum> EnumInterfaceThreadSafeDecorator::func2Async(Enum2Enum param2, std::function<void(Enum2Enum)> callback)
{
    return m_impl->func2Async(param2, callback);
}
Enum3Enum EnumInterfaceThreadSafeDecorator::func3(Enum3Enum param3)
{
    return m_impl->func3(param3);
}

std::future<Enum3Enum> EnumInterfaceThreadSafeDecorator::func3Async(Enum3Enum param3, std::function<void(Enum3Enum)> callback)
{
    return m_impl->func3Async(param3, callback);
}
void EnumInterfaceThreadSafeDecorator::setProp0(Enum0Enum prop0)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop0Mutex);
    m_impl->setProp0(prop0);
}

Enum0Enum EnumInterfaceThreadSafeDecorator::getProp0() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop0Mutex);
    return m_impl->getProp0();
}
void EnumInterfaceThreadSafeDecorator::setProp1(Enum1Enum prop1)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    m_impl->setProp1(prop1);
}

Enum1Enum EnumInterfaceThreadSafeDecorator::getProp1() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    return m_impl->getProp1();
}
void EnumInterfaceThreadSafeDecorator::setProp2(Enum2Enum prop2)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop2Mutex);
    m_impl->setProp2(prop2);
}

Enum2Enum EnumInterfaceThreadSafeDecorator::getProp2() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop2Mutex);
    return m_impl->getProp2();
}
void EnumInterfaceThreadSafeDecorator::setProp3(Enum3Enum prop3)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop3Mutex);
    m_impl->setProp3(prop3);
}

Enum3Enum EnumInterfaceThreadSafeDecorator::getProp3() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop3Mutex);
    return m_impl->getProp3();
}

IEnumInterfacePublisher& EnumInterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}