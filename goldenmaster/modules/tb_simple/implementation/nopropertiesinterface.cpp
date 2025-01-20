

#include "tb_simple/implementation/nopropertiesinterface.h"
#include "tb_simple/generated/core/nopropertiesinterface.publisher.h"
#include "tb_simple/generated/core/nopropertiesinterface.data.h"

using namespace Test::TbSimple;

NoPropertiesInterface::NoPropertiesInterface()
    : m_publisher(std::make_unique<NoPropertiesInterfacePublisher>())
{
}
NoPropertiesInterface::~NoPropertiesInterface()
{
}

void NoPropertiesInterface::funcVoid()
{
    // do business logic here
}

std::future<void> NoPropertiesInterface::funcVoidAsync( std::function<void(void)> callback)
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

bool NoPropertiesInterface::funcBool(bool paramBool)
{
    (void) paramBool; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return false;
}

std::future<bool> NoPropertiesInterface::funcBoolAsync(bool paramBool, std::function<void(bool)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramBool]()
        {auto result = funcBool(paramBool);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

INoPropertiesInterfacePublisher& NoPropertiesInterface::_getPublisher() const
{
    return *m_publisher;
}
