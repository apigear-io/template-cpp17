#include <memory>
#include "catch2/catch.hpp"
#include "tb_same2/implementation/samestruct1interface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::TbSame2;
TEST_CASE("Testing SameStruct1Interface", "[SameStruct1Interface]"){
    std::unique_ptr<ISameStruct1Interface> testSameStruct1Interface = std::make_unique<SameStruct1Interface>();
    // setup your test
    SECTION("Test operation func1") {
        // Do implement test here
        testSameStruct1Interface->func1(Struct1());
    }

    SECTION("Test operation async func1") {
        // Do implement test here

        auto future = testSameStruct1Interface->func1Async(Struct1());
    }

    SECTION("Test operation async func1 with a callback") {
        // Do implement test here

        auto future = testSameStruct1Interface->func1Async(Struct1(),[](Struct1 value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test property prop1") {
        // Do implement test here
        testSameStruct1Interface->setProp1(Struct1());
        auto actual = testSameStruct1Interface->getProp1();
        auto expected =  Struct1();
        REQUIRE(actual == expected);
    }
}
