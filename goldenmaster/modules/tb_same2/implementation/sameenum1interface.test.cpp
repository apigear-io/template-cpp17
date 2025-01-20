#include <memory>
#include "catch2/catch.hpp"
#include "tb_same2/implementation/sameenum1interface.h"

using namespace Test::TbSame2;
TEST_CASE("Testing SameEnum1Interface", "[SameEnum1Interface]"){
    std::unique_ptr<ISameEnum1Interface> testSameEnum1Interface = std::make_unique<SameEnum1Interface>();
    // setup your test
    SECTION("Test operation func1") {
        // Do implement test here
        testSameEnum1Interface->func1(Enum1Enum::value1);
    }

    SECTION("Test operation async func1") {
        // Do implement test here

        auto future = testSameEnum1Interface->func1Async(Enum1Enum::value1);
    }

    SECTION("Test operation async func1 with a callback") {
        // Do implement test here

        auto future = testSameEnum1Interface->func1Async(Enum1Enum::value1,[](Enum1Enum value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test property prop1") {
        // Do implement test here
        testSameEnum1Interface->setProp1(Enum1Enum::value1);
        REQUIRE( testSameEnum1Interface->getProp1() == Enum1Enum::value1 );
    }
}
