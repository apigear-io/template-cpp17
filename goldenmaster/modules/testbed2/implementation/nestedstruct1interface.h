
#pragma once
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"
#include "testbed2/generated/core/nestedstruct1interface.data.h"
#include <memory>

namespace Test {
namespace Testbed2 {

/**
* The NestedStruct1Interface implementation.
*/
class TEST_TESTBED2_EXPORT NestedStruct1Interface : public INestedStruct1Interface
{
public:
    explicit NestedStruct1Interface();
    ~NestedStruct1Interface();
public:
    void setProp1(const NestedStruct1& prop1) override;
    const NestedStruct1& getProp1() const override;
    
    NestedStruct1 func1(const NestedStruct1& param1) override;
    std::future<NestedStruct1> func1Async(const NestedStruct1& param1, std::function<void(NestedStruct1)> callback = nullptr) override;
        
    /**
    * Access to a publisher, use it to subscribe for NestedStruct1Interface changes and signal emission.
    * @return The publisher for NestedStruct1Interface.
    */
    INestedStruct1InterfacePublisher& _getPublisher() const override;
private:
    /** The publisher for the NestedStruct1Interface. */
    std::unique_ptr<INestedStruct1InterfacePublisher> m_publisher;
    /** The helper structure to store all the properties for NestedStruct1Interface. */
    NestedStruct1InterfaceData m_data;
};
} // namespace Testbed2
} // namespace Test
