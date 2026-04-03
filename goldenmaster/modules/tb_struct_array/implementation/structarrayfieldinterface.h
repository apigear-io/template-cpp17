
#pragma once
#include "tb_struct_array/generated/api/tb_struct_array.h"
#include "tb_struct_array/generated/api/common.h"
#include "tb_struct_array/generated/core/structarrayfieldinterface.data.h"
#include <memory>

namespace Test {
namespace TbStructArray {

/**
* The StructArrayFieldInterface implementation.
*/
class TEST_TB_STRUCT_ARRAY_EXPORT StructArrayFieldInterface : public IStructArrayFieldInterface
{
public:
    explicit StructArrayFieldInterface();
    ~StructArrayFieldInterface();
public:
    void setPropStructArray(const StructWithArrayOfStructs& propStructArray) override;
    const StructWithArrayOfStructs& getPropStructArray() const override;
    
    void setPropEnumArray(const StructWithArrayOfEnums& propEnumArray) override;
    const StructWithArrayOfEnums& getPropEnumArray() const override;
    
    void setPropIntArray(const StructWithArrayOfInts& propIntArray) override;
    const StructWithArrayOfInts& getPropIntArray() const override;
    
    void setPropMixed(const MixedStruct& propMixed) override;
    const MixedStruct& getPropMixed() const override;
    
    MixedStruct funcMixed(const MixedStruct& paramMixed) override;
    std::future<MixedStruct> funcMixedAsync(const MixedStruct& paramMixed, std::function<void(MixedStruct)> callback = nullptr) override;
        
    StructWithArrayOfStructs funcStructArray(const StructWithArrayOfStructs& paramPoints) override;
    std::future<StructWithArrayOfStructs> funcStructArrayAsync(const StructWithArrayOfStructs& paramPoints, std::function<void(StructWithArrayOfStructs)> callback = nullptr) override;
        
    /**
    * Access to a publisher, use it to subscribe for StructArrayFieldInterface changes and signal emission.
    * @return The publisher for StructArrayFieldInterface.
    */
    IStructArrayFieldInterfacePublisher& _getPublisher() const override;
private:
    /** The publisher for the StructArrayFieldInterface. */
    std::unique_ptr<IStructArrayFieldInterfacePublisher> m_publisher;
    /** The helper structure to store all the properties for StructArrayFieldInterface. */
    StructArrayFieldInterfaceData m_data;
};
} // namespace TbStructArray
} // namespace Test
