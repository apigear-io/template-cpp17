find_package(apigear OPTIONAL_COMPONENTS nats)
set (SOURCES_NATS
    enuminterfaceservice.cpp
    enuminterfaceclient.cpp
)
add_library(tb_enum-nats SHARED ${SOURCES_NATS})
add_library(tb_enum::tb_enum-nats ALIAS tb_enum-nats)
target_include_directories(tb_enum-nats
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_enum-nats
    PRIVATE
    tb_enum::tb_enum-core
    PUBLIC
    apigear::nats
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_enum-nats PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_enum-nats PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_enum-nats
        EXPORT Tb_enumNatsTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_enum/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_enumNatsTargets
  NAMESPACE tb_enum::
)

install(EXPORT Tb_enumNatsTargets
  FILE Tb_enumNatsTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_enum::
)

if(BUILD_TESTING)
enable_testing()
if (ENABLE_NATS_TEST_FOR_NON_LINUX_OS OR ((NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin") AND (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")))
add_subdirectory(tests)
endif()
endif()
