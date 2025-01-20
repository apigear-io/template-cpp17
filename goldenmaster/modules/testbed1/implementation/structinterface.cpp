

#include "testbed1/implementation/structinterface.h"
#include "testbed1/generated/core/structinterface.publisher.h"
#include "testbed1/generated/core/structinterface.data.h"

using namespace Test::Testbed1;

StructInterface::StructInterface()
    : m_publisher(std::make_unique<StructInterfacePublisher>())
{
}
StructInterface::~StructInterface()
{
}

void StructInterface::setPropBool(const StructBool& propBool)
{
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

const StructBool& StructInterface::getPropBool() const
{
    return m_data.m_propBool;
}

void StructInterface::setPropInt(const StructInt& propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

const StructInt& StructInterface::getPropInt() const
{
    return m_data.m_propInt;
}

void StructInterface::setPropFloat(const StructFloat& propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

const StructFloat& StructInterface::getPropFloat() const
{
    return m_data.m_propFloat;
}

void StructInterface::setPropString(const StructString& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const StructString& StructInterface::getPropString() const
{
    return m_data.m_propString;
}

StructBool StructInterface::funcBool(const StructBool& paramBool)
{
    (void) paramBool; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return StructBool();
}

std::future<StructBool> StructInterface::funcBoolAsync(const StructBool& paramBool, std::function<void(StructBool)> callback)
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

StructBool StructInterface::funcInt(const StructInt& paramInt)
{
    (void) paramInt; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return StructBool();
}

std::future<StructBool> StructInterface::funcIntAsync(const StructInt& paramInt, std::function<void(StructBool)> callback)
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

StructFloat StructInterface::funcFloat(const StructFloat& paramFloat)
{
    (void) paramFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return StructFloat();
}

std::future<StructFloat> StructInterface::funcFloatAsync(const StructFloat& paramFloat, std::function<void(StructFloat)> callback)
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

StructString StructInterface::funcString(const StructString& paramString)
{
    (void) paramString; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return StructString();
}

std::future<StructString> StructInterface::funcStringAsync(const StructString& paramString, std::function<void(StructString)> callback)
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

IStructInterfacePublisher& StructInterface::_getPublisher() const
{
    return *m_publisher;
}
