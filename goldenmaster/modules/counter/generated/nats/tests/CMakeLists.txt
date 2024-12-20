
cmake_minimum_required(VERSION 3.24)
project(test_counter_generated_nats)

set(SPDLOG_DEBUG_ON true)
set(SPDLOG_TRACE_ON true)
include(CTest)

enable_testing()
find_package(apigear OPTIONAL_COMPONENTS nats)
find_package(counter QUIET COMPONENTS counter-implementation  counter-core counter-nats)

find_package(Catch2 REQUIRED)

set(TEST_COUNTER_GENERATED_NATS_SOURCES
    test_main.cpp
    test_counter.cpp
    )


include_directories(test_counter_generated_nats
    PRIVATE
    $<BUILD_INTERFACE:${MODULES_DIR}>
)

add_executable(test_counter_generated_nats ${TEST_COUNTER_GENERATED_NATS_SOURCES})
add_test(NAME test_counter_generated_nats COMMAND $<TARGET_FILE:test_counter_generated_nats>)

target_link_libraries(test_counter_generated_nats PRIVATE
    apigear::nats
    counter-implementation
    counter-core
    counter-nats
    custom_types::custom_types-core
    extern_types::extern_types-core
    Catch2::Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(Catch)

install(TARGETS test_counter_generated_nats
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

