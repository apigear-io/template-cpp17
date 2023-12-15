{{- $module_id := snake .Module.Name -}}
{{- $module_idFirstUpper := upper1 $module_id -}}
{{- $SOURCES := printf "%s_SOURCES" $module_id -}}

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear QUIET COMPONENTS poco-tracer)
set (SOURCES_MONITOR
{{- range .Module.Interfaces }}
{{- $interface:= . }}
    {{lower (camel $interface.Name)}}.tracedecorator.cpp
    {{lower (camel $interface.Name)}}.tracer.cpp
{{- end }}
)
add_library({{$module_id}}-monitor SHARED ${SOURCES_MONITOR})
add_library({{$module_id}}::{{$module_id}}-monitor ALIAS {{$module_id}}-monitor)
target_include_directories({{$module_id}}-monitor
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../modules>
    $<INSTALL_INTERFACE:include/{{$module_id}}>
)
target_link_libraries({{$module_id}}-monitor PUBLIC
    {{$module_id}}::{{$module_id}}-core
    apigear::poco-tracer
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options({{$module_id}}-monitor PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options({{$module_id}}-monitor PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS {{$module_id}}-monitor
        EXPORT {{$module_idFirstUpper}}MonitorTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/{{$module_id}}/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT {{$module_idFirstUpper}}MonitorTargets
  NAMESPACE {{$module_id}}::
)

install(EXPORT {{$module_idFirstUpper}}MonitorTargets
  FILE {{$module_idFirstUpper}}MonitorTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE {{$module_id }}::
)
