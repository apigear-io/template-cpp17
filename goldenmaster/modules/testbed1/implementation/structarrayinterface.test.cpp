#include <memory>
#include "catch2/catch.hpp"
#include "testbed1/implementation/structarrayinterface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::Testbed1;
TEST_CASE("Testing StructArrayInterface", "[StructArrayInterface]"){
    std::unique_ptr<IStructArrayInterface> testStructArrayInterface = std::make_unique<StructArrayInterface>();
    // setup your test
    SECTION("Test operation funcBool") {
        // Do implement test here
        testStructArrayInterface->funcBool(std::list<StructBool>());
    }

    SECTION("Test operation async funcBool") {
        // Do implement test here

        auto future = testStructArrayInterface->funcBoolAsync(std::list<StructBool>());
    }

    SECTION("Test operation async funcBool with a callback") {
        // Do implement test here

        auto future = testStructArrayInterface->funcBoolAsync(std::list<StructBool>(),[](std::list<StructBool> value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcInt") {
        // Do implement test here
        testStructArrayInterface->funcInt(std::list<StructInt>());
    }

    SECTION("Test operation async funcInt") {
        // Do implement test here

        auto future = testStructArrayInterface->funcIntAsync(std::list<StructInt>());
    }

    SECTION("Test operation async funcInt with a callback") {
        // Do implement test here

        auto future = testStructArrayInterface->funcIntAsync(std::list<StructInt>(),[](std::list<StructInt> value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testStructArrayInterface->funcFloat(std::list<StructFloat>());
    }

    SECTION("Test operation async funcFloat") {
        // Do implement test here

        auto future = testStructArrayInterface->funcFloatAsync(std::list<StructFloat>());
    }

    SECTION("Test operation async funcFloat with a callback") {
        // Do implement test here

        auto future = testStructArrayInterface->funcFloatAsync(std::list<StructFloat>(),[](std::list<StructFloat> value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testStructArrayInterface->funcString(std::list<StructString>());
    }

    SECTION("Test operation async funcString") {
        // Do implement test here

        auto future = testStructArrayInterface->funcStringAsync(std::list<StructString>());
    }

    SECTION("Test operation async funcString with a callback") {
        // Do implement test here

        auto future = testStructArrayInterface->funcStringAsync(std::list<StructString>(),[](std::list<StructString> value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test property propBool") {
        // Do implement test here
        testStructArrayInterface->setPropBool(std::list<StructBool>());
        auto actual = testStructArrayInterface->getPropBool();
        auto expected =  std::list<StructBool>();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testStructArrayInterface->setPropInt(std::list<StructInt>());
        auto actual = testStructArrayInterface->getPropInt();
        auto expected =  std::list<StructInt>();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testStructArrayInterface->setPropFloat(std::list<StructFloat>());
        auto actual = testStructArrayInterface->getPropFloat();
        auto expected =  std::list<StructFloat>();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propString") {
        // Do implement test here
        testStructArrayInterface->setPropString(std::list<StructString>());
        auto actual = testStructArrayInterface->getPropString();
        auto expected =  std::list<StructString>();
        REQUIRE(actual == expected);
    }
}
