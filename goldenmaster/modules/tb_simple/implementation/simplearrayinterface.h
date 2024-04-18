
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/core/simplearrayinterface.data.h"
#include <memory>

namespace Test {
namespace TbSimple {

/**
* The SimpleArrayInterface implementation.
*/
class TEST_TB_SIMPLE_EXPORT SimpleArrayInterface : public ISimpleArrayInterface
{
public:
    explicit SimpleArrayInterface();
    ~SimpleArrayInterface();
public:
    void setPropBool(const std::list<bool>& propBool) override;
    const std::list<bool>& getPropBool() const override;
    
    void setPropInt(const std::list<int>& propInt) override;
    const std::list<int>& getPropInt() const override;
    
    void setPropInt32(const std::list<int32_t>& propInt32) override;
    const std::list<int32_t>& getPropInt32() const override;
    
    void setPropInt64(const std::list<int64_t>& propInt64) override;
    const std::list<int64_t>& getPropInt64() const override;
    
    void setPropFloat(const std::list<float>& propFloat) override;
    const std::list<float>& getPropFloat() const override;
    
    void setPropFloat32(const std::list<float>& propFloat32) override;
    const std::list<float>& getPropFloat32() const override;
    
    void setPropFloat64(const std::list<double>& propFloat64) override;
    const std::list<double>& getPropFloat64() const override;
    
    void setPropString(const std::list<std::string>& propString) override;
    const std::list<std::string>& getPropString() const override;
    
    void setPropReadOnlyString(const std::string& propReadOnlyString);
    const std::string& getPropReadOnlyString() const override;
    
    std::list<bool> funcBool(const std::list<bool>& paramBool) override;
    std::future<std::list<bool>> funcBoolAsync(const std::list<bool>& paramBool) override;
        
    std::list<int> funcInt(const std::list<int>& paramInt) override;
    std::future<std::list<int>> funcIntAsync(const std::list<int>& paramInt) override;
        
    std::list<int32_t> funcInt32(const std::list<int32_t>& paramInt32) override;
    std::future<std::list<int32_t>> funcInt32Async(const std::list<int32_t>& paramInt32) override;
        
    std::list<int64_t> funcInt64(const std::list<int64_t>& paramInt64) override;
    std::future<std::list<int64_t>> funcInt64Async(const std::list<int64_t>& paramInt64) override;
        
    std::list<float> funcFloat(const std::list<float>& paramFloat) override;
    std::future<std::list<float>> funcFloatAsync(const std::list<float>& paramFloat) override;
        
    std::list<float> funcFloat32(const std::list<float>& paramFloat32) override;
    std::future<std::list<float>> funcFloat32Async(const std::list<float>& paramFloat32) override;
        
    std::list<double> funcFloat64(const std::list<double>& paramFloat) override;
    std::future<std::list<double>> funcFloat64Async(const std::list<double>& paramFloat) override;
        
    std::list<std::string> funcString(const std::list<std::string>& paramString) override;
    std::future<std::list<std::string>> funcStringAsync(const std::list<std::string>& paramString) override;
        
    /**
    * Access to a publisher, use it to subscribe for SimpleArrayInterface changes and signal emission.
    * @return The publisher for SimpleArrayInterface.
    */
    ISimpleArrayInterfacePublisher& _getPublisher() const override;
private:
    /** The publisher for the SimpleArrayInterface. */
    std::unique_ptr<ISimpleArrayInterfacePublisher> m_publisher;
    /** The helper structure to store all the properties for SimpleArrayInterface. */
    SimpleArrayInterfaceData m_data;
};
} // namespace TbSimple
} // namespace Test
