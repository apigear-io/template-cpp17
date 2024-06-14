set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set (SOURCES_CORE_IMPL
    counter.cpp
)
add_library(counter-implementation SHARED ${SOURCES_CORE_IMPL})
add_library(counter::counter-implementation ALIAS counter-implementation)
target_include_directories(counter-implementation
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(counter-implementation PUBLIC counter::counter-api PRIVATE counter::counter-core Threads::Threads)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(counter-implementation PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(counter-implementation PRIVATE /W4 /WX /wd4251)
endif()

# add test cases
if(BUILD_TESTING)

find_package(Catch2 REQUIRED)

set (SOURCES_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../generated/core/counter.test.cpp
    counter.test.cpp
)
add_executable(test_counter
    ${SOURCES_TEST}
)
target_link_libraries(test_counter counter::counter-implementation Catch2::Catch2)
target_include_directories(test_counter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_counter PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(test_counter PRIVATE /W4 /WX /wd4251)
endif()

add_test(NAME test_counter COMMAND $<TARGET_FILE:test_counter>)
endif(BUILD_TESTING)

install(TARGETS counter-implementation
        EXPORT CounterImplementationTargets)
# install includes
FILE(GLOB Counter_INCLUDES *.h)
install(FILES ${Counter_INCLUDES}
        DESTINATION include/counter/implementation)

export(EXPORT CounterImplementationTargets
  NAMESPACE counter::
)

install(EXPORT CounterImplementationTargets
  FILE CounterImplementationTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE counter::
)
