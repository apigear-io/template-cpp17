#include "testbed1/generated/core/testbed1.json.adapter.h"

namespace Test {
namespace Testbed1 {
void from_json(const nlohmann::json& j, StructBool& p) {
    p = StructBool(
        j.at("fieldBool").get<bool>()
    );
}
void to_json(nlohmann::json& j, const StructBool& p) {
    j = nlohmann::json{
        {"fieldBool", p.fieldBool}
        };
}

std::ostream& operator<<(std::ostream& os, const StructBool& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, StructInt& p) {
    p = StructInt(
        j.at("fieldInt").get<int>()
    );
}
void to_json(nlohmann::json& j, const StructInt& p) {
    j = nlohmann::json{
        {"fieldInt", p.fieldInt}
        };
}

std::ostream& operator<<(std::ostream& os, const StructInt& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, StructFloat& p) {
    p = StructFloat(
        j.at("fieldFloat").get<float>()
    );
}
void to_json(nlohmann::json& j, const StructFloat& p) {
    j = nlohmann::json{
        {"fieldFloat", p.fieldFloat}
        };
}

std::ostream& operator<<(std::ostream& os, const StructFloat& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, StructString& p) {
    p = StructString(
        j.at("fieldString").get<std::string>()
    );
}
void to_json(nlohmann::json& j, const StructString& p) {
    j = nlohmann::json{
        {"fieldString", p.fieldString}
        };
}

std::ostream& operator<<(std::ostream& os, const StructString& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
} // namespace Testbed1
} // namespace Test
