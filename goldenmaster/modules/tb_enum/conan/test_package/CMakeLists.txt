cmake_minimum_required(VERSION 3.24)
project(Testtb_enum)
include(CTest)
find_package(tb_enum CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add test for tb_enum
set (SOURCES_TEST
    main.cpp
)
add_executable(test_tb_enum
    ${SOURCES_TEST}
)
target_link_libraries(test_tb_enum tb_enum::tb_enum-implementation)
add_test(NAME test_tb_enum COMMAND $<TARGET_FILE:test_tb_enum>)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_tb_enum PRIVATE -Wall -Wextra -Wpedantic -Werror)
else()
  target_compile_options(test_tb_enum PRIVATE /W4 /WX /wd4251)
endif()
