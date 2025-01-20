
#pragma once
#include "tb_same2/generated/api/tb_same2.h"
#include "tb_same2/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace TbSame2 {

/** 
* @brief The SameStruct1InterfaceThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the SameStruct1Interface interface.
* @see SameStruct1Interface
*
\code{.cpp}
using namespace Test::TbSame2;

std::unique_ptr<ISameStruct1Interface> testSameStruct1Interface = std::make_unique<SameStruct1InterfaceThreadSafeDecorator>(std::make_shared<SameStruct1Interface>());

// Thread safe access
auto prop1 = testSameStruct1Interface->getProp1();
testSameStruct1Interface->setProp1(Struct1());
\endcode
*/
class TEST_TB_SAME2_EXPORT SameStruct1InterfaceThreadSafeDecorator : public ISameStruct1Interface
{
public:
    /** 
    * ctor
    * @param impl The SameStruct1Interface object to make thread safe.
    */
    explicit SameStruct1InterfaceThreadSafeDecorator(std::shared_ptr<ISameStruct1Interface> impl);

    /** 
    * Forwards call to SameStruct1Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    Struct1 func1(const Struct1& param1) override;
    /** 
    * Forwards call to SameStruct1Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<Struct1> func1Async(const Struct1& param1, std::function<void(Struct1)> callback = nullptr) override;

    /** Guards and forwards call to SameStruct1Interface implementation. */
    void setProp1(const Struct1& prop1) override;
    /** Guards and forwards call to SameStruct1Interface implementation. */
    const Struct1& getProp1() const override;

    /**
    * Access to a publisher, use it to subscribe for SameStruct1Interface changes and signal emission.
    * This call is thread safe.
    * @return The publisher for SameStruct1Interface.
    */
    ISameStruct1InterfacePublisher& _getPublisher() const override;
private:
    /** The SameStruct1Interface object which is guarded */
    std::shared_ptr<ISameStruct1Interface> m_impl;
    // Mutex for prop1 property
    mutable std::shared_timed_mutex m_prop1Mutex;
};
} // namespace TbSame2
} // namespace Test
