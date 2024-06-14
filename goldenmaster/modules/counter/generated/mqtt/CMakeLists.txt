find_package(apigear OPTIONAL_COMPONENTS paho-mqtt)
find_package(custom_types REQUIRED COMPONENTS core)
find_package(extern_types REQUIRED COMPONENTS core)
set (SOURCES_MQTT
    counterservice.cpp
    counterclient.cpp
)
add_library(counter-mqtt SHARED ${SOURCES_MQTT})
add_library(counter::counter-mqtt ALIAS counter-mqtt)
target_include_directories(counter-mqtt
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(counter-mqtt
    PRIVATE
    counter::counter-core
    custom_types::custom_types-core
    extern_types::extern_types-core
    PUBLIC
    apigear::paho-mqtt
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(counter-mqtt PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(counter-mqtt PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS counter-mqtt
        EXPORT CounterMqttTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/counter/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT CounterMqttTargets
  NAMESPACE counter::
)

install(EXPORT CounterMqttTargets
  FILE CounterMqttTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE counter::
)
