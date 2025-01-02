#include <memory>
#include "catch2/catch.hpp"
#include "testbed2/implementation/nestedstruct1interface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::Testbed2;
TEST_CASE("Testing NestedStruct1Interface", "[NestedStruct1Interface]"){
    std::unique_ptr<INestedStruct1Interface> testNestedStruct1Interface = std::make_unique<NestedStruct1Interface>();
    // setup your test
    SECTION("Test operation func1") {
        // Do implement test here
        testNestedStruct1Interface->func1(NestedStruct1());
    }
    SECTION("Test property prop1") {
        // Do implement test here
        testNestedStruct1Interface->setProp1(NestedStruct1());
        auto actual = testNestedStruct1Interface->getProp1();
        auto expected =  NestedStruct1();
        REQUIRE(actual == expected);
    }
}
