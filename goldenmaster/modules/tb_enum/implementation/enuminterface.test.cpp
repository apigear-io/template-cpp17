#include <memory>
#include "catch2/catch.hpp"
#include "tb_enum/implementation/enuminterface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::TbEnum;
TEST_CASE("Testing EnumInterface", "[EnumInterface]"){
    std::unique_ptr<IEnumInterface> testEnumInterface = std::make_unique<EnumInterface>();
    // setup your test
    SECTION("Test operation func0") {
        // Do implement test here
        testEnumInterface->func0(Enum0Enum::value0);
    }
    SECTION("Test operation func1") {
        // Do implement test here
        testEnumInterface->func1(Enum1Enum::value1);
    }
    SECTION("Test operation func2") {
        // Do implement test here
        testEnumInterface->func2(Enum2Enum::value2);
    }
    SECTION("Test operation func3") {
        // Do implement test here
        testEnumInterface->func3(Enum3Enum::value3);
    }
    SECTION("Test property prop0") {
        // Do implement test here
        testEnumInterface->setProp0(Enum0Enum::value0);
        auto actual = testEnumInterface->getProp0();
        auto expected =  Enum0Enum::value0;
        REQUIRE(actual == expected);
    }
    SECTION("Test property prop1") {
        // Do implement test here
        testEnumInterface->setProp1(Enum1Enum::value1);
        auto actual = testEnumInterface->getProp1();
        auto expected =  Enum1Enum::value1;
        REQUIRE(actual == expected);
    }
    SECTION("Test property prop2") {
        // Do implement test here
        testEnumInterface->setProp2(Enum2Enum::value2);
        auto actual = testEnumInterface->getProp2();
        auto expected =  Enum2Enum::value2;
        REQUIRE(actual == expected);
    }
    SECTION("Test property prop3") {
        // Do implement test here
        testEnumInterface->setProp3(Enum3Enum::value3);
        auto actual = testEnumInterface->getProp3();
        auto expected =  Enum3Enum::value3;
        REQUIRE(actual == expected);
    }
}
