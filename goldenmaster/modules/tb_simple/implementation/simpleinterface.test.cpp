#include <memory>
#include "catch2/catch.hpp"
#include "tb_simple/implementation/simpleinterface.h"

using namespace Test::TbSimple;
TEST_CASE("Testing SimpleInterface", "[SimpleInterface]"){
    std::unique_ptr<ISimpleInterface> testSimpleInterface = std::make_unique<SimpleInterface>();
    // setup your test
    SECTION("Test operation funcNoReturnValue") {
        // Do implement test here
        testSimpleInterface->funcNoReturnValue(false);
    }

    SECTION("Test operation async funcNoReturnValue") {
        // Do implement test here

        auto future = testSimpleInterface->funcNoReturnValueAsync(false);
    }

    SECTION("Test operation async funcNoReturnValue with a callback") {
        // Do implement test here

        auto future = testSimpleInterface->funcNoReturnValueAsync(false,[]( ){ /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcBool") {
        // Do implement test here
        testSimpleInterface->funcBool(false);
    }

    SECTION("Test operation async funcBool") {
        // Do implement test here

        auto future = testSimpleInterface->funcBoolAsync(false);
    }

    SECTION("Test operation async funcBool with a callback") {
        // Do implement test here

        auto future = testSimpleInterface->funcBoolAsync(false,[](bool value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcInt") {
        // Do implement test here
        testSimpleInterface->funcInt(0);
    }

    SECTION("Test operation async funcInt") {
        // Do implement test here

        auto future = testSimpleInterface->funcIntAsync(0);
    }

    SECTION("Test operation async funcInt with a callback") {
        // Do implement test here

        auto future = testSimpleInterface->funcIntAsync(0,[](int value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcInt32") {
        // Do implement test here
        testSimpleInterface->funcInt32(0);
    }

    SECTION("Test operation async funcInt32") {
        // Do implement test here

        auto future = testSimpleInterface->funcInt32Async(0);
    }

    SECTION("Test operation async funcInt32 with a callback") {
        // Do implement test here

        auto future = testSimpleInterface->funcInt32Async(0,[](int32_t value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcInt64") {
        // Do implement test here
        testSimpleInterface->funcInt64(0LL);
    }

    SECTION("Test operation async funcInt64") {
        // Do implement test here

        auto future = testSimpleInterface->funcInt64Async(0LL);
    }

    SECTION("Test operation async funcInt64 with a callback") {
        // Do implement test here

        auto future = testSimpleInterface->funcInt64Async(0LL,[](int64_t value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testSimpleInterface->funcFloat(0.0f);
    }

    SECTION("Test operation async funcFloat") {
        // Do implement test here

        auto future = testSimpleInterface->funcFloatAsync(0.0f);
    }

    SECTION("Test operation async funcFloat with a callback") {
        // Do implement test here

        auto future = testSimpleInterface->funcFloatAsync(0.0f,[](float value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcFloat32") {
        // Do implement test here
        testSimpleInterface->funcFloat32(0.0f);
    }

    SECTION("Test operation async funcFloat32") {
        // Do implement test here

        auto future = testSimpleInterface->funcFloat32Async(0.0f);
    }

    SECTION("Test operation async funcFloat32 with a callback") {
        // Do implement test here

        auto future = testSimpleInterface->funcFloat32Async(0.0f,[](float value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcFloat64") {
        // Do implement test here
        testSimpleInterface->funcFloat64(0.0);
    }

    SECTION("Test operation async funcFloat64") {
        // Do implement test here

        auto future = testSimpleInterface->funcFloat64Async(0.0);
    }

    SECTION("Test operation async funcFloat64 with a callback") {
        // Do implement test here

        auto future = testSimpleInterface->funcFloat64Async(0.0,[](double value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testSimpleInterface->funcString(std::string());
    }

    SECTION("Test operation async funcString") {
        // Do implement test here

        auto future = testSimpleInterface->funcStringAsync(std::string());
    }

    SECTION("Test operation async funcString with a callback") {
        // Do implement test here

        auto future = testSimpleInterface->funcStringAsync(std::string(),[](std::string value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test property propBool") {
        // Do implement test here
        testSimpleInterface->setPropBool(false);
        REQUIRE( testSimpleInterface->getPropBool() == false );
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testSimpleInterface->setPropInt(0);
        REQUIRE( testSimpleInterface->getPropInt() == 0 );
    }
    SECTION("Test property propInt32") {
        // Do implement test here
        testSimpleInterface->setPropInt32(0);
        REQUIRE( testSimpleInterface->getPropInt32() == 0 );
    }
    SECTION("Test property propInt64") {
        // Do implement test here
        testSimpleInterface->setPropInt64(0LL);
        REQUIRE( testSimpleInterface->getPropInt64() == 0LL );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testSimpleInterface->setPropFloat(0.0f);
        REQUIRE( testSimpleInterface->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propFloat32") {
        // Do implement test here
        testSimpleInterface->setPropFloat32(0.0f);
        REQUIRE( testSimpleInterface->getPropFloat32() == Approx( 0.0f ) );
    }
    SECTION("Test property propFloat64") {
        // Do implement test here
        testSimpleInterface->setPropFloat64(0.0);
        REQUIRE( testSimpleInterface->getPropFloat64() == 0.0 );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testSimpleInterface->setPropString(std::string());
        REQUIRE( testSimpleInterface->getPropString() == std::string() );
    }
}
