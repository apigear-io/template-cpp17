
#pragma once
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"
#include "testbed1/generated/core/structinterface.data.h"
#include <memory>

namespace Test {
namespace Testbed1 {

/**
* The StructInterface implementation.
*/
class TEST_TESTBED1_EXPORT StructInterface : public IStructInterface
{
public:
    explicit StructInterface();
    ~StructInterface();
public:
    void setPropBool(const StructBool& propBool) override;
    const StructBool& getPropBool() const override;
    
    void setPropInt(const StructInt& propInt) override;
    const StructInt& getPropInt() const override;
    
    void setPropFloat(const StructFloat& propFloat) override;
    const StructFloat& getPropFloat() const override;
    
    void setPropString(const StructString& propString) override;
    const StructString& getPropString() const override;
    
    StructBool funcBool(const StructBool& paramBool) override;
    std::future<StructBool> funcBoolAsync(const StructBool& paramBool, std::function<void(StructBool)> callback = nullptr) override;
        
    StructInt funcInt(const StructInt& paramInt) override;
    std::future<StructInt> funcIntAsync(const StructInt& paramInt, std::function<void(StructInt)> callback = nullptr) override;
        
    StructFloat funcFloat(const StructFloat& paramFloat) override;
    std::future<StructFloat> funcFloatAsync(const StructFloat& paramFloat, std::function<void(StructFloat)> callback = nullptr) override;
        
    StructString funcString(const StructString& paramString) override;
    std::future<StructString> funcStringAsync(const StructString& paramString, std::function<void(StructString)> callback = nullptr) override;
        
    /**
    * Access to a publisher, use it to subscribe for StructInterface changes and signal emission.
    * @return The publisher for StructInterface.
    */
    IStructInterfacePublisher& _getPublisher() const override;
private:
    /** The publisher for the StructInterface. */
    std::unique_ptr<IStructInterfacePublisher> m_publisher;
    /** The helper structure to store all the properties for StructInterface. */
    StructInterfaceData m_data;
};
} // namespace Testbed1
} // namespace Test
