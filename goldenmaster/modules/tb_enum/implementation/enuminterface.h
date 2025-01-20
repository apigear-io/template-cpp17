
#pragma once
#include "tb_enum/generated/api/tb_enum.h"
#include "tb_enum/generated/api/common.h"
#include "tb_enum/generated/core/enuminterface.data.h"
#include <memory>

namespace Test {
namespace TbEnum {

/**
* The EnumInterface implementation.
*/
class TEST_TB_ENUM_EXPORT EnumInterface : public IEnumInterface
{
public:
    explicit EnumInterface();
    ~EnumInterface();
public:
    void setProp0(Enum0Enum prop0) override;
    Enum0Enum getProp0() const override;
    
    void setProp1(Enum1Enum prop1) override;
    Enum1Enum getProp1() const override;
    
    void setProp2(Enum2Enum prop2) override;
    Enum2Enum getProp2() const override;
    
    void setProp3(Enum3Enum prop3) override;
    Enum3Enum getProp3() const override;
    
    Enum0Enum func0(Enum0Enum param0) override;
    std::future<Enum0Enum> func0Async(Enum0Enum param0, std::function<void(Enum0Enum)> callback = nullptr) override;
        
    Enum1Enum func1(Enum1Enum param1) override;
    std::future<Enum1Enum> func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback = nullptr) override;
        
    Enum2Enum func2(Enum2Enum param2) override;
    std::future<Enum2Enum> func2Async(Enum2Enum param2, std::function<void(Enum2Enum)> callback = nullptr) override;
        
    Enum3Enum func3(Enum3Enum param3) override;
    std::future<Enum3Enum> func3Async(Enum3Enum param3, std::function<void(Enum3Enum)> callback = nullptr) override;
        
    /**
    * Access to a publisher, use it to subscribe for EnumInterface changes and signal emission.
    * @return The publisher for EnumInterface.
    */
    IEnumInterfacePublisher& _getPublisher() const override;
private:
    /** The publisher for the EnumInterface. */
    std::unique_ptr<IEnumInterfacePublisher> m_publisher;
    /** The helper structure to store all the properties for EnumInterface. */
    EnumInterfaceData m_data;
};
} // namespace TbEnum
} // namespace Test
