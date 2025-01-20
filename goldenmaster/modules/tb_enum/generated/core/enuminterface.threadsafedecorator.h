
#pragma once
#include "tb_enum/generated/api/tb_enum.h"
#include "tb_enum/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace TbEnum {

/** 
* @brief The EnumInterfaceThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the EnumInterface interface.
* @see EnumInterface
*
\code{.cpp}
using namespace Test::TbEnum;

std::unique_ptr<IEnumInterface> testEnumInterface = std::make_unique<EnumInterfaceThreadSafeDecorator>(std::make_shared<EnumInterface>());

// Thread safe access
auto prop0 = testEnumInterface->getProp0();
testEnumInterface->setProp0(Enum0Enum::value0);
auto prop1 = testEnumInterface->getProp1();
testEnumInterface->setProp1(Enum1Enum::value1);
auto prop2 = testEnumInterface->getProp2();
testEnumInterface->setProp2(Enum2Enum::value2);
auto prop3 = testEnumInterface->getProp3();
testEnumInterface->setProp3(Enum3Enum::value3);
\endcode
*/
class TEST_TB_ENUM_EXPORT EnumInterfaceThreadSafeDecorator : public IEnumInterface
{
public:
    /** 
    * ctor
    * @param impl The EnumInterface object to make thread safe.
    */
    explicit EnumInterfaceThreadSafeDecorator(std::shared_ptr<IEnumInterface> impl);

    /** 
    * Forwards call to EnumInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    Enum0Enum func0(Enum0Enum param0) override;
    /** 
    * Forwards call to EnumInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<Enum0Enum> func0Async(Enum0Enum param0, std::function<void(Enum0Enum)> callback = nullptr) override;

    /** 
    * Forwards call to EnumInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    Enum1Enum func1(Enum1Enum param1) override;
    /** 
    * Forwards call to EnumInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<Enum1Enum> func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback = nullptr) override;

    /** 
    * Forwards call to EnumInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    Enum2Enum func2(Enum2Enum param2) override;
    /** 
    * Forwards call to EnumInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<Enum2Enum> func2Async(Enum2Enum param2, std::function<void(Enum2Enum)> callback = nullptr) override;

    /** 
    * Forwards call to EnumInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    Enum3Enum func3(Enum3Enum param3) override;
    /** 
    * Forwards call to EnumInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<Enum3Enum> func3Async(Enum3Enum param3, std::function<void(Enum3Enum)> callback = nullptr) override;

    /** Guards and forwards call to EnumInterface implementation. */
    void setProp0(Enum0Enum prop0) override;
    /** Guards and forwards call to EnumInterface implementation. */
    Enum0Enum getProp0() const override;

    /** Guards and forwards call to EnumInterface implementation. */
    void setProp1(Enum1Enum prop1) override;
    /** Guards and forwards call to EnumInterface implementation. */
    Enum1Enum getProp1() const override;

    /** Guards and forwards call to EnumInterface implementation. */
    void setProp2(Enum2Enum prop2) override;
    /** Guards and forwards call to EnumInterface implementation. */
    Enum2Enum getProp2() const override;

    /** Guards and forwards call to EnumInterface implementation. */
    void setProp3(Enum3Enum prop3) override;
    /** Guards and forwards call to EnumInterface implementation. */
    Enum3Enum getProp3() const override;

    /**
    * Access to a publisher, use it to subscribe for EnumInterface changes and signal emission.
    * This call is thread safe.
    * @return The publisher for EnumInterface.
    */
    IEnumInterfacePublisher& _getPublisher() const override;
private:
    /** The EnumInterface object which is guarded */
    std::shared_ptr<IEnumInterface> m_impl;
    // Mutex for prop0 property
    mutable std::shared_timed_mutex m_prop0Mutex;
    // Mutex for prop1 property
    mutable std::shared_timed_mutex m_prop1Mutex;
    // Mutex for prop2 property
    mutable std::shared_timed_mutex m_prop2Mutex;
    // Mutex for prop3 property
    mutable std::shared_timed_mutex m_prop3Mutex;
};
} // namespace TbEnum
} // namespace Test
