cmake_minimum_required(VERSION 3.20)
project(Testcustom_types)
include(CTest)
find_package(custom_types CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add test for custom_types
set (SOURCES_TEST
    main.cpp
)
add_executable(test_custom_types
    ${SOURCES_TEST}
)
add_test(NAME test_custom_types COMMAND $<TARGET_FILE:test_custom_types>)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_custom_types PRIVATE -Wall -Wextra -Wpedantic -Werror)
else()
  target_compile_options(test_custom_types PRIVATE /W4 /WX /wd4251)
endif()
