cmake_minimum_required(VERSION 3.24)
project(MQTTServer)

# append local binary directory for conan packages to be found
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES
    main.cpp
)
add_executable(MQTTServer
    ${SOURCES}
)

find_package(apigear REQUIRED COMPONENTS utilities)
find_package(testbed2 REQUIRED COMPONENTS testbed2-core testbed2-implementation testbed2-mqtt)
find_package(tb_enum REQUIRED COMPONENTS tb_enum-core tb_enum-implementation tb_enum-mqtt)
find_package(tb_same1 REQUIRED COMPONENTS tb_same1-core tb_same1-implementation tb_same1-mqtt)
find_package(tb_same2 REQUIRED COMPONENTS tb_same2-core tb_same2-implementation tb_same2-mqtt)
find_package(tb_simple REQUIRED COMPONENTS tb_simple-core tb_simple-implementation tb_simple-mqtt)
find_package(testbed1 REQUIRED COMPONENTS testbed1-core testbed1-implementation testbed1-mqtt)
find_package(tb_names REQUIRED COMPONENTS tb_names-core tb_names-implementation tb_names-mqtt)
find_package(custom_types REQUIRED COMPONENTS custom_types-core)
find_package(extern_types REQUIRED COMPONENTS extern_types-core)
find_package(counter REQUIRED COMPONENTS counter-core counter-implementation counter-mqtt)
target_link_libraries(MQTTServer
    apigear::utilities
    testbed2::testbed2-core
    testbed2::testbed2-implementation
    testbed2::testbed2-mqtt
    tb_enum::tb_enum-core
    tb_enum::tb_enum-implementation
    tb_enum::tb_enum-mqtt
    tb_same1::tb_same1-core
    tb_same1::tb_same1-implementation
    tb_same1::tb_same1-mqtt
    tb_same2::tb_same2-core
    tb_same2::tb_same2-implementation
    tb_same2::tb_same2-mqtt
    tb_simple::tb_simple-core
    tb_simple::tb_simple-implementation
    tb_simple::tb_simple-mqtt
    testbed1::testbed1-core
    testbed1::testbed1-implementation
    testbed1::testbed1-mqtt
    tb_names::tb_names-core
    tb_names::tb_names-implementation
    tb_names::tb_names-mqtt
    custom_types::custom_types-core
    extern_types::extern_types-core
    counter::counter-core
    counter::counter-implementation
    counter::counter-mqtt
)

# we assume that the examples are built together with the libraries and thus ignore this warning
if(MSVC)
  target_compile_options(MQTTServer PRIVATE /wd4251)
endif()

install(TARGETS MQTTServer
        RUNTIME DESTINATION bin COMPONENT Runtime)
