set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set (SOURCES_CORE_IMPL
)
add_library(custom_types-implementation SHARED ${SOURCES_CORE_IMPL})
add_library(custom_types::custom_types-implementation ALIAS custom_types-implementation)
target_include_directories(custom_types-implementation
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(custom_types-implementation PUBLIC custom_types::custom_types-api PRIVATE custom_types::custom_types-core Threads::Threads)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(custom_types-implementation PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(custom_types-implementation PRIVATE /W4 /WX /wd4251)
endif()

# add test cases
if(BUILD_TESTING)

find_package(Catch2 REQUIRED)

set (SOURCES_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../generated/core/custom_types.test.cpp
)
add_executable(test_custom_types
    ${SOURCES_TEST}
)
target_link_libraries(test_custom_types custom_types::custom_types-implementation Catch2::Catch2)
target_include_directories(test_custom_types PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_custom_types PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(test_custom_types PRIVATE /W4 /WX /wd4251)
endif()

add_test(NAME test_custom_types COMMAND $<TARGET_FILE:test_custom_types>)
endif(BUILD_TESTING)

install(TARGETS custom_types-implementation
        EXPORT Custom_typesImplementationTargets)
# install includes
FILE(GLOB Custom_types_INCLUDES *.h)
install(FILES ${Custom_types_INCLUDES}
        DESTINATION include/custom_types/implementation)

export(EXPORT Custom_typesImplementationTargets
  NAMESPACE custom_types::
)

install(EXPORT Custom_typesImplementationTargets
  FILE Custom_typesImplementationTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE custom_types::
)
