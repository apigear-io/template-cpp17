#include <memory>
#include "catch2/catch.hpp"
#include "tb_names/implementation/names.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::TbNames;
TEST_CASE("Testing NamEs", "[NamEs]"){
    std::unique_ptr<INamEs> testNamEs = std::make_unique<NamEs>();
    // setup your test
    SECTION("Test operation SOME_FUNCTION") {
        // Do implement test here
        testNamEs->sOME_FUNCTION(false);
    }
    SECTION("Test operation Some_Function2") {
        // Do implement test here
        testNamEs->some_Function2(false);
    }
    SECTION("Test property Switch") {
        // Do implement test here
        testNamEs->setSwitch(false);
        auto actual = testNamEs->getSwitch();
        auto expected =  false;
        REQUIRE(actual == expected);
    }
    SECTION("Test property SOME_PROPERTY") {
        // Do implement test here
        testNamEs->setSomeProperty(0);
        auto actual = testNamEs->getSomeProperty();
        auto expected =  0;
        REQUIRE(actual == expected);
    }
    SECTION("Test property Some_Poperty2") {
        // Do implement test here
        testNamEs->setSomePoperty2(0);
        auto actual = testNamEs->getSomePoperty2();
        auto expected =  0;
        REQUIRE(actual == expected);
    }
    SECTION("Test property enum_property") {
        // Do implement test here
        testNamEs->setEnumProperty(Enum_With_Under_scoresEnum::First_Value);
        auto actual = testNamEs->getEnumProperty();
        auto expected =  Enum_With_Under_scoresEnum::First_Value;
        REQUIRE(actual == expected);
    }
}
