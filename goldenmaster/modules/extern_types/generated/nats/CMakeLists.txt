find_package(apigear OPTIONAL_COMPONENTS nats)
set (SOURCES_NATS
)
add_library(extern_types-nats SHARED ${SOURCES_NATS})
add_library(extern_types::extern_types-nats ALIAS extern_types-nats)
target_include_directories(extern_types-nats
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(extern_types-nats
    PRIVATE
    extern_types::extern_types-core
    PUBLIC
    apigear::nats
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(extern_types-nats PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(extern_types-nats PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS extern_types-nats
        EXPORT Extern_typesNatsTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/extern_types/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Extern_typesNatsTargets
  NAMESPACE extern_types::
)

install(EXPORT Extern_typesNatsTargets
  FILE Extern_typesNatsTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE extern_types::
)

if(BUILD_TESTING)
enable_testing()
add_subdirectory(tests)
endif()
