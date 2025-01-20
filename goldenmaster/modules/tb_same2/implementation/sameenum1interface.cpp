

#include "tb_same2/implementation/sameenum1interface.h"
#include "tb_same2/generated/core/sameenum1interface.publisher.h"
#include "tb_same2/generated/core/sameenum1interface.data.h"

using namespace Test::TbSame2;

SameEnum1Interface::SameEnum1Interface()
    : m_publisher(std::make_unique<SameEnum1InterfacePublisher>())
{
}
SameEnum1Interface::~SameEnum1Interface()
{
}

void SameEnum1Interface::setProp1(Enum1Enum prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

Enum1Enum SameEnum1Interface::getProp1() const
{
    return m_data.m_prop1;
}

Enum1Enum SameEnum1Interface::func1(Enum1Enum param1)
{
    (void) param1; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return Enum1Enum::value1;
}

std::future<Enum1Enum> SameEnum1Interface::func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    param1]()
        {auto result = func1(param1);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

ISameEnum1InterfacePublisher& SameEnum1Interface::_getPublisher() const
{
    return *m_publisher;
}
