#include "custom_types/generated/core/custom_types.json.adapter.h"

namespace Test {
namespace CustomTypes {
void from_json(const nlohmann::json& j, Vector3D& p) {
    p = Vector3D(
        j.at("x").get<float>(),
        j.at("y").get<float>(),
        j.at("z").get<float>()
    );
}
void to_json(nlohmann::json& j, const Vector3D& p) {
    j = nlohmann::json{
        {"x", p.x},
        {"y", p.y},
        {"z", p.z}
        };
}

std::ostream& operator<<(std::ostream& os, const Vector3D& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
} // namespace CustomTypes
} // namespace Test
