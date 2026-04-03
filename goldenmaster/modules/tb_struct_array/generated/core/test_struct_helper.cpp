#include "test_struct_helper.h"

using namespace Test;

void TbStructArray::fillTestPoint(TbStructArray::Point& test_point)
{
	test_point.x = 1.1f;
	test_point.y = 1.1f;
}

void TbStructArray::fillTestStructWithArrayOfStructs(TbStructArray::StructWithArrayOfStructs& test_struct_with_array_of_structs)
{
	auto local_points_array = std::list<TbStructArray::Point>();
	auto elementpoints = TbStructArray::Point();
	fillTestPoint(elementpoints);
	local_points_array.push_back(elementpoints);
	test_struct_with_array_of_structs.points = local_points_array;
}

void TbStructArray::fillTestStructWithArrayOfEnums(TbStructArray::StructWithArrayOfEnums& test_struct_with_array_of_enums)
{
	auto local_tags_array = std::list<TbStructArray::TestEnumEnum>();
	auto elementtags = TbStructArray::TestEnumEnum::value2;
	local_tags_array.push_back(elementtags);
	test_struct_with_array_of_enums.tags = local_tags_array;
}

void TbStructArray::fillTestStructWithArrayOfInts(TbStructArray::StructWithArrayOfInts& test_struct_with_array_of_ints)
{
	auto local_values_array = std::list<int>();
	auto elementvalues = 1;
	local_values_array.push_back(elementvalues);
	test_struct_with_array_of_ints.values = local_values_array;
}

void TbStructArray::fillTestMixedStruct(TbStructArray::MixedStruct& test_mixed_struct)
{
	test_mixed_struct.id = 1;
	test_mixed_struct.name = std::string("xyz");
	fillTestPoint(test_mixed_struct.origin);
	auto local_points_array = std::list<TbStructArray::Point>();
	auto elementpoints = TbStructArray::Point();
	fillTestPoint(elementpoints);
	local_points_array.push_back(elementpoints);
	test_mixed_struct.points = local_points_array;
	auto local_flags_array = std::list<TbStructArray::TestEnumEnum>();
	auto elementflags = TbStructArray::TestEnumEnum::value2;
	local_flags_array.push_back(elementflags);
	test_mixed_struct.flags = local_flags_array;
	auto local_scores_array = std::list<int>();
	auto elementscores = 1;
	local_scores_array.push_back(elementscores);
	test_mixed_struct.scores = local_scores_array;
}
