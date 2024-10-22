cmake_minimum_required(VERSION 3.24)
project(Testtb_simple)
include(CTest)
find_package(tb_simple CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add test for tb_simple
set (SOURCES_TEST
    main.cpp
)
add_executable(test_tb_simple
    ${SOURCES_TEST}
)
target_link_libraries(test_tb_simple tb_simple::tb_simple-implementation)
add_test(NAME test_tb_simple COMMAND $<TARGET_FILE:test_tb_simple>)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_tb_simple PRIVATE -Wall -Wextra -Wpedantic -Werror)
else()
  target_compile_options(test_tb_simple PRIVATE /W4 /WX /wd4251)
endif()
