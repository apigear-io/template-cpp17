
#pragma once
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace Testbed2 {

/** 
* @brief The NestedStruct3InterfaceThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the NestedStruct3Interface interface.
* @see NestedStruct3Interface
*
\code{.cpp}
using namespace Test::Testbed2;

std::unique_ptr<INestedStruct3Interface> testNestedStruct3Interface = std::make_unique<NestedStruct3InterfaceThreadSafeDecorator>(std::make_shared<NestedStruct3Interface>());

// Thread safe access
auto prop1 = testNestedStruct3Interface->getProp1();
testNestedStruct3Interface->setProp1(NestedStruct1());
auto prop2 = testNestedStruct3Interface->getProp2();
testNestedStruct3Interface->setProp2(NestedStruct2());
auto prop3 = testNestedStruct3Interface->getProp3();
testNestedStruct3Interface->setProp3(NestedStruct3());
\endcode
*/
class TEST_TESTBED2_EXPORT NestedStruct3InterfaceThreadSafeDecorator : public INestedStruct3Interface
{
public:
    /** 
    * ctor
    * @param impl The NestedStruct3Interface object to make thread safe.
    */
    explicit NestedStruct3InterfaceThreadSafeDecorator(std::shared_ptr<INestedStruct3Interface> impl);

    /** 
    * Forwards call to NestedStruct3Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    NestedStruct1 func1(const NestedStruct1& param1) override;
    /** 
    * Forwards call to NestedStruct3Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<NestedStruct1> func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback = nullptr) override;

    /** 
    * Forwards call to NestedStruct3Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    NestedStruct1 func2(const NestedStruct1& param1, const NestedStruct2& param2) override;
    /** 
    * Forwards call to NestedStruct3Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<NestedStruct1> func2Async(const NestedStruct1& param1, const NestedStruct2& param2, std::function<void(NestedStruct1)> callback = nullptr) override;

    /** 
    * Forwards call to NestedStruct3Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    NestedStruct1 func3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3) override;
    /** 
    * Forwards call to NestedStruct3Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<NestedStruct1> func3Async(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3, std::function<void(NestedStruct1)> callback = nullptr) override;

    /** Guards and forwards call to NestedStruct3Interface implementation. */
    void setProp1(const NestedStruct1& prop1) override;
    /** Guards and forwards call to NestedStruct3Interface implementation. */
    const NestedStruct1& getProp1() const override;

    /** Guards and forwards call to NestedStruct3Interface implementation. */
    void setProp2(const NestedStruct2& prop2) override;
    /** Guards and forwards call to NestedStruct3Interface implementation. */
    const NestedStruct2& getProp2() const override;

    /** Guards and forwards call to NestedStruct3Interface implementation. */
    void setProp3(const NestedStruct3& prop3) override;
    /** Guards and forwards call to NestedStruct3Interface implementation. */
    const NestedStruct3& getProp3() const override;

    /**
    * Access to a publisher, use it to subscribe for NestedStruct3Interface changes and signal emission.
    * This call is thread safe.
    * @return The publisher for NestedStruct3Interface.
    */
    INestedStruct3InterfacePublisher& _getPublisher() const override;
private:
    /** The NestedStruct3Interface object which is guarded */
    std::shared_ptr<INestedStruct3Interface> m_impl;
    // Mutex for prop1 property
    mutable std::shared_timed_mutex m_prop1Mutex;
    // Mutex for prop2 property
    mutable std::shared_timed_mutex m_prop2Mutex;
    // Mutex for prop3 property
    mutable std::shared_timed_mutex m_prop3Mutex;
};
} // namespace Testbed2
} // namespace Test
