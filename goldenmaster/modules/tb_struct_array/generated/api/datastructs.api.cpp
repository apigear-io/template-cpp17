#include "tb_struct_array/generated/api/datastructs.api.h"

namespace Test {
namespace TbStructArray {

// ********************************************************************
// Enumeration TestEnum
// ********************************************************************
TestEnumEnum toTestEnumEnum(std::uint8_t v, bool *ok)
{
    if (ok != nullptr) {
        *ok = true;
    }
    switch (v) {
        case 1: return TestEnumEnum::value1;
        case 2: return TestEnumEnum::value2;
        default:
            if (ok != nullptr) {
                *ok = false;
            }
            return TestEnumEnum::value1;
    }
}
// ********************************************************************
// Struct Point
// ********************************************************************
Point::Point() = default;
Point::Point(float x, float y):
    x(x),
    y(y)
{
}

bool operator==(const Point& lhs, const Point& rhs) noexcept
{
    return (
        // consider using fuzzy compare, check library ApiGear::Utilities::fuzzyCompare
        lhs.x == rhs.x &&
        // consider using fuzzy compare, check library ApiGear::Utilities::fuzzyCompare
        lhs.y == rhs.y

    );
}

bool operator!=(const Point& lhs, const Point& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct StructWithArrayOfStructs
// ********************************************************************
StructWithArrayOfStructs::StructWithArrayOfStructs() = default;
StructWithArrayOfStructs::StructWithArrayOfStructs(const std::list<Point>& points):
    points(points)
{
}

bool operator==(const StructWithArrayOfStructs& lhs, const StructWithArrayOfStructs& rhs) noexcept
{
    return (
        lhs.points == rhs.points

    );
}

bool operator!=(const StructWithArrayOfStructs& lhs, const StructWithArrayOfStructs& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct StructWithArrayOfEnums
// ********************************************************************
StructWithArrayOfEnums::StructWithArrayOfEnums() = default;
StructWithArrayOfEnums::StructWithArrayOfEnums(const std::list<TestEnumEnum>& tags):
    tags(tags)
{
}

bool operator==(const StructWithArrayOfEnums& lhs, const StructWithArrayOfEnums& rhs) noexcept
{
    return (
        lhs.tags == rhs.tags

    );
}

bool operator!=(const StructWithArrayOfEnums& lhs, const StructWithArrayOfEnums& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct StructWithArrayOfInts
// ********************************************************************
StructWithArrayOfInts::StructWithArrayOfInts() = default;
StructWithArrayOfInts::StructWithArrayOfInts(const std::list<int>& values):
    values(values)
{
}

bool operator==(const StructWithArrayOfInts& lhs, const StructWithArrayOfInts& rhs) noexcept
{
    return (
        lhs.values == rhs.values

    );
}

bool operator!=(const StructWithArrayOfInts& lhs, const StructWithArrayOfInts& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct MixedStruct
// ********************************************************************
MixedStruct::MixedStruct() = default;
MixedStruct::MixedStruct(int id, const std::string& name, const Point& origin, const std::list<Point>& points, const std::list<TestEnumEnum>& flags, const std::list<int>& scores):
    id(id),
    name(name),
    origin(origin),
    points(points),
    flags(flags),
    scores(scores)
{
}

bool operator==(const MixedStruct& lhs, const MixedStruct& rhs) noexcept
{
    return (
        lhs.id == rhs.id &&
        lhs.name == rhs.name &&
        lhs.origin == rhs.origin &&
        lhs.points == rhs.points &&
        lhs.flags == rhs.flags &&
        lhs.scores == rhs.scores

    );
}

bool operator!=(const MixedStruct& lhs, const MixedStruct& rhs) noexcept
{
    return !(lhs == rhs);
}
} // namespace TbStructArray
} // namespace Test
