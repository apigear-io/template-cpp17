#include <memory>
#include "catch2/catch.hpp"
#include "testbed2/implementation/manyparaminterface.h"

using namespace Test::Testbed2;
TEST_CASE("Testing ManyParamInterface", "[ManyParamInterface]"){
    std::unique_ptr<IManyParamInterface> testManyParamInterface = std::make_unique<ManyParamInterface>();
    // setup your test
    SECTION("Test operation func1") {
        // Do implement test here
        testManyParamInterface->func1(0);
    }

    SECTION("Test operation async func1") {
        // Do implement test here

        auto future = testManyParamInterface->func1Async(0);
    }

    SECTION("Test operation async func1 with a callback") {
        // Do implement test here

        auto future = testManyParamInterface->func1Async(0,[](int value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation func2") {
        // Do implement test here
        testManyParamInterface->func2(0, 0);
    }

    SECTION("Test operation async func2") {
        // Do implement test here

        auto future = testManyParamInterface->func2Async(0, 0);
    }

    SECTION("Test operation async func2 with a callback") {
        // Do implement test here

        auto future = testManyParamInterface->func2Async(0, 0,[](int value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation func3") {
        // Do implement test here
        testManyParamInterface->func3(0, 0, 0);
    }

    SECTION("Test operation async func3") {
        // Do implement test here

        auto future = testManyParamInterface->func3Async(0, 0, 0);
    }

    SECTION("Test operation async func3 with a callback") {
        // Do implement test here

        auto future = testManyParamInterface->func3Async(0, 0, 0,[](int value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation func4") {
        // Do implement test here
        testManyParamInterface->func4(0, 0, 0, 0);
    }

    SECTION("Test operation async func4") {
        // Do implement test here

        auto future = testManyParamInterface->func4Async(0, 0, 0, 0);
    }

    SECTION("Test operation async func4 with a callback") {
        // Do implement test here

        auto future = testManyParamInterface->func4Async(0, 0, 0, 0,[](int value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test property prop1") {
        // Do implement test here
        testManyParamInterface->setProp1(0);
        REQUIRE( testManyParamInterface->getProp1() == 0 );
    }
    SECTION("Test property prop2") {
        // Do implement test here
        testManyParamInterface->setProp2(0);
        REQUIRE( testManyParamInterface->getProp2() == 0 );
    }
    SECTION("Test property prop3") {
        // Do implement test here
        testManyParamInterface->setProp3(0);
        REQUIRE( testManyParamInterface->getProp3() == 0 );
    }
    SECTION("Test property prop4") {
        // Do implement test here
        testManyParamInterface->setProp4(0);
        REQUIRE( testManyParamInterface->getProp4() == 0 );
    }
}
