#pragma once

#include <cinttypes>
#include <string>
#include <list>

#include "tb_struct_array/generated/api/common.h"

namespace Test {
namespace TbStructArray {
struct Point;
struct StructWithArrayOfStructs;
struct StructWithArrayOfEnums;
struct StructWithArrayOfInts;
struct MixedStruct;

/**
 * Enumeration TestEnum
 */
enum class TestEnumEnum {
    value1 = 1,
    value2 = 2
};
TEST_TB_STRUCT_ARRAY_EXPORT TestEnumEnum toTestEnumEnum(std::uint8_t v, bool *ok);

/**
 * Struct Point
 */
struct TEST_TB_STRUCT_ARRAY_EXPORT Point
{
    Point();
    Point(float x, float y);

    float x{};
    float y{};

};
bool TEST_TB_STRUCT_ARRAY_EXPORT operator==(const Point &, const Point &) noexcept;
bool TEST_TB_STRUCT_ARRAY_EXPORT operator!=(const Point &, const Point &) noexcept;

/**
 * Struct StructWithArrayOfStructs
 */
struct TEST_TB_STRUCT_ARRAY_EXPORT StructWithArrayOfStructs
{
    StructWithArrayOfStructs();
    StructWithArrayOfStructs(const std::list<Point>& points);

    std::list<Point> points{};

};
bool TEST_TB_STRUCT_ARRAY_EXPORT operator==(const StructWithArrayOfStructs &, const StructWithArrayOfStructs &) noexcept;
bool TEST_TB_STRUCT_ARRAY_EXPORT operator!=(const StructWithArrayOfStructs &, const StructWithArrayOfStructs &) noexcept;

/**
 * Struct StructWithArrayOfEnums
 */
struct TEST_TB_STRUCT_ARRAY_EXPORT StructWithArrayOfEnums
{
    StructWithArrayOfEnums();
    StructWithArrayOfEnums(const std::list<TestEnumEnum>& tags);

    std::list<TestEnumEnum> tags{};

};
bool TEST_TB_STRUCT_ARRAY_EXPORT operator==(const StructWithArrayOfEnums &, const StructWithArrayOfEnums &) noexcept;
bool TEST_TB_STRUCT_ARRAY_EXPORT operator!=(const StructWithArrayOfEnums &, const StructWithArrayOfEnums &) noexcept;

/**
 * Struct StructWithArrayOfInts
 */
struct TEST_TB_STRUCT_ARRAY_EXPORT StructWithArrayOfInts
{
    StructWithArrayOfInts();
    StructWithArrayOfInts(const std::list<int>& values);

    std::list<int> values{};

};
bool TEST_TB_STRUCT_ARRAY_EXPORT operator==(const StructWithArrayOfInts &, const StructWithArrayOfInts &) noexcept;
bool TEST_TB_STRUCT_ARRAY_EXPORT operator!=(const StructWithArrayOfInts &, const StructWithArrayOfInts &) noexcept;

/**
 * Struct MixedStruct
 */
struct TEST_TB_STRUCT_ARRAY_EXPORT MixedStruct
{
    MixedStruct();
    MixedStruct(int id, const std::string& name, const Point& origin, const std::list<Point>& points, const std::list<TestEnumEnum>& flags, const std::list<int>& scores);

    int id{};
    std::string name{};
    Point origin{};
    std::list<Point> points{};
    std::list<TestEnumEnum> flags{};
    std::list<int> scores{};

};
bool TEST_TB_STRUCT_ARRAY_EXPORT operator==(const MixedStruct &, const MixedStruct &) noexcept;
bool TEST_TB_STRUCT_ARRAY_EXPORT operator!=(const MixedStruct &, const MixedStruct &) noexcept;
} // namespace TbStructArray
} // namespace Test
