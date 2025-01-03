find_package(apigear OPTIONAL_COMPONENTS nats)
set (SOURCES_NATS
    namesservice.cpp
    namesclient.cpp
)
add_library(tb_names-nats SHARED ${SOURCES_NATS})
add_library(tb_names::tb_names-nats ALIAS tb_names-nats)
target_include_directories(tb_names-nats
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_names-nats
    PRIVATE
    tb_names::tb_names-core
    PUBLIC
    apigear::nats
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_names-nats PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_names-nats PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_names-nats
        EXPORT Tb_namesNatsTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_names/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_namesNatsTargets
  NAMESPACE tb_names::
)

install(EXPORT Tb_namesNatsTargets
  FILE Tb_namesNatsTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_names::
)

if(BUILD_TESTING)
enable_testing()
if (ENABLE_NATS_TEST_FOR_NON_LINUX_OS OR ((NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin") AND (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")))
add_subdirectory(tests)
endif()
endif()
