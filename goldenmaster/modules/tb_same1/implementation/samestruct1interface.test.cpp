#include <memory>
#include "catch2/catch.hpp"
#include "tb_same1/implementation/samestruct1interface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::TbSame1;
TEST_CASE("Testing SameStruct1Interface", "[SameStruct1Interface]"){
    std::unique_ptr<ISameStruct1Interface> testSameStruct1Interface = std::make_unique<SameStruct1Interface>();
    // setup your test
    SECTION("Test operation func1") {
        // Do implement test here
        testSameStruct1Interface->func1(Struct1());
    }
    SECTION("Test property prop1") {
        // Do implement test here
        testSameStruct1Interface->setProp1(Struct1());
        auto actual = testSameStruct1Interface->getProp1();
        auto expected =  Struct1();
        REQUIRE(actual == expected);
    }
}
