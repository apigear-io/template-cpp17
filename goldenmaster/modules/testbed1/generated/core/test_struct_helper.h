
#pragma once
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"


namespace Test {
namespace Testbed1 {

TEST_TESTBED1_EXPORT void fillTestStructBool(StructBool& test_struct_bool);

TEST_TESTBED1_EXPORT void fillTestStructInt(StructInt& test_struct_int);

TEST_TESTBED1_EXPORT void fillTestStructFloat(StructFloat& test_struct_float);

TEST_TESTBED1_EXPORT void fillTestStructString(StructString& test_struct_string);

TEST_TESTBED1_EXPORT void fillTestStructStruct(StructStruct& test_struct_struct);

TEST_TESTBED1_EXPORT void fillTestStructEnum(StructEnum& test_struct_enum);

TEST_TESTBED1_EXPORT void fillTestStructBoolWithArray(StructBoolWithArray& test_struct_bool_with_array);

TEST_TESTBED1_EXPORT void fillTestStructIntWithArray(StructIntWithArray& test_struct_int_with_array);

TEST_TESTBED1_EXPORT void fillTestStructFloatWithArray(StructFloatWithArray& test_struct_float_with_array);

TEST_TESTBED1_EXPORT void fillTestStructStringWithArray(StructStringWithArray& test_struct_string_with_array);

TEST_TESTBED1_EXPORT void fillTestStructStructWithArray(StructStructWithArray& test_struct_struct_with_array);

TEST_TESTBED1_EXPORT void fillTestStructEnumWithArray(StructEnumWithArray& test_struct_enum_with_array);

}
}
