#pragma once

#include "testbed1/generated/api/testbed1.h"


namespace Test
{
namespace Testbed1
{

/**
* A helper structure for implementations of StructArrayInterface. Stores all the properties.
*/
struct StructArrayInterfaceData
{
    std::list<StructBool> m_propBool {std::list<StructBool>()};
    std::list<StructInt> m_propInt {std::list<StructInt>()};
    std::list<StructFloat> m_propFloat {std::list<StructFloat>()};
    std::list<StructString> m_propString {std::list<StructString>()};
    std::list<Enum0Enum> m_propEnum {std::list<Enum0Enum>()};
};

}
}