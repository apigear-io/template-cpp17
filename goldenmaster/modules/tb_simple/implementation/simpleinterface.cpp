

#include "tb_simple/implementation/simpleinterface.h"
#include "tb_simple/generated/core/simpleinterface.publisher.h"
#include "tb_simple/generated/core/simpleinterface.data.h"

using namespace Test::TbSimple;

SimpleInterface::SimpleInterface()
    : m_publisher(std::make_unique<SimpleInterfacePublisher>())
{
}
SimpleInterface::~SimpleInterface()
{
}

void SimpleInterface::setPropBool(bool propBool)
{
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

bool SimpleInterface::getPropBool() const
{
    return m_data.m_propBool;
}

void SimpleInterface::setPropInt(int propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

int SimpleInterface::getPropInt() const
{
    return m_data.m_propInt;
}

void SimpleInterface::setPropInt32(int32_t propInt32)
{
    if (m_data.m_propInt32 != propInt32) {
        m_data.m_propInt32 = propInt32;
        m_publisher->publishPropInt32Changed(propInt32);
    }
}

int32_t SimpleInterface::getPropInt32() const
{
    return m_data.m_propInt32;
}

void SimpleInterface::setPropInt64(int64_t propInt64)
{
    if (m_data.m_propInt64 != propInt64) {
        m_data.m_propInt64 = propInt64;
        m_publisher->publishPropInt64Changed(propInt64);
    }
}

int64_t SimpleInterface::getPropInt64() const
{
    return m_data.m_propInt64;
}

void SimpleInterface::setPropFloat(float propFloat)
{
    // consider using fuzzy compare, check library ApiGear::Utilities::fuzzyCompare
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

float SimpleInterface::getPropFloat() const
{
    return m_data.m_propFloat;
}

void SimpleInterface::setPropFloat32(float propFloat32)
{
    // consider using fuzzy compare, check library ApiGear::Utilities::fuzzyCompare
    if (m_data.m_propFloat32 != propFloat32) {
        m_data.m_propFloat32 = propFloat32;
        m_publisher->publishPropFloat32Changed(propFloat32);
    }
}

float SimpleInterface::getPropFloat32() const
{
    return m_data.m_propFloat32;
}

void SimpleInterface::setPropFloat64(double propFloat64)
{
    // consider using fuzzy compare, check library ApiGear::Utilities::fuzzyCompare
    if (m_data.m_propFloat64 != propFloat64) {
        m_data.m_propFloat64 = propFloat64;
        m_publisher->publishPropFloat64Changed(propFloat64);
    }
}

double SimpleInterface::getPropFloat64() const
{
    return m_data.m_propFloat64;
}

void SimpleInterface::setPropString(const std::string& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::string& SimpleInterface::getPropString() const
{
    return m_data.m_propString;
}

void SimpleInterface::funcNoReturnValue(bool paramBool)
{
    (void) paramBool; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
}

std::future<void> SimpleInterface::funcNoReturnValueAsync(bool paramBool)
{
    return std::async(std::launch::async, [this,
                    paramBool]()
        {
            return funcNoReturnValue(paramBool);
        }
    );
}

bool SimpleInterface::funcBool(bool paramBool)
{
    (void) paramBool; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return false;
}

std::future<bool> SimpleInterface::funcBoolAsync(bool paramBool)
{
    return std::async(std::launch::async, [this,
                    paramBool]()
        {
            return funcBool(paramBool);
        }
    );
}

int SimpleInterface::funcInt(int paramInt)
{
    (void) paramInt; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0;
}

std::future<int> SimpleInterface::funcIntAsync(int paramInt)
{
    return std::async(std::launch::async, [this,
                    paramInt]()
        {
            return funcInt(paramInt);
        }
    );
}

int32_t SimpleInterface::funcInt32(int32_t paramInt32)
{
    (void) paramInt32; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0;
}

std::future<int32_t> SimpleInterface::funcInt32Async(int32_t paramInt32)
{
    return std::async(std::launch::async, [this,
                    paramInt32]()
        {
            return funcInt32(paramInt32);
        }
    );
}

int64_t SimpleInterface::funcInt64(int64_t paramInt64)
{
    (void) paramInt64; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0LL;
}

std::future<int64_t> SimpleInterface::funcInt64Async(int64_t paramInt64)
{
    return std::async(std::launch::async, [this,
                    paramInt64]()
        {
            return funcInt64(paramInt64);
        }
    );
}

float SimpleInterface::funcFloat(float paramFloat)
{
    (void) paramFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0.0f;
}

std::future<float> SimpleInterface::funcFloatAsync(float paramFloat)
{
    return std::async(std::launch::async, [this,
                    paramFloat]()
        {
            return funcFloat(paramFloat);
        }
    );
}

float SimpleInterface::funcFloat32(float paramFloat32)
{
    (void) paramFloat32; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0.0f;
}

std::future<float> SimpleInterface::funcFloat32Async(float paramFloat32)
{
    return std::async(std::launch::async, [this,
                    paramFloat32]()
        {
            return funcFloat32(paramFloat32);
        }
    );
}

double SimpleInterface::funcFloat64(double paramFloat)
{
    (void) paramFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0.0;
}

std::future<double> SimpleInterface::funcFloat64Async(double paramFloat)
{
    return std::async(std::launch::async, [this,
                    paramFloat]()
        {
            return funcFloat64(paramFloat);
        }
    );
}

std::string SimpleInterface::funcString(const std::string& paramString)
{
    (void) paramString; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::string();
}

std::future<std::string> SimpleInterface::funcStringAsync(const std::string& paramString)
{
    return std::async(std::launch::async, [this,
                    paramString]()
        {
            return funcString(paramString);
        }
    );
}

ISimpleInterfacePublisher& SimpleInterface::_getPublisher() const
{
    return *m_publisher;
}
