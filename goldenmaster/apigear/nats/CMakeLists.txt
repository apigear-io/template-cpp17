find_package(nlohmann_json REQUIRED)
find_package(cnats REQUIRED)
if(TARGET cnats::nats_static)
message(STATUS "cnats library: found static library")
set(NATS_LIB cnats::nats_static)
if(TARGET cnats::nats_staticd)
    set(NATS_LIB_DEBUG cnats::nats_staticd)
else()
    set(NATS_LIB_DEBUG cnats::nats_static)
endif()
elseif(TARGET cnats::nats)
message(STATUS "cnats library: found dynamic library")
set(NATS_LIB cnats::nats)
if(TARGET cnats::natsd)
    set(NATS_LIB_DEBUG cnats::natsd)
else()
    set(NATS_LIB_DEBUG cnats::nats)
endif()
else()
message(FATAL_ERROR "cnats library not found")
endif()
find_package(apigear COMPONENTS utilities)

set (SOURCES
  private/natscwrapper.cpp
  natsbase.cpp
  natsclient.cpp
  natsservice.cpp
  baseadapter.cpp
)
add_library(nats SHARED ${SOURCES})
add_library(apigear::nats ALIAS nats)
target_include_directories(nats
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(nats PUBLIC utilities nlohmann_json::nlohmann_json )
if (CONAN_BUILD)
target_link_libraries(nats PRIVATE ${CONAN_NATS_LIB})
elseif(MSVC AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(nats PRIVATE ${NATS_LIB_DEBUG})
elseif(MSVC)
    target_link_libraries(nats PRIVATE ${NATS_LIB})
else()
target_link_libraries(nats PRIVATE debug ${NATS_LIB_DEBUG} optimized ${NATS_LIB})
endif()

if(NOT MSVC)
  target_compile_options(nats PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wnon-virtual-dtor -Woverloaded-virtual -Wcast-align -Werror -fvisibility=hidden -Wno-unknown-pragmas)
else()
  target_compile_options(nats PRIVATE /W4 /WX /wd4251)
endif()

 #add test cases
if(BUILD_TESTING)
enable_testing()
find_package(Catch2 REQUIRED)

set (SOURCES_TEST
    ../apigear.test.cpp
)
add_executable(test_nats ${SOURCES_TEST})
target_include_directories(test_nats PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_nats nats Catch2::Catch2)

add_test(NAME test_nats COMMAND $<TARGET_FILE:test_nats>)
endif(BUILD_TESTING)

# install binary files
install(TARGETS nats
        EXPORT ApiGearNatsTargets)
# install includes
FILE(GLOB APIGEAR_INCLUDES *.h)
install(FILES ${APIGEAR_INCLUDES}
        DESTINATION include/apigear/nats)

export(EXPORT ApiGearNatsTargets
  NAMESPACE apigear::
)

install(EXPORT ApiGearNatsTargets
  FILE ApiGearNatsTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE apigear::
)
