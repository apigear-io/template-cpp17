{{- $features := .Features -}}
cmake_minimum_required(VERSION 3.24)
project(OLinkClient)

# append local binary directory for conan packages to be found
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES
    main.cpp
)
add_executable(OLinkClient
    ${SOURCES}
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(OLinkClient PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(OLinkClient PRIVATE /W4 /WX /wd4251)
  # disable the warning for getenv - needs better cross platform solution
  target_compile_definitions(OLinkClient PRIVATE -D_CRT_SECURE_NO_WARNINGS)
endif()

{{- if $features.monitor }}

find_package(apigear REQUIRED COMPONENTS poco-tracer)
{{- end }}
{{- $features := .Features}}
{{- range .System.Modules }}
{{- $module := . }}
{{- $module_id := snake .Name }}
find_package({{$module_id}} REQUIRED COMPONENTS {{$module_id}}-core {{- if ( len $module.Interfaces ) }} {{$module_id}}-implementation 
{{- if $features.monitor }} {{$module_id}}-monitor {{- end }} {{$module_id}}-olink{{ end }})
{{- end }}
target_link_libraries(OLinkClient
{{- if $features.monitor }}
    apigear::poco-tracer
{{- end }}
{{- range .System.Modules }}
{{- $module := . }}
{{- $module_id := snake .Name }}
    {{- if ( len $module.Interfaces ) }}
    {{$module_id}}::{{$module_id}}-core
    {{$module_id}}::{{$module_id}}-implementation
{{ if $features.monitor }}    {{$module_id}}::{{$module_id}}-monitor {{- end }}
    {{$module_id}}::{{$module_id}}-olink
    {{- end }}
{{- end }}
)

install(TARGETS OLinkClient
        RUNTIME DESTINATION bin COMPONENT Runtime)
