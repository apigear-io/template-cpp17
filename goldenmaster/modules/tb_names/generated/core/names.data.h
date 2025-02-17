#pragma once

#include "tb_names/generated/api/tb_names.h"


namespace Test
{
namespace TbNames
{

/**
* A helper structure for implementations of Nam_Es. Stores all the properties.
*/
struct NamEsData
{
    bool m_Switch {false};
    int m_SOME_PROPERTY {0};
    int m_Some_Poperty2 {0};
    Enum_With_Under_scoresEnum m_enum_property {Enum_With_Under_scoresEnum::First_Value};
};

}
}