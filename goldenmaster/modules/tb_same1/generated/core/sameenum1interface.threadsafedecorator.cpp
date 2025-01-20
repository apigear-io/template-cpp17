

#include "tb_same1/generated/core/sameenum1interface.threadsafedecorator.h"

using namespace Test::TbSame1;
SameEnum1InterfaceThreadSafeDecorator::SameEnum1InterfaceThreadSafeDecorator(std::shared_ptr<ISameEnum1Interface> impl)
    : m_impl(impl)
{
}
Enum1Enum SameEnum1InterfaceThreadSafeDecorator::func1(Enum1Enum param1)
{
    return m_impl->func1(param1);
}

std::future<Enum1Enum> SameEnum1InterfaceThreadSafeDecorator::func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback)
{
    return m_impl->func1Async(param1, callback);
}
void SameEnum1InterfaceThreadSafeDecorator::setProp1(Enum1Enum prop1)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    m_impl->setProp1(prop1);
}

Enum1Enum SameEnum1InterfaceThreadSafeDecorator::getProp1() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    return m_impl->getProp1();
}

ISameEnum1InterfacePublisher& SameEnum1InterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}