find_package(apigear OPTIONAL_COMPONENTS nats)
find_package(custom_types REQUIRED COMPONENTS core)
find_package(extern_types REQUIRED COMPONENTS core)
set (SOURCES_NATS
    counterservice.cpp
    counterclient.cpp
)
add_library(counter-nats SHARED ${SOURCES_NATS})
add_library(counter::counter-nats ALIAS counter-nats)
target_include_directories(counter-nats
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(counter-nats
    PRIVATE
    counter::counter-core
    custom_types::custom_types-core
    extern_types::extern_types-core
    PUBLIC
    apigear::nats
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(counter-nats PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(counter-nats PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS counter-nats
        EXPORT CounterNatsTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/counter/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT CounterNatsTargets
  NAMESPACE counter::
)

install(EXPORT CounterNatsTargets
  FILE CounterNatsTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE counter::
)

if(BUILD_TESTING)
enable_testing()
add_subdirectory(tests)
endif()
