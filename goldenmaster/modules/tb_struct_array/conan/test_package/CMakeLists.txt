cmake_minimum_required(VERSION 3.24)
project(Testtb_struct_array)
include(CTest)
find_package(tb_struct_array CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add test for tb_struct_array
set (SOURCES_TEST
    main.cpp
)
add_executable(test_tb_struct_array
    ${SOURCES_TEST}
)
target_link_libraries(test_tb_struct_array tb_struct_array::tb_struct_array-implementation)
add_test(NAME test_tb_struct_array COMMAND $<TARGET_FILE:test_tb_struct_array>)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_tb_struct_array PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wnon-virtual-dtor -Woverloaded-virtual -Wcast-align -Werror)
else()
  target_compile_options(test_tb_struct_array PRIVATE /W4 /WX /wd4251)
endif()
