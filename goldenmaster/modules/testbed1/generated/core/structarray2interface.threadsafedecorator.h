
#pragma once
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace Testbed1 {

/**
* @brief The StructArray2InterfaceThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own @c std::shared_timed_mutex — multiple concurrent
* get calls are allowed, but a set call is exclusive.
*
* @note Operation (method) calls are NOT guarded by this decorator. If the underlying
* implementation is not thread safe, callers must coordinate access to operations themselves.
* Operations can be locked by adding the same mutex mechanism in the concrete
* implementation of StructArray2Interface.
* @see StructArray2Interface
*
\code{.cpp}
using namespace Test::Testbed1;

std::unique_ptr<IStructArray2Interface> testStructArray2Interface = std::make_unique<StructArray2InterfaceThreadSafeDecorator>(std::make_shared<StructArray2Interface>());

// Thread safe access
auto propBool = testStructArray2Interface->getPropBool();
testStructArray2Interface->setPropBool(StructBoolWithArray());
auto propInt = testStructArray2Interface->getPropInt();
testStructArray2Interface->setPropInt(StructIntWithArray());
auto propFloat = testStructArray2Interface->getPropFloat();
testStructArray2Interface->setPropFloat(StructFloatWithArray());
auto propString = testStructArray2Interface->getPropString();
testStructArray2Interface->setPropString(StructStringWithArray());
auto propEnum = testStructArray2Interface->getPropEnum();
testStructArray2Interface->setPropEnum(StructEnumWithArray());
\endcode
*/
class TEST_TESTBED1_EXPORT StructArray2InterfaceThreadSafeDecorator : public IStructArray2Interface
{
public:
    /** 
    * ctor
    * @param impl The StructArray2Interface object to make thread safe.
    */
    explicit StructArray2InterfaceThreadSafeDecorator(std::shared_ptr<IStructArray2Interface> impl);

    /** 
    * Forwards call to StructArray2Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::list<StructBool> funcBool(const StructBoolWithArray& paramBool) override;
    /** 
    * Forwards call to StructArray2Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<std::list<StructBool>> funcBoolAsync(const StructBoolWithArray& paramBool, std::function<void(std::list<StructBool>)> callback = nullptr) override;

    /** 
    * Forwards call to StructArray2Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::list<StructInt> funcInt(const StructIntWithArray& paramInt) override;
    /** 
    * Forwards call to StructArray2Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<std::list<StructInt>> funcIntAsync(const StructIntWithArray& paramInt, std::function<void(std::list<StructInt>)> callback = nullptr) override;

    /** 
    * Forwards call to StructArray2Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::list<StructFloat> funcFloat(const StructFloatWithArray& paramFloat) override;
    /** 
    * Forwards call to StructArray2Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<std::list<StructFloat>> funcFloatAsync(const StructFloatWithArray& paramFloat, std::function<void(std::list<StructFloat>)> callback = nullptr) override;

    /** 
    * Forwards call to StructArray2Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::list<StructString> funcString(const StructStringWithArray& paramString) override;
    /** 
    * Forwards call to StructArray2Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<std::list<StructString>> funcStringAsync(const StructStringWithArray& paramString, std::function<void(std::list<StructString>)> callback = nullptr) override;

    /** 
    * Forwards call to StructArray2Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::list<Enum0Enum> funcEnum(const StructEnumWithArray& paramEnum) override;
    /** 
    * Forwards call to StructArray2Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<std::list<Enum0Enum>> funcEnumAsync(const StructEnumWithArray& paramEnum, std::function<void(std::list<Enum0Enum>)> callback = nullptr) override;

    /** Guards and forwards call to StructArray2Interface implementation. */
    void setPropBool(const StructBoolWithArray& propBool) override;
    /** Guards and forwards call to StructArray2Interface implementation. */
    const StructBoolWithArray& getPropBool() const override;

    /** Guards and forwards call to StructArray2Interface implementation. */
    void setPropInt(const StructIntWithArray& propInt) override;
    /** Guards and forwards call to StructArray2Interface implementation. */
    const StructIntWithArray& getPropInt() const override;

    /** Guards and forwards call to StructArray2Interface implementation. */
    void setPropFloat(const StructFloatWithArray& propFloat) override;
    /** Guards and forwards call to StructArray2Interface implementation. */
    const StructFloatWithArray& getPropFloat() const override;

    /** Guards and forwards call to StructArray2Interface implementation. */
    void setPropString(const StructStringWithArray& propString) override;
    /** Guards and forwards call to StructArray2Interface implementation. */
    const StructStringWithArray& getPropString() const override;

    /** Guards and forwards call to StructArray2Interface implementation. */
    void setPropEnum(const StructEnumWithArray& propEnum) override;
    /** Guards and forwards call to StructArray2Interface implementation. */
    const StructEnumWithArray& getPropEnum() const override;

    /**
    * Access to a publisher, use it to subscribe for StructArray2Interface changes and signal emission.
    * This call is thread safe.
    * @return The publisher for StructArray2Interface.
    */
    IStructArray2InterfacePublisher& _getPublisher() const override;
private:
    /** The StructArray2Interface object which is guarded */
    std::shared_ptr<IStructArray2Interface> m_impl;
    // Mutex for propBool property
    mutable std::shared_timed_mutex m_propBoolMutex;
    // Mutex for propInt property
    mutable std::shared_timed_mutex m_propIntMutex;
    // Mutex for propFloat property
    mutable std::shared_timed_mutex m_propFloatMutex;
    // Mutex for propString property
    mutable std::shared_timed_mutex m_propStringMutex;
    // Mutex for propEnum property
    mutable std::shared_timed_mutex m_propEnumMutex;
};
} // namespace Testbed1
} // namespace Test
