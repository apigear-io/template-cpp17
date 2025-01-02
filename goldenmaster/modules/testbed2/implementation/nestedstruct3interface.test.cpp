#include <memory>
#include "catch2/catch.hpp"
#include "testbed2/implementation/nestedstruct3interface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::Testbed2;
TEST_CASE("Testing NestedStruct3Interface", "[NestedStruct3Interface]"){
    std::unique_ptr<INestedStruct3Interface> testNestedStruct3Interface = std::make_unique<NestedStruct3Interface>();
    // setup your test
    SECTION("Test operation func1") {
        // Do implement test here
        testNestedStruct3Interface->func1(NestedStruct1());
    }
    SECTION("Test operation func2") {
        // Do implement test here
        testNestedStruct3Interface->func2(NestedStruct1(), NestedStruct2());
    }
    SECTION("Test operation func3") {
        // Do implement test here
        testNestedStruct3Interface->func3(NestedStruct1(), NestedStruct2(), NestedStruct3());
    }
    SECTION("Test property prop1") {
        // Do implement test here
        testNestedStruct3Interface->setProp1(NestedStruct1());
        auto actual = testNestedStruct3Interface->getProp1();
        auto expected =  NestedStruct1();
        REQUIRE(actual == expected);
    }
    SECTION("Test property prop2") {
        // Do implement test here
        testNestedStruct3Interface->setProp2(NestedStruct2());
        auto actual = testNestedStruct3Interface->getProp2();
        auto expected =  NestedStruct2();
        REQUIRE(actual == expected);
    }
    SECTION("Test property prop3") {
        // Do implement test here
        testNestedStruct3Interface->setProp3(NestedStruct3());
        auto actual = testNestedStruct3Interface->getProp3();
        auto expected =  NestedStruct3();
        REQUIRE(actual == expected);
    }
}
