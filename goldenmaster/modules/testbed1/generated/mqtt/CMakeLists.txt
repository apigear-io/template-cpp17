find_package(apigear OPTIONAL_COMPONENTS paho-mqtt)
set (SOURCES_MQTT
    structinterfaceservice.cpp
    structinterfaceclient.cpp
    structarrayinterfaceservice.cpp
    structarrayinterfaceclient.cpp
)
add_library(testbed1-mqtt SHARED ${SOURCES_MQTT})
add_library(testbed1::testbed1-mqtt ALIAS testbed1-mqtt)
target_include_directories(testbed1-mqtt
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(testbed1-mqtt
    PRIVATE
    testbed1::testbed1-core
    PUBLIC
    apigear::paho-mqtt
    apigear::utilities
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(testbed1-mqtt PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(testbed1-mqtt PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS testbed1-mqtt
        EXPORT Testbed1MqttTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/testbed1/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Testbed1MqttTargets
  NAMESPACE testbed1::
)

install(EXPORT Testbed1MqttTargets
  FILE Testbed1MqttTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE testbed1::
)

if(BUILD_TESTING)
enable_testing()
if (ENABLE_MQTT_TEST_FOR_NON_LINUX_OS OR ((NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin") AND (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")))
add_subdirectory(tests)
endif()
endif()
