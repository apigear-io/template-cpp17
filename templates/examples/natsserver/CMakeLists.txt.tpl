cmake_minimum_required(VERSION 3.24)
project(NatsServer)

# append local binary directory for conan packages to be found
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES
    main.cpp
)
add_executable(NatsServer
    ${SOURCES}
)

find_package(apigear REQUIRED COMPONENTS utilities)
{{- range .System.Modules }}
{{- $module := . }}
{{- $module_id := snake .Name }}
find_package({{$module_id}} REQUIRED COMPONENTS {{$module_id}}-core {{- if ( len $module.Interfaces ) }} {{$module_id}}-implementation {{$module_id}}-nats{{ end }})
{{- end }}
target_link_libraries(NatsServer
    apigear::utilities
    apigear::nats
{{- range .System.Modules }}
{{- $module := . }}
{{- $module_id := snake .Name }}
    {{$module_id}}::{{$module_id}}-core
    {{- if ( len $module.Interfaces ) }}
    {{$module_id}}::{{$module_id}}-implementation
    {{$module_id}}::{{$module_id}}-nats
    {{- end }}
{{- end }}
)

# we assume that the examples are built together with the libraries and thus ignore this warning
if(MSVC)
  target_compile_options(NatsServer PRIVATE /wd4251)
endif()

install(TARGETS NatsServer
        RUNTIME DESTINATION bin COMPONENT Runtime)
