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

    SECTION("Test operation async funcVoid") {
        // Do implement test here

        auto future = testNoPropertiesInterface->funcVoidAsync();
    }

    SECTION("Test operation async funcVoid with a callback") {
        // Do implement test here

        auto future = testNoPropertiesInterface->funcVoidAsync([]( ){ /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcBool") {
        // Do implement test here
        testNoPropertiesInterface->funcBool(false);
    }

    SECTION("Test operation async funcBool") {
        // Do implement test here

        auto future = testNoPropertiesInterface->funcBoolAsync(false);
    }

    SECTION("Test operation async funcBool with a callback") {
        // Do implement test here

        auto future = testNoPropertiesInterface->funcBoolAsync(false,[](bool value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
}
