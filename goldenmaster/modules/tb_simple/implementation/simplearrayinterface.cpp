

#include "tb_simple/implementation/simplearrayinterface.h"
#include "tb_simple/generated/core/simplearrayinterface.publisher.h"
#include "tb_simple/generated/core/simplearrayinterface.data.h"

using namespace Test::TbSimple;

SimpleArrayInterface::SimpleArrayInterface()
    : m_publisher(std::make_unique<SimpleArrayInterfacePublisher>())
{
}
SimpleArrayInterface::~SimpleArrayInterface()
{
}

void SimpleArrayInterface::setPropBool(const std::list<bool>& propBool)
{
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

const std::list<bool>& SimpleArrayInterface::getPropBool() const
{
    return m_data.m_propBool;
}

void SimpleArrayInterface::setPropInt(const std::list<int>& propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

const std::list<int>& SimpleArrayInterface::getPropInt() const
{
    return m_data.m_propInt;
}

void SimpleArrayInterface::setPropInt32(const std::list<int32_t>& propInt32)
{
    if (m_data.m_propInt32 != propInt32) {
        m_data.m_propInt32 = propInt32;
        m_publisher->publishPropInt32Changed(propInt32);
    }
}

const std::list<int32_t>& SimpleArrayInterface::getPropInt32() const
{
    return m_data.m_propInt32;
}

void SimpleArrayInterface::setPropInt64(const std::list<int64_t>& propInt64)
{
    if (m_data.m_propInt64 != propInt64) {
        m_data.m_propInt64 = propInt64;
        m_publisher->publishPropInt64Changed(propInt64);
    }
}

const std::list<int64_t>& SimpleArrayInterface::getPropInt64() const
{
    return m_data.m_propInt64;
}

void SimpleArrayInterface::setPropFloat(const std::list<float>& propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

const std::list<float>& SimpleArrayInterface::getPropFloat() const
{
    return m_data.m_propFloat;
}

void SimpleArrayInterface::setPropFloat32(const std::list<float>& propFloat32)
{
    if (m_data.m_propFloat32 != propFloat32) {
        m_data.m_propFloat32 = propFloat32;
        m_publisher->publishPropFloat32Changed(propFloat32);
    }
}

const std::list<float>& SimpleArrayInterface::getPropFloat32() const
{
    return m_data.m_propFloat32;
}

void SimpleArrayInterface::setPropFloat64(const std::list<double>& propFloat64)
{
    if (m_data.m_propFloat64 != propFloat64) {
        m_data.m_propFloat64 = propFloat64;
        m_publisher->publishPropFloat64Changed(propFloat64);
    }
}

const std::list<double>& SimpleArrayInterface::getPropFloat64() const
{
    return m_data.m_propFloat64;
}

void SimpleArrayInterface::setPropString(const std::list<std::string>& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::list<std::string>& SimpleArrayInterface::getPropString() const
{
    return m_data.m_propString;
}

void SimpleArrayInterface::setPropReadOnlyString(const std::string& propReadOnlyString)
{
    if (m_data.m_propReadOnlyString != propReadOnlyString) {
        m_data.m_propReadOnlyString = propReadOnlyString;
        m_publisher->publishPropReadOnlyStringChanged(propReadOnlyString);
    }
}

const std::string& SimpleArrayInterface::getPropReadOnlyString() const
{
    return m_data.m_propReadOnlyString;
}

std::list<bool> SimpleArrayInterface::funcBool(const std::list<bool>& paramBool)
{
    (void) paramBool; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<bool>();
}

std::future<std::list<bool>> SimpleArrayInterface::funcBoolAsync(const std::list<bool>& paramBool, std::function<void(std::list<bool>)> callback)
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

std::list<int> SimpleArrayInterface::funcInt(const std::list<int>& paramInt)
{
    (void) paramInt; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<int>();
}

std::future<std::list<int>> SimpleArrayInterface::funcIntAsync(const std::list<int>& paramInt, std::function<void(std::list<int>)> callback)
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

std::list<int32_t> SimpleArrayInterface::funcInt32(const std::list<int32_t>& paramInt32)
{
    (void) paramInt32; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<int32_t>();
}

std::future<std::list<int32_t>> SimpleArrayInterface::funcInt32Async(const std::list<int32_t>& paramInt32, std::function<void(std::list<int32_t>)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramInt32]()
        {auto result = funcInt32(paramInt32);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

std::list<int64_t> SimpleArrayInterface::funcInt64(const std::list<int64_t>& paramInt64)
{
    (void) paramInt64; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<int64_t>();
}

std::future<std::list<int64_t>> SimpleArrayInterface::funcInt64Async(const std::list<int64_t>& paramInt64, std::function<void(std::list<int64_t>)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramInt64]()
        {auto result = funcInt64(paramInt64);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

std::list<float> SimpleArrayInterface::funcFloat(const std::list<float>& paramFloat)
{
    (void) paramFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<float>();
}

std::future<std::list<float>> SimpleArrayInterface::funcFloatAsync(const std::list<float>& paramFloat, std::function<void(std::list<float>)> callback)
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

std::list<float> SimpleArrayInterface::funcFloat32(const std::list<float>& paramFloat32)
{
    (void) paramFloat32; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<float>();
}

std::future<std::list<float>> SimpleArrayInterface::funcFloat32Async(const std::list<float>& paramFloat32, std::function<void(std::list<float>)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramFloat32]()
        {auto result = funcFloat32(paramFloat32);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

std::list<double> SimpleArrayInterface::funcFloat64(const std::list<double>& paramFloat)
{
    (void) paramFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<double>();
}

std::future<std::list<double>> SimpleArrayInterface::funcFloat64Async(const std::list<double>& paramFloat, std::function<void(std::list<double>)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramFloat]()
        {auto result = funcFloat64(paramFloat);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

std::list<std::string> SimpleArrayInterface::funcString(const std::list<std::string>& paramString)
{
    (void) paramString; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::list<std::string>();
}

std::future<std::list<std::string>> SimpleArrayInterface::funcStringAsync(const std::list<std::string>& paramString, std::function<void(std::list<std::string>)> callback)
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

ISimpleArrayInterfacePublisher& SimpleArrayInterface::_getPublisher() const
{
    return *m_publisher;
}
