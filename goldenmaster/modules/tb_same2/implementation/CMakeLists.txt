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
add_library(tb_same2-implementation SHARED ${SOURCES_CORE_IMPL})
add_library(tb_same2::tb_same2-implementation ALIAS tb_same2-implementation)
target_include_directories(tb_same2-implementation
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_same2-implementation PUBLIC tb_same2::tb_same2-api PRIVATE tb_same2::tb_same2-core Threads::Threads)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_same2-implementation PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_same2-implementation PRIVATE /W4 /WX /wd4251)
endif()

# add test cases
if(BUILD_TESTING)

find_package(Catch2 REQUIRED)

set (SOURCES_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../generated/core/tb_same2.test.cpp
    samestruct1interface.test.cpp
    samestruct2interface.test.cpp
    sameenum1interface.test.cpp
    sameenum2interface.test.cpp
)
add_executable(test_tb_same2
    ${SOURCES_TEST}
)
target_link_libraries(test_tb_same2 tb_same2::tb_same2-implementation Catch2::Catch2)
target_include_directories(test_tb_same2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_tb_same2 PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(test_tb_same2 PRIVATE /W4 /WX /wd4251)
endif()

add_test(NAME test_tb_same2 COMMAND $<TARGET_FILE:test_tb_same2>)
endif(BUILD_TESTING)

install(TARGETS tb_same2-implementation
        EXPORT Tb_same2ImplementationTargets)
# install includes
FILE(GLOB Tb_same2_INCLUDES *.h)
install(FILES ${Tb_same2_INCLUDES}
        DESTINATION include/tb_same2/implementation)

export(EXPORT Tb_same2ImplementationTargets
  NAMESPACE tb_same2::
)

install(EXPORT Tb_same2ImplementationTargets
  FILE Tb_same2ImplementationTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_same2::
)
