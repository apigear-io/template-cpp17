#include <memory>
#include "catch2/catch.hpp"
#include "tb_same1/implementation/samestruct2interface.h"
#include "apigear/utilities/fuzzy_compare.h"

using namespace Test::TbSame1;
TEST_CASE("Testing SameStruct2Interface", "[SameStruct2Interface]"){
    std::unique_ptr<ISameStruct2Interface> testSameStruct2Interface = std::make_unique<SameStruct2Interface>();
    // setup your test
    SECTION("Test operation func1") {
        // Do implement test here
        testSameStruct2Interface->func1(Struct1());
    }
    SECTION("Test operation func2") {
        // Do implement test here
        testSameStruct2Interface->func2(Struct1(), Struct2());
    }
    SECTION("Test property prop1") {
        // Do implement test here
        testSameStruct2Interface->setProp1(Struct2());
        auto actual = testSameStruct2Interface->getProp1();
        auto expected =  Struct2();
        REQUIRE(actual == expected);
    }
    SECTION("Test property prop2") {
        // Do implement test here
        testSameStruct2Interface->setProp2(Struct2());
        auto actual = testSameStruct2Interface->getProp2();
        auto expected =  Struct2();
        REQUIRE(actual == expected);
    }
}
