

#include "testbed2/generated/core/manyparaminterface.threadsafedecorator.h"

using namespace Test::Testbed2;
ManyParamInterfaceThreadSafeDecorator::ManyParamInterfaceThreadSafeDecorator(std::shared_ptr<IManyParamInterface> impl)
    : m_impl(impl)
{
}
int ManyParamInterfaceThreadSafeDecorator::func1(int param1)
{
    return m_impl->func1(param1);
}

std::future<int> ManyParamInterfaceThreadSafeDecorator::func1Async(int param1, std::function<void(int)> callback)
{
    return m_impl->func1Async(param1, callback);
}
int ManyParamInterfaceThreadSafeDecorator::func2(int param1, int param2)
{
    return m_impl->func2(param1, param2);
}

std::future<int> ManyParamInterfaceThreadSafeDecorator::func2Async(int param1, int param2, std::function<void(int)> callback)
{
    return m_impl->func2Async(param1, param2, callback);
}
int ManyParamInterfaceThreadSafeDecorator::func3(int param1, int param2, int param3)
{
    return m_impl->func3(param1, param2, param3);
}

std::future<int> ManyParamInterfaceThreadSafeDecorator::func3Async(int param1, int param2, int param3, std::function<void(int)> callback)
{
    return m_impl->func3Async(param1, param2, param3, callback);
}
int ManyParamInterfaceThreadSafeDecorator::func4(int param1, int param2, int param3, int param4)
{
    return m_impl->func4(param1, param2, param3, param4);
}

std::future<int> ManyParamInterfaceThreadSafeDecorator::func4Async(int param1, int param2, int param3, int param4, std::function<void(int)> callback)
{
    return m_impl->func4Async(param1, param2, param3, param4, callback);
}
void ManyParamInterfaceThreadSafeDecorator::setProp1(int prop1)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    m_impl->setProp1(prop1);
}

int ManyParamInterfaceThreadSafeDecorator::getProp1() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop1Mutex);
    return m_impl->getProp1();
}
void ManyParamInterfaceThreadSafeDecorator::setProp2(int prop2)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop2Mutex);
    m_impl->setProp2(prop2);
}

int ManyParamInterfaceThreadSafeDecorator::getProp2() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop2Mutex);
    return m_impl->getProp2();
}
void ManyParamInterfaceThreadSafeDecorator::setProp3(int prop3)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop3Mutex);
    m_impl->setProp3(prop3);
}

int ManyParamInterfaceThreadSafeDecorator::getProp3() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop3Mutex);
    return m_impl->getProp3();
}
void ManyParamInterfaceThreadSafeDecorator::setProp4(int prop4)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_prop4Mutex);
    m_impl->setProp4(prop4);
}

int ManyParamInterfaceThreadSafeDecorator::getProp4() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_prop4Mutex);
    return m_impl->getProp4();
}

IManyParamInterfacePublisher& ManyParamInterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}