cmake_minimum_required(VERSION 3.1)
project(OLinkClientSimuExample)

# append local binary directory for conan packages to be found
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES
    main.cpp
)
add_executable(OLinkClientSimuExample
    ${SOURCES}
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(OLinkClientSimuExample PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(OLinkClientSimuExample PRIVATE /W4 /WX /wd4251)
  # disable the warning for getenv - needs better cross platform solution
  target_compile_definitions(OLinkClientSimuExample PRIVATE -D_CRT_SECURE_NO_WARNINGS)
endif()

find_package(io_world QUIET COMPONENTS io_world-core io_world-implementation io_world-monitor io_world-olink)
target_link_libraries(OLinkClientSimuExample
    io_world::io_world-core
    io_world::io_world-implementation
    io_world::io_world-monitor
    io_world::io_world-olink
)

install(TARGETS OLinkClientSimuExample
        RUNTIME DESTINATION bin COMPONENT Runtime)
