set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set (SOURCES_CORE_IMPL
    voidinterface.cpp
    simpleinterface.cpp
    simplearrayinterface.cpp
    nopropertiesinterface.cpp
    nooperationsinterface.cpp
    nosignalsinterface.cpp
)
add_library(tb_simple-implementation SHARED ${SOURCES_CORE_IMPL})
add_library(tb_simple::tb_simple-implementation ALIAS tb_simple-implementation)
target_include_directories(tb_simple-implementation
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_simple-implementation PUBLIC tb_simple::tb_simple-api PRIVATE tb_simple::tb_simple-core Threads::Threads)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_simple-implementation PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_simple-implementation PRIVATE /W4 /WX /wd4251)
endif()

# add test cases
if(BUILD_TESTING)

find_package(Catch2 REQUIRED)

set (SOURCES_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../generated/core/tb_simple.test.cpp
    voidinterface.test.cpp
    simpleinterface.test.cpp
    simplearrayinterface.test.cpp
    nopropertiesinterface.test.cpp
    nooperationsinterface.test.cpp
    nosignalsinterface.test.cpp
)
add_executable(test_tb_simple
    ${SOURCES_TEST}
)
target_link_libraries(test_tb_simple tb_simple::tb_simple-implementation Catch2::Catch2)
target_include_directories(test_tb_simple PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_tb_simple PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(test_tb_simple PRIVATE /W4 /WX /wd4251)
endif()

add_test(NAME test_tb_simple COMMAND $<TARGET_FILE:test_tb_simple>)
endif(BUILD_TESTING)

install(TARGETS tb_simple-implementation
        EXPORT Tb_simpleImplementationTargets)
# install includes
FILE(GLOB Tb_simple_INCLUDES *.h)
install(FILES ${Tb_simple_INCLUDES}
        DESTINATION include/tb_simple/implementation)

export(EXPORT Tb_simpleImplementationTargets
  NAMESPACE tb_simple::
)

install(EXPORT Tb_simpleImplementationTargets
  FILE Tb_simpleImplementationTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_simple::
)
