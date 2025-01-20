
#pragma once
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace Testbed1 {

/** 
* @brief The StructArrayInterfaceThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the StructArrayInterface interface.
* @see StructArrayInterface
*
\code{.cpp}
using namespace Test::Testbed1;

std::unique_ptr<IStructArrayInterface> testStructArrayInterface = std::make_unique<StructArrayInterfaceThreadSafeDecorator>(std::make_shared<StructArrayInterface>());

// Thread safe access
auto propBool = testStructArrayInterface->getPropBool();
testStructArrayInterface->setPropBool(std::list<StructBool>());
auto propInt = testStructArrayInterface->getPropInt();
testStructArrayInterface->setPropInt(std::list<StructInt>());
auto propFloat = testStructArrayInterface->getPropFloat();
testStructArrayInterface->setPropFloat(std::list<StructFloat>());
auto propString = testStructArrayInterface->getPropString();
testStructArrayInterface->setPropString(std::list<StructString>());
\endcode
*/
class TEST_TESTBED1_EXPORT StructArrayInterfaceThreadSafeDecorator : public IStructArrayInterface
{
public:
    /** 
    * ctor
    * @param impl The StructArrayInterface object to make thread safe.
    */
    explicit StructArrayInterfaceThreadSafeDecorator(std::shared_ptr<IStructArrayInterface> impl);

    /** 
    * Forwards call to StructArrayInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    StructBool funcBool(const std::list<StructBool>& paramBool) override;
    /** 
    * Forwards call to StructArrayInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<StructBool> funcBoolAsync(const std::list<StructBool>& paramBool, std::function<void(StructBool)> callback = nullptr) override;

    /** 
    * Forwards call to StructArrayInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    StructBool funcInt(const std::list<StructInt>& paramInt) override;
    /** 
    * Forwards call to StructArrayInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<StructBool> funcIntAsync(const std::list<StructInt>& paramInt, std::function<void(StructBool)> callback = nullptr) override;

    /** 
    * Forwards call to StructArrayInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    StructBool funcFloat(const std::list<StructFloat>& paramFloat) override;
    /** 
    * Forwards call to StructArrayInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<StructBool> funcFloatAsync(const std::list<StructFloat>& paramFloat, std::function<void(StructBool)> callback = nullptr) override;

    /** 
    * Forwards call to StructArrayInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    StructBool funcString(const std::list<StructString>& paramString) override;
    /** 
    * Forwards call to StructArrayInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<StructBool> funcStringAsync(const std::list<StructString>& paramString, std::function<void(StructBool)> callback = nullptr) override;

    /** Guards and forwards call to StructArrayInterface implementation. */
    void setPropBool(const std::list<StructBool>& propBool) override;
    /** Guards and forwards call to StructArrayInterface implementation. */
    const std::list<StructBool>& getPropBool() const override;

    /** Guards and forwards call to StructArrayInterface implementation. */
    void setPropInt(const std::list<StructInt>& propInt) override;
    /** Guards and forwards call to StructArrayInterface implementation. */
    const std::list<StructInt>& getPropInt() const override;

    /** Guards and forwards call to StructArrayInterface implementation. */
    void setPropFloat(const std::list<StructFloat>& propFloat) override;
    /** Guards and forwards call to StructArrayInterface implementation. */
    const std::list<StructFloat>& getPropFloat() const override;

    /** Guards and forwards call to StructArrayInterface implementation. */
    void setPropString(const std::list<StructString>& propString) override;
    /** Guards and forwards call to StructArrayInterface implementation. */
    const std::list<StructString>& getPropString() const override;

    /**
    * Access to a publisher, use it to subscribe for StructArrayInterface changes and signal emission.
    * This call is thread safe.
    * @return The publisher for StructArrayInterface.
    */
    IStructArrayInterfacePublisher& _getPublisher() const override;
private:
    /** The StructArrayInterface object which is guarded */
    std::shared_ptr<IStructArrayInterface> m_impl;
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
