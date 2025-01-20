
#pragma once
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"
#include "testbed2/generated/core/nestedstruct2interface.data.h"
#include <memory>

namespace Test {
namespace Testbed2 {

/**
* The NestedStruct2Interface implementation.
*/
class TEST_TESTBED2_EXPORT NestedStruct2Interface : public INestedStruct2Interface
{
public:
    explicit NestedStruct2Interface();
    ~NestedStruct2Interface();
public:
    void setProp1(const NestedStruct1& prop1) override;
    const NestedStruct1& getProp1() const override;
    
    void setProp2(const NestedStruct2& prop2) override;
    const NestedStruct2& getProp2() const override;
    
    NestedStruct1 func1(const NestedStruct1& param1) override;
    std::future<NestedStruct1> func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback = nullptr) override;
        
    NestedStruct1 func2(const NestedStruct1& param1, const NestedStruct2& param2) override;
    std::future<NestedStruct1> func2Async(const NestedStruct1& param1, const NestedStruct2& param2, std::function<void(NestedStruct1)> callback = nullptr) override;
        
    /**
    * Access to a publisher, use it to subscribe for NestedStruct2Interface changes and signal emission.
    * @return The publisher for NestedStruct2Interface.
    */
    INestedStruct2InterfacePublisher& _getPublisher() const override;
private:
    /** The publisher for the NestedStruct2Interface. */
    std::unique_ptr<INestedStruct2InterfacePublisher> m_publisher;
    /** The helper structure to store all the properties for NestedStruct2Interface. */
    NestedStruct2InterfaceData m_data;
};
} // namespace Testbed2
} // namespace Test
