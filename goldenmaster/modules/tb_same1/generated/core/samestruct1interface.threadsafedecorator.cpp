

#include "tb_same1/generated/core/samestruct1interface.threadsafedecorator.h"

using namespace Test::TbSame1;
SameStruct1InterfaceThreadSafeDecorator::SameStruct1InterfaceThreadSafeDecorator(std::shared_ptr<ISameStruct1Interface> impl)
    : m_impl(impl)
{
}
Struct1 SameStruct1InterfaceThreadSafeDecorator::func1(const Struct1& param1)
{
    return m_impl->func1(param1);
}

std::future<Struct1> SameStruct1InterfaceThreadSafeDecorator::func1Async(const Struct1& param1, std::function<void(Struct1)> callback)
{
    return m_impl->func1Async(param1, callback);
}
void SameStruct1InterfaceThreadSafeDecorator::setProp1(const Struct1& prop1)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    m_impl->setProp1(prop1);
}

const Struct1& SameStruct1InterfaceThreadSafeDecorator::getProp1() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    return m_impl->getProp1();
}

ISameStruct1InterfacePublisher& SameStruct1InterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}