cmake_minimum_required(VERSION 3.24)
project(Testtb_same2)
include(CTest)
find_package(tb_same2 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add test for tb_same2
set (SOURCES_TEST
    main.cpp
)
add_executable(test_tb_same2
    ${SOURCES_TEST}
)
target_link_libraries(test_tb_same2 tb_same2::tb_same2-implementation)
add_test(NAME test_tb_same2 COMMAND $<TARGET_FILE:test_tb_same2>)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_tb_same2 PRIVATE -Wall -Wextra -Wpedantic -Werror)
else()
  target_compile_options(test_tb_same2 PRIVATE /W4 /WX /wd4251)
endif()
