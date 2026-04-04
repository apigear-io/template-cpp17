cmake_minimum_required(VERSION 3.24)
project(testbed2)

# needed to access CMAKE_INSTALL_LIBDIR
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(InstallDir ${CMAKE_INSTALL_LIBDIR}/cmake/testbed2)

# enable testing
if(BUILD_TESTING)
include(CTest)
enable_testing()
endif(BUILD_TESTING)

# define variable for library include paths
get_filename_component(MODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)
# Import APIGEAR_BUILD_WITH_* flags from installed apigear package.
# When built via top-level CMakeLists (FetchContent), these are already set.
find_package(apigear QUIET)

add_subdirectory(generated/api)
add_subdirectory(generated/core)
add_subdirectory(implementation)
if(APIGEAR_BUILD_WITH_MONITOR)
add_subdirectory(generated/monitor)
endif()
if(APIGEAR_BUILD_WITH_OLINK)
add_subdirectory(generated/olink)
endif()
if(APIGEAR_BUILD_WITH_MQTT)
add_subdirectory(generated/mqtt)
endif()
if(APIGEAR_BUILD_WITH_NATS)
add_subdirectory(generated/nats)
endif()

include(CMakePackageConfigHelpers)
configure_package_config_file(Testbed2Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/testbed2Config.cmake
  INSTALL_DESTINATION ${InstallDir})
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/testbed2ConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMinorVersion )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/testbed2Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/testbed2ConfigVersion.cmake
        DESTINATION ${InstallDir} )
