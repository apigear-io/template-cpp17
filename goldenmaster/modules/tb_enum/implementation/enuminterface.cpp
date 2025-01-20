

#include "tb_enum/implementation/enuminterface.h"
#include "tb_enum/generated/core/enuminterface.publisher.h"
#include "tb_enum/generated/core/enuminterface.data.h"

using namespace Test::TbEnum;

EnumInterface::EnumInterface()
    : m_publisher(std::make_unique<EnumInterfacePublisher>())
{
}
EnumInterface::~EnumInterface()
{
}

void EnumInterface::setProp0(Enum0Enum prop0)
{
    if (m_data.m_prop0 != prop0) {
        m_data.m_prop0 = prop0;
        m_publisher->publishProp0Changed(prop0);
    }
}

Enum0Enum EnumInterface::getProp0() const
{
    return m_data.m_prop0;
}

void EnumInterface::setProp1(Enum1Enum prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

Enum1Enum EnumInterface::getProp1() const
{
    return m_data.m_prop1;
}

void EnumInterface::setProp2(Enum2Enum prop2)
{
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

Enum2Enum EnumInterface::getProp2() const
{
    return m_data.m_prop2;
}

void EnumInterface::setProp3(Enum3Enum prop3)
{
    if (m_data.m_prop3 != prop3) {
        m_data.m_prop3 = prop3;
        m_publisher->publishProp3Changed(prop3);
    }
}

Enum3Enum EnumInterface::getProp3() const
{
    return m_data.m_prop3;
}

Enum0Enum EnumInterface::func0(Enum0Enum param0)
{
    (void) param0; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return Enum0Enum::value0;
}

std::future<Enum0Enum> EnumInterface::func0Async(Enum0Enum param0, std::function<void(Enum0Enum)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    param0]()
        {auto result = func0(param0);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

Enum1Enum EnumInterface::func1(Enum1Enum param1)
{
    (void) param1; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return Enum1Enum::value1;
}

std::future<Enum1Enum> EnumInterface::func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback)
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

Enum2Enum EnumInterface::func2(Enum2Enum param2)
{
    (void) param2; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return Enum2Enum::value2;
}

std::future<Enum2Enum> EnumInterface::func2Async(Enum2Enum param2, std::function<void(Enum2Enum)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    param2]()
        {auto result = func2(param2);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

Enum3Enum EnumInterface::func3(Enum3Enum param3)
{
    (void) param3; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return Enum3Enum::value3;
}

std::future<Enum3Enum> EnumInterface::func3Async(Enum3Enum param3, std::function<void(Enum3Enum)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    param3]()
        {auto result = func3(param3);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

IEnumInterfacePublisher& EnumInterface::_getPublisher() const
{
    return *m_publisher;
}
