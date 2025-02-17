set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-olink)
set (SOURCES_OLINK
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
add_library(tb_simple-olink SHARED ${SOURCES_OLINK})
add_library(tb_simple::tb_simple-olink ALIAS tb_simple-olink)
target_include_directories(tb_simple-olink
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_simple-olink
    PRIVATE
    tb_simple::tb_simple-core
    PUBLIC
    apigear::poco-olink
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_simple-olink PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_simple-olink PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_simple-olink
        EXPORT Tb_simpleOLinkTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_simple/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_simpleOLinkTargets
  NAMESPACE tb_simple::
)

install(EXPORT Tb_simpleOLinkTargets
  FILE Tb_simpleOLinkTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_simple::
)
