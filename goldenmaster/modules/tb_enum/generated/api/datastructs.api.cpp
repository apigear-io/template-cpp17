#include "tb_enum/generated/api/datastructs.api.h"
#include "apigear/utilities/fuzzy_compare.h"

namespace Test {
namespace TbEnum {

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
        case 2: return Enum2Enum::value2;
        case 1: return Enum2Enum::value1;
        case 0: return Enum2Enum::value0;
        default:
            if (ok != nullptr) {
                *ok = false;
            }
            return Enum2Enum::value2;
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
        case 3: return Enum3Enum::value3;
        case 2: return Enum3Enum::value2;
        case 1: return Enum3Enum::value1;
        default:
            if (ok != nullptr) {
                *ok = false;
            }
            return Enum3Enum::value3;
    }
}
} // namespace TbEnum
} // namespace Test
