
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace TbSimple {

/** 
* @brief The SimpleInterfaceThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the SimpleInterface interface.
* @see SimpleInterface
*
\code{.cpp}
using namespace Test::TbSimple;

std::unique_ptr<ISimpleInterface> testSimpleInterface = std::make_unique<SimpleInterfaceThreadSafeDecorator>(std::make_shared<SimpleInterface>());

// Thread safe access
auto propBool = testSimpleInterface->getPropBool();
testSimpleInterface->setPropBool(false);
auto propInt = testSimpleInterface->getPropInt();
testSimpleInterface->setPropInt(0);
auto propInt32 = testSimpleInterface->getPropInt32();
testSimpleInterface->setPropInt32(0);
auto propInt64 = testSimpleInterface->getPropInt64();
testSimpleInterface->setPropInt64(0LL);
auto propFloat = testSimpleInterface->getPropFloat();
testSimpleInterface->setPropFloat(0.0f);
auto propFloat32 = testSimpleInterface->getPropFloat32();
testSimpleInterface->setPropFloat32(0.0f);
auto propFloat64 = testSimpleInterface->getPropFloat64();
testSimpleInterface->setPropFloat64(0.0);
auto propString = testSimpleInterface->getPropString();
testSimpleInterface->setPropString(std::string());
\endcode
*/
class TEST_TB_SIMPLE_EXPORT SimpleInterfaceThreadSafeDecorator : public ISimpleInterface
{
public:
    /** 
    * ctor
    * @param impl The SimpleInterface object to make thread safe.
    */
    explicit SimpleInterfaceThreadSafeDecorator(std::shared_ptr<ISimpleInterface> impl);

    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    void funcNoReturnValue(bool paramBool) override;
    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<void> funcNoReturnValueAsync(bool paramBool, std::function<void(void)> callback = nullptr) override;

    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    bool funcBool(bool paramBool) override;
    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<bool> funcBoolAsync(bool paramBool, std::function<void(bool)> callback = nullptr) override;

    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    int funcInt(int paramInt) override;
    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<int> funcIntAsync(int paramInt, std::function<void(int)> callback = nullptr) override;

    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    int32_t funcInt32(int32_t paramInt32) override;
    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<int32_t> funcInt32Async(int32_t paramInt32, std::function<void(int32_t)> callback = nullptr) override;

    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    int64_t funcInt64(int64_t paramInt64) override;
    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<int64_t> funcInt64Async(int64_t paramInt64, std::function<void(int64_t)> callback = nullptr) override;

    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    float funcFloat(float paramFloat) override;
    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<float> funcFloatAsync(float paramFloat, std::function<void(float)> callback = nullptr) override;

    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    float funcFloat32(float paramFloat32) override;
    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<float> funcFloat32Async(float paramFloat32, std::function<void(float)> callback = nullptr) override;

    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    double funcFloat64(double paramFloat) override;
    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<double> funcFloat64Async(double paramFloat, std::function<void(double)> callback = nullptr) override;

    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::string funcString(const std::string& paramString) override;
    /** 
    * Forwards call to SimpleInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<std::string> funcStringAsync(const std::string& paramString, std::function<void(std::string)> callback = nullptr) override;

    /** Guards and forwards call to SimpleInterface implementation. */
    void setPropBool(bool propBool) override;
    /** Guards and forwards call to SimpleInterface implementation. */
    bool getPropBool() const override;

    /** Guards and forwards call to SimpleInterface implementation. */
    void setPropInt(int propInt) override;
    /** Guards and forwards call to SimpleInterface implementation. */
    int getPropInt() const override;

    /** Guards and forwards call to SimpleInterface implementation. */
    void setPropInt32(int32_t propInt32) override;
    /** Guards and forwards call to SimpleInterface implementation. */
    int32_t getPropInt32() const override;

    /** Guards and forwards call to SimpleInterface implementation. */
    void setPropInt64(int64_t propInt64) override;
    /** Guards and forwards call to SimpleInterface implementation. */
    int64_t getPropInt64() const override;

    /** Guards and forwards call to SimpleInterface implementation. */
    void setPropFloat(float propFloat) override;
    /** Guards and forwards call to SimpleInterface implementation. */
    float getPropFloat() const override;

    /** Guards and forwards call to SimpleInterface implementation. */
    void setPropFloat32(float propFloat32) override;
    /** Guards and forwards call to SimpleInterface implementation. */
    float getPropFloat32() const override;

    /** Guards and forwards call to SimpleInterface implementation. */
    void setPropFloat64(double propFloat64) override;
    /** Guards and forwards call to SimpleInterface implementation. */
    double getPropFloat64() const override;

    /** Guards and forwards call to SimpleInterface implementation. */
    void setPropString(const std::string& propString) override;
    /** Guards and forwards call to SimpleInterface implementation. */
    const std::string& getPropString() const override;

    /**
    * Access to a publisher, use it to subscribe for SimpleInterface changes and signal emission.
    * This call is thread safe.
    * @return The publisher for SimpleInterface.
    */
    ISimpleInterfacePublisher& _getPublisher() const override;
private:
    /** The SimpleInterface object which is guarded */
    std::shared_ptr<ISimpleInterface> m_impl;
    // Mutex for propBool property
    mutable std::shared_timed_mutex m_propBoolMutex;
    // Mutex for propInt property
    mutable std::shared_timed_mutex m_propIntMutex;
    // Mutex for propInt32 property
    mutable std::shared_timed_mutex m_propInt32Mutex;
    // Mutex for propInt64 property
    mutable std::shared_timed_mutex m_propInt64Mutex;
    // Mutex for propFloat property
    mutable std::shared_timed_mutex m_propFloatMutex;
    // Mutex for propFloat32 property
    mutable std::shared_timed_mutex m_propFloat32Mutex;
    // Mutex for propFloat64 property
    mutable std::shared_timed_mutex m_propFloat64Mutex;
    // Mutex for propString property
    mutable std::shared_timed_mutex m_propStringMutex;
};
} // namespace TbSimple
} // namespace Test
