#include "custom_types/generated/api/datastructs.api.h"

namespace Test {
namespace CustomTypes {
// ********************************************************************
// Struct Vector3D
// ********************************************************************
Vector3D::Vector3D() = default;
Vector3D::Vector3D(float x, float y, float z):
    x(x),
    y(y),
    z(z)
{
}

bool operator==(const Vector3D& lhs, const Vector3D& rhs) noexcept
{
    return (
        lhs.x == rhs.x &&
        lhs.y == rhs.y &&
        lhs.z == rhs.z

    );
}

bool operator!=(const Vector3D& lhs, const Vector3D& rhs) noexcept
{
    return !(lhs == rhs);
}
} // namespace CustomTypes
} // namespace Test
