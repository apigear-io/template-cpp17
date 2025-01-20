#include <memory>
#include "catch2/catch.hpp"
#include "counter/implementation/counter.h"
#include "apigear/utilities/fuzzy_compare.h"

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
    SECTION("Test operation incrementArray") {
        // Do implement test here
        testCounter->incrementArray(std::list<Eigen::Vector3f>());
    }

    SECTION("Test operation async incrementArray") {
        // Do implement test here

        auto future = testCounter->incrementArrayAsync(std::list<Eigen::Vector3f>());
    }

    SECTION("Test operation async incrementArray with a callback") {
        // Do implement test here

        auto future = testCounter->incrementArrayAsync(std::list<Eigen::Vector3f>(),[](std::list<Eigen::Vector3f> value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
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
    SECTION("Test operation decrementArray") {
        // Do implement test here
        testCounter->decrementArray(std::list<Test::CustomTypes::Vector3D>());
    }

    SECTION("Test operation async decrementArray") {
        // Do implement test here

        auto future = testCounter->decrementArrayAsync(std::list<Test::CustomTypes::Vector3D>());
    }

    SECTION("Test operation async decrementArray with a callback") {
        // Do implement test here

        auto future = testCounter->decrementArrayAsync(std::list<Test::CustomTypes::Vector3D>(),[](std::list<Test::CustomTypes::Vector3D> value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test property vector") {
        // Do implement test here
        testCounter->setVector(Test::CustomTypes::Vector3D());
        auto actual = testCounter->getVector();
        auto expected =  Test::CustomTypes::Vector3D();
        REQUIRE(actual == expected);
    }
    SECTION("Test property extern_vector") {
        // Do implement test here
        testCounter->setExternVector(Eigen::Vector3f(0,0,0));
        auto actual = testCounter->getExternVector();
        auto expected =  Eigen::Vector3f(0,0,0);
        REQUIRE(actual == expected);
    }
    SECTION("Test property vectorArray") {
        // Do implement test here
        testCounter->setVectorArray(std::list<Test::CustomTypes::Vector3D>());
        auto actual = testCounter->getVectorArray();
        auto expected =  std::list<Test::CustomTypes::Vector3D>();
        REQUIRE(actual == expected);
    }
    SECTION("Test property extern_vectorArray") {
        // Do implement test here
        testCounter->setExternVectorArray(std::list<Eigen::Vector3f>());
        auto actual = testCounter->getExternVectorArray();
        auto expected =  std::list<Eigen::Vector3f>();
        REQUIRE(actual == expected);
    }
}
