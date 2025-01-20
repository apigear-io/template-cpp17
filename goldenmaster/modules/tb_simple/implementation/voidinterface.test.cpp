#include <memory>
#include "catch2/catch.hpp"
#include "tb_simple/implementation/voidinterface.h"

using namespace Test::TbSimple;
TEST_CASE("Testing VoidInterface", "[VoidInterface]"){
    std::unique_ptr<IVoidInterface> testVoidInterface = std::make_unique<VoidInterface>();
    // setup your test
    SECTION("Test operation funcVoid") {
        // Do implement test here
        testVoidInterface->funcVoid();
    }

    SECTION("Test operation async funcVoid") {
        // Do implement test here

        auto future = testVoidInterface->funcVoidAsync();
    }

    SECTION("Test operation async funcVoid with a callback") {
        // Do implement test here

        auto future = testVoidInterface->funcVoidAsync([]( ){ /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
}
