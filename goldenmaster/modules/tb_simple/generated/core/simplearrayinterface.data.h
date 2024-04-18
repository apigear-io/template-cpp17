#pragma once

#include "tb_simple/generated/api/tb_simple.h"


namespace Test
{
namespace TbSimple
{

/**
* A helper structure for implementations of SimpleArrayInterface. Stores all the properties.
*/
struct SimpleArrayInterfaceData
{
    std::list<bool> m_propBool {std::list<bool>()};
    std::list<int> m_propInt {std::list<int>()};
    std::list<int32_t> m_propInt32 {std::list<int32_t>()};
    std::list<int64_t> m_propInt64 {std::list<int64_t>()};
    std::list<float> m_propFloat {std::list<float>()};
    std::list<float> m_propFloat32 {std::list<float>()};
    std::list<double> m_propFloat64 {std::list<double>()};
    std::list<std::string> m_propString {std::list<std::string>()};
    std::string m_propReadOnlyString {std::string()};
};

}
}