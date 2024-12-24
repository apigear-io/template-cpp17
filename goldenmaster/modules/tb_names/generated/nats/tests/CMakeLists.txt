
cmake_minimum_required(VERSION 3.24)
project(test_tb_names_generated_nats)

set(SPDLOG_DEBUG_ON true)
set(SPDLOG_TRACE_ON true)
include(CTest)

enable_testing()
find_package(apigear OPTIONAL_COMPONENTS nats)
find_package(tb_names QUIET COMPONENTS tb_names-implementation  tb_names-core tb_names-nats)

find_package(Catch2 REQUIRED)

set(TEST_TB_NAMES_GENERATED_NATS_SOURCES
    test_main.cpp
    test_names.cpp
    )


include_directories(test_tb_names_generated_nats
    PRIVATE
    $<BUILD_INTERFACE:${MODULES_DIR}>
)

add_executable(test_tb_names_generated_nats ${TEST_TB_NAMES_GENERATED_NATS_SOURCES})
add_test(NAME test_tb_names_generated_nats COMMAND $<TARGET_FILE:test_tb_names_generated_nats>)

target_link_libraries(test_tb_names_generated_nats PRIVATE
    apigear::nats
    tb_names-implementation
    tb_names-core
    tb_names-nats
    Catch2::Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(Catch)

install(TARGETS test_tb_names_generated_nats
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

