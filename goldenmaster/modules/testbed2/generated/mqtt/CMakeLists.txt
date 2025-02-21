find_package(apigear OPTIONAL_COMPONENTS paho-mqtt)
set (SOURCES_MQTT
    manyparaminterfaceservice.cpp
    manyparaminterfaceclient.cpp
    nestedstruct1interfaceservice.cpp
    nestedstruct1interfaceclient.cpp
    nestedstruct2interfaceservice.cpp
    nestedstruct2interfaceclient.cpp
    nestedstruct3interfaceservice.cpp
    nestedstruct3interfaceclient.cpp
)
add_library(testbed2-mqtt SHARED ${SOURCES_MQTT})
add_library(testbed2::testbed2-mqtt ALIAS testbed2-mqtt)
target_include_directories(testbed2-mqtt
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(testbed2-mqtt
    PRIVATE
    testbed2::testbed2-core
    PUBLIC
    apigear::paho-mqtt
    apigear::utilities
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(testbed2-mqtt PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(testbed2-mqtt PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS testbed2-mqtt
        EXPORT Testbed2MqttTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/testbed2/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Testbed2MqttTargets
  NAMESPACE testbed2::
)

install(EXPORT Testbed2MqttTargets
  FILE Testbed2MqttTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE testbed2::
)

if(BUILD_TESTING)
enable_testing()
if (ENABLE_MQTT_TEST_FOR_NON_LINUX_OS OR ((NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin") AND (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")))
add_subdirectory(tests)
endif()
endif()
