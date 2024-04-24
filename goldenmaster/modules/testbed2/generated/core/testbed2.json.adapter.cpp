#include "testbed2/generated/core/testbed2.json.adapter.h"

namespace Test {
namespace Testbed2 {
void from_json(const nlohmann::json& j, Struct1& p) {
    p = Struct1(
        j.at("field1").get<int>()
    );
}
void to_json(nlohmann::json& j, const Struct1& p) {
    j = nlohmann::json{
        {"field1", p.field1}
        };
}

std::ostream& operator<<(std::ostream& os, const Struct1& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, Struct2& p) {
    p = Struct2(
        j.at("field1").get<int>(),
        j.at("field2").get<int>()
    );
}
void to_json(nlohmann::json& j, const Struct2& p) {
    j = nlohmann::json{
        {"field1", p.field1},
        {"field2", p.field2}
        };
}

std::ostream& operator<<(std::ostream& os, const Struct2& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, Struct3& p) {
    p = Struct3(
        j.at("field1").get<int>(),
        j.at("field2").get<int>(),
        j.at("field3").get<int>()
    );
}
void to_json(nlohmann::json& j, const Struct3& p) {
    j = nlohmann::json{
        {"field1", p.field1},
        {"field2", p.field2},
        {"field3", p.field3}
        };
}

std::ostream& operator<<(std::ostream& os, const Struct3& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, Struct4& p) {
    p = Struct4(
        j.at("field1").get<int>(),
        j.at("field2").get<int>(),
        j.at("field3").get<int>(),
        j.at("field4").get<int>()
    );
}
void to_json(nlohmann::json& j, const Struct4& p) {
    j = nlohmann::json{
        {"field1", p.field1},
        {"field2", p.field2},
        {"field3", p.field3},
        {"field4", p.field4}
        };
}

std::ostream& operator<<(std::ostream& os, const Struct4& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, NestedStruct1& p) {
    p = NestedStruct1(
        j.at("field1").get<Struct1>()
    );
}
void to_json(nlohmann::json& j, const NestedStruct1& p) {
    j = nlohmann::json{
        {"field1", p.field1}
        };
}

std::ostream& operator<<(std::ostream& os, const NestedStruct1& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, NestedStruct2& p) {
    p = NestedStruct2(
        j.at("field1").get<Struct1>(),
        j.at("field2").get<Struct2>()
    );
}
void to_json(nlohmann::json& j, const NestedStruct2& p) {
    j = nlohmann::json{
        {"field1", p.field1},
        {"field2", p.field2}
        };
}

std::ostream& operator<<(std::ostream& os, const NestedStruct2& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
void from_json(const nlohmann::json& j, NestedStruct3& p) {
    p = NestedStruct3(
        j.at("field1").get<Struct1>(),
        j.at("field2").get<Struct2>(),
        j.at("field3").get<Struct3>()
    );
}
void to_json(nlohmann::json& j, const NestedStruct3& p) {
    j = nlohmann::json{
        {"field1", p.field1},
        {"field2", p.field2},
        {"field3", p.field3}
        };
}

std::ostream& operator<<(std::ostream& os, const NestedStruct3& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
} // namespace Testbed2
} // namespace Test
