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
    SECTION("Test operation decrement") {
        // Do implement test here
        testCounter->decrement(Test::CustomTypes::Vector3D());
    }
    SECTION("Test property vector") {
        // Do implement test here
        testCounter->setVector(Test::CustomTypes::Vector3D());
        auto actual = testCounter->getVector();
        auto expected =  Test::CustomTypes::Vector3D();
        REQUIRE(actual == expected 
        );
    }
    SECTION("Test property extern_vector") {
        // Do implement test here
        testCounter->setExternVector(Eigen::Vector3f(0,0,0));
        auto actual = testCounter->getExternVector();
        auto expected =  Eigen::Vector3f(0,0,0);
        REQUIRE(actual == expected 
        );
    }
}
