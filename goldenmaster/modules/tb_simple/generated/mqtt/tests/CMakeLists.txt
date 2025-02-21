
cmake_minimum_required(VERSION 3.24)
project(test_tb_simple_generated_mqtt)

set(SPDLOG_DEBUG_ON true)
set(SPDLOG_TRACE_ON true)
include(CTest)

enable_testing()
find_package(apigear OPTIONAL_COMPONENTS paho-mqtt)
find_package(tb_simple QUIET COMPONENTS tb_simple-implementation  tb_simple-core tb_simple-mqtt)

find_package(Catch2 REQUIRED)

set(TEST_TB_SIMPLE_GENERATED_MQTT_SOURCES
    test_main.cpp
    test_voidinterface.cpp
    test_simpleinterface.cpp
    test_simplearrayinterface.cpp
    test_nopropertiesinterface.cpp
    test_nooperationsinterface.cpp
    test_nosignalsinterface.cpp
    )


include_directories(test_tb_simple_generated_mqtt
    PRIVATE
    $<BUILD_INTERFACE:${MODULES_DIR}>
)

add_executable(test_tb_simple_generated_mqtt ${TEST_TB_SIMPLE_GENERATED_MQTT_SOURCES})
add_test(NAME test_tb_simple_generated_mqtt COMMAND $<TARGET_FILE:test_tb_simple_generated_mqtt>)

target_link_libraries(test_tb_simple_generated_mqtt PRIVATE
    tb_simple-implementation
    tb_simple-core
    tb_simple-mqtt
    Catch2::Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(Catch)

install(TARGETS test_tb_simple_generated_mqtt
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

