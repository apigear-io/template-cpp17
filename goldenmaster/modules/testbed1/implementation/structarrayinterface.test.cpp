#include <memory>
#include "catch2/catch.hpp"
#include "testbed1/implementation/structarrayinterface.h"

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

        auto future = testStructArrayInterface->funcBoolAsync(std::list<StructBool>(),[](StructBool value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
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

        auto future = testStructArrayInterface->funcIntAsync(std::list<StructInt>(),[](StructBool value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
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

        auto future = testStructArrayInterface->funcFloatAsync(std::list<StructFloat>(),[](StructBool value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
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

        auto future = testStructArrayInterface->funcStringAsync(std::list<StructString>(),[](StructBool value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test property propBool") {
        // Do implement test here
        testStructArrayInterface->setPropBool(std::list<StructBool>());
        REQUIRE( testStructArrayInterface->getPropBool() == std::list<StructBool>() );
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testStructArrayInterface->setPropInt(std::list<StructInt>());
        REQUIRE( testStructArrayInterface->getPropInt() == std::list<StructInt>() );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testStructArrayInterface->setPropFloat(std::list<StructFloat>());
        REQUIRE( testStructArrayInterface->getPropFloat() == std::list<StructFloat>() );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testStructArrayInterface->setPropString(std::list<StructString>());
        REQUIRE( testStructArrayInterface->getPropString() == std::list<StructString>() );
    }
}
