

#include "testbed2/generated/core/nestedstruct2interface.threadsafedecorator.h"

using namespace Test::Testbed2;
NestedStruct2InterfaceThreadSafeDecorator::NestedStruct2InterfaceThreadSafeDecorator(std::shared_ptr<INestedStruct2Interface> impl)
    : m_impl(impl)
{
}
NestedStruct1 NestedStruct2InterfaceThreadSafeDecorator::func1(const NestedStruct1& param1)
{
    return m_impl->func1(param1);
}

std::future<NestedStruct1> NestedStruct2InterfaceThreadSafeDecorator::func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback)
{
    return m_impl->func1Async(param1, callback);
}
NestedStruct1 NestedStruct2InterfaceThreadSafeDecorator::func2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    return m_impl->func2(param1, param2);
}

std::future<NestedStruct1> NestedStruct2InterfaceThreadSafeDecorator::func2Async(const NestedStruct1& param1, const NestedStruct2& param2, std::function<void(NestedStruct1)> callback)
{
    return m_impl->func2Async(param1, param2, callback);
}
void NestedStruct2InterfaceThreadSafeDecorator::setProp1(const NestedStruct1& prop1)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    m_impl->setProp1(prop1);
}

const NestedStruct1& NestedStruct2InterfaceThreadSafeDecorator::getProp1() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    return m_impl->getProp1();
}
void NestedStruct2InterfaceThreadSafeDecorator::setProp2(const NestedStruct2& prop2)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop2Mutex);
    m_impl->setProp2(prop2);
}

const NestedStruct2& NestedStruct2InterfaceThreadSafeDecorator::getProp2() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop2Mutex);
    return m_impl->getProp2();
}

INestedStruct2InterfacePublisher& NestedStruct2InterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}