#include "test_struct_helper.h"

using namespace Test;

void Testbed2::fillTestStruct1(Testbed2::Struct1& test_struct1)
{
	test_struct1.field1 = 1;
}

void Testbed2::fillTestStruct2(Testbed2::Struct2& test_struct2)
{
	test_struct2.field1 = 1;
	test_struct2.field2 = 1;
}

void Testbed2::fillTestStruct3(Testbed2::Struct3& test_struct3)
{
	test_struct3.field1 = 1;
	test_struct3.field2 = 1;
	test_struct3.field3 = 1;
}

void Testbed2::fillTestStruct4(Testbed2::Struct4& test_struct4)
{
	test_struct4.field1 = 1;
	test_struct4.field2 = 1;
	test_struct4.field3 = 1;
	test_struct4.field4 = 1;
}

void Testbed2::fillTestNestedStruct1(Testbed2::NestedStruct1& test_nested_struct1)
{
	fillTestStruct1(test_nested_struct1.field1);
}

void Testbed2::fillTestNestedStruct2(Testbed2::NestedStruct2& test_nested_struct2)
{
	fillTestStruct1(test_nested_struct2.field1);
	fillTestStruct2(test_nested_struct2.field2);
}

void Testbed2::fillTestNestedStruct3(Testbed2::NestedStruct3& test_nested_struct3)
{
	fillTestStruct1(test_nested_struct3.field1);
	fillTestStruct2(test_nested_struct3.field2);
	fillTestStruct3(test_nested_struct3.field3);
}
