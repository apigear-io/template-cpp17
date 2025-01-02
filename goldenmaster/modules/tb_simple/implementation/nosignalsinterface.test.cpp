#include <memory>
#include "catch2/catch.hpp"
#include "tb_simple/implementation/nosignalsinterface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::TbSimple;
TEST_CASE("Testing NoSignalsInterface", "[NoSignalsInterface]"){
    std::unique_ptr<INoSignalsInterface> testNoSignalsInterface = std::make_unique<NoSignalsInterface>();
    // setup your test
    SECTION("Test operation funcVoid") {
        // Do implement test here
        testNoSignalsInterface->funcVoid();
    }
    SECTION("Test operation funcBool") {
        // Do implement test here
        testNoSignalsInterface->funcBool(false);
    }
    SECTION("Test property propBool") {
        // Do implement test here
        testNoSignalsInterface->setPropBool(false);
        auto actual = testNoSignalsInterface->getPropBool();
        auto expected =  false;
        REQUIRE(actual == expected);
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testNoSignalsInterface->setPropInt(0);
        auto actual = testNoSignalsInterface->getPropInt();
        auto expected =  0;
        REQUIRE(actual == expected);
    }
}
