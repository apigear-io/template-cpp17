

#include "tb_same2/implementation/samestruct1interface.h"
#include "tb_same2/generated/core/samestruct1interface.publisher.h"
#include "tb_same2/generated/core/samestruct1interface.data.h"

using namespace Test::TbSame2;

SameStruct1Interface::SameStruct1Interface()
    : m_publisher(std::make_unique<SameStruct1InterfacePublisher>())
{
}
SameStruct1Interface::~SameStruct1Interface()
{
}

void SameStruct1Interface::setProp1(const Struct1& prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

const Struct1& SameStruct1Interface::getProp1() const
{
    return m_data.m_prop1;
}

Struct1 SameStruct1Interface::func1(const Struct1& param1)
{
    (void) param1; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return Struct1();
}

std::future<Struct1> SameStruct1Interface::func1Async(const Struct1& param1, std::function<void(Struct1)> callback)
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

ISameStruct1InterfacePublisher& SameStruct1Interface::_getPublisher() const
{
    return *m_publisher;
}
