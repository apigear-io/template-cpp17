{{- $module_id := snake .Module.Name -}}
{{- $module_idFirstUpper := upper1 $module_id -}}
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
{{- if  len .Module.Interfaces  }}
find_package(apigear REQUIRED utilities)
{{- end }}
set (SOURCES_CORE_SUPPORT
    {{$module_id}}.json.adapter.cpp
    test_struct_helper.cpp
{{- range .Module.Interfaces }}
{{- $interface:= . }}
    {{lower (camel $interface.Name)}}.publisher.cpp
    {{lower (camel $interface.Name)}}.threadsafedecorator.cpp
{{- end }}
)
add_library({{$module_id}}-core SHARED ${SOURCES_CORE_SUPPORT})
add_library({{$module_id}}::{{$module_id}}-core ALIAS {{$module_id}}-core)
target_include_directories({{$module_id}}-core
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries({{$module_id}}-core PUBLIC{{ if len .Module.Interfaces  }} apigear::utilities{{ end }} {{$module_id}}::{{$module_id}}-api nlohmann_json::nlohmann_json)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options({{$module_id}}-core PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options({{$module_id}}-core PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS {{$module_id}}-core
        EXPORT {{$module_idFirstUpper}}CoreTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/{{$module_id}}/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT {{$module_idFirstUpper}}CoreTargets
  NAMESPACE {{$module_id}}::
)

install(EXPORT {{$module_idFirstUpper}}CoreTargets
  FILE {{$module_idFirstUpper}}CoreTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE {{$module_id }}::
)
