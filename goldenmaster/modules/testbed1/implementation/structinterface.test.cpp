#include <memory>
#include "catch2/catch.hpp"
#include "testbed1/implementation/structinterface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::Testbed1;
TEST_CASE("Testing StructInterface", "[StructInterface]"){
    std::unique_ptr<IStructInterface> testStructInterface = std::make_unique<StructInterface>();
    // setup your test
    SECTION("Test operation funcBool") {
        // Do implement test here
        testStructInterface->funcBool(StructBool());
    }

    SECTION("Test operation async funcBool") {
        // Do implement test here

        auto future = testStructInterface->funcBoolAsync(StructBool());
    }

    SECTION("Test operation async funcBool with a callback") {
        // Do implement test here

        auto future = testStructInterface->funcBoolAsync(StructBool(),[](StructBool value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcInt") {
        // Do implement test here
        testStructInterface->funcInt(StructInt());
    }

    SECTION("Test operation async funcInt") {
        // Do implement test here

        auto future = testStructInterface->funcIntAsync(StructInt());
    }

    SECTION("Test operation async funcInt with a callback") {
        // Do implement test here

        auto future = testStructInterface->funcIntAsync(StructInt(),[](StructInt value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testStructInterface->funcFloat(StructFloat());
    }

    SECTION("Test operation async funcFloat") {
        // Do implement test here

        auto future = testStructInterface->funcFloatAsync(StructFloat());
    }

    SECTION("Test operation async funcFloat with a callback") {
        // Do implement test here

        auto future = testStructInterface->funcFloatAsync(StructFloat(),[](StructFloat value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testStructInterface->funcString(StructString());
    }

    SECTION("Test operation async funcString") {
        // Do implement test here

        auto future = testStructInterface->funcStringAsync(StructString());
    }

    SECTION("Test operation async funcString with a callback") {
        // Do implement test here

        auto future = testStructInterface->funcStringAsync(StructString(),[](StructString value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test property propBool") {
        // Do implement test here
        testStructInterface->setPropBool(StructBool());
        auto actual = testStructInterface->getPropBool();
        auto expected =  StructBool();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testStructInterface->setPropInt(StructInt());
        auto actual = testStructInterface->getPropInt();
        auto expected =  StructInt();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testStructInterface->setPropFloat(StructFloat());
        auto actual = testStructInterface->getPropFloat();
        auto expected =  StructFloat();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propString") {
        // Do implement test here
        testStructInterface->setPropString(StructString());
        auto actual = testStructInterface->getPropString();
        auto expected =  StructString();
        REQUIRE(actual == expected);
    }
}
