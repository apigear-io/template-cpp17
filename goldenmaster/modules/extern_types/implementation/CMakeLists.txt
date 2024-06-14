set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set (SOURCES_CORE_IMPL
)
add_library(extern_types-implementation SHARED ${SOURCES_CORE_IMPL})
add_library(extern_types::extern_types-implementation ALIAS extern_types-implementation)
target_include_directories(extern_types-implementation
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(extern_types-implementation PUBLIC extern_types::extern_types-api PRIVATE extern_types::extern_types-core Threads::Threads)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(extern_types-implementation PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(extern_types-implementation PRIVATE /W4 /WX /wd4251)
endif()

# add test cases
if(BUILD_TESTING)

find_package(Catch2 REQUIRED)

set (SOURCES_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../generated/core/extern_types.test.cpp
)
add_executable(test_extern_types
    ${SOURCES_TEST}
)
target_link_libraries(test_extern_types extern_types::extern_types-implementation Catch2::Catch2)
target_include_directories(test_extern_types PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_extern_types PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(test_extern_types PRIVATE /W4 /WX /wd4251)
endif()

add_test(NAME test_extern_types COMMAND $<TARGET_FILE:test_extern_types>)
endif(BUILD_TESTING)

install(TARGETS extern_types-implementation
        EXPORT Extern_typesImplementationTargets)
# install includes
FILE(GLOB Extern_types_INCLUDES *.h)
install(FILES ${Extern_types_INCLUDES}
        DESTINATION include/extern_types/implementation)

export(EXPORT Extern_typesImplementationTargets
  NAMESPACE extern_types::
)

install(EXPORT Extern_typesImplementationTargets
  FILE Extern_typesImplementationTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE extern_types::
)
