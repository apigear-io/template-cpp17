{{- $module_id := snake .Module.Name -}}
{{- $module_idFirstUpper := upper1 $module_id -}}
{{- $features := .Features -}}
cmake_minimum_required(VERSION 3.20)
project({{$module_id}})

# needed to access CMAKE_INSTALL_LIBDIR
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 14)
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

add_subdirectory(generated/api)
{{- if $features.core }}
add_subdirectory(generated/core)
{{- end}}
{{- if and $features.stubs ( len .Module.Interfaces ) }}
add_subdirectory(implementation)
{{- end}}
{{- if and $features.monitor ( len .Module.Interfaces ) }}
add_subdirectory(generated/monitor)
{{- end}}
{{- if and $features.olink ( len .Module.Interfaces ) }}
add_subdirectory(generated/olink)
{{- end}}
{{- if and $features.mqtt ( len .Module.Interfaces ) }}
add_subdirectory(generated/mqtt)
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
