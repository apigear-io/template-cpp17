
#pragma once
#include "tb_same2/generated/api/tb_same2.h"
#include "tb_same2/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace TbSame2 {

/** 
* @brief The SameStruct2InterfaceThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the SameStruct2Interface interface.
* @see SameStruct2Interface
*
\code{.cpp}
using namespace Test::TbSame2;

std::unique_ptr<ISameStruct2Interface> testSameStruct2Interface = std::make_unique<SameStruct2InterfaceThreadSafeDecorator>(std::make_shared<SameStruct2Interface>());

// Thread safe access
auto prop1 = testSameStruct2Interface->getProp1();
testSameStruct2Interface->setProp1(Struct2());
auto prop2 = testSameStruct2Interface->getProp2();
testSameStruct2Interface->setProp2(Struct2());
\endcode
*/
class TEST_TB_SAME2_EXPORT SameStruct2InterfaceThreadSafeDecorator : public ISameStruct2Interface
{
public:
    /** 
    * ctor
    * @param impl The SameStruct2Interface object to make thread safe.
    */
    explicit SameStruct2InterfaceThreadSafeDecorator(std::shared_ptr<ISameStruct2Interface> impl);

    /** 
    * Forwards call to SameStruct2Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    Struct1 func1(const Struct1& param1) override;
    /** 
    * Forwards call to SameStruct2Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<Struct1> func1Async(const Struct1& param1, std::function<void(Struct1)> callback = nullptr) override;

    /** 
    * Forwards call to SameStruct2Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    Struct1 func2(const Struct1& param1, const Struct2& param2) override;
    /** 
    * Forwards call to SameStruct2Interface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<Struct1> func2Async(const Struct1& param1, const Struct2& param2, std::function<void(Struct1)> callback = nullptr) override;

    /** Guards and forwards call to SameStruct2Interface implementation. */
    void setProp1(const Struct2& prop1) override;
    /** Guards and forwards call to SameStruct2Interface implementation. */
    const Struct2& getProp1() const override;

    /** Guards and forwards call to SameStruct2Interface implementation. */
    void setProp2(const Struct2& prop2) override;
    /** Guards and forwards call to SameStruct2Interface implementation. */
    const Struct2& getProp2() const override;

    /**
    * Access to a publisher, use it to subscribe for SameStruct2Interface changes and signal emission.
    * This call is thread safe.
    * @return The publisher for SameStruct2Interface.
    */
    ISameStruct2InterfacePublisher& _getPublisher() const override;
private:
    /** The SameStruct2Interface object which is guarded */
    std::shared_ptr<ISameStruct2Interface> m_impl;
    // Mutex for prop1 property
    mutable std::shared_timed_mutex m_prop1Mutex;
    // Mutex for prop2 property
    mutable std::shared_timed_mutex m_prop2Mutex;
};
} // namespace TbSame2
} // namespace Test
