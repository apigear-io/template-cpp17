#include "tb_same2/generated/api/datastructs.api.h"
#include "apigear/utilities/fuzzy_compare.h"

namespace Test {
namespace TbSame2 {

// ********************************************************************
// Enumeration Enum1
// ********************************************************************
Enum1Enum toEnum1Enum(std::uint8_t v, bool *ok)
{
    if (ok != nullptr) {
        *ok = true;
    }
    switch (v) {
        case 1: return Enum1Enum::value1;
        case 2: return Enum1Enum::value2;
        default:
            if (ok != nullptr) {
                *ok = false;
            }
            return Enum1Enum::value1;
    }
}

// ********************************************************************
// Enumeration Enum2
// ********************************************************************
Enum2Enum toEnum2Enum(std::uint8_t v, bool *ok)
{
    if (ok != nullptr) {
        *ok = true;
    }
    switch (v) {
        case 1: return Enum2Enum::value1;
        case 2: return Enum2Enum::value2;
        default:
            if (ok != nullptr) {
                *ok = false;
            }
            return Enum2Enum::value1;
    }
}
// ********************************************************************
// Struct Struct1
// ********************************************************************
Struct1::Struct1() = default;
Struct1::Struct1(int field1, int field2, int field3):
    field1(field1),
    field2(field2),
    field3(field3)
{
}

bool operator==(const Struct1& lhs, const Struct1& rhs) noexcept
{
    return (
        lhs.field1 == rhs.field1 &&
        lhs.field2 == rhs.field2 &&
        lhs.field3 == rhs.field3

    );
}

bool operator!=(const Struct1& lhs, const Struct1& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct Struct2
// ********************************************************************
Struct2::Struct2() = default;
Struct2::Struct2(int field1, int field2, int field3):
    field1(field1),
    field2(field2),
    field3(field3)
{
}

bool operator==(const Struct2& lhs, const Struct2& rhs) noexcept
{
    return (
        lhs.field1 == rhs.field1 &&
        lhs.field2 == rhs.field2 &&
        lhs.field3 == rhs.field3

    );
}

bool operator!=(const Struct2& lhs, const Struct2& rhs) noexcept
{
    return !(lhs == rhs);
}
} // namespace TbSame2
} // namespace Test
