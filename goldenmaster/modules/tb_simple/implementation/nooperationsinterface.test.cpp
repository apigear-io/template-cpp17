#include <memory>
#include "catch2/catch.hpp"
#include "tb_simple/implementation/nooperationsinterface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::TbSimple;
TEST_CASE("Testing NoOperationsInterface", "[NoOperationsInterface]"){
    std::unique_ptr<INoOperationsInterface> testNoOperationsInterface = std::make_unique<NoOperationsInterface>();
    // setup your test
    SECTION("Test property propBool") {
        // Do implement test here
        testNoOperationsInterface->setPropBool(false);
        auto actual = testNoOperationsInterface->getPropBool();
        auto expected =  false;
        REQUIRE(actual == expected);
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testNoOperationsInterface->setPropInt(0);
        auto actual = testNoOperationsInterface->getPropInt();
        auto expected =  0;
        REQUIRE(actual == expected);
    }
}
