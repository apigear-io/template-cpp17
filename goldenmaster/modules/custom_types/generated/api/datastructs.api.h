#pragma once

#include <cinttypes>
#include <string>
#include <list>

#include "custom_types/generated/api/common.h"

namespace Test {
namespace CustomTypes {
struct Vector3D;

/**
 * Struct Vector3D
 */
struct TEST_CUSTOM_TYPES_EXPORT Vector3D
{
    Vector3D();
    Vector3D(float x, float y, float z);

    float x{};
    float y{};
    float z{};

};
bool TEST_CUSTOM_TYPES_EXPORT operator==(const Vector3D &, const Vector3D &) noexcept;
bool TEST_CUSTOM_TYPES_EXPORT operator!=(const Vector3D &, const Vector3D &) noexcept;
} // namespace CustomTypes
} // namespace Test
