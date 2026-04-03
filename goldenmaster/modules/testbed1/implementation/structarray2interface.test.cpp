#include <memory>
#include "catch2/catch.hpp"
#include "testbed1/implementation/structarray2interface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::Testbed1;
TEST_CASE("Testing StructArray2Interface", "[StructArray2Interface]"){
    std::unique_ptr<IStructArray2Interface> testStructArray2Interface = std::make_unique<StructArray2Interface>();
    // setup your test
    SECTION("Test operation funcBool") {
        // Do implement test here
        testStructArray2Interface->funcBool(StructBoolWithArray());
    }

    SECTION("Test operation async funcBool") {
        // Do implement test here

        auto future = testStructArray2Interface->funcBoolAsync(StructBoolWithArray());
    }

    SECTION("Test operation async funcBool with a callback") {
        // Do implement test here

        auto future = testStructArray2Interface->funcBoolAsync(StructBoolWithArray(),[](std::list<StructBool> value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcInt") {
        // Do implement test here
        testStructArray2Interface->funcInt(StructIntWithArray());
    }

    SECTION("Test operation async funcInt") {
        // Do implement test here

        auto future = testStructArray2Interface->funcIntAsync(StructIntWithArray());
    }

    SECTION("Test operation async funcInt with a callback") {
        // Do implement test here

        auto future = testStructArray2Interface->funcIntAsync(StructIntWithArray(),[](std::list<StructInt> value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testStructArray2Interface->funcFloat(StructFloatWithArray());
    }

    SECTION("Test operation async funcFloat") {
        // Do implement test here

        auto future = testStructArray2Interface->funcFloatAsync(StructFloatWithArray());
    }

    SECTION("Test operation async funcFloat with a callback") {
        // Do implement test here

        auto future = testStructArray2Interface->funcFloatAsync(StructFloatWithArray(),[](std::list<StructFloat> value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testStructArray2Interface->funcString(StructStringWithArray());
    }

    SECTION("Test operation async funcString") {
        // Do implement test here

        auto future = testStructArray2Interface->funcStringAsync(StructStringWithArray());
    }

    SECTION("Test operation async funcString with a callback") {
        // Do implement test here

        auto future = testStructArray2Interface->funcStringAsync(StructStringWithArray(),[](std::list<StructString> value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcEnum") {
        // Do implement test here
        testStructArray2Interface->funcEnum(StructEnumWithArray());
    }

    SECTION("Test operation async funcEnum") {
        // Do implement test here

        auto future = testStructArray2Interface->funcEnumAsync(StructEnumWithArray());
    }

    SECTION("Test operation async funcEnum with a callback") {
        // Do implement test here

        auto future = testStructArray2Interface->funcEnumAsync(StructEnumWithArray(),[](std::list<Enum0Enum> value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test property propBool") {
        // Do implement test here
        testStructArray2Interface->setPropBool(StructBoolWithArray());
        auto actual = testStructArray2Interface->getPropBool();
        auto expected =  StructBoolWithArray();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testStructArray2Interface->setPropInt(StructIntWithArray());
        auto actual = testStructArray2Interface->getPropInt();
        auto expected =  StructIntWithArray();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testStructArray2Interface->setPropFloat(StructFloatWithArray());
        auto actual = testStructArray2Interface->getPropFloat();
        auto expected =  StructFloatWithArray();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propString") {
        // Do implement test here
        testStructArray2Interface->setPropString(StructStringWithArray());
        auto actual = testStructArray2Interface->getPropString();
        auto expected =  StructStringWithArray();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propEnum") {
        // Do implement test here
        testStructArray2Interface->setPropEnum(StructEnumWithArray());
        auto actual = testStructArray2Interface->getPropEnum();
        auto expected =  StructEnumWithArray();
        REQUIRE(actual == expected);
    }
}
