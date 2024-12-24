
cmake_minimum_required(VERSION 3.24)
project(test_testbed2_generated_nats)

set(SPDLOG_DEBUG_ON true)
set(SPDLOG_TRACE_ON true)
include(CTest)

enable_testing()
find_package(apigear OPTIONAL_COMPONENTS nats)
find_package(testbed2 QUIET COMPONENTS testbed2-implementation  testbed2-core testbed2-nats)

find_package(Catch2 REQUIRED)

set(TEST_TESTBED2_GENERATED_NATS_SOURCES
    test_main.cpp
    test_manyparaminterface.cpp
    test_nestedstruct1interface.cpp
    test_nestedstruct2interface.cpp
    test_nestedstruct3interface.cpp
    )


include_directories(test_testbed2_generated_nats
    PRIVATE
    $<BUILD_INTERFACE:${MODULES_DIR}>
)

add_executable(test_testbed2_generated_nats ${TEST_TESTBED2_GENERATED_NATS_SOURCES})
add_test(NAME test_testbed2_generated_nats COMMAND $<TARGET_FILE:test_testbed2_generated_nats>)

target_link_libraries(test_testbed2_generated_nats PRIVATE
    apigear::nats
    testbed2-implementation
    testbed2-core
    testbed2-nats
    Catch2::Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(Catch)

install(TARGETS test_testbed2_generated_nats
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

