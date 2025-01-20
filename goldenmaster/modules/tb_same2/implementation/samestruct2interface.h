
#pragma once
#include "tb_same2/generated/api/tb_same2.h"
#include "tb_same2/generated/api/common.h"
#include "tb_same2/generated/core/samestruct2interface.data.h"
#include <memory>

namespace Test {
namespace TbSame2 {

/**
* The SameStruct2Interface implementation.
*/
class TEST_TB_SAME2_EXPORT SameStruct2Interface : public ISameStruct2Interface
{
public:
    explicit SameStruct2Interface();
    ~SameStruct2Interface();
public:
    void setProp1(const Struct2& prop1) override;
    const Struct2& getProp1() const override;
    
    void setProp2(const Struct2& prop2) override;
    const Struct2& getProp2() const override;
    
    Struct1 func1(const Struct1& param1) override;
    std::future<Struct1> func1Async(const Struct1& param1, std::function<void(Struct1)> callback = nullptr) override;
        
    Struct1 func2(const Struct1& param1, const Struct2& param2) override;
    std::future<Struct1> func2Async(const Struct1& param1, const Struct2& param2, std::function<void(Struct1)> callback = nullptr) override;
        
    /**
    * Access to a publisher, use it to subscribe for SameStruct2Interface changes and signal emission.
    * @return The publisher for SameStruct2Interface.
    */
    ISameStruct2InterfacePublisher& _getPublisher() const override;
private:
    /** The publisher for the SameStruct2Interface. */
    std::unique_ptr<ISameStruct2InterfacePublisher> m_publisher;
    /** The helper structure to store all the properties for SameStruct2Interface. */
    SameStruct2InterfaceData m_data;
};
} // namespace TbSame2
} // namespace Test
