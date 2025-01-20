#include <memory>
#include "catch2/catch.hpp"
#include "tb_same2/implementation/sameenum2interface.h"

using namespace Test::TbSame2;
TEST_CASE("Testing SameEnum2Interface", "[SameEnum2Interface]"){
    std::unique_ptr<ISameEnum2Interface> testSameEnum2Interface = std::make_unique<SameEnum2Interface>();
    // setup your test
    SECTION("Test operation func1") {
        // Do implement test here
        testSameEnum2Interface->func1(Enum1Enum::value1);
    }

    SECTION("Test operation async func1") {
        // Do implement test here

        auto future = testSameEnum2Interface->func1Async(Enum1Enum::value1);
    }

    SECTION("Test operation async func1 with a callback") {
        // Do implement test here

        auto future = testSameEnum2Interface->func1Async(Enum1Enum::value1,[](Enum1Enum value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation func2") {
        // Do implement test here
        testSameEnum2Interface->func2(Enum1Enum::value1, Enum2Enum::value1);
    }

    SECTION("Test operation async func2") {
        // Do implement test here

        auto future = testSameEnum2Interface->func2Async(Enum1Enum::value1, Enum2Enum::value1);
    }

    SECTION("Test operation async func2 with a callback") {
        // Do implement test here

        auto future = testSameEnum2Interface->func2Async(Enum1Enum::value1, Enum2Enum::value1,[](Enum1Enum value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test property prop1") {
        // Do implement test here
        testSameEnum2Interface->setProp1(Enum1Enum::value1);
        REQUIRE( testSameEnum2Interface->getProp1() == Enum1Enum::value1 );
    }
    SECTION("Test property prop2") {
        // Do implement test here
        testSameEnum2Interface->setProp2(Enum2Enum::value1);
        REQUIRE( testSameEnum2Interface->getProp2() == Enum2Enum::value1 );
    }
}
