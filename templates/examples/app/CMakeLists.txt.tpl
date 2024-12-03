{{- $features := .Features -}}
cmake_minimum_required(VERSION 3.24)
project(App)

# append local binary directory for conan packages to be found
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES
    main.cpp
)
add_executable(app
    ${SOURCES}
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(app PRIVATE /W4 /WX /wd4251)
endif()
{{- nl }}

{{- range .System.Modules }}
{{- $module := . }}
{{- $module_id := snake .Name }}
find_package({{$module_id}} REQUIRED COMPONENTS {{$module_id}}-core {{- if ( len $module.Interfaces ) }} {{$module_id}}-implementation {{ if $features.monitor }}{{$module_id}}-monitor {{- end}} {{- end }})
{{- end }}
{{- if $features.monitor }}
find_package(apigear REQUIRED COMPONENTS poco-tracer)
{{- end }}
target_link_libraries(app
{{- if $features.monitor }}
    apigear::poco-tracer
{{- end }}
{{- range .System.Modules }}
{{- $module := . }}
{{- $module_id := snake .Name }}
    {{$module_id}}::{{$module_id}}-core
    {{- if ( len $module.Interfaces ) }}
    {{$module_id}}::{{$module_id}}-implementation
    {{ if $features.monitor }}{{$module_id}}::{{$module_id}}-monitor {{- end}}
    {{- end }}
{{- end }}
)

install(TARGETS app
        RUNTIME DESTINATION bin COMPONENT Runtime)
