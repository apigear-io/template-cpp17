

#include "testbed2/generated/core/nestedstruct3interface.threadsafedecorator.h"

using namespace Test::Testbed2;
NestedStruct3InterfaceThreadSafeDecorator::NestedStruct3InterfaceThreadSafeDecorator(std::shared_ptr<INestedStruct3Interface> impl)
    : m_impl(impl)
{
}
NestedStruct1 NestedStruct3InterfaceThreadSafeDecorator::func1(const NestedStruct1& param1)
{
    return m_impl->func1(param1);
}

std::future<NestedStruct1> NestedStruct3InterfaceThreadSafeDecorator::func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback)
{
    return m_impl->func1Async(param1, callback);
}
NestedStruct1 NestedStruct3InterfaceThreadSafeDecorator::func2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    return m_impl->func2(param1, param2);
}

std::future<NestedStruct1> NestedStruct3InterfaceThreadSafeDecorator::func2Async(const NestedStruct1& param1, const NestedStruct2& param2, std::function<void(NestedStruct1)> callback)
{
    return m_impl->func2Async(param1, param2, callback);
}
NestedStruct1 NestedStruct3InterfaceThreadSafeDecorator::func3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3)
{
    return m_impl->func3(param1, param2, param3);
}

std::future<NestedStruct1> NestedStruct3InterfaceThreadSafeDecorator::func3Async(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3, std::function<void(NestedStruct1)> callback)
{
    return m_impl->func3Async(param1, param2, param3, callback);
}
void NestedStruct3InterfaceThreadSafeDecorator::setProp1(const NestedStruct1& prop1)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    m_impl->setProp1(prop1);
}

const NestedStruct1& NestedStruct3InterfaceThreadSafeDecorator::getProp1() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    return m_impl->getProp1();
}
void NestedStruct3InterfaceThreadSafeDecorator::setProp2(const NestedStruct2& prop2)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop2Mutex);
    m_impl->setProp2(prop2);
}

const NestedStruct2& NestedStruct3InterfaceThreadSafeDecorator::getProp2() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop2Mutex);
    return m_impl->getProp2();
}
void NestedStruct3InterfaceThreadSafeDecorator::setProp3(const NestedStruct3& prop3)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop3Mutex);
    m_impl->setProp3(prop3);
}

const NestedStruct3& NestedStruct3InterfaceThreadSafeDecorator::getProp3() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop3Mutex);
    return m_impl->getProp3();
}

INestedStruct3InterfacePublisher& NestedStruct3InterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}