cmake_minimum_required(VERSION 3.24)
project(Testtestbed2)
include(CTest)
find_package(testbed2 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add test for testbed2
set (SOURCES_TEST
    main.cpp
)
add_executable(test_testbed2
    ${SOURCES_TEST}
)
target_link_libraries(test_testbed2 testbed2::testbed2-implementation)
add_test(NAME test_testbed2 COMMAND $<TARGET_FILE:test_testbed2>)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_testbed2 PRIVATE -Wall -Wextra -Wpedantic -Werror)
else()
  target_compile_options(test_testbed2 PRIVATE /W4 /WX /wd4251)
endif()
