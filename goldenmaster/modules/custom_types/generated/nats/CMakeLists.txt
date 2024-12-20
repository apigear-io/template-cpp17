find_package(apigear OPTIONAL_COMPONENTS nats)
set (SOURCES_NATS
)
add_library(custom_types-nats SHARED ${SOURCES_NATS})
add_library(custom_types::custom_types-nats ALIAS custom_types-nats)
target_include_directories(custom_types-nats
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(custom_types-nats
    PRIVATE
    custom_types::custom_types-core
    PUBLIC
    apigear::nats
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(custom_types-nats PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(custom_types-nats PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS custom_types-nats
        EXPORT Custom_typesNatsTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/custom_types/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Custom_typesNatsTargets
  NAMESPACE custom_types::
)

install(EXPORT Custom_typesNatsTargets
  FILE Custom_typesNatsTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE custom_types::
)

if(BUILD_TESTING)
enable_testing()
add_subdirectory(tests)
endif()
