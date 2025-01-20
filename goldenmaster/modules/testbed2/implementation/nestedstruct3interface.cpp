

#include "testbed2/implementation/nestedstruct3interface.h"
#include "testbed2/generated/core/nestedstruct3interface.publisher.h"
#include "testbed2/generated/core/nestedstruct3interface.data.h"

using namespace Test::Testbed2;

NestedStruct3Interface::NestedStruct3Interface()
    : m_publisher(std::make_unique<NestedStruct3InterfacePublisher>())
{
}
NestedStruct3Interface::~NestedStruct3Interface()
{
}

void NestedStruct3Interface::setProp1(const NestedStruct1& prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

const NestedStruct1& NestedStruct3Interface::getProp1() const
{
    return m_data.m_prop1;
}

void NestedStruct3Interface::setProp2(const NestedStruct2& prop2)
{
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

const NestedStruct2& NestedStruct3Interface::getProp2() const
{
    return m_data.m_prop2;
}

void NestedStruct3Interface::setProp3(const NestedStruct3& prop3)
{
    if (m_data.m_prop3 != prop3) {
        m_data.m_prop3 = prop3;
        m_publisher->publishProp3Changed(prop3);
    }
}

const NestedStruct3& NestedStruct3Interface::getProp3() const
{
    return m_data.m_prop3;
}

NestedStruct1 NestedStruct3Interface::func1(const NestedStruct1& param1)
{
    (void) param1; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return NestedStruct1();
}

std::future<NestedStruct1> NestedStruct3Interface::func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback)
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

NestedStruct1 NestedStruct3Interface::func2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    (void) param1; // suppress the 'Unreferenced Formal Parameter' warning.
    (void) param2; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return NestedStruct1();
}

std::future<NestedStruct1> NestedStruct3Interface::func2Async(const NestedStruct1& param1, const NestedStruct2& param2, std::function<void(NestedStruct1)> callback)
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

NestedStruct1 NestedStruct3Interface::func3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3)
{
    (void) param1; // suppress the 'Unreferenced Formal Parameter' warning.
    (void) param2; // suppress the 'Unreferenced Formal Parameter' warning.
    (void) param3; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return NestedStruct1();
}

std::future<NestedStruct1> NestedStruct3Interface::func3Async(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3, std::function<void(NestedStruct1)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    param1,
                    param2,
                    param3]()
        {auto result = func3(param1, param2, param3);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

INestedStruct3InterfacePublisher& NestedStruct3Interface::_getPublisher() const
{
    return *m_publisher;
}
