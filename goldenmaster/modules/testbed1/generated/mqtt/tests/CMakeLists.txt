
cmake_minimum_required(VERSION 3.24)
project(test_testbed1_generated_mqtt)

set(SPDLOG_DEBUG_ON true)
set(SPDLOG_TRACE_ON true)
include(CTest)

enable_testing()
find_package(apigear OPTIONAL_COMPONENTS paho-mqtt)
find_package(testbed1 QUIET COMPONENTS testbed1-implementation  testbed1-core testbed1-mqtt)

find_package(Catch2 REQUIRED)

set(TEST_TESTBED1_GENERATED_MQTT_SOURCES
    test_main.cpp
    test_structinterface.cpp
    test_structarrayinterface.cpp
    )


include_directories(test_testbed1_generated_mqtt
    PRIVATE
    $<BUILD_INTERFACE:${MODULES_DIR}>
)

add_executable(test_testbed1_generated_mqtt ${TEST_TESTBED1_GENERATED_MQTT_SOURCES})
add_test(NAME test_testbed1_generated_mqtt COMMAND $<TARGET_FILE:test_testbed1_generated_mqtt>)

target_link_libraries(test_testbed1_generated_mqtt PRIVATE
    testbed1-implementation
    testbed1-core
    testbed1-mqtt
    Catch2::Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(Catch)

install(TARGETS test_testbed1_generated_mqtt
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

