cmake_minimum_required(VERSION 3.24)
project(NatsClient)

# append local binary directory for conan packages to be found
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES
    main.cpp
)
add_executable(NatsClient
    ${SOURCES}
)

find_package(apigear REQUIRED COMPONENTS utilities)
find_package(testbed2 REQUIRED COMPONENTS testbed2-core testbed2-nats)
find_package(tb_enum REQUIRED COMPONENTS tb_enum-core tb_enum-nats)
find_package(tb_same1 REQUIRED COMPONENTS tb_same1-core tb_same1-nats)
find_package(tb_same2 REQUIRED COMPONENTS tb_same2-core tb_same2-nats)
find_package(tb_simple REQUIRED COMPONENTS tb_simple-core tb_simple-nats)
find_package(testbed1 REQUIRED COMPONENTS testbed1-core testbed1-nats)
find_package(tb_names REQUIRED COMPONENTS tb_names-core tb_names-nats)
find_package(custom_types REQUIRED COMPONENTS custom_types-core)
find_package(extern_types REQUIRED COMPONENTS extern_types-core)
find_package(counter REQUIRED COMPONENTS counter-core counter-nats)
find_package(apigear REQUIRED COMPONENTS nats)
target_link_libraries(NatsClient
    apigear::utilities
    apigear::nats
    testbed2::testbed2-core
    testbed2::testbed2-nats
    tb_enum::tb_enum-core
    tb_enum::tb_enum-nats
    tb_same1::tb_same1-core
    tb_same1::tb_same1-nats
    tb_same2::tb_same2-core
    tb_same2::tb_same2-nats
    tb_simple::tb_simple-core
    tb_simple::tb_simple-nats
    testbed1::testbed1-core
    testbed1::testbed1-nats
    tb_names::tb_names-core
    tb_names::tb_names-nats
    counter::counter-core
    counter::counter-nats
)

# we assume that the examples are built together with the libraries and thus ignore this warning
if(MSVC)
  target_compile_options(NatsClient PRIVATE /wd4251)
endif()

install(TARGETS NatsClient
        RUNTIME DESTINATION bin COMPONENT Runtime)
