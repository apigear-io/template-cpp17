set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set (SOURCES_CORE_IMPL
    structinterface.cpp
    structarrayinterface.cpp
)
add_library(testbed1-implementation SHARED ${SOURCES_CORE_IMPL})
add_library(testbed1::testbed1-implementation ALIAS testbed1-implementation)
target_include_directories(testbed1-implementation
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(testbed1-implementation PUBLIC testbed1::testbed1-api PRIVATE testbed1::testbed1-core Threads::Threads)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(testbed1-implementation PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(testbed1-implementation PRIVATE /W4 /WX /wd4251)
endif()

# add test cases
if(BUILD_TESTING)

find_package(Catch2 REQUIRED)

set (SOURCES_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../generated/core/testbed1.test.cpp
    structinterface.test.cpp
    structarrayinterface.test.cpp
)
add_executable(test_testbed1
    ${SOURCES_TEST}
)
target_link_libraries(test_testbed1 testbed1::testbed1-implementation Catch2::Catch2)
target_include_directories(test_testbed1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_testbed1 PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(test_testbed1 PRIVATE /W4 /WX /wd4251)
endif()

add_test(NAME test_testbed1 COMMAND $<TARGET_FILE:test_testbed1>)
endif(BUILD_TESTING)

install(TARGETS testbed1-implementation
        EXPORT Testbed1ImplementationTargets)
# install includes
FILE(GLOB Testbed1_INCLUDES *.h)
install(FILES ${Testbed1_INCLUDES}
        DESTINATION include/testbed1/implementation)

export(EXPORT Testbed1ImplementationTargets
  NAMESPACE testbed1::
)

install(EXPORT Testbed1ImplementationTargets
  FILE Testbed1ImplementationTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE testbed1::
)
