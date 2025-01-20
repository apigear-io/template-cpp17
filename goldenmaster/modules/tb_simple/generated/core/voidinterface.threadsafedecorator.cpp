

#include "tb_simple/generated/core/voidinterface.threadsafedecorator.h"

using namespace Test::TbSimple;
VoidInterfaceThreadSafeDecorator::VoidInterfaceThreadSafeDecorator(std::shared_ptr<IVoidInterface> impl)
    : m_impl(impl)
{
}
void VoidInterfaceThreadSafeDecorator::funcVoid()
{
    return m_impl->funcVoid();
}

std::future<void> VoidInterfaceThreadSafeDecorator::funcVoidAsync( std::function<void(void)> callback)
{
    return m_impl->funcVoidAsync( callback);
}

IVoidInterfacePublisher& VoidInterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}