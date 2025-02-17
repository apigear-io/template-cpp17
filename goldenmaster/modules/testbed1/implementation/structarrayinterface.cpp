

#include "testbed1/implementation/structarrayinterface.h"
#include "testbed1/generated/core/structarrayinterface.publisher.h"
#include "testbed1/generated/core/structarrayinterface.data.h"

using namespace Test::Testbed1;

StructArrayInterface::StructArrayInterface()
    : m_publisher(std::make_unique<StructArrayInterfacePublisher>())
{
}
StructArrayInterface::~StructArrayInterface()
{
}

void StructArrayInterface::setPropBool(const std::list<StructBool>& propBool)
{
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

const std::list<StructBool>& StructArrayInterface::getPropBool() const
{
    return m_data.m_propBool;
}

void StructArrayInterface::setPropInt(const std::list<StructInt>& propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

const std::list<StructInt>& StructArrayInterface::getPropInt() const
{
    return m_data.m_propInt;
}

void StructArrayInterface::setPropFloat(const std::list<StructFloat>& propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

const std::list<StructFloat>& StructArrayInterface::getPropFloat() const
{
    return m_data.m_propFloat;
}

void StructArrayInterface::setPropString(const std::list<StructString>& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::list<StructString>& StructArrayInterface::getPropString() const
{
    return m_data.m_propString;
}

std::list<StructBool> StructArrayInterface::funcBool(const std::list<StructBool>& paramBool)
{
    (void) paramBool; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<StructBool>();
}

std::future<std::list<StructBool>> StructArrayInterface::funcBoolAsync(const std::list<StructBool>& paramBool)
{
    return std::async(std::launch::async, [this,
                    paramBool]()
        {
            return funcBool(paramBool);
        }
    );
}

std::list<StructInt> StructArrayInterface::funcInt(const std::list<StructInt>& paramInt)
{
    (void) paramInt; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<StructInt>();
}

std::future<std::list<StructInt>> StructArrayInterface::funcIntAsync(const std::list<StructInt>& paramInt)
{
    return std::async(std::launch::async, [this,
                    paramInt]()
        {
            return funcInt(paramInt);
        }
    );
}

std::list<StructFloat> StructArrayInterface::funcFloat(const std::list<StructFloat>& paramFloat)
{
    (void) paramFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<StructFloat>();
}

std::future<std::list<StructFloat>> StructArrayInterface::funcFloatAsync(const std::list<StructFloat>& paramFloat)
{
    return std::async(std::launch::async, [this,
                    paramFloat]()
        {
            return funcFloat(paramFloat);
        }
    );
}

std::list<StructString> StructArrayInterface::funcString(const std::list<StructString>& paramString)
{
    (void) paramString; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<StructString>();
}

std::future<std::list<StructString>> StructArrayInterface::funcStringAsync(const std::list<StructString>& paramString)
{
    return std::async(std::launch::async, [this,
                    paramString]()
        {
            return funcString(paramString);
        }
    );
}

IStructArrayInterfacePublisher& StructArrayInterface::_getPublisher() const
{
    return *m_publisher;
}
