

#include "tb_simple/generated/core/emptyinterface.threadsafedecorator.h"

using namespace Test::TbSimple;
EmptyInterfaceThreadSafeDecorator::EmptyInterfaceThreadSafeDecorator(std::shared_ptr<IEmptyInterface> impl)
    : m_impl(impl)
{
}

IEmptyInterfacePublisher& EmptyInterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}