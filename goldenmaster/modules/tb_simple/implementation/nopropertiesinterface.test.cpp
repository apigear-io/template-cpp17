#include <memory>
#include "catch2/catch.hpp"
#include "tb_simple/implementation/nopropertiesinterface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::TbSimple;
TEST_CASE("Testing NoPropertiesInterface", "[NoPropertiesInterface]"){
    std::unique_ptr<INoPropertiesInterface> testNoPropertiesInterface = std::make_unique<NoPropertiesInterface>();
    // setup your test
    SECTION("Test operation funcVoid") {
        // Do implement test here
        testNoPropertiesInterface->funcVoid();
    }
    SECTION("Test operation funcBool") {
        // Do implement test here
        testNoPropertiesInterface->funcBool(false);
    }
}
