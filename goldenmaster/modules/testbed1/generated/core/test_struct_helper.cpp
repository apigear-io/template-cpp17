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

void Testbed1::fillTestStructStruct(Testbed1::StructStruct& test_struct_struct)
{
	fillTestStructString(test_struct_struct.fieldString);
}

void Testbed1::fillTestStructEnum(Testbed1::StructEnum& test_struct_enum)
{
	test_struct_enum.fieldEnum = Testbed1::Enum0Enum::value1;
}

void Testbed1::fillTestStructBoolWithArray(Testbed1::StructBoolWithArray& test_struct_bool_with_array)
{
	auto local_field_bool_array = std::list<bool>();
	auto elementfield_bool = true;
	local_field_bool_array.push_back(elementfield_bool);
	test_struct_bool_with_array.fieldBool = local_field_bool_array;
}

void Testbed1::fillTestStructIntWithArray(Testbed1::StructIntWithArray& test_struct_int_with_array)
{
	auto local_field_int_array = std::list<int>();
	auto elementfield_int = 1;
	local_field_int_array.push_back(elementfield_int);
	test_struct_int_with_array.fieldInt = local_field_int_array;
}

void Testbed1::fillTestStructFloatWithArray(Testbed1::StructFloatWithArray& test_struct_float_with_array)
{
	auto local_field_float_array = std::list<float>();
	auto elementfield_float = 1.1f;
	local_field_float_array.push_back(elementfield_float);
	test_struct_float_with_array.fieldFloat = local_field_float_array;
}

void Testbed1::fillTestStructStringWithArray(Testbed1::StructStringWithArray& test_struct_string_with_array)
{
	auto local_field_string_array = std::list<std::string>();
	auto elementfield_string = std::string("xyz");
	local_field_string_array.push_back(elementfield_string);
	test_struct_string_with_array.fieldString = local_field_string_array;
}

void Testbed1::fillTestStructStructWithArray(Testbed1::StructStructWithArray& test_struct_struct_with_array)
{
	auto local_field_struct_array = std::list<Testbed1::StructStringWithArray>();
	auto elementfield_struct = Testbed1::StructStringWithArray();
	fillTestStructStringWithArray(elementfield_struct);
	local_field_struct_array.push_back(elementfield_struct);
	test_struct_struct_with_array.fieldStruct = local_field_struct_array;
}

void Testbed1::fillTestStructEnumWithArray(Testbed1::StructEnumWithArray& test_struct_enum_with_array)
{
	auto local_field_enum_array = std::list<Testbed1::Enum0Enum>();
	auto elementfield_enum = Testbed1::Enum0Enum::value1;
	local_field_enum_array.push_back(elementfield_enum);
	test_struct_enum_with_array.fieldEnum = local_field_enum_array;
}
