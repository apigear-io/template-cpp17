find_package(nlohmann_json REQUIRED)
find_package(cnats COMPONENTS nats_static REQUIRED)
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
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(nats PRIVATE cnats::nats_static utilities PUBLIC nlohmann_json::nlohmann_json )

if(NOT MSVC)
  target_compile_options(nats PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden -Wno-unknown-pragmas)
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
