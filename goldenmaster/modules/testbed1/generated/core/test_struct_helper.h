
#pragma once
#include "testbed1/generated/api/testbed1.h"
#include "testbed1/generated/api/common.h"


namespace Test {
namespace Testbed1 {

TEST_TESTBED1_EXPORT void fillTestStructBool(StructBool& test_struct_bool);

TEST_TESTBED1_EXPORT void fillTestStructInt(StructInt& test_struct_int);

TEST_TESTBED1_EXPORT void fillTestStructFloat(StructFloat& test_struct_float);

TEST_TESTBED1_EXPORT void fillTestStructString(StructString& test_struct_string);

}
}
