

#include "tb_simple/implementation/voidinterface.h"
#include "tb_simple/generated/core/voidinterface.publisher.h"
#include "tb_simple/generated/core/voidinterface.data.h"

using namespace Test::TbSimple;

VoidInterface::VoidInterface()
    : m_publisher(std::make_unique<VoidInterfacePublisher>())
{
}
VoidInterface::~VoidInterface()
{
}

void VoidInterface::funcVoid()
{
    // do business logic here
}

std::future<void> VoidInterface::funcVoidAsync( std::function<void(void)> callback)
{
    return std::async(std::launch::async, [this, callback]()
        {funcVoid();
            if (callback)
            {
                callback();
            }
        }
    );
}

IVoidInterfacePublisher& VoidInterface::_getPublisher() const
{
    return *m_publisher;
}
