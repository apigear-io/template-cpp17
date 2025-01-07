
cmake_minimum_required(VERSION 3.24)
project(test_testbed2_generated_olink)

set(SPDLOG_DEBUG_ON true)
set(SPDLOG_TRACE_ON true)
include(CTest)

enable_testing()
find_package(apigear OPTIONAL_COMPONENTS poco-olink)
find_package(testbed2 QUIET COMPONENTS testbed2-implementation  testbed2-core testbed2-olink)

find_package(Catch2 REQUIRED)

set(TEST_TESTBED2_GENERATED_OLINK_SOURCES
    test_main.cpp
    test_manyparaminterface.cpp
    test_nestedstruct1interface.cpp
    test_nestedstruct2interface.cpp
    test_nestedstruct3interface.cpp
    )


include_directories(test_testbed2_generated_olink
    PRIVATE
    $<BUILD_INTERFACE:${MODULES_DIR}>
)

add_executable(test_testbed2_generated_olink ${TEST_TESTBED2_GENERATED_OLINK_SOURCES})
add_test(NAME test_testbed2_generated_olink COMMAND $<TARGET_FILE:test_testbed2_generated_olink>)

target_link_libraries(test_testbed2_generated_olink PRIVATE
    poco-olink
    testbed2-implementation
    testbed2-core
    testbed2-olink
    Catch2::Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(Catch)

install(TARGETS test_testbed2_generated_olink
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

