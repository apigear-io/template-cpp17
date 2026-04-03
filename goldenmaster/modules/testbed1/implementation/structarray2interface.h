
#pragma once
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"
#include "testbed1/generated/core/structarray2interface.data.h"
#include <memory>

namespace Test {
namespace Testbed1 {

/**
* The StructArray2Interface implementation.
*/
class TEST_TESTBED1_EXPORT StructArray2Interface : public IStructArray2Interface
{
public:
    explicit StructArray2Interface();
    ~StructArray2Interface();
public:
    void setPropBool(const StructBoolWithArray& propBool) override;
    const StructBoolWithArray& getPropBool() const override;
    
    void setPropInt(const StructIntWithArray& propInt) override;
    const StructIntWithArray& getPropInt() const override;
    
    void setPropFloat(const StructFloatWithArray& propFloat) override;
    const StructFloatWithArray& getPropFloat() const override;
    
    void setPropString(const StructStringWithArray& propString) override;
    const StructStringWithArray& getPropString() const override;
    
    void setPropEnum(const StructEnumWithArray& propEnum) override;
    const StructEnumWithArray& getPropEnum() const override;
    
    std::list<StructBool> funcBool(const StructBoolWithArray& paramBool) override;
    std::future<std::list<StructBool>> funcBoolAsync(const StructBoolWithArray& paramBool, std::function<void(std::list<StructBool>)> callback = nullptr) override;
        
    std::list<StructInt> funcInt(const StructIntWithArray& paramInt) override;
    std::future<std::list<StructInt>> funcIntAsync(const StructIntWithArray& paramInt, std::function<void(std::list<StructInt>)> callback = nullptr) override;
        
    std::list<StructFloat> funcFloat(const StructFloatWithArray& paramFloat) override;
    std::future<std::list<StructFloat>> funcFloatAsync(const StructFloatWithArray& paramFloat, std::function<void(std::list<StructFloat>)> callback = nullptr) override;
        
    std::list<StructString> funcString(const StructStringWithArray& paramString) override;
    std::future<std::list<StructString>> funcStringAsync(const StructStringWithArray& paramString, std::function<void(std::list<StructString>)> callback = nullptr) override;
        
    std::list<Enum0Enum> funcEnum(const StructEnumWithArray& paramEnum) override;
    std::future<std::list<Enum0Enum>> funcEnumAsync(const StructEnumWithArray& paramEnum, std::function<void(std::list<Enum0Enum>)> callback = nullptr) override;
        
    /**
    * Access to a publisher, use it to subscribe for StructArray2Interface changes and signal emission.
    * @return The publisher for StructArray2Interface.
    */
    IStructArray2InterfacePublisher& _getPublisher() const override;
private:
    /** The publisher for the StructArray2Interface. */
    std::unique_ptr<IStructArray2InterfacePublisher> m_publisher;
    /** The helper structure to store all the properties for StructArray2Interface. */
    StructArray2InterfaceData m_data;
};
} // namespace Testbed1
} // namespace Test
