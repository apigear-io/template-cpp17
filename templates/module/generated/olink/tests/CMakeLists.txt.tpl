{{- $module_id := printf "%s" (snake .Module.Name) }}
{{- $MODULE_ID := printf "%s" (SNAKE .Module.Name) }}
cmake_minimum_required(VERSION 3.24)
project(test_{{$module_id}}_generated_olink)

set(SPDLOG_DEBUG_ON true)
set(SPDLOG_TRACE_ON true)
include(CTest)

enable_testing()
find_package(apigear OPTIONAL_COMPONENTS poco-olink)
find_package({{$module_id}} QUIET COMPONENTS {{$module_id}}-implementation  {{$module_id}}-core {{$module_id}}-olink)

find_package(Catch2 REQUIRED)

set(TEST_{{$MODULE_ID}}_GENERATED_OLINK_SOURCES
    test_main.cpp
{{- range .Module.Interfaces }}
    test_{{lower (camel .Name)}}.cpp
{{- end }}
    )


include_directories(test_{{$module_id}}_generated_olink
    PRIVATE
    $<BUILD_INTERFACE:${MODULES_DIR}>
)

add_executable(test_{{$module_id}}_generated_olink ${TEST_{{$MODULE_ID}}_GENERATED_OLINK_SOURCES})
add_test(NAME test_{{$module_id}}_generated_olink COMMAND $<TARGET_FILE:test_{{$module_id}}_generated_olink>)

target_link_libraries(test_{{$module_id}}_generated_olink PRIVATE
    poco-olink
    {{$module_id}}-implementation
    {{$module_id}}-core
    {{$module_id}}-olink
{{- range .Module.Imports }}
    {{snake .Name}}::{{snake .Name}}-core
{{- end }}
    Catch2::Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(Catch)

install(TARGETS test_{{$module_id}}_generated_olink
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

