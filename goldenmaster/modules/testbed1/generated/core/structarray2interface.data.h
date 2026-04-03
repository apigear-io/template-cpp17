#pragma once

#include "testbed1/generated/api/testbed1.h"


namespace Test
{
namespace Testbed1
{

/**
* A helper structure for implementations of StructArray2Interface. Stores all the properties.
*/
struct StructArray2InterfaceData
{
    StructBoolWithArray m_propBool {StructBoolWithArray()};
    StructIntWithArray m_propInt {StructIntWithArray()};
    StructFloatWithArray m_propFloat {StructFloatWithArray()};
    StructStringWithArray m_propString {StructStringWithArray()};
    StructEnumWithArray m_propEnum {StructEnumWithArray()};
};

}
}