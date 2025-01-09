find_package(apigear OPTIONAL_COMPONENTS paho-mqtt)
set (SOURCES_MQTT
    samestruct1interfaceservice.cpp
    samestruct1interfaceclient.cpp
    samestruct2interfaceservice.cpp
    samestruct2interfaceclient.cpp
    sameenum1interfaceservice.cpp
    sameenum1interfaceclient.cpp
    sameenum2interfaceservice.cpp
    sameenum2interfaceclient.cpp
)
add_library(tb_same1-mqtt SHARED ${SOURCES_MQTT})
add_library(tb_same1::tb_same1-mqtt ALIAS tb_same1-mqtt)
target_include_directories(tb_same1-mqtt
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_same1-mqtt
    PRIVATE
    tb_same1::tb_same1-core
    PUBLIC
    apigear::paho-mqtt
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_same1-mqtt PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_same1-mqtt PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_same1-mqtt
        EXPORT Tb_same1MqttTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_same1/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_same1MqttTargets
  NAMESPACE tb_same1::
)

install(EXPORT Tb_same1MqttTargets
  FILE Tb_same1MqttTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_same1::
)

if(BUILD_TESTING)
enable_testing()
if (ENABLE_MQTT_TEST_FOR_NON_LINUX_OS OR ((NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin") AND (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")))
add_subdirectory(tests)
endif()
endif()
