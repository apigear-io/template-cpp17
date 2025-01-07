
cmake_minimum_required(VERSION 3.24)
project(test_extern_types_generated_olink)

set(SPDLOG_DEBUG_ON true)
set(SPDLOG_TRACE_ON true)
include(CTest)

enable_testing()
find_package(apigear OPTIONAL_COMPONENTS poco-olink)
find_package(extern_types QUIET COMPONENTS extern_types-implementation  extern_types-core extern_types-olink)

find_package(Catch2 REQUIRED)

set(TEST_EXTERN_TYPES_GENERATED_OLINK_SOURCES
    test_main.cpp
    )


include_directories(test_extern_types_generated_olink
    PRIVATE
    $<BUILD_INTERFACE:${MODULES_DIR}>
)

add_executable(test_extern_types_generated_olink ${TEST_EXTERN_TYPES_GENERATED_OLINK_SOURCES})
add_test(NAME test_extern_types_generated_olink COMMAND $<TARGET_FILE:test_extern_types_generated_olink>)

target_link_libraries(test_extern_types_generated_olink PRIVATE
    poco-olink
    extern_types-implementation
    extern_types-core
    extern_types-olink
    Catch2::Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(Catch)

install(TARGETS test_extern_types_generated_olink
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

