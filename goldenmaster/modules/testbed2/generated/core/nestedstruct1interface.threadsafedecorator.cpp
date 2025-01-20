

#include "testbed2/generated/core/nestedstruct1interface.threadsafedecorator.h"

using namespace Test::Testbed2;
NestedStruct1InterfaceThreadSafeDecorator::NestedStruct1InterfaceThreadSafeDecorator(std::shared_ptr<INestedStruct1Interface> impl)
    : m_impl(impl)
{
}
NestedStruct1 NestedStruct1InterfaceThreadSafeDecorator::func1(const NestedStruct1& param1)
{
    return m_impl->func1(param1);
}

std::future<NestedStruct1> NestedStruct1InterfaceThreadSafeDecorator::func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback)
{
    return m_impl->func1Async(param1, callback);
}
void NestedStruct1InterfaceThreadSafeDecorator::setProp1(const NestedStruct1& prop1)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    m_impl->setProp1(prop1);
}

const NestedStruct1& NestedStruct1InterfaceThreadSafeDecorator::getProp1() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    return m_impl->getProp1();
}

INestedStruct1InterfacePublisher& NestedStruct1InterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}