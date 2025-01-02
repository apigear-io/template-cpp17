set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set (SOURCES_CORE_IMPL
    manyparaminterface.cpp
    nestedstruct1interface.cpp
    nestedstruct2interface.cpp
    nestedstruct3interface.cpp
)
add_library(testbed2-implementation SHARED ${SOURCES_CORE_IMPL})
add_library(testbed2::testbed2-implementation ALIAS testbed2-implementation)
target_include_directories(testbed2-implementation
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(testbed2-implementation PUBLIC testbed2::testbed2-api PRIVATE testbed2::testbed2-core Threads::Threads)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(testbed2-implementation PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(testbed2-implementation PRIVATE /W4 /WX /wd4251)
endif()

# add test cases
if(BUILD_TESTING)

find_package(Catch2 REQUIRED)
find_package(apigear REQUIRED utilities)

set (SOURCES_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../generated/core/testbed2.test.cpp
    manyparaminterface.test.cpp
    nestedstruct1interface.test.cpp
    nestedstruct2interface.test.cpp
    nestedstruct3interface.test.cpp
)
add_executable(test_testbed2
    ${SOURCES_TEST}
)
target_link_libraries(test_testbed2 apigear::utilities testbed2::testbed2-implementation Catch2::Catch2)
target_include_directories(test_testbed2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_testbed2 PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(test_testbed2 PRIVATE /W4 /WX /wd4251)
endif()

add_test(NAME test_testbed2 COMMAND $<TARGET_FILE:test_testbed2>)
endif(BUILD_TESTING)

install(TARGETS testbed2-implementation
        EXPORT Testbed2ImplementationTargets)
# install includes
FILE(GLOB Testbed2_INCLUDES *.h)
install(FILES ${Testbed2_INCLUDES}
        DESTINATION include/testbed2/implementation)

export(EXPORT Testbed2ImplementationTargets
  NAMESPACE testbed2::
)

install(EXPORT Testbed2ImplementationTargets
  FILE Testbed2ImplementationTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE testbed2::
)
