

#include "tb_same1/generated/core/samestruct2interface.threadsafedecorator.h"

using namespace Test::TbSame1;
SameStruct2InterfaceThreadSafeDecorator::SameStruct2InterfaceThreadSafeDecorator(std::shared_ptr<ISameStruct2Interface> impl)
    : m_impl(impl)
{
}
Struct1 SameStruct2InterfaceThreadSafeDecorator::func1(const Struct1& param1)
{
    return m_impl->func1(param1);
}

std::future<Struct1> SameStruct2InterfaceThreadSafeDecorator::func1Async(const Struct1& param1, std::function<void(Struct1)> callback)
{
    return m_impl->func1Async(param1, callback);
}
Struct1 SameStruct2InterfaceThreadSafeDecorator::func2(const Struct1& param1, const Struct2& param2)
{
    return m_impl->func2(param1, param2);
}

std::future<Struct1> SameStruct2InterfaceThreadSafeDecorator::func2Async(const Struct1& param1, const Struct2& param2, std::function<void(Struct1)> callback)
{
    return m_impl->func2Async(param1, param2, callback);
}
void SameStruct2InterfaceThreadSafeDecorator::setProp1(const Struct2& prop1)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    m_impl->setProp1(prop1);
}

const Struct2& SameStruct2InterfaceThreadSafeDecorator::getProp1() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    return m_impl->getProp1();
}
void SameStruct2InterfaceThreadSafeDecorator::setProp2(const Struct2& prop2)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop2Mutex);
    m_impl->setProp2(prop2);
}

const Struct2& SameStruct2InterfaceThreadSafeDecorator::getProp2() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop2Mutex);
    return m_impl->getProp2();
}

ISameStruct2InterfacePublisher& SameStruct2InterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}