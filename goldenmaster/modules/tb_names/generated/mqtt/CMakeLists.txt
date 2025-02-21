find_package(apigear OPTIONAL_COMPONENTS paho-mqtt)
set (SOURCES_MQTT
    namesservice.cpp
    namesclient.cpp
)
add_library(tb_names-mqtt SHARED ${SOURCES_MQTT})
add_library(tb_names::tb_names-mqtt ALIAS tb_names-mqtt)
target_include_directories(tb_names-mqtt
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_names-mqtt
    PRIVATE
    tb_names::tb_names-core
    PUBLIC
    apigear::paho-mqtt
    apigear::utilities
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_names-mqtt PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_names-mqtt PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_names-mqtt
        EXPORT Tb_namesMqttTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_names/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_namesMqttTargets
  NAMESPACE tb_names::
)

install(EXPORT Tb_namesMqttTargets
  FILE Tb_namesMqttTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_names::
)

if(BUILD_TESTING)
enable_testing()
if (ENABLE_MQTT_TEST_FOR_NON_LINUX_OS OR ((NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin") AND (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")))
add_subdirectory(tests)
endif()
endif()
