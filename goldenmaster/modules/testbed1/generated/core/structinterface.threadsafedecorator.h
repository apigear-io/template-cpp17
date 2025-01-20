
#pragma once
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace Testbed1 {

/** 
* @brief The StructInterfaceThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the StructInterface interface.
* @see StructInterface
*
\code{.cpp}
using namespace Test::Testbed1;

std::unique_ptr<IStructInterface> testStructInterface = std::make_unique<StructInterfaceThreadSafeDecorator>(std::make_shared<StructInterface>());

// Thread safe access
auto propBool = testStructInterface->getPropBool();
testStructInterface->setPropBool(StructBool());
auto propInt = testStructInterface->getPropInt();
testStructInterface->setPropInt(StructInt());
auto propFloat = testStructInterface->getPropFloat();
testStructInterface->setPropFloat(StructFloat());
auto propString = testStructInterface->getPropString();
testStructInterface->setPropString(StructString());
\endcode
*/
class TEST_TESTBED1_EXPORT StructInterfaceThreadSafeDecorator : public IStructInterface
{
public:
    /** 
    * ctor
    * @param impl The StructInterface object to make thread safe.
    */
    explicit StructInterfaceThreadSafeDecorator(std::shared_ptr<IStructInterface> impl);

    /** 
    * Forwards call to StructInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    StructBool funcBool(const StructBool& paramBool) override;
    /** 
    * Forwards call to StructInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<StructBool> funcBoolAsync(const StructBool& paramBool, std::function<void(StructBool)> callback = nullptr) override;

    /** 
    * Forwards call to StructInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    StructInt funcInt(const StructInt& paramInt) override;
    /** 
    * Forwards call to StructInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<StructInt> funcIntAsync(const StructInt& paramInt, std::function<void(StructInt)> callback = nullptr) override;

    /** 
    * Forwards call to StructInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    StructFloat funcFloat(const StructFloat& paramFloat) override;
    /** 
    * Forwards call to StructInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<StructFloat> funcFloatAsync(const StructFloat& paramFloat, std::function<void(StructFloat)> callback = nullptr) override;

    /** 
    * Forwards call to StructInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    StructString funcString(const StructString& paramString) override;
    /** 
    * Forwards call to StructInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<StructString> funcStringAsync(const StructString& paramString, std::function<void(StructString)> callback = nullptr) override;

    /** Guards and forwards call to StructInterface implementation. */
    void setPropBool(const StructBool& propBool) override;
    /** Guards and forwards call to StructInterface implementation. */
    const StructBool& getPropBool() const override;

    /** Guards and forwards call to StructInterface implementation. */
    void setPropInt(const StructInt& propInt) override;
    /** Guards and forwards call to StructInterface implementation. */
    const StructInt& getPropInt() const override;

    /** Guards and forwards call to StructInterface implementation. */
    void setPropFloat(const StructFloat& propFloat) override;
    /** Guards and forwards call to StructInterface implementation. */
    const StructFloat& getPropFloat() const override;

    /** Guards and forwards call to StructInterface implementation. */
    void setPropString(const StructString& propString) override;
    /** Guards and forwards call to StructInterface implementation. */
    const StructString& getPropString() const override;

    /**
    * Access to a publisher, use it to subscribe for StructInterface changes and signal emission.
    * This call is thread safe.
    * @return The publisher for StructInterface.
    */
    IStructInterfacePublisher& _getPublisher() const override;
private:
    /** The StructInterface object which is guarded */
    std::shared_ptr<IStructInterface> m_impl;
    // Mutex for propBool property
    mutable std::shared_timed_mutex m_propBoolMutex;
    // Mutex for propInt property
    mutable std::shared_timed_mutex m_propIntMutex;
    // Mutex for propFloat property
    mutable std::shared_timed_mutex m_propFloatMutex;
    // Mutex for propString property
    mutable std::shared_timed_mutex m_propStringMutex;
};
} // namespace Testbed1
} // namespace Test
