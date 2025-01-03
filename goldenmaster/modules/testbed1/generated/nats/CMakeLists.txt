find_package(apigear OPTIONAL_COMPONENTS nats)
set (SOURCES_NATS
    structinterfaceservice.cpp
    structinterfaceclient.cpp
    structarrayinterfaceservice.cpp
    structarrayinterfaceclient.cpp
)
add_library(testbed1-nats SHARED ${SOURCES_NATS})
add_library(testbed1::testbed1-nats ALIAS testbed1-nats)
target_include_directories(testbed1-nats
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(testbed1-nats
    PRIVATE
    testbed1::testbed1-core
    PUBLIC
    apigear::nats
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(testbed1-nats PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(testbed1-nats PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS testbed1-nats
        EXPORT Testbed1NatsTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/testbed1/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Testbed1NatsTargets
  NAMESPACE testbed1::
)

install(EXPORT Testbed1NatsTargets
  FILE Testbed1NatsTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE testbed1::
)

if(BUILD_TESTING)
enable_testing()
if (ENABLE_NATS_TEST_FOR_NON_LINUX_OS OR ((NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin") AND (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")))
add_subdirectory(tests)
endif()
endif()
