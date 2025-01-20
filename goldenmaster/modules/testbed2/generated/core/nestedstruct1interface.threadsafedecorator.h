
#pragma once
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace Testbed2 {

/** 
* @brief The NestedStruct1InterfaceThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the NestedStruct1Interface interface.
* @see NestedStruct1Interface
*
\code{.cpp}
using namespace Test::Testbed2;

std::unique_ptr<INestedStruct1Interface> testNestedStruct1Interface = std::make_unique<NestedStruct1InterfaceThreadSafeDecorator>(std::make_shared<NestedStruct1Interface>());

// Thread safe access
auto prop1 = testNestedStruct1Interface->getProp1();
testNestedStruct1Interface->setProp1(NestedStruct1());
\endcode
*/
class TEST_TESTBED2_EXPORT NestedStruct1InterfaceThreadSafeDecorator : public INestedStruct1Interface
{
public:
    /** 
    * ctor
    * @param impl The NestedStruct1Interface object to make thread safe.
    */
    explicit NestedStruct1InterfaceThreadSafeDecorator(std::shared_ptr<INestedStruct1Interface> impl);

    /** 
    * Forwards call to NestedStruct1Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    NestedStruct1 func1(const NestedStruct1& param1) override;
    /** 
    * Forwards call to NestedStruct1Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<NestedStruct1> func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback = nullptr) override;

    /** Guards and forwards call to NestedStruct1Interface implementation. */
    void setProp1(const NestedStruct1& prop1) override;
    /** Guards and forwards call to NestedStruct1Interface implementation. */
    const NestedStruct1& getProp1() const override;

    /**
    * Access to a publisher, use it to subscribe for NestedStruct1Interface changes and signal emission.
    * This call is thread safe.
    * @return The publisher for NestedStruct1Interface.
    */
    INestedStruct1InterfacePublisher& _getPublisher() const override;
private:
    /** The NestedStruct1Interface object which is guarded */
    std::shared_ptr<INestedStruct1Interface> m_impl;
    // Mutex for prop1 property
    mutable std::shared_timed_mutex m_prop1Mutex;
};
} // namespace Testbed2
} // namespace Test
