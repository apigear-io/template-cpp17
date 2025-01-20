
#pragma once
#include "tb_same2/generated/api/tb_same2.h"
#include "tb_same2/generated/api/common.h"
#include "tb_same2/generated/core/sameenum1interface.data.h"
#include <memory>

namespace Test {
namespace TbSame2 {

/**
* The SameEnum1Interface implementation.
*/
class TEST_TB_SAME2_EXPORT SameEnum1Interface : public ISameEnum1Interface
{
public:
    explicit SameEnum1Interface();
    ~SameEnum1Interface();
public:
    void setProp1(Enum1Enum prop1) override;
    Enum1Enum getProp1() const override;
    
    Enum1Enum func1(Enum1Enum param1) override;
    std::future<Enum1Enum> func1Async(Enum1Enum param1, std::function<void(Enum1Enum)> callback = nullptr) override;
        
    /**
    * Access to a publisher, use it to subscribe for SameEnum1Interface changes and signal emission.
    * @return The publisher for SameEnum1Interface.
    */
    ISameEnum1InterfacePublisher& _getPublisher() const override;
private:
    /** The publisher for the SameEnum1Interface. */
    std::unique_ptr<ISameEnum1InterfacePublisher> m_publisher;
    /** The helper structure to store all the properties for SameEnum1Interface. */
    SameEnum1InterfaceData m_data;
};
} // namespace TbSame2
} // namespace Test
