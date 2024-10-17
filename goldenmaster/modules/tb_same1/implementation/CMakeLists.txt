set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set (SOURCES_CORE_IMPL
    samestruct1interface.cpp
    samestruct2interface.cpp
    sameenum1interface.cpp
    sameenum2interface.cpp
)
add_library(tb_same1-implementation SHARED ${SOURCES_CORE_IMPL})
add_library(tb_same1::tb_same1-implementation ALIAS tb_same1-implementation)
target_include_directories(tb_same1-implementation
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_same1-implementation PUBLIC tb_same1::tb_same1-api PRIVATE tb_same1::tb_same1-core Threads::Threads)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_same1-implementation PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_same1-implementation PRIVATE /W4 /WX /wd4251)
endif()

# add test cases
if(BUILD_TESTING)

find_package(Catch2 REQUIRED)

set (SOURCES_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../generated/core/tb_same1.test.cpp
    samestruct1interface.test.cpp
    samestruct2interface.test.cpp
    sameenum1interface.test.cpp
    sameenum2interface.test.cpp
)
add_executable(test_tb_same1
    ${SOURCES_TEST}
)
target_link_libraries(test_tb_same1 tb_same1::tb_same1-implementation Catch2::Catch2)
target_include_directories(test_tb_same1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_tb_same1 PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(test_tb_same1 PRIVATE /W4 /WX /wd4251)
endif()

add_test(NAME test_tb_same1 COMMAND $<TARGET_FILE:test_tb_same1>)
endif(BUILD_TESTING)

install(TARGETS tb_same1-implementation
        EXPORT Tb_same1ImplementationTargets)
# install includes
FILE(GLOB Tb_same1_INCLUDES *.h)
install(FILES ${Tb_same1_INCLUDES}
        DESTINATION include/tb_same1/implementation)

export(EXPORT Tb_same1ImplementationTargets
  NAMESPACE tb_same1::
)

install(EXPORT Tb_same1ImplementationTargets
  FILE Tb_same1ImplementationTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_same1::
)
