cmake_minimum_required(VERSION 3.24)
project(Testextern_types)
include(CTest)
find_package(extern_types CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add test for extern_types
set (SOURCES_TEST
    main.cpp
)
add_executable(test_extern_types
    ${SOURCES_TEST}
)
add_test(NAME test_extern_types COMMAND $<TARGET_FILE:test_extern_types>)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_extern_types PRIVATE -Wall -Wextra -Wpedantic -Werror)
else()
  target_compile_options(test_extern_types PRIVATE /W4 /WX /wd4251)
endif()
