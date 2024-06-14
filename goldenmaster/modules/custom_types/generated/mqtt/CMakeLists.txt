find_package(apigear OPTIONAL_COMPONENTS paho-mqtt)
set (SOURCES_MQTT
)
add_library(custom_types-mqtt SHARED ${SOURCES_MQTT})
add_library(custom_types::custom_types-mqtt ALIAS custom_types-mqtt)
target_include_directories(custom_types-mqtt
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(custom_types-mqtt
    PRIVATE
    custom_types::custom_types-core
    PUBLIC
    apigear::paho-mqtt
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(custom_types-mqtt PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(custom_types-mqtt PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS custom_types-mqtt
        EXPORT Custom_typesMqttTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/custom_types/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Custom_typesMqttTargets
  NAMESPACE custom_types::
)

install(EXPORT Custom_typesMqttTargets
  FILE Custom_typesMqttTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE custom_types::
)
