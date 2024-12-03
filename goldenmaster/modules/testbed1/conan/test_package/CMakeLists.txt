cmake_minimum_required(VERSION 3.24)
project(Testtestbed1)
include(CTest)
find_package(testbed1 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add test for testbed1
set (SOURCES_TEST
    main.cpp
)
add_executable(test_testbed1
    ${SOURCES_TEST}
)
target_link_libraries(test_testbed1 testbed1::testbed1-implementation)
add_test(NAME test_testbed1 COMMAND $<TARGET_FILE:test_testbed1>)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_testbed1 PRIVATE -Wall -Wextra -Wpedantic -Werror)
else()
  target_compile_options(test_testbed1 PRIVATE /W4 /WX /wd4251)
endif()
