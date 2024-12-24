{{- $module_id := snake .Module.Name -}}
{{- $module_idFirstUpper := upper1 $module_id -}}
{{- $SOURCES := printf "%s_SOURCES" $module_id -}}

find_package(apigear OPTIONAL_COMPONENTS nats)
{{- range .Module.Imports }}
find_package({{snake .Name}} REQUIRED COMPONENTS core)
{{- end }}
set (SOURCES_NATS
{{- range .Module.Interfaces }}
{{- $interface:= . }}
    {{lower (camel $interface.Name)}}service.cpp
    {{lower (camel $interface.Name)}}client.cpp
{{- end }}
)
add_library({{$module_id}}-nats SHARED ${SOURCES_NATS})
add_library({{$module_id}}::{{$module_id}}-nats ALIAS {{$module_id}}-nats)
target_include_directories({{$module_id}}-nats
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries({{$module_id}}-nats
    PRIVATE
    {{$module_id}}::{{$module_id}}-core
{{- range .Module.Imports }}
    {{snake .Name}}::{{snake .Name}}-core
{{- end }}
    PUBLIC
    apigear::nats
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options({{$module_id}}-nats PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options({{$module_id}}-nats PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS {{$module_id}}-nats
        EXPORT {{$module_idFirstUpper}}NatsTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/{{$module_id}}/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT {{$module_idFirstUpper}}NatsTargets
  NAMESPACE {{$module_id}}::
)

install(EXPORT {{$module_idFirstUpper}}NatsTargets
  FILE {{$module_idFirstUpper}}NatsTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE {{$module_id }}::
)
