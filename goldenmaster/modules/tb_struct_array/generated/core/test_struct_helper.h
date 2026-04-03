
#pragma once
#include "tb_struct_array/generated/api/tb_struct_array.h"
#include "tb_struct_array/generated/api/common.h"


namespace Test {
namespace TbStructArray {

TEST_TB_STRUCT_ARRAY_EXPORT void fillTestPoint(Point& test_point);

TEST_TB_STRUCT_ARRAY_EXPORT void fillTestStructWithArrayOfStructs(StructWithArrayOfStructs& test_struct_with_array_of_structs);

TEST_TB_STRUCT_ARRAY_EXPORT void fillTestStructWithArrayOfEnums(StructWithArrayOfEnums& test_struct_with_array_of_enums);

TEST_TB_STRUCT_ARRAY_EXPORT void fillTestStructWithArrayOfInts(StructWithArrayOfInts& test_struct_with_array_of_ints);

TEST_TB_STRUCT_ARRAY_EXPORT void fillTestMixedStruct(MixedStruct& test_mixed_struct);

}
}
