

#include "tb_simple/generated/core/simpleinterface.threadsafedecorator.h"

using namespace Test::TbSimple;
SimpleInterfaceThreadSafeDecorator::SimpleInterfaceThreadSafeDecorator(std::shared_ptr<ISimpleInterface> impl)
    : m_impl(impl)
{
}
void SimpleInterfaceThreadSafeDecorator::funcNoReturnValue(bool paramBool)
{
    return m_impl->funcNoReturnValue(paramBool);
}

std::future<void> SimpleInterfaceThreadSafeDecorator::funcNoReturnValueAsync(bool paramBool, std::function<void(void)> callback)
{
    return m_impl->funcNoReturnValueAsync(paramBool, callback);
}
bool SimpleInterfaceThreadSafeDecorator::funcBool(bool paramBool)
{
    return m_impl->funcBool(paramBool);
}

std::future<bool> SimpleInterfaceThreadSafeDecorator::funcBoolAsync(bool paramBool, std::function<void(bool)> callback)
{
    return m_impl->funcBoolAsync(paramBool, callback);
}
int SimpleInterfaceThreadSafeDecorator::funcInt(int paramInt)
{
    return m_impl->funcInt(paramInt);
}

std::future<int> SimpleInterfaceThreadSafeDecorator::funcIntAsync(int paramInt, std::function<void(int)> callback)
{
    return m_impl->funcIntAsync(paramInt, callback);
}
int32_t SimpleInterfaceThreadSafeDecorator::funcInt32(int32_t paramInt32)
{
    return m_impl->funcInt32(paramInt32);
}

std::future<int32_t> SimpleInterfaceThreadSafeDecorator::funcInt32Async(int32_t paramInt32, std::function<void(int32_t)> callback)
{
    return m_impl->funcInt32Async(paramInt32, callback);
}
int64_t SimpleInterfaceThreadSafeDecorator::funcInt64(int64_t paramInt64)
{
    return m_impl->funcInt64(paramInt64);
}

std::future<int64_t> SimpleInterfaceThreadSafeDecorator::funcInt64Async(int64_t paramInt64, std::function<void(int64_t)> callback)
{
    return m_impl->funcInt64Async(paramInt64, callback);
}
float SimpleInterfaceThreadSafeDecorator::funcFloat(float paramFloat)
{
    return m_impl->funcFloat(paramFloat);
}

std::future<float> SimpleInterfaceThreadSafeDecorator::funcFloatAsync(float paramFloat, std::function<void(float)> callback)
{
    return m_impl->funcFloatAsync(paramFloat, callback);
}
float SimpleInterfaceThreadSafeDecorator::funcFloat32(float paramFloat32)
{
    return m_impl->funcFloat32(paramFloat32);
}

std::future<float> SimpleInterfaceThreadSafeDecorator::funcFloat32Async(float paramFloat32, std::function<void(float)> callback)
{
    return m_impl->funcFloat32Async(paramFloat32, callback);
}
double SimpleInterfaceThreadSafeDecorator::funcFloat64(double paramFloat)
{
    return m_impl->funcFloat64(paramFloat);
}

std::future<double> SimpleInterfaceThreadSafeDecorator::funcFloat64Async(double paramFloat, std::function<void(double)> callback)
{
    return m_impl->funcFloat64Async(paramFloat, callback);
}
std::string SimpleInterfaceThreadSafeDecorator::funcString(const std::string& paramString)
{
    return m_impl->funcString(paramString);
}

std::future<std::string> SimpleInterfaceThreadSafeDecorator::funcStringAsync(const std::string& paramString, std::function<void(std::string)> callback)
{
    return m_impl->funcStringAsync(paramString, callback);
}
void SimpleInterfaceThreadSafeDecorator::setPropBool(bool propBool)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propBoolMutex);
    m_impl->setPropBool(propBool);
}

bool SimpleInterfaceThreadSafeDecorator::getPropBool() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propBoolMutex);
    return m_impl->getPropBool();
}
void SimpleInterfaceThreadSafeDecorator::setPropInt(int propInt)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    m_impl->setPropInt(propInt);
}

int SimpleInterfaceThreadSafeDecorator::getPropInt() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    return m_impl->getPropInt();
}
void SimpleInterfaceThreadSafeDecorator::setPropInt32(int32_t propInt32)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propInt32Mutex);
    m_impl->setPropInt32(propInt32);
}

int32_t SimpleInterfaceThreadSafeDecorator::getPropInt32() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propInt32Mutex);
    return m_impl->getPropInt32();
}
void SimpleInterfaceThreadSafeDecorator::setPropInt64(int64_t propInt64)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propInt64Mutex);
    m_impl->setPropInt64(propInt64);
}

int64_t SimpleInterfaceThreadSafeDecorator::getPropInt64() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propInt64Mutex);
    return m_impl->getPropInt64();
}
void SimpleInterfaceThreadSafeDecorator::setPropFloat(float propFloat)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    m_impl->setPropFloat(propFloat);
}

float SimpleInterfaceThreadSafeDecorator::getPropFloat() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    return m_impl->getPropFloat();
}
void SimpleInterfaceThreadSafeDecorator::setPropFloat32(float propFloat32)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloat32Mutex);
    m_impl->setPropFloat32(propFloat32);
}

float SimpleInterfaceThreadSafeDecorator::getPropFloat32() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloat32Mutex);
    return m_impl->getPropFloat32();
}
void SimpleInterfaceThreadSafeDecorator::setPropFloat64(double propFloat64)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloat64Mutex);
    m_impl->setPropFloat64(propFloat64);
}

double SimpleInterfaceThreadSafeDecorator::getPropFloat64() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloat64Mutex);
    return m_impl->getPropFloat64();
}
void SimpleInterfaceThreadSafeDecorator::setPropString(const std::string& propString)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    m_impl->setPropString(propString);
}

const std::string& SimpleInterfaceThreadSafeDecorator::getPropString() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    return m_impl->getPropString();
}

ISimpleInterfacePublisher& SimpleInterfaceThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}