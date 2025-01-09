
cmake_minimum_required(VERSION 3.24)
project(test_extern_types_generated_mqtt)

set(SPDLOG_DEBUG_ON true)
set(SPDLOG_TRACE_ON true)
include(CTest)

enable_testing()
find_package(apigear OPTIONAL_COMPONENTS paho-mqtt)
find_package(extern_types QUIET COMPONENTS extern_types-implementation  extern_types-core extern_types-mqtt)

find_package(Catch2 REQUIRED)

set(TEST_EXTERN_TYPES_GENERATED_MQTT_SOURCES
    test_main.cpp
    )


include_directories(test_extern_types_generated_mqtt
    PRIVATE
    $<BUILD_INTERFACE:${MODULES_DIR}>
)

add_executable(test_extern_types_generated_mqtt ${TEST_EXTERN_TYPES_GENERATED_MQTT_SOURCES})
add_test(NAME test_extern_types_generated_mqtt COMMAND $<TARGET_FILE:test_extern_types_generated_mqtt>)

target_link_libraries(test_extern_types_generated_mqtt PRIVATE
    paho-mqtt
    extern_types-implementation
    extern_types-core
    extern_types-mqtt
    Catch2::Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(Catch)

install(TARGETS test_extern_types_generated_mqtt
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

