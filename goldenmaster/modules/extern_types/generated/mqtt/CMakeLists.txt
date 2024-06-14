find_package(apigear OPTIONAL_COMPONENTS paho-mqtt)
set (SOURCES_MQTT
)
add_library(extern_types-mqtt SHARED ${SOURCES_MQTT})
add_library(extern_types::extern_types-mqtt ALIAS extern_types-mqtt)
target_include_directories(extern_types-mqtt
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(extern_types-mqtt
    PRIVATE
    extern_types::extern_types-core
    PUBLIC
    apigear::paho-mqtt
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(extern_types-mqtt PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(extern_types-mqtt PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS extern_types-mqtt
        EXPORT Extern_typesMqttTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/extern_types/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Extern_typesMqttTargets
  NAMESPACE extern_types::
)

install(EXPORT Extern_typesMqttTargets
  FILE Extern_typesMqttTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE extern_types::
)
