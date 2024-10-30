find_package(apigear OPTIONAL_COMPONENTS nats)
set (SOURCES_NATS
    manyparaminterfaceservice.cpp
    manyparaminterfaceclient.cpp
    nestedstruct1interfaceservice.cpp
    nestedstruct1interfaceclient.cpp
    nestedstruct2interfaceservice.cpp
    nestedstruct2interfaceclient.cpp
    nestedstruct3interfaceservice.cpp
    nestedstruct3interfaceclient.cpp
)
add_library(testbed2-nats SHARED ${SOURCES_NATS})
add_library(testbed2::testbed2-nats ALIAS testbed2-nats)
target_include_directories(testbed2-nats
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(testbed2-nats
    PRIVATE
    testbed2::testbed2-core
    PUBLIC
    apigear::nats
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(testbed2-nats PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(testbed2-nats PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS testbed2-nats
        EXPORT Testbed2NatsTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/testbed2/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Testbed2NatsTargets
  NAMESPACE testbed2::
)

install(EXPORT Testbed2NatsTargets
  FILE Testbed2NatsTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE testbed2::
)
