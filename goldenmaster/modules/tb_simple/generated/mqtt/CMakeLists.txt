find_package(apigear OPTIONAL_COMPONENTS paho-mqtt)
set (SOURCES_MQTT
    voidinterfaceservice.cpp
    voidinterfaceclient.cpp
    simpleinterfaceservice.cpp
    simpleinterfaceclient.cpp
    simplearrayinterfaceservice.cpp
    simplearrayinterfaceclient.cpp
    nopropertiesinterfaceservice.cpp
    nopropertiesinterfaceclient.cpp
    nooperationsinterfaceservice.cpp
    nooperationsinterfaceclient.cpp
    nosignalsinterfaceservice.cpp
    nosignalsinterfaceclient.cpp
    emptyinterfaceservice.cpp
    emptyinterfaceclient.cpp
)
add_library(tb_simple-mqtt SHARED ${SOURCES_MQTT})
add_library(tb_simple::tb_simple-mqtt ALIAS tb_simple-mqtt)
target_include_directories(tb_simple-mqtt
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_simple-mqtt
    PRIVATE
    tb_simple::tb_simple-core
    PUBLIC
    apigear::paho-mqtt
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_simple-mqtt PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_simple-mqtt PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_simple-mqtt
        EXPORT Tb_simpleMqttTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_simple/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_simpleMqttTargets
  NAMESPACE tb_simple::
)

install(EXPORT Tb_simpleMqttTargets
  FILE Tb_simpleMqttTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_simple::
)
