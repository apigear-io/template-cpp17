#include "testbed1/generated/api/datastructs.api.h"

namespace Test {
namespace Testbed1 {

// ********************************************************************
// Enumeration Enum0
// ********************************************************************
Enum0Enum toEnum0Enum(std::uint8_t v, bool *ok)
{
    if (ok != nullptr) {
        *ok = true;
    }
    switch (v) {
        case 0: return Enum0Enum::value0;
        case 1: return Enum0Enum::value1;
        case 2: return Enum0Enum::value2;
        default:
            if (ok != nullptr) {
                *ok = false;
            }
            return Enum0Enum::value0;
    }
}
// ********************************************************************
// Struct StructBool
// ********************************************************************
StructBool::StructBool() = default;
StructBool::StructBool(bool fieldBool):
    fieldBool(fieldBool)
{
}

bool operator==(const StructBool& lhs, const StructBool& rhs) noexcept
{
    return (
        lhs.fieldBool == rhs.fieldBool

    );
}

bool operator!=(const StructBool& lhs, const StructBool& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct StructInt
// ********************************************************************
StructInt::StructInt() = default;
StructInt::StructInt(int fieldInt):
    fieldInt(fieldInt)
{
}

bool operator==(const StructInt& lhs, const StructInt& rhs) noexcept
{
    return (
        lhs.fieldInt == rhs.fieldInt

    );
}

bool operator!=(const StructInt& lhs, const StructInt& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct StructFloat
// ********************************************************************
StructFloat::StructFloat() = default;
StructFloat::StructFloat(float fieldFloat):
    fieldFloat(fieldFloat)
{
}

bool operator==(const StructFloat& lhs, const StructFloat& rhs) noexcept
{
    return (
        // consider using fuzzy compare, check library ApiGear::Utilities::fuzzyCompare
        lhs.fieldFloat == rhs.fieldFloat

    );
}

bool operator!=(const StructFloat& lhs, const StructFloat& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct StructString
// ********************************************************************
StructString::StructString() = default;
StructString::StructString(const std::string& fieldString):
    fieldString(fieldString)
{
}

bool operator==(const StructString& lhs, const StructString& rhs) noexcept
{
    return (
        lhs.fieldString == rhs.fieldString

    );
}

bool operator!=(const StructString& lhs, const StructString& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct StructStruct
// ********************************************************************
StructStruct::StructStruct() = default;
StructStruct::StructStruct(const StructString& fieldString):
    fieldString(fieldString)
{
}

bool operator==(const StructStruct& lhs, const StructStruct& rhs) noexcept
{
    return (
        lhs.fieldString == rhs.fieldString

    );
}

bool operator!=(const StructStruct& lhs, const StructStruct& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct StructEnum
// ********************************************************************
StructEnum::StructEnum() = default;
StructEnum::StructEnum(Enum0Enum fieldEnum):
    fieldEnum(fieldEnum)
{
}

bool operator==(const StructEnum& lhs, const StructEnum& rhs) noexcept
{
    return (
        lhs.fieldEnum == rhs.fieldEnum

    );
}

bool operator!=(const StructEnum& lhs, const StructEnum& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct StructBoolWithArray
// ********************************************************************
StructBoolWithArray::StructBoolWithArray() = default;
StructBoolWithArray::StructBoolWithArray(const std::list<bool>& fieldBool):
    fieldBool(fieldBool)
{
}

bool operator==(const StructBoolWithArray& lhs, const StructBoolWithArray& rhs) noexcept
{
    return (
        lhs.fieldBool == rhs.fieldBool

    );
}

bool operator!=(const StructBoolWithArray& lhs, const StructBoolWithArray& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct StructIntWithArray
// ********************************************************************
StructIntWithArray::StructIntWithArray() = default;
StructIntWithArray::StructIntWithArray(const std::list<int>& fieldInt):
    fieldInt(fieldInt)
{
}

bool operator==(const StructIntWithArray& lhs, const StructIntWithArray& rhs) noexcept
{
    return (
        lhs.fieldInt == rhs.fieldInt

    );
}

bool operator!=(const StructIntWithArray& lhs, const StructIntWithArray& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct StructFloatWithArray
// ********************************************************************
StructFloatWithArray::StructFloatWithArray() = default;
StructFloatWithArray::StructFloatWithArray(const std::list<float>& fieldFloat):
    fieldFloat(fieldFloat)
{
}

bool operator==(const StructFloatWithArray& lhs, const StructFloatWithArray& rhs) noexcept
{
    return (
        lhs.fieldFloat == rhs.fieldFloat

    );
}

bool operator!=(const StructFloatWithArray& lhs, const StructFloatWithArray& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct StructStringWithArray
// ********************************************************************
StructStringWithArray::StructStringWithArray() = default;
StructStringWithArray::StructStringWithArray(const std::list<std::string>& fieldString):
    fieldString(fieldString)
{
}

bool operator==(const StructStringWithArray& lhs, const StructStringWithArray& rhs) noexcept
{
    return (
        lhs.fieldString == rhs.fieldString

    );
}

bool operator!=(const StructStringWithArray& lhs, const StructStringWithArray& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct StructStructWithArray
// ********************************************************************
StructStructWithArray::StructStructWithArray() = default;
StructStructWithArray::StructStructWithArray(const std::list<StructStringWithArray>& fieldStruct):
    fieldStruct(fieldStruct)
{
}

bool operator==(const StructStructWithArray& lhs, const StructStructWithArray& rhs) noexcept
{
    return (
        lhs.fieldStruct == rhs.fieldStruct

    );
}

bool operator!=(const StructStructWithArray& lhs, const StructStructWithArray& rhs) noexcept
{
    return !(lhs == rhs);
}
// ********************************************************************
// Struct StructEnumWithArray
// ********************************************************************
StructEnumWithArray::StructEnumWithArray() = default;
StructEnumWithArray::StructEnumWithArray(const std::list<Enum0Enum>& fieldEnum):
    fieldEnum(fieldEnum)
{
}

bool operator==(const StructEnumWithArray& lhs, const StructEnumWithArray& rhs) noexcept
{
    return (
        lhs.fieldEnum == rhs.fieldEnum

    );
}

bool operator!=(const StructEnumWithArray& lhs, const StructEnumWithArray& rhs) noexcept
{
    return !(lhs == rhs);
}
} // namespace Testbed1
} // namespace Test
