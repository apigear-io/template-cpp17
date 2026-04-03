#pragma once

#include "tb_struct_array/generated/api/tb_struct_array.h"


namespace Test
{
namespace TbStructArray
{

/**
* A helper structure for implementations of StructArrayFieldInterface. Stores all the properties.
*/
struct StructArrayFieldInterfaceData
{
    StructWithArrayOfStructs m_propStructArray {StructWithArrayOfStructs()};
    StructWithArrayOfEnums m_propEnumArray {StructWithArrayOfEnums()};
    StructWithArrayOfInts m_propIntArray {StructWithArrayOfInts()};
    MixedStruct m_propMixed {MixedStruct()};
};

}
}