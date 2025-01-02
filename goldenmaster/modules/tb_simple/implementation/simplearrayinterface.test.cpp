#include <memory>
#include "catch2/catch.hpp"
#include "tb_simple/implementation/simplearrayinterface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::TbSimple;
TEST_CASE("Testing SimpleArrayInterface", "[SimpleArrayInterface]"){
    std::unique_ptr<ISimpleArrayInterface> testSimpleArrayInterface = std::make_unique<SimpleArrayInterface>();
    // setup your test
    SECTION("Test operation funcBool") {
        // Do implement test here
        testSimpleArrayInterface->funcBool(std::list<bool>());
    }
    SECTION("Test operation funcInt") {
        // Do implement test here
        testSimpleArrayInterface->funcInt(std::list<int>());
    }
    SECTION("Test operation funcInt32") {
        // Do implement test here
        testSimpleArrayInterface->funcInt32(std::list<int32_t>());
    }
    SECTION("Test operation funcInt64") {
        // Do implement test here
        testSimpleArrayInterface->funcInt64(std::list<int64_t>());
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testSimpleArrayInterface->funcFloat(std::list<float>());
    }
    SECTION("Test operation funcFloat32") {
        // Do implement test here
        testSimpleArrayInterface->funcFloat32(std::list<float>());
    }
    SECTION("Test operation funcFloat64") {
        // Do implement test here
        testSimpleArrayInterface->funcFloat64(std::list<double>());
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testSimpleArrayInterface->funcString(std::list<std::string>());
    }
    SECTION("Test property propBool") {
        // Do implement test here
        testSimpleArrayInterface->setPropBool(std::list<bool>());
        auto actual = testSimpleArrayInterface->getPropBool();
        auto expected =  std::list<bool>();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testSimpleArrayInterface->setPropInt(std::list<int>());
        auto actual = testSimpleArrayInterface->getPropInt();
        auto expected =  std::list<int>();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propInt32") {
        // Do implement test here
        testSimpleArrayInterface->setPropInt32(std::list<int32_t>());
        auto actual = testSimpleArrayInterface->getPropInt32();
        auto expected =  std::list<int32_t>();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propInt64") {
        // Do implement test here
        testSimpleArrayInterface->setPropInt64(std::list<int64_t>());
        auto actual = testSimpleArrayInterface->getPropInt64();
        auto expected =  std::list<int64_t>();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testSimpleArrayInterface->setPropFloat(std::list<float>());
        auto actual = testSimpleArrayInterface->getPropFloat();
        auto expected =  std::list<float>();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propFloat32") {
        // Do implement test here
        testSimpleArrayInterface->setPropFloat32(std::list<float>());
        auto actual = testSimpleArrayInterface->getPropFloat32();
        auto expected =  std::list<float>();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propFloat64") {
        // Do implement test here
        testSimpleArrayInterface->setPropFloat64(std::list<double>());
        auto actual = testSimpleArrayInterface->getPropFloat64();
        auto expected =  std::list<double>();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propString") {
        // Do implement test here
        testSimpleArrayInterface->setPropString(std::list<std::string>());
        auto actual = testSimpleArrayInterface->getPropString();
        auto expected =  std::list<std::string>();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propReadOnlyString") {
        // Do implement test here
        auto actual = testSimpleArrayInterface->getPropReadOnlyString();
        auto expected =  std::string();
        REQUIRE(actual == expected);
    }
}
