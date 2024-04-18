#include <memory>
#include "catch2/catch.hpp"
#include "tb_simple/implementation/simplearrayinterface.h"

using namespace Test::TbSimple;
TEST_CASE("Testing SimpleArrayInterface", "[SimpleArrayInterface]"){
    std::unique_ptr<ISimpleArrayInterface> testSimpleArrayInterface = std::make_unique<SimpleArrayInterface>();
    // setup your test
    SECTION("Test operation funcBool") {
        // Do implement test here
        testSimpleArrayInterface->funcBool(std::list<bool>());
    }
    SECTION("Test operation funcInt") {
        // Do implement test here
        testSimpleArrayInterface->funcInt(std::list<int>());
    }
    SECTION("Test operation funcInt32") {
        // Do implement test here
        testSimpleArrayInterface->funcInt32(std::list<int32_t>());
    }
    SECTION("Test operation funcInt64") {
        // Do implement test here
        testSimpleArrayInterface->funcInt64(std::list<int64_t>());
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testSimpleArrayInterface->funcFloat(std::list<float>());
    }
    SECTION("Test operation funcFloat32") {
        // Do implement test here
        testSimpleArrayInterface->funcFloat32(std::list<float>());
    }
    SECTION("Test operation funcFloat64") {
        // Do implement test here
        testSimpleArrayInterface->funcFloat64(std::list<double>());
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testSimpleArrayInterface->funcString(std::list<std::string>());
    }
    SECTION("Test property propBool") {
        // Do implement test here
        testSimpleArrayInterface->setPropBool(std::list<bool>());
        REQUIRE( testSimpleArrayInterface->getPropBool() == std::list<bool>() );
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testSimpleArrayInterface->setPropInt(std::list<int>());
        REQUIRE( testSimpleArrayInterface->getPropInt() == std::list<int>() );
    }
    SECTION("Test property propInt32") {
        // Do implement test here
        testSimpleArrayInterface->setPropInt32(std::list<int32_t>());
        REQUIRE( testSimpleArrayInterface->getPropInt32() == std::list<int32_t>() );
    }
    SECTION("Test property propInt64") {
        // Do implement test here
        testSimpleArrayInterface->setPropInt64(std::list<int64_t>());
        REQUIRE( testSimpleArrayInterface->getPropInt64() == std::list<int64_t>() );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testSimpleArrayInterface->setPropFloat(std::list<float>());
        REQUIRE( testSimpleArrayInterface->getPropFloat() == std::list<float>() );
    }
    SECTION("Test property propFloat32") {
        // Do implement test here
        testSimpleArrayInterface->setPropFloat32(std::list<float>());
        REQUIRE( testSimpleArrayInterface->getPropFloat32() == std::list<float>() );
    }
    SECTION("Test property propFloat64") {
        // Do implement test here
        testSimpleArrayInterface->setPropFloat64(std::list<double>());
        REQUIRE( testSimpleArrayInterface->getPropFloat64() == std::list<double>() );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testSimpleArrayInterface->setPropString(std::list<std::string>());
        REQUIRE( testSimpleArrayInterface->getPropString() == std::list<std::string>() );
    }
    SECTION("Test property propReadOnlyString") {
        // Do implement test here
        REQUIRE( testSimpleArrayInterface->getPropReadOnlyString() == std::string() );
    }
}
