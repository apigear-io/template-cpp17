#include "tb_names/generated/api/datastructs.api.h"

namespace Test {
namespace TbNames {

// ********************************************************************
// Enumeration Enum_With_Under_scores
// ********************************************************************
Enum_With_Under_scoresEnum toEnum_With_Under_scoresEnum(std::uint8_t v, bool *ok)
{
    if (ok != nullptr) {
        *ok = true;
    }
    switch (v) {
        case 0: return Enum_With_Under_scoresEnum::First_Value;
        case 1: return Enum_With_Under_scoresEnum::second_value;
        case 2: return Enum_With_Under_scoresEnum::third_Value;
        default:
            if (ok != nullptr) {
                *ok = false;
            }
            return Enum_With_Under_scoresEnum::First_Value;
    }
}
} // namespace TbNames
} // namespace Test
