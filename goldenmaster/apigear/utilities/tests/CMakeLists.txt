cmake_minimum_required(VERSION 3.24)
project(test_apigear_utilities)

set(SPDLOG_DEBUG_ON true)
set(SPDLOG_TRACE_ON true)
include(CTest)

if(BUILD_TESTING)
enable_testing()
find_package(Catch2 REQUIRED)

set(TEST_APIGEAR_UTILITIES_SOURCES
    test_main.cpp
    logger.test.cpp
    )

add_executable(test_apigear_utilities ${TEST_APIGEAR_UTILITIES_SOURCES})


add_test(NAME test_apigear_utilities COMMAND $<TARGET_FILE:test_apigear_utilities>)

target_link_libraries(test_apigear_utilities PRIVATE apigear::utilities Catch2::Catch2)

endif() # BUILD_TESTING
