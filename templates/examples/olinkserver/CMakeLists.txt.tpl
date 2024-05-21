cmake_minimum_required(VERSION 3.20)
project(OLinkServer)

# append local binary directory for conan packages to be found
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/cmake)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES
    main.cpp
)
add_executable(OLinkServer
    ${SOURCES}
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(OLinkServer PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(OLinkServer PRIVATE /W4 /WX /wd4251)
  # disable the warning for getenv - needs better cross platform solution
  target_compile_definitions(OLinkServer PRIVATE -D_CRT_SECURE_NO_WARNINGS)
endif()

find_package(apigear REQUIRED COMPONENTS utilities)
{{- range .System.Modules }}
{{- $module := . }}
{{- $module_id := snake .Name }}
find_package({{$module_id}} REQUIRED COMPONENTS {{$module_id}}-core {{- if ( len $module.Interfaces ) }} {{$module_id}}-implementation {{$module_id}}-olink{{ end }})
{{- end }}
target_link_libraries(OLinkServer
{{- range .System.Modules }}
{{- $module := . }}
{{- $module_id := snake .Name }}
    {{$module_id}}::{{$module_id}}-core
    {{- if ( len $module.Interfaces ) }}
    {{$module_id}}::{{$module_id}}-implementation
    {{$module_id}}::{{$module_id}}-olink
    {{- end }}
{{- end }}
)

install(TARGETS OLinkServer
        RUNTIME DESTINATION bin COMPONENT Runtime)
