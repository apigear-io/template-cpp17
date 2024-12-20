
#pragma once
#include "testbed2/generated/api/testbed2.h"
#include "testbed2/generated/api/common.h"


namespace Test {
namespace Testbed2 {

TEST_TESTBED2_EXPORT void fillTestStruct1(Struct1& test_struct1);

TEST_TESTBED2_EXPORT void fillTestStruct2(Struct2& test_struct2);

TEST_TESTBED2_EXPORT void fillTestStruct3(Struct3& test_struct3);

TEST_TESTBED2_EXPORT void fillTestStruct4(Struct4& test_struct4);

TEST_TESTBED2_EXPORT void fillTestNestedStruct1(NestedStruct1& test_nested_struct1);

TEST_TESTBED2_EXPORT void fillTestNestedStruct2(NestedStruct2& test_nested_struct2);

TEST_TESTBED2_EXPORT void fillTestNestedStruct3(NestedStruct3& test_nested_struct3);

}
}
