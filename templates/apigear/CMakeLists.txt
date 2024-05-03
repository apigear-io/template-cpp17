cmake_minimum_required(VERSION 3.20)
project(apigear)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(apigear_COMPONENTS "")

# needed to access CMAKE_INSTALL_LIBDIR
include(GNUInstallDirs)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(InstallDir ${CMAKE_INSTALL_LIBDIR}/cmake/apigear)

option(BUILD_TESTING "Enable this option to build the test targets" OFF)
option(APIGEAR_BUILD_WITH_OLINK "Enables the build of the OLINK backend" OFF)
option(APIGEAR_BUILD_WITH_MONITOR "Enables the build of the monitoring support library" OFF)
option(APIGEAR_BUILD_WITH_MQTT "Enables the build of the MQTT backend" OFF)
# this options is only here for the conan build until there is a conan based solution for objectlink-core
option(APIGEAR_FETCH_OLINKCORE "Fetch and build objectlink-core, if not pre-installed" OFF)

if(APIGEAR_FETCH_OLINKCORE)
find_package(olink_core QUIET)
if(NOT olink_core_FOUND)
  # pull olink_core as dependency
  message(STATUS "olink_core NOT FOUND, fetching the git repository")
  include(FetchContent)
  FetchContent_Declare(olink_core
      GIT_REPOSITORY https://github.com/apigear-io/objectlink-core-cpp.git
      GIT_TAG v0.2.10
      GIT_SHALLOW TRUE
      EXCLUDE_FROM_ALL FALSE
      OVERRIDE_FIND_PACKAGE
  )
  FetchContent_MakeAvailable(olink_core)
endif()
endif() # APIGEAR_FETCH_OLINKCORE

# enable testing
if(BUILD_TESTING)
include(CTest)
enable_testing()
endif(BUILD_TESTING)

add_subdirectory(utilities)
list(APPEND apigear_COMPONENTS "utilities")

if(APIGEAR_BUILD_WITH_MONITOR)
add_subdirectory(tracer)
list(APPEND apigear_COMPONENTS "tracer")
endif()

if(APIGEAR_BUILD_WITH_OLINK)
add_subdirectory(olink)
list(APPEND apigear_COMPONENTS "olink")
endif()

if(APIGEAR_BUILD_WITH_MQTT)
add_subdirectory(mqtt)
list(APPEND apigear_COMPONENTS "mqtt")
endif()

include(CMakePackageConfigHelpers)
configure_package_config_file(ApigearConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/apigearConfig.cmake
  INSTALL_DESTINATION ${InstallDir}
  PATH_VARS APIGEAR_BUILD_WITH_MONITOR APIGEAR_BUILD_WITH_OLINK APIGEAR_BUILD_WITH_MQTT)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/apigearConfigVersion.cmake
  VERSION 3.6.0
  COMPATIBILITY SameMinorVersion )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/apigearConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/apigearConfigVersion.cmake
        DESTINATION ${InstallDir} )
