cmake_minimum_required(VERSION 3.24)
project(Testcounter)
include(CTest)
find_package(counter CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add test for counter
set (SOURCES_TEST
    main.cpp
)
add_executable(test_counter
    ${SOURCES_TEST}
)
target_link_libraries(test_counter counter::counter-implementation)
add_test(NAME test_counter COMMAND $<TARGET_FILE:test_counter>)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_counter PRIVATE -Wall -Wextra -Wpedantic -Werror)
else()
  target_compile_options(test_counter PRIVATE /W4 /WX /wd4251)
endif()
