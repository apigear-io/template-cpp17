
#pragma once
#include "tb_same1/generated/api/tb_same1.h"
#include "tb_same1/generated/api/common.h"
#include "tb_same1/generated/core/samestruct1interface.data.h"
#include <memory>

namespace Test {
namespace TbSame1 {

/**
* The SameStruct1Interface implementation.
*/
class TEST_TB_SAME1_EXPORT SameStruct1Interface : public ISameStruct1Interface
{
public:
    explicit SameStruct1Interface();
    ~SameStruct1Interface();
public:
    void setProp1(const Struct1& prop1) override;
    const Struct1& getProp1() const override;
    
    Struct1 func1(const Struct1& param1) override;
    std::future<Struct1> func1Async(const Struct1& param1, std::function<void(Struct1)> callback = nullptr) override;
        
    /**
    * Access to a publisher, use it to subscribe for SameStruct1Interface changes and signal emission.
    * @return The publisher for SameStruct1Interface.
    */
    ISameStruct1InterfacePublisher& _getPublisher() const override;
private:
    /** The publisher for the SameStruct1Interface. */
    std::unique_ptr<ISameStruct1InterfacePublisher> m_publisher;
    /** The helper structure to store all the properties for SameStruct1Interface. */
    SameStruct1InterfaceData m_data;
};
} // namespace TbSame1
} // namespace Test
