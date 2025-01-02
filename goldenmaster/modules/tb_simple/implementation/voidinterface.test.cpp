#include <memory>
#include "catch2/catch.hpp"
#include "tb_simple/implementation/voidinterface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::TbSimple;
TEST_CASE("Testing VoidInterface", "[VoidInterface]"){
    std::unique_ptr<IVoidInterface> testVoidInterface = std::make_unique<VoidInterface>();
    // setup your test
    SECTION("Test operation funcVoid") {
        // Do implement test here
        testVoidInterface->funcVoid();
    }
}
