
#pragma once
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"
#include "testbed1/generated/core/structarrayinterface.data.h"
#include <memory>

namespace Test {
namespace Testbed1 {

/**
* The StructArrayInterface implementation.
*/
class TEST_TESTBED1_EXPORT StructArrayInterface : public IStructArrayInterface
{
public:
    explicit StructArrayInterface();
    ~StructArrayInterface();
public:
    void setPropBool(const std::list<StructBool>& propBool) override;
    const std::list<StructBool>& getPropBool() const override;
    
    void setPropInt(const std::list<StructInt>& propInt) override;
    const std::list<StructInt>& getPropInt() const override;
    
    void setPropFloat(const std::list<StructFloat>& propFloat) override;
    const std::list<StructFloat>& getPropFloat() const override;
    
    void setPropString(const std::list<StructString>& propString) override;
    const std::list<StructString>& getPropString() const override;
    
    std::list<StructBool> funcBool(const std::list<StructBool>& paramBool) override;
    std::future<std::list<StructBool>> funcBoolAsync(const std::list<StructBool>& paramBool, std::function<void(std::list<StructBool>)> callback = nullptr) override;
        
    std::list<StructInt> funcInt(const std::list<StructInt>& paramInt) override;
    std::future<std::list<StructInt>> funcIntAsync(const std::list<StructInt>& paramInt, std::function<void(std::list<StructInt>)> callback = nullptr) override;
        
    std::list<StructFloat> funcFloat(const std::list<StructFloat>& paramFloat) override;
    std::future<std::list<StructFloat>> funcFloatAsync(const std::list<StructFloat>& paramFloat, std::function<void(std::list<StructFloat>)> callback = nullptr) override;
        
    std::list<StructString> funcString(const std::list<StructString>& paramString) override;
    std::future<std::list<StructString>> funcStringAsync(const std::list<StructString>& paramString, std::function<void(std::list<StructString>)> callback = nullptr) override;
        
    /**
    * Access to a publisher, use it to subscribe for StructArrayInterface changes and signal emission.
    * @return The publisher for StructArrayInterface.
    */
    IStructArrayInterfacePublisher& _getPublisher() const override;
private:
    /** The publisher for the StructArrayInterface. */
    std::unique_ptr<IStructArrayInterfacePublisher> m_publisher;
    /** The helper structure to store all the properties for StructArrayInterface. */
    StructArrayInterfaceData m_data;
};
} // namespace Testbed1
} // namespace Test
