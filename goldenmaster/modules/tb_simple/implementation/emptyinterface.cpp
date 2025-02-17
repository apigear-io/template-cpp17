

#include "tb_simple/implementation/emptyinterface.h"
#include "tb_simple/generated/core/emptyinterface.publisher.h"
#include "tb_simple/generated/core/emptyinterface.data.h"

using namespace Test::TbSimple;

EmptyInterface::EmptyInterface()
    : m_publisher(std::make_unique<EmptyInterfacePublisher>())
{
}
EmptyInterface::~EmptyInterface()
{
}

IEmptyInterfacePublisher& EmptyInterface::_getPublisher() const
{
    return *m_publisher;
}
