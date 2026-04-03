#pragma once

#include <cinttypes>
#include <string>
#include <list>

#include "testbed1/generated/api/common.h"

namespace Test {
namespace Testbed1 {
struct StructBool;
struct StructInt;
struct StructFloat;
struct StructString;
struct StructStruct;
struct StructEnum;
struct StructBoolWithArray;
struct StructIntWithArray;
struct StructFloatWithArray;
struct StructStringWithArray;
struct StructStructWithArray;
struct StructEnumWithArray;

/**
 * Enumeration Enum0
 */
enum class Enum0Enum {
    value0 = 0,
    value1 = 1,
    value2 = 2
};
TEST_TESTBED1_EXPORT Enum0Enum toEnum0Enum(std::uint8_t v, bool *ok);

/**
 * Struct StructBool
 */
struct TEST_TESTBED1_EXPORT StructBool
{
    StructBool();
    StructBool(bool fieldBool);

    bool fieldBool{};

};
bool TEST_TESTBED1_EXPORT operator==(const StructBool &, const StructBool &) noexcept;
bool TEST_TESTBED1_EXPORT operator!=(const StructBool &, const StructBool &) noexcept;

/**
 * Struct StructInt
 */
struct TEST_TESTBED1_EXPORT StructInt
{
    StructInt();
    StructInt(int fieldInt);

    int fieldInt{};

};
bool TEST_TESTBED1_EXPORT operator==(const StructInt &, const StructInt &) noexcept;
bool TEST_TESTBED1_EXPORT operator!=(const StructInt &, const StructInt &) noexcept;

/**
 * Struct StructFloat
 */
struct TEST_TESTBED1_EXPORT StructFloat
{
    StructFloat();
    StructFloat(float fieldFloat);

    float fieldFloat{};

};
bool TEST_TESTBED1_EXPORT operator==(const StructFloat &, const StructFloat &) noexcept;
bool TEST_TESTBED1_EXPORT operator!=(const StructFloat &, const StructFloat &) noexcept;

/**
 * Struct StructString
 */
struct TEST_TESTBED1_EXPORT StructString
{
    StructString();
    StructString(const std::string& fieldString);

    std::string fieldString{};

};
bool TEST_TESTBED1_EXPORT operator==(const StructString &, const StructString &) noexcept;
bool TEST_TESTBED1_EXPORT operator!=(const StructString &, const StructString &) noexcept;

/**
 * Struct StructStruct
 */
struct TEST_TESTBED1_EXPORT StructStruct
{
    StructStruct();
    StructStruct(const StructString& fieldString);

    StructString fieldString{};

};
bool TEST_TESTBED1_EXPORT operator==(const StructStruct &, const StructStruct &) noexcept;
bool TEST_TESTBED1_EXPORT operator!=(const StructStruct &, const StructStruct &) noexcept;

/**
 * Struct StructEnum
 */
struct TEST_TESTBED1_EXPORT StructEnum
{
    StructEnum();
    StructEnum(Enum0Enum fieldEnum);

    Enum0Enum fieldEnum{};

};
bool TEST_TESTBED1_EXPORT operator==(const StructEnum &, const StructEnum &) noexcept;
bool TEST_TESTBED1_EXPORT operator!=(const StructEnum &, const StructEnum &) noexcept;

/**
 * Struct StructBoolWithArray
 */
struct TEST_TESTBED1_EXPORT StructBoolWithArray
{
    StructBoolWithArray();
    StructBoolWithArray(const std::list<bool>& fieldBool);

    std::list<bool> fieldBool{};

};
bool TEST_TESTBED1_EXPORT operator==(const StructBoolWithArray &, const StructBoolWithArray &) noexcept;
bool TEST_TESTBED1_EXPORT operator!=(const StructBoolWithArray &, const StructBoolWithArray &) noexcept;

/**
 * Struct StructIntWithArray
 */
struct TEST_TESTBED1_EXPORT StructIntWithArray
{
    StructIntWithArray();
    StructIntWithArray(const std::list<int>& fieldInt);

    std::list<int> fieldInt{};

};
bool TEST_TESTBED1_EXPORT operator==(const StructIntWithArray &, const StructIntWithArray &) noexcept;
bool TEST_TESTBED1_EXPORT operator!=(const StructIntWithArray &, const StructIntWithArray &) noexcept;

/**
 * Struct StructFloatWithArray
 */
struct TEST_TESTBED1_EXPORT StructFloatWithArray
{
    StructFloatWithArray();
    StructFloatWithArray(const std::list<float>& fieldFloat);

    std::list<float> fieldFloat{};

};
bool TEST_TESTBED1_EXPORT operator==(const StructFloatWithArray &, const StructFloatWithArray &) noexcept;
bool TEST_TESTBED1_EXPORT operator!=(const StructFloatWithArray &, const StructFloatWithArray &) noexcept;

/**
 * Struct StructStringWithArray
 */
struct TEST_TESTBED1_EXPORT StructStringWithArray
{
    StructStringWithArray();
    StructStringWithArray(const std::list<std::string>& fieldString);

    std::list<std::string> fieldString{};

};
bool TEST_TESTBED1_EXPORT operator==(const StructStringWithArray &, const StructStringWithArray &) noexcept;
bool TEST_TESTBED1_EXPORT operator!=(const StructStringWithArray &, const StructStringWithArray &) noexcept;

/**
 * Struct StructStructWithArray
 */
struct TEST_TESTBED1_EXPORT StructStructWithArray
{
    StructStructWithArray();
    StructStructWithArray(const std::list<StructStringWithArray>& fieldStruct);

    std::list<StructStringWithArray> fieldStruct{};

};
bool TEST_TESTBED1_EXPORT operator==(const StructStructWithArray &, const StructStructWithArray &) noexcept;
bool TEST_TESTBED1_EXPORT operator!=(const StructStructWithArray &, const StructStructWithArray &) noexcept;

/**
 * Struct StructEnumWithArray
 */
struct TEST_TESTBED1_EXPORT StructEnumWithArray
{
    StructEnumWithArray();
    StructEnumWithArray(const std::list<Enum0Enum>& fieldEnum);

    std::list<Enum0Enum> fieldEnum{};

};
bool TEST_TESTBED1_EXPORT operator==(const StructEnumWithArray &, const StructEnumWithArray &) noexcept;
bool TEST_TESTBED1_EXPORT operator!=(const StructEnumWithArray &, const StructEnumWithArray &) noexcept;
} // namespace Testbed1
} // namespace Test
