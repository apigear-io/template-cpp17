cmake_minimum_required(VERSION 3.20)
project(utilities)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (SOURCES
    logger.cpp
    threadpool.cpp
)
add_library(utilities SHARED ${SOURCES})
add_library(apigear::utilities ALIAS utilities)
target_include_directories(utilities
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
    $<INSTALL_INTERFACE:include>
)

# install binary files
install(TARGETS utilities
        EXPORT ApiGearUtilitiesTargets)
# install includes
FILE(GLOB_RECURSE APIGEAR_INCLUDES *.h)
install(FILES ${APIGEAR_INCLUDES}
        DESTINATION include/apigear/utilities)

export(EXPORT ApiGearUtilitiesTargets
  NAMESPACE apigear::
)

install(EXPORT ApiGearUtilitiesTargets
  FILE ApiGearUtilitiesTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE apigear::
)

add_subdirectory (tests)
