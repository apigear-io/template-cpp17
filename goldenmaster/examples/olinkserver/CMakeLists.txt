cmake_minimum_required(VERSION 3.24)
project(OLinkServer)

# append local binary directory for conan packages to be found
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES
    main.cpp
)
add_executable(OLinkServer
    ${SOURCES}
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(OLinkServer PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(OLinkServer PRIVATE /W4 /WX /wd4251)
  # disable the warning for getenv - needs better cross platform solution
  target_compile_definitions(OLinkServer PRIVATE -D_CRT_SECURE_NO_WARNINGS)
endif()

find_package(apigear REQUIRED COMPONENTS utilities)
find_package(testbed2 REQUIRED COMPONENTS testbed2-core testbed2-implementation testbed2-olink)
find_package(tb_enum REQUIRED COMPONENTS tb_enum-core tb_enum-implementation tb_enum-olink)
find_package(tb_same1 REQUIRED COMPONENTS tb_same1-core tb_same1-implementation tb_same1-olink)
find_package(tb_same2 REQUIRED COMPONENTS tb_same2-core tb_same2-implementation tb_same2-olink)
find_package(tb_simple REQUIRED COMPONENTS tb_simple-core tb_simple-implementation tb_simple-olink)
find_package(testbed1 REQUIRED COMPONENTS testbed1-core testbed1-implementation testbed1-olink)
find_package(tb_names REQUIRED COMPONENTS tb_names-core tb_names-implementation tb_names-olink)
find_package(custom_types REQUIRED COMPONENTS custom_types-core)
find_package(extern_types REQUIRED COMPONENTS extern_types-core)
find_package(counter REQUIRED COMPONENTS counter-core counter-implementation counter-olink)
target_link_libraries(OLinkServer
    testbed2::testbed2-core
    testbed2::testbed2-implementation
    testbed2::testbed2-olink
    tb_enum::tb_enum-core
    tb_enum::tb_enum-implementation
    tb_enum::tb_enum-olink
    tb_same1::tb_same1-core
    tb_same1::tb_same1-implementation
    tb_same1::tb_same1-olink
    tb_same2::tb_same2-core
    tb_same2::tb_same2-implementation
    tb_same2::tb_same2-olink
    tb_simple::tb_simple-core
    tb_simple::tb_simple-implementation
    tb_simple::tb_simple-olink
    testbed1::testbed1-core
    testbed1::testbed1-implementation
    testbed1::testbed1-olink
    tb_names::tb_names-core
    tb_names::tb_names-implementation
    tb_names::tb_names-olink
    custom_types::custom_types-core
    extern_types::extern_types-core
    counter::counter-core
    counter::counter-implementation
    counter::counter-olink
)

install(TARGETS OLinkServer
        RUNTIME DESTINATION bin COMPONENT Runtime)
