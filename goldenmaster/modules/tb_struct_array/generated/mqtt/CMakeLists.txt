find_package(apigear OPTIONAL_COMPONENTS paho-mqtt)
set (SOURCES_MQTT
    structarrayfieldinterfaceservice.cpp
    structarrayfieldinterfaceclient.cpp
)
add_library(tb_struct_array-mqtt SHARED ${SOURCES_MQTT})
add_library(tb_struct_array::tb_struct_array-mqtt ALIAS tb_struct_array-mqtt)
target_include_directories(tb_struct_array-mqtt
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_struct_array-mqtt
    PRIVATE
    tb_struct_array::tb_struct_array-core
    PUBLIC
    apigear::paho-mqtt
    apigear::utilities
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_struct_array-mqtt PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wnon-virtual-dtor -Woverloaded-virtual -Wcast-align -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_struct_array-mqtt PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_struct_array-mqtt
        EXPORT Tb_struct_arrayMqttTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_struct_array/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_struct_arrayMqttTargets
  NAMESPACE tb_struct_array::
)

install(EXPORT Tb_struct_arrayMqttTargets
  FILE Tb_struct_arrayMqttTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_struct_array::
)

if(BUILD_TESTING)
enable_testing()
if (ENABLE_MQTT_TEST_FOR_NON_LINUX_OS OR ((NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin") AND (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")))
add_subdirectory(tests)
endif()
endif()
