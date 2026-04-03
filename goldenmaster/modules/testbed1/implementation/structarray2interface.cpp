

#include "testbed1/implementation/structarray2interface.h"
#include "testbed1/generated/core/structarray2interface.publisher.h"
#include "testbed1/generated/core/structarray2interface.data.h"

using namespace Test::Testbed1;

StructArray2Interface::StructArray2Interface()
    : m_publisher(std::make_unique<StructArray2InterfacePublisher>())
{
}
StructArray2Interface::~StructArray2Interface()
{
}

void StructArray2Interface::setPropBool(const StructBoolWithArray& propBool)
{
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

const StructBoolWithArray& StructArray2Interface::getPropBool() const
{
    return m_data.m_propBool;
}

void StructArray2Interface::setPropInt(const StructIntWithArray& propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

const StructIntWithArray& StructArray2Interface::getPropInt() const
{
    return m_data.m_propInt;
}

void StructArray2Interface::setPropFloat(const StructFloatWithArray& propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

const StructFloatWithArray& StructArray2Interface::getPropFloat() const
{
    return m_data.m_propFloat;
}

void StructArray2Interface::setPropString(const StructStringWithArray& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const StructStringWithArray& StructArray2Interface::getPropString() const
{
    return m_data.m_propString;
}

void StructArray2Interface::setPropEnum(const StructEnumWithArray& propEnum)
{
    if (m_data.m_propEnum != propEnum) {
        m_data.m_propEnum = propEnum;
        m_publisher->publishPropEnumChanged(propEnum);
    }
}

const StructEnumWithArray& StructArray2Interface::getPropEnum() const
{
    return m_data.m_propEnum;
}

std::list<StructBool> StructArray2Interface::funcBool(const StructBoolWithArray& paramBool)
{
    (void) paramBool; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<StructBool>();
}

std::future<std::list<StructBool>> StructArray2Interface::funcBoolAsync(const StructBoolWithArray& paramBool, std::function<void(std::list<StructBool>)> callback)
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

std::list<StructInt> StructArray2Interface::funcInt(const StructIntWithArray& paramInt)
{
    (void) paramInt; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<StructInt>();
}

std::future<std::list<StructInt>> StructArray2Interface::funcIntAsync(const StructIntWithArray& paramInt, std::function<void(std::list<StructInt>)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramInt]()
        {auto result = funcInt(paramInt);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

std::list<StructFloat> StructArray2Interface::funcFloat(const StructFloatWithArray& paramFloat)
{
    (void) paramFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<StructFloat>();
}

std::future<std::list<StructFloat>> StructArray2Interface::funcFloatAsync(const StructFloatWithArray& paramFloat, std::function<void(std::list<StructFloat>)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramFloat]()
        {auto result = funcFloat(paramFloat);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

std::list<StructString> StructArray2Interface::funcString(const StructStringWithArray& paramString)
{
    (void) paramString; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<StructString>();
}

std::future<std::list<StructString>> StructArray2Interface::funcStringAsync(const StructStringWithArray& paramString, std::function<void(std::list<StructString>)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramString]()
        {auto result = funcString(paramString);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

std::list<Enum0Enum> StructArray2Interface::funcEnum(const StructEnumWithArray& paramEnum)
{
    (void) paramEnum; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<Enum0Enum>();
}

std::future<std::list<Enum0Enum>> StructArray2Interface::funcEnumAsync(const StructEnumWithArray& paramEnum, std::function<void(std::list<Enum0Enum>)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramEnum]()
        {auto result = funcEnum(paramEnum);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

IStructArray2InterfacePublisher& StructArray2Interface::_getPublisher() const
{
    return *m_publisher;
}
