#include "test_struct_helper.h"

using namespace Test;

void Testbed1::fillTestStructBool(Testbed1::StructBool& test_struct_bool)
{
	test_struct_bool.fieldBool = true;
}

void Testbed1::fillTestStructInt(Testbed1::StructInt& test_struct_int)
{
	test_struct_int.fieldInt = 1;
}

void Testbed1::fillTestStructFloat(Testbed1::StructFloat& test_struct_float)
{
	test_struct_float.fieldFloat = 1.1f;
}

void Testbed1::fillTestStructString(Testbed1::StructString& test_struct_string)
{
	test_struct_string.fieldString = std::string("xyz");
}
