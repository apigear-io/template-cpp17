

#include "tb_same1/implementation/samestruct2interface.h"
#include "tb_same1/generated/core/samestruct2interface.publisher.h"
#include "tb_same1/generated/core/samestruct2interface.data.h"

using namespace Test::TbSame1;

SameStruct2Interface::SameStruct2Interface()
    : m_publisher(std::make_unique<SameStruct2InterfacePublisher>())
{
}
SameStruct2Interface::~SameStruct2Interface()
{
}

void SameStruct2Interface::setProp1(const Struct2& prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

const Struct2& SameStruct2Interface::getProp1() const
{
    return m_data.m_prop1;
}

void SameStruct2Interface::setProp2(const Struct2& prop2)
{
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

const Struct2& SameStruct2Interface::getProp2() const
{
    return m_data.m_prop2;
}

Struct1 SameStruct2Interface::func1(const Struct1& param1)
{
    (void) param1; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return Struct1();
}

std::future<Struct1> SameStruct2Interface::func1Async(const Struct1& param1, std::function<void(Struct1)> callback)
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

Struct1 SameStruct2Interface::func2(const Struct1& param1, const Struct2& param2)
{
    (void) param1; // suppress the 'Unreferenced Formal Parameter' warning.
    (void) param2; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return Struct1();
}

std::future<Struct1> SameStruct2Interface::func2Async(const Struct1& param1, const Struct2& param2, std::function<void(Struct1)> callback)
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

ISameStruct2InterfacePublisher& SameStruct2Interface::_getPublisher() const
{
    return *m_publisher;
}
