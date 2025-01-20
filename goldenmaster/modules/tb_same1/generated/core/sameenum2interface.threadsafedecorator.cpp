

#include "tb_same1/generated/core/sameenum2interface.threadsafedecorator.h"

using namespace Test::TbSame1;
SameEnum2InterfaceThreadSafeDecorator::SameEnum2InterfaceThreadSafeDecorator(std::shared_ptr<ISameEnum2Interface> impl)
    : m_impl(impl)
{
}
Enum1Enum SameEnum2InterfaceThreadSafeDecorator::func1(Enum1Enum param1)
{
    return m_impl->func1(param1);
}

std::future<Enum1Enum> SameEnum2InterfaceThreadSafeDecorator::func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback)
{
    return m_impl->func1Async(param1, callback);
}
Enum1Enum SameEnum2InterfaceThreadSafeDecorator::func2(Enum1Enum param1, Enum2Enum param2)
{
    return m_impl->func2(param1, param2);
}

std::future<Enum1Enum> SameEnum2InterfaceThreadSafeDecorator::func2Async(Enum1Enum param1, Enum2Enum param2, std::function<void(Enum1Enum)> callback)
{
    return m_impl->func2Async(param1, param2, callback);
}
void SameEnum2InterfaceThreadSafeDecorator::setProp1(Enum1Enum prop1)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    m_impl->setProp1(prop1);
}

Enum1Enum SameEnum2InterfaceThreadSafeDecorator::getProp1() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    return m_impl->getProp1();
}
void SameEnum2InterfaceThreadSafeDecorator::setProp2(Enum2Enum prop2)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop2Mutex);
    m_impl->setProp2(prop2);
}

Enum2Enum SameEnum2InterfaceThreadSafeDecorator::getProp2() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop2Mutex);
    return m_impl->getProp2();
}

ISameEnum2InterfacePublisher& SameEnum2InterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}