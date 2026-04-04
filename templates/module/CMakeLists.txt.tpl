{{- $module_id := snake .Module.Name -}}
{{- $module_idFirstUpper := upper1 $module_id -}}
{{- $features := .Features -}}
cmake_minimum_required(VERSION 3.24)
project({{$module_id}})

# needed to access CMAKE_INSTALL_LIBDIR
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(InstallDir ${CMAKE_INSTALL_LIBDIR}/cmake/{{$module_id}})

# enable testing
if(BUILD_TESTING)
include(CTest)
enable_testing()
endif(BUILD_TESTING)

# define variable for library include paths
get_filename_component(MODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)

{{- if or $features.monitor $features.olink $features.mqtt $features.nats }}
# Import APIGEAR_BUILD_WITH_* flags from installed apigear package.
# When built via top-level CMakeLists (FetchContent), these are already set.
find_package(apigear QUIET)
{{- end }}

add_subdirectory(generated/api)
{{- if $features.core }}
add_subdirectory(generated/core)
{{- end}}
{{- if and $features.stubs ( len .Module.Interfaces ) }}
add_subdirectory(implementation)
{{- end}}
{{- if and $features.monitor ( len .Module.Interfaces ) }}
if(APIGEAR_BUILD_WITH_MONITOR)
add_subdirectory(generated/monitor)
endif()
{{- end}}
{{- if and $features.olink ( len .Module.Interfaces ) }}
if(APIGEAR_BUILD_WITH_OLINK)
add_subdirectory(generated/olink)
endif()
{{- end}}
{{- if and $features.mqtt ( len .Module.Interfaces ) }}
if(APIGEAR_BUILD_WITH_MQTT)
add_subdirectory(generated/mqtt)
endif()
{{- end}}
{{- if and $features.nats ( len .Module.Interfaces ) }}
if(APIGEAR_BUILD_WITH_NATS)
add_subdirectory(generated/nats)
endif()
{{- end}}

include(CMakePackageConfigHelpers)
configure_package_config_file({{$module_idFirstUpper}}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/{{$module_id}}Config.cmake
  INSTALL_DESTINATION ${InstallDir})
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/{{snake .Module.Name}}ConfigVersion.cmake
  VERSION {{.Module.Version}}
  COMPATIBILITY SameMinorVersion )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/{{snake .Module.Name}}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/{{snake .Module.Name}}ConfigVersion.cmake
        DESTINATION ${InstallDir} )
