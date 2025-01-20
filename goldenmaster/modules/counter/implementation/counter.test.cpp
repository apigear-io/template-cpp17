#include <memory>
#include "catch2/catch.hpp"
#include "counter/implementation/counter.h"

using namespace Test::Counter;
TEST_CASE("Testing Counter", "[Counter]"){
    std::unique_ptr<ICounter> testCounter = std::make_unique<Counter>();
    // setup your test
    SECTION("Test operation increment") {
        // Do implement test here
        testCounter->increment(Eigen::Vector3f(0,0,0));
    }

    SECTION("Test operation async increment") {
        // Do implement test here

        auto future = testCounter->incrementAsync(Eigen::Vector3f(0,0,0));
    }

    SECTION("Test operation async increment with a callback") {
        // Do implement test here

        auto future = testCounter->incrementAsync(Eigen::Vector3f(0,0,0),[](Eigen::Vector3f value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation decrement") {
        // Do implement test here
        testCounter->decrement(Test::CustomTypes::Vector3D());
    }

    SECTION("Test operation async decrement") {
        // Do implement test here

        auto future = testCounter->decrementAsync(Test::CustomTypes::Vector3D());
    }

    SECTION("Test operation async decrement with a callback") {
        // Do implement test here

        auto future = testCounter->decrementAsync(Test::CustomTypes::Vector3D(),[](Test::CustomTypes::Vector3D value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test property vector") {
        // Do implement test here
        testCounter->setVector(Test::CustomTypes::Vector3D());
        REQUIRE( testCounter->getVector() == Test::CustomTypes::Vector3D() );
    }
    SECTION("Test property extern_vector") {
        // Do implement test here
        testCounter->setExternVector(Eigen::Vector3f(0,0,0));
        REQUIRE( testCounter->getExternVector() == Eigen::Vector3f(0,0,0) );
    }
}
