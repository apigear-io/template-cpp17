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
void from_json(const nlohmann::json& j, StructStruct& p) {
    p = StructStruct(
        j.at("fieldString").get<StructString>()
    );
}
void to_json(nlohmann::json& j, const StructStruct& p) {
    j = nlohmann::json{
        {"fieldString", p.fieldString}
        };
}

std::ostream& operator<<(std::ostream& os, const StructStruct& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, StructEnum& p) {
    p = StructEnum(
        j.at("fieldEnum").get<Enum0Enum>()
    );
}
void to_json(nlohmann::json& j, const StructEnum& p) {
    j = nlohmann::json{
        {"fieldEnum", p.fieldEnum}
        };
}

std::ostream& operator<<(std::ostream& os, const StructEnum& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, StructBoolWithArray& p) {
    p = StructBoolWithArray(
        j.at("fieldBool").get<std::list<bool>>()
    );
}
void to_json(nlohmann::json& j, const StructBoolWithArray& p) {
    j = nlohmann::json{
        {"fieldBool", p.fieldBool}
        };
}

std::ostream& operator<<(std::ostream& os, const StructBoolWithArray& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, StructIntWithArray& p) {
    p = StructIntWithArray(
        j.at("fieldInt").get<std::list<int>>()
    );
}
void to_json(nlohmann::json& j, const StructIntWithArray& p) {
    j = nlohmann::json{
        {"fieldInt", p.fieldInt}
        };
}

std::ostream& operator<<(std::ostream& os, const StructIntWithArray& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, StructFloatWithArray& p) {
    p = StructFloatWithArray(
        j.at("fieldFloat").get<std::list<float>>()
    );
}
void to_json(nlohmann::json& j, const StructFloatWithArray& p) {
    j = nlohmann::json{
        {"fieldFloat", p.fieldFloat}
        };
}

std::ostream& operator<<(std::ostream& os, const StructFloatWithArray& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, StructStringWithArray& p) {
    p = StructStringWithArray(
        j.at("fieldString").get<std::list<std::string>>()
    );
}
void to_json(nlohmann::json& j, const StructStringWithArray& p) {
    j = nlohmann::json{
        {"fieldString", p.fieldString}
        };
}

std::ostream& operator<<(std::ostream& os, const StructStringWithArray& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, StructStructWithArray& p) {
    p = StructStructWithArray(
        j.at("fieldStruct").get<std::list<StructStringWithArray>>()
    );
}
void to_json(nlohmann::json& j, const StructStructWithArray& p) {
    j = nlohmann::json{
        {"fieldStruct", p.fieldStruct}
        };
}

std::ostream& operator<<(std::ostream& os, const StructStructWithArray& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, StructEnumWithArray& p) {
    p = StructEnumWithArray(
        j.at("fieldEnum").get<std::list<Enum0Enum>>()
    );
}
void to_json(nlohmann::json& j, const StructEnumWithArray& p) {
    j = nlohmann::json{
        {"fieldEnum", p.fieldEnum}
        };
}

std::ostream& operator<<(std::ostream& os, const StructEnumWithArray& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
} // namespace Testbed1
} // namespace Test
