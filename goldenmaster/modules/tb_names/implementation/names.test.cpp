#include <memory>
#include "catch2/catch.hpp"
#include "tb_names/implementation/names.h"

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
        REQUIRE( testNamEs->getSwitch() == false );
    }
    SECTION("Test property SOME_PROPERTY") {
        // Do implement test here
        testNamEs->setSomeProperty(0);
        REQUIRE( testNamEs->getSomeProperty() == 0 );
    }
    SECTION("Test property Some_Poperty2") {
        // Do implement test here
        testNamEs->setSomePoperty2(0);
        REQUIRE( testNamEs->getSomePoperty2() == 0 );
    }
    SECTION("Test property enum_property") {
        // Do implement test here
        testNamEs->setEnumProperty(Enum_With_Under_scoresEnum::First_Value);
        REQUIRE( testNamEs->getEnumProperty() == Enum_With_Under_scoresEnum::First_Value );
    }
}
