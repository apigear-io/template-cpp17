{{- $module_id := snake .Module.Name -}}
{{- $module_idFirstUpper := upper1 $module_id -}}
{{- $SOURCES := printf "%s_SOURCES" $module_id -}}

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-olink)
{{- range .Module.Imports }}
find_package({{snake .Name}} REQUIRED COMPONENTS core)
{{- end }}
set (SOURCES_OLINK
{{- range .Module.Interfaces }}
{{- $interface:= . }}
    {{lower (camel $interface.Name)}}service.cpp
    {{lower (camel $interface.Name)}}client.cpp
{{- end }}
)
add_library({{$module_id}}-olink SHARED ${SOURCES_OLINK})
add_library({{$module_id}}::{{$module_id}}-olink ALIAS {{$module_id}}-olink)
target_include_directories({{$module_id}}-olink
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries({{$module_id}}-olink
    PRIVATE
    {{$module_id}}::{{$module_id}}-core
{{- range .Module.Imports }}
    {{snake .Name}}::{{snake .Name}}-core
{{- end }}
    PUBLIC
    apigear::poco-olink
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options({{$module_id}}-olink PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options({{$module_id}}-olink PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS {{$module_id}}-olink
        EXPORT {{$module_idFirstUpper}}OLinkTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/{{$module_id}}/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT {{$module_idFirstUpper}}OLinkTargets
  NAMESPACE {{$module_id}}::
)

install(EXPORT {{$module_idFirstUpper}}OLinkTargets
  FILE {{$module_idFirstUpper}}OLinkTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE {{$module_id }}::
)
