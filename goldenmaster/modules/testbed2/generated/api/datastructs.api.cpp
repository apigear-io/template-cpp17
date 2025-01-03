#include "testbed2/generated/api/datastructs.api.h"
#include "apigear/utilities/fuzzy_compare.h"

namespace Test {
namespace Testbed2 {

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
        case 3: return Enum1Enum::value3;
        case 4: return Enum1Enum::value4;
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
        case 3: return Enum2Enum::value3;
        case 4: return Enum2Enum::value4;
        default:
            if (ok != nullptr) {
                *ok = false;
            }
            return Enum2Enum::value1;
    }
}

// ********************************************************************
// Enumeration Enum3
// ********************************************************************
Enum3Enum toEnum3Enum(std::uint8_t v, bool *ok)
{
    if (ok != nullptr) {
        *ok = true;
    }
    switch (v) {
        case 1: return Enum3Enum::value1;
        case 2: return Enum3Enum::value2;
        case 3: return Enum3Enum::value3;
        case 4: return Enum3Enum::value4;
        default:
            if (ok != nullptr) {
                *ok = false;
            }
            return Enum3Enum::value1;
    }
}
// ********************************************************************
// Struct Struct1
// ********************************************************************
Struct1::Struct1() = default;
Struct1::Struct1(int field1):
    field1(field1)
{
}

bool operator==(const Struct1& lhs, const Struct1& rhs) noexcept
{
    return (
        lhs.field1 == rhs.field1

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
Struct2::Struct2(int field1, int field2):
    field1(field1),
    field2(field2)
{
}

bool operator==(const Struct2& lhs, const Struct2& rhs) noexcept
{
    return (
        lhs.field1 == rhs.field1 &&
        lhs.field2 == rhs.field2

    );
}

bool operator!=(const Struct2& lhs, const Struct2& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct Struct3
// ********************************************************************
Struct3::Struct3() = default;
Struct3::Struct3(int field1, int field2, int field3):
    field1(field1),
    field2(field2),
    field3(field3)
{
}

bool operator==(const Struct3& lhs, const Struct3& rhs) noexcept
{
    return (
        lhs.field1 == rhs.field1 &&
        lhs.field2 == rhs.field2 &&
        lhs.field3 == rhs.field3

    );
}

bool operator!=(const Struct3& lhs, const Struct3& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct Struct4
// ********************************************************************
Struct4::Struct4() = default;
Struct4::Struct4(int field1, int field2, int field3, int field4):
    field1(field1),
    field2(field2),
    field3(field3),
    field4(field4)
{
}

bool operator==(const Struct4& lhs, const Struct4& rhs) noexcept
{
    return (
        lhs.field1 == rhs.field1 &&
        lhs.field2 == rhs.field2 &&
        lhs.field3 == rhs.field3 &&
        lhs.field4 == rhs.field4

    );
}

bool operator!=(const Struct4& lhs, const Struct4& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct NestedStruct1
// ********************************************************************
NestedStruct1::NestedStruct1() = default;
NestedStruct1::NestedStruct1(const Struct1& field1):
    field1(field1)
{
}

bool operator==(const NestedStruct1& lhs, const NestedStruct1& rhs) noexcept
{
    return (
        lhs.field1 == rhs.field1

    );
}

bool operator!=(const NestedStruct1& lhs, const NestedStruct1& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct NestedStruct2
// ********************************************************************
NestedStruct2::NestedStruct2() = default;
NestedStruct2::NestedStruct2(const Struct1& field1, const Struct2& field2):
    field1(field1),
    field2(field2)
{
}

bool operator==(const NestedStruct2& lhs, const NestedStruct2& rhs) noexcept
{
    return (
        lhs.field1 == rhs.field1 &&
        lhs.field2 == rhs.field2

    );
}

bool operator!=(const NestedStruct2& lhs, const NestedStruct2& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct NestedStruct3
// ********************************************************************
NestedStruct3::NestedStruct3() = default;
NestedStruct3::NestedStruct3(const Struct1& field1, const Struct2& field2, const Struct3& field3):
    field1(field1),
    field2(field2),
    field3(field3)
{
}

bool operator==(const NestedStruct3& lhs, const NestedStruct3& rhs) noexcept
{
    return (
        lhs.field1 == rhs.field1 &&
        lhs.field2 == rhs.field2 &&
        lhs.field3 == rhs.field3

    );
}

bool operator!=(const NestedStruct3& lhs, const NestedStruct3& rhs) noexcept
{
    return !(lhs == rhs);
}
} // namespace Testbed2
} // namespace Test
