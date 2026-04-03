#include "tb_struct_array/generated/core/tb_struct_array.json.adapter.h"

namespace Test {
namespace TbStructArray {
void from_json(const nlohmann::json& j, Point& p) {
    p = Point(
        j.at("x").get<float>(),
        j.at("y").get<float>()
    );
}
void to_json(nlohmann::json& j, const Point& p) {
    j = nlohmann::json{
        {"x", p.x},
        {"y", p.y}
        };
}

std::ostream& operator<<(std::ostream& os, const Point& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, StructWithArrayOfStructs& p) {
    p = StructWithArrayOfStructs(
        j.at("points").get<std::list<Point>>()
    );
}
void to_json(nlohmann::json& j, const StructWithArrayOfStructs& p) {
    j = nlohmann::json{
        {"points", p.points}
        };
}

std::ostream& operator<<(std::ostream& os, const StructWithArrayOfStructs& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, StructWithArrayOfEnums& p) {
    p = StructWithArrayOfEnums(
        j.at("tags").get<std::list<TestEnumEnum>>()
    );
}
void to_json(nlohmann::json& j, const StructWithArrayOfEnums& p) {
    j = nlohmann::json{
        {"tags", p.tags}
        };
}

std::ostream& operator<<(std::ostream& os, const StructWithArrayOfEnums& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, StructWithArrayOfInts& p) {
    p = StructWithArrayOfInts(
        j.at("values").get<std::list<int>>()
    );
}
void to_json(nlohmann::json& j, const StructWithArrayOfInts& p) {
    j = nlohmann::json{
        {"values", p.values}
        };
}

std::ostream& operator<<(std::ostream& os, const StructWithArrayOfInts& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, MixedStruct& p) {
    p = MixedStruct(
        j.at("id").get<int>(),
        j.at("name").get<std::string>(),
        j.at("origin").get<Point>(),
        j.at("points").get<std::list<Point>>(),
        j.at("flags").get<std::list<TestEnumEnum>>(),
        j.at("scores").get<std::list<int>>()
    );
}
void to_json(nlohmann::json& j, const MixedStruct& p) {
    j = nlohmann::json{
        {"id", p.id},
        {"name", p.name},
        {"origin", p.origin},
        {"points", p.points},
        {"flags", p.flags},
        {"scores", p.scores}
        };
}

std::ostream& operator<<(std::ostream& os, const MixedStruct& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
} // namespace TbStructArray
} // namespace Test
