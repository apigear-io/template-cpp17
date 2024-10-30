find_package(apigear OPTIONAL_COMPONENTS nats)
set (SOURCES_NATS
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
add_library(tb_simple-nats SHARED ${SOURCES_NATS})
add_library(tb_simple::tb_simple-nats ALIAS tb_simple-nats)
target_include_directories(tb_simple-nats
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_simple-nats
    PRIVATE
    tb_simple::tb_simple-core
    PUBLIC
    apigear::nats
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_simple-nats PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_simple-nats PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_simple-nats
        EXPORT Tb_simpleNatsTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_simple/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_simpleNatsTargets
  NAMESPACE tb_simple::
)

install(EXPORT Tb_simpleNatsTargets
  FILE Tb_simpleNatsTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_simple::
)
