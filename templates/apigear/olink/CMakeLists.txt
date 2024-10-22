cmake_minimum_required(VERSION 3.24)
project(poco-olink)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(olink_core REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Poco REQUIRED Foundation Net Util)

set (SOURCES
    olinkhost.cpp
    olinkconnection.cpp
    private/olinkremote.cpp
    private/olinkwebsockethandler.cpp
    private/requesthandlerfactory.cpp
    private/connectionstorage.cpp
    private/socketwrapper.cpp
)
add_library(poco-olink SHARED ${SOURCES})
add_library(apigear::poco-olink ALIAS poco-olink)
target_include_directories(poco-olink
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(poco-olink PUBLIC olink_core::olink_core apigear::utilities Poco::Net PRIVATE Poco::Util)


# install binary files
install(TARGETS poco-olink
        EXPORT ApiGearPocoOlinkTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/apigear FILES_MATCHING PATTERN "*.h")

export(EXPORT ApiGearPocoOlinkTargets
  NAMESPACE apigear::
)

install(EXPORT ApiGearPocoOlinkTargets
  FILE ApiGearPocoOlinkTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE apigear::
)

add_subdirectory (tests)
