cmake_minimum_required(VERSION 3.20)
project(AppThreadSafe)

# append local binary directory for conan packages to be found
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES
    main.cpp
)
add_executable(appthreadsafe
    ${SOURCES}
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(appthreadsafe PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(appthreadsafe PRIVATE /W4 /WX /wd4251)
endif()

find_package(testbed2 REQUIRED COMPONENTS testbed2-core testbed2-implementation)
find_package(tb_enum REQUIRED COMPONENTS tb_enum-core tb_enum-implementation)
find_package(tb_same1 REQUIRED COMPONENTS tb_same1-core tb_same1-implementation)
find_package(tb_same2 REQUIRED COMPONENTS tb_same2-core tb_same2-implementation)
find_package(tb_simple REQUIRED COMPONENTS tb_simple-core tb_simple-implementation)
find_package(testbed1 REQUIRED COMPONENTS testbed1-core testbed1-implementation)
find_package(tb_names REQUIRED COMPONENTS tb_names-core tb_names-implementation)
find_package(custom_types REQUIRED COMPONENTS custom_types-core)
find_package(extern_types REQUIRED COMPONENTS extern_types-core)
find_package(counter REQUIRED COMPONENTS counter-core counter-implementation)
target_link_libraries(appthreadsafe
    testbed2::testbed2-core
    testbed2::testbed2-implementation
    tb_enum::tb_enum-core
    tb_enum::tb_enum-implementation
    tb_same1::tb_same1-core
    tb_same1::tb_same1-implementation
    tb_same2::tb_same2-core
    tb_same2::tb_same2-implementation
    tb_simple::tb_simple-core
    tb_simple::tb_simple-implementation
    testbed1::testbed1-core
    testbed1::testbed1-implementation
    tb_names::tb_names-core
    tb_names::tb_names-implementation
    counter::counter-core
    counter::counter-implementation
)

install(TARGETS appthreadsafe
        RUNTIME DESTINATION bin COMPONENT Runtime)
