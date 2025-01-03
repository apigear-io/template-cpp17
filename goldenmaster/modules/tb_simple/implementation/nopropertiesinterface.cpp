

#include "tb_simple/implementation/nopropertiesinterface.h"
#include "tb_simple/generated/core/nopropertiesinterface.publisher.h"
#include "tb_simple/generated/core/nopropertiesinterface.data.h"
#include "apigear/utilities/fuzzy_compare.h"

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

std::future<void> NoPropertiesInterface::funcVoidAsync()
{
    return std::async(std::launch::async, [this]()
        {
            return funcVoid();
        }
    );
}

bool NoPropertiesInterface::funcBool(bool paramBool)
{
    (void) paramBool; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return false;
}

std::future<bool> NoPropertiesInterface::funcBoolAsync(bool paramBool)
{
    return std::async(std::launch::async, [this,
                    paramBool]()
        {
            return funcBool(paramBool);
        }
    );
}

INoPropertiesInterfacePublisher& NoPropertiesInterface::_getPublisher() const
{
    return *m_publisher;
}
