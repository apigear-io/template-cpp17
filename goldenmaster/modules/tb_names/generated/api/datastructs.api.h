#pragma once

#include <cinttypes>
#include <string>
#include <list>

#include "tb_names/generated/api/common.h"

namespace Test {
namespace TbNames {

/**
 * Enumeration Enum_With_Under_scores
 */
enum class Enum_With_Under_scoresEnum {
    First_Value = 0,
    second_value = 1,
    third_Value = 2
};
TEST_TB_NAMES_EXPORT Enum_With_Under_scoresEnum toEnum_With_Under_scoresEnum(std::uint8_t v, bool *ok);
} // namespace TbNames
} // namespace Test
