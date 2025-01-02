#pragma warning (disable: 4251) 
#pragma warning (disable: 4099) 

#include <catch2/catch.hpp>
#include <iostream>
#include <sstream>

#include "../fuzzy_compare.h"


TEST_CASE("Fuzzy comparison of floating-point numbers") {

    SECTION("Exact number")
    {
        REQUIRE(ApiGear::Utilities::fuzzyCompare(1.0, 1.0));
        REQUIRE(ApiGear::Utilities::fuzzyCompare(0.0, 0.0));
    }

    SECTION("Within absolute tolerance")
    {
        REQUIRE(ApiGear::Utilities::fuzzyCompare(1.0, 1.0 + 10 * std::numeric_limits<double>::epsilon()));
        REQUIRE(ApiGear::Utilities::fuzzyCompare(0.0, 10 * std::numeric_limits<double>::epsilon()));
    }

    SECTION("Within relative tolerance")
    {
        REQUIRE(ApiGear::Utilities::fuzzyCompare(1.0, 1.0 + 1e-10));
    }

    SECTION("Outside relative tolerance")
    {
        REQUIRE_FALSE(ApiGear::Utilities::fuzzyCompare(1.0, 1.0 + 1e-6));
    }

    SECTION("Adjusted relative tolerance")
    {
        REQUIRE(ApiGear::Utilities::fuzzyCompare(1e6, 1e6 + 1, 1e-6));
    }

    SECTION("Outside adjusted relative tolerance")
    {
        REQUIRE_FALSE(ApiGear::Utilities::fuzzyCompare(1e6, 1e6 + 2, 1e-6));
    }

    SECTION("Negative numbers comparison") {
        REQUIRE(ApiGear::Utilities::fuzzyCompare(-1.0, -1.0));
        REQUIRE(ApiGear::Utilities::fuzzyCompare(-1.0, -1.0 - 1e-10));
        REQUIRE_FALSE(ApiGear::Utilities::fuzzyCompare(-1.0, -1.0 - 1e-6));
    }

    SECTION("Comparison near zero") {
        REQUIRE(ApiGear::Utilities::fuzzyCompare(0.0, 0.0));
        REQUIRE(ApiGear::Utilities::fuzzyCompare(0.0, std::numeric_limits<double>::epsilon() * 99));
        REQUIRE_FALSE(ApiGear::Utilities::fuzzyCompare(0.0, std::numeric_limits<double>::epsilon() * 101));
    }

    SECTION("Comparison near zero, adjusted absolute tolerance") {
        REQUIRE(ApiGear::Utilities::fuzzyCompare(0.0, 1e-12, 1e-9, 1e-12));
        REQUIRE_FALSE(ApiGear::Utilities::fuzzyCompare(0.0, 1e-10, 1e-9, 1e-12));
    }

    SECTION("Different types of floating-point numbers") {
        REQUIRE(ApiGear::Utilities::fuzzyCompare(1.0f, 1.0f + 1e-6f, 1e-5f));
        REQUIRE(ApiGear::Utilities::fuzzyCompare(1.0L, 1.0L + 1e-12L, 1e-11L));
    }

    SECTION("Edge cases for large numbers") {
        REQUIRE(ApiGear::Utilities::fuzzyCompare(1e10, 1e10 + 1e1, 1e-9));
        REQUIRE_FALSE(ApiGear::Utilities::fuzzyCompare(1e10, 1e10 + 1e3, 1e-9));
    }
}
