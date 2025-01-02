#include <memory>
#include "catch2/catch.hpp"
#include "tb_simple/implementation/simpleinterface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::TbSimple;
TEST_CASE("Testing SimpleInterface", "[SimpleInterface]"){
    std::unique_ptr<ISimpleInterface> testSimpleInterface = std::make_unique<SimpleInterface>();
    // setup your test
    SECTION("Test operation funcNoReturnValue") {
        // Do implement test here
        testSimpleInterface->funcNoReturnValue(false);
    }
    SECTION("Test operation funcBool") {
        // Do implement test here
        testSimpleInterface->funcBool(false);
    }
    SECTION("Test operation funcInt") {
        // Do implement test here
        testSimpleInterface->funcInt(0);
    }
    SECTION("Test operation funcInt32") {
        // Do implement test here
        testSimpleInterface->funcInt32(0);
    }
    SECTION("Test operation funcInt64") {
        // Do implement test here
        testSimpleInterface->funcInt64(0LL);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testSimpleInterface->funcFloat(0.0f);
    }
    SECTION("Test operation funcFloat32") {
        // Do implement test here
        testSimpleInterface->funcFloat32(0.0f);
    }
    SECTION("Test operation funcFloat64") {
        // Do implement test here
        testSimpleInterface->funcFloat64(0.0);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testSimpleInterface->funcString(std::string());
    }
    SECTION("Test property propBool") {
        // Do implement test here
        testSimpleInterface->setPropBool(false);
        auto actual = testSimpleInterface->getPropBool();
        auto expected =  false;
        REQUIRE(actual == expected);
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testSimpleInterface->setPropInt(0);
        auto actual = testSimpleInterface->getPropInt();
        auto expected =  0;
        REQUIRE(actual == expected);
    }
    SECTION("Test property propInt32") {
        // Do implement test here
        testSimpleInterface->setPropInt32(0);
        auto actual = testSimpleInterface->getPropInt32();
        auto expected =  0;
        REQUIRE(actual == expected);
    }
    SECTION("Test property propInt64") {
        // Do implement test here
        testSimpleInterface->setPropInt64(0LL);
        auto actual = testSimpleInterface->getPropInt64();
        auto expected =  0LL;
        REQUIRE(actual == expected);
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testSimpleInterface->setPropFloat(0.0f);
        auto actual = testSimpleInterface->getPropFloat();
        auto expected =  0.0f;
        REQUIRE(ApiGear::Utilities::fuzzyCompare(actual, expected));
    }
    SECTION("Test property propFloat32") {
        // Do implement test here
        testSimpleInterface->setPropFloat32(0.0f);
        auto actual = testSimpleInterface->getPropFloat32();
        auto expected =  0.0f;
        REQUIRE(ApiGear::Utilities::fuzzyCompare(actual, expected));
    }
    SECTION("Test property propFloat64") {
        // Do implement test here
        testSimpleInterface->setPropFloat64(0.0);
        auto actual = testSimpleInterface->getPropFloat64();
        auto expected =  0.0;
        REQUIRE(ApiGear::Utilities::fuzzyCompare(actual, expected));
    }
    SECTION("Test property propString") {
        // Do implement test here
        testSimpleInterface->setPropString(std::string());
        auto actual = testSimpleInterface->getPropString();
        auto expected =  std::string();
        REQUIRE(actual == expected);
    }
}
