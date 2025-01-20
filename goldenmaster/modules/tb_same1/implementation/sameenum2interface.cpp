

#include "tb_same1/implementation/sameenum2interface.h"
#include "tb_same1/generated/core/sameenum2interface.publisher.h"
#include "tb_same1/generated/core/sameenum2interface.data.h"

using namespace Test::TbSame1;

SameEnum2Interface::SameEnum2Interface()
    : m_publisher(std::make_unique<SameEnum2InterfacePublisher>())
{
}
SameEnum2Interface::~SameEnum2Interface()
{
}

void SameEnum2Interface::setProp1(Enum1Enum prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

Enum1Enum SameEnum2Interface::getProp1() const
{
    return m_data.m_prop1;
}

void SameEnum2Interface::setProp2(Enum2Enum prop2)
{
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

Enum2Enum SameEnum2Interface::getProp2() const
{
    return m_data.m_prop2;
}

Enum1Enum SameEnum2Interface::func1(Enum1Enum param1)
{
    (void) param1; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return Enum1Enum::value1;
}

std::future<Enum1Enum> SameEnum2Interface::func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback)
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

Enum1Enum SameEnum2Interface::func2(Enum1Enum param1, Enum2Enum param2)
{
    (void) param1; // suppress the 'Unreferenced Formal Parameter' warning.
    (void) param2; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return Enum1Enum::value1;
}

std::future<Enum1Enum> SameEnum2Interface::func2Async(Enum1Enum param1, Enum2Enum param2, std::function<void(Enum1Enum)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    param1,
                    param2]()
        {auto result = func2(param1, param2);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

ISameEnum2InterfacePublisher& SameEnum2Interface::_getPublisher() const
{
    return *m_publisher;
}
