

#include "tb_simple/generated/core/nopropertiesinterface.threadsafedecorator.h"

using namespace Test::TbSimple;
NoPropertiesInterfaceThreadSafeDecorator::NoPropertiesInterfaceThreadSafeDecorator(std::shared_ptr<INoPropertiesInterface> impl)
    : m_impl(impl)
{
}
void NoPropertiesInterfaceThreadSafeDecorator::funcVoid()
{
    return m_impl->funcVoid();
}

std::future<void> NoPropertiesInterfaceThreadSafeDecorator::funcVoidAsync( std::function<void(void)> callback)
{
    return m_impl->funcVoidAsync( callback);
}
bool NoPropertiesInterfaceThreadSafeDecorator::funcBool(bool paramBool)
{
    return m_impl->funcBool(paramBool);
}

std::future<bool> NoPropertiesInterfaceThreadSafeDecorator::funcBoolAsync(bool paramBool, std::function<void(bool)> callback)
{
    return m_impl->funcBoolAsync(paramBool, callback);
}

INoPropertiesInterfacePublisher& NoPropertiesInterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}