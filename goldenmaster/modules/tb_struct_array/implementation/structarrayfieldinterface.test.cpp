#include <memory>
#include "catch2/catch.hpp"
#include "tb_struct_array/implementation/structarrayfieldinterface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::TbStructArray;
TEST_CASE("Testing StructArrayFieldInterface", "[StructArrayFieldInterface]"){
    std::unique_ptr<IStructArrayFieldInterface> testStructArrayFieldInterface = std::make_unique<StructArrayFieldInterface>();
    // setup your test
    SECTION("Test operation funcMixed") {
        // Do implement test here
        testStructArrayFieldInterface->funcMixed(MixedStruct());
    }

    SECTION("Test operation async funcMixed") {
        // Do implement test here

        auto future = testStructArrayFieldInterface->funcMixedAsync(MixedStruct());
    }

    SECTION("Test operation async funcMixed with a callback") {
        // Do implement test here

        auto future = testStructArrayFieldInterface->funcMixedAsync(MixedStruct(),[](MixedStruct value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test operation funcStructArray") {
        // Do implement test here
        testStructArrayFieldInterface->funcStructArray(StructWithArrayOfStructs());
    }

    SECTION("Test operation async funcStructArray") {
        // Do implement test here

        auto future = testStructArrayFieldInterface->funcStructArrayAsync(StructWithArrayOfStructs());
    }

    SECTION("Test operation async funcStructArray with a callback") {
        // Do implement test here

        auto future = testStructArrayFieldInterface->funcStructArrayAsync(StructWithArrayOfStructs(),[](StructWithArrayOfStructs value){ (void)value; /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ }
            );
    }
    SECTION("Test property propStructArray") {
        // Do implement test here
        testStructArrayFieldInterface->setPropStructArray(StructWithArrayOfStructs());
        auto actual = testStructArrayFieldInterface->getPropStructArray();
        auto expected =  StructWithArrayOfStructs();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propEnumArray") {
        // Do implement test here
        testStructArrayFieldInterface->setPropEnumArray(StructWithArrayOfEnums());
        auto actual = testStructArrayFieldInterface->getPropEnumArray();
        auto expected =  StructWithArrayOfEnums();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propIntArray") {
        // Do implement test here
        testStructArrayFieldInterface->setPropIntArray(StructWithArrayOfInts());
        auto actual = testStructArrayFieldInterface->getPropIntArray();
        auto expected =  StructWithArrayOfInts();
        REQUIRE(actual == expected);
    }
    SECTION("Test property propMixed") {
        // Do implement test here
        testStructArrayFieldInterface->setPropMixed(MixedStruct());
        auto actual = testStructArrayFieldInterface->getPropMixed();
        auto expected =  MixedStruct();
        REQUIRE(actual == expected);
    }
}
