{{- $module_id := printf "%s" (snake .Module.Name) }}
{{- $MODULE_ID := printf "%s" (SNAKE .Module.Name) }}
cmake_minimum_required(VERSION 3.24)
project(test_{{$module_id}}_generated_mqtt)

set(SPDLOG_DEBUG_ON true)
set(SPDLOG_TRACE_ON true)
include(CTest)

enable_testing()
find_package(apigear OPTIONAL_COMPONENTS paho-mqtt)
find_package({{$module_id}} QUIET COMPONENTS {{$module_id}}-implementation  {{$module_id}}-core {{$module_id}}-mqtt)

find_package(Catch2 REQUIRED)

set(TEST_{{$MODULE_ID}}_GENERATED_MQTT_SOURCES
    test_main.cpp
{{- range .Module.Interfaces }}
    test_{{lower (camel .Name)}}.cpp
{{- end }}
    )


include_directories(test_{{$module_id}}_generated_mqtt
    PRIVATE
    $<BUILD_INTERFACE:${MODULES_DIR}>
)

add_executable(test_{{$module_id}}_generated_mqtt ${TEST_{{$MODULE_ID}}_GENERATED_MQTT_SOURCES})
add_test(NAME test_{{$module_id}}_generated_mqtt COMMAND $<TARGET_FILE:test_{{$module_id}}_generated_mqtt>)

target_link_libraries(test_{{$module_id}}_generated_mqtt PRIVATE
    paho-mqtt
    {{$module_id}}-implementation
    {{$module_id}}-core
    {{$module_id}}-mqtt
{{- range .Module.Imports }}
    {{snake .Name}}::{{snake .Name}}-core
{{- end }}
    Catch2::Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(Catch)

install(TARGETS test_{{$module_id}}_generated_mqtt
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

