{{- $module_id := snake .Module.Name -}}
cmake_minimum_required(VERSION 3.20)
project(Test{{$module_id}})
include(CTest)
find_package({{$module_id}} CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add test for {{$module_id}}
set (SOURCES_TEST
    main.cpp
)
add_executable(test_{{$module_id}}
    ${SOURCES_TEST}
)
{{- if ( len .Module.Interfaces ) }}
target_link_libraries(test_{{$module_id}} {{$module_id}}::{{$module_id}}-implementation)
{{- end }}
add_test(NAME test_{{$module_id}} COMMAND $<TARGET_FILE:test_{{$module_id}}>)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_{{$module_id}} PRIVATE -Wall -Wextra -Wpedantic -Werror)
else()
  target_compile_options(test_{{$module_id}} PRIVATE /W4 /WX /wd4251)
endif()
