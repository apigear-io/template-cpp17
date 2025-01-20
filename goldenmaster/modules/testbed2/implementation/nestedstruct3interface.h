
#pragma once
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"
#include "testbed2/generated/core/nestedstruct3interface.data.h"
#include <memory>

namespace Test {
namespace Testbed2 {

/**
* The NestedStruct3Interface implementation.
*/
class TEST_TESTBED2_EXPORT NestedStruct3Interface : public INestedStruct3Interface
{
public:
    explicit NestedStruct3Interface();
    ~NestedStruct3Interface();
public:
    void setProp1(const NestedStruct1& prop1) override;
    const NestedStruct1& getProp1() const override;
    
    void setProp2(const NestedStruct2& prop2) override;
    const NestedStruct2& getProp2() const override;
    
    void setProp3(const NestedStruct3& prop3) override;
    const NestedStruct3& getProp3() const override;
    
    NestedStruct1 func1(const NestedStruct1& param1) override;
    std::future<NestedStruct1> func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback = nullptr) override;
        
    NestedStruct1 func2(const NestedStruct1& param1, const NestedStruct2& param2) override;
    std::future<NestedStruct1> func2Async(const NestedStruct1& param1, const NestedStruct2& param2, std::function<void(NestedStruct1)> callback = nullptr) override;
        
    NestedStruct1 func3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3) override;
    std::future<NestedStruct1> func3Async(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3, std::function<void(NestedStruct1)> callback = nullptr) override;
        
    /**
    * Access to a publisher, use it to subscribe for NestedStruct3Interface changes and signal emission.
    * @return The publisher for NestedStruct3Interface.
    */
    INestedStruct3InterfacePublisher& _getPublisher() const override;
private:
    /** The publisher for the NestedStruct3Interface. */
    std::unique_ptr<INestedStruct3InterfacePublisher> m_publisher;
    /** The helper structure to store all the properties for NestedStruct3Interface. */
    NestedStruct3InterfaceData m_data;
};
} // namespace Testbed2
} // namespace Test
