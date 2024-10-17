set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set (SOURCES_CORE_IMPL
    enuminterface.cpp
)
add_library(tb_enum-implementation SHARED ${SOURCES_CORE_IMPL})
add_library(tb_enum::tb_enum-implementation ALIAS tb_enum-implementation)
target_include_directories(tb_enum-implementation
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_enum-implementation PUBLIC tb_enum::tb_enum-api PRIVATE tb_enum::tb_enum-core Threads::Threads)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_enum-implementation PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_enum-implementation PRIVATE /W4 /WX /wd4251)
endif()

# add test cases
if(BUILD_TESTING)

find_package(Catch2 REQUIRED)

set (SOURCES_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../generated/core/tb_enum.test.cpp
    enuminterface.test.cpp
)
add_executable(test_tb_enum
    ${SOURCES_TEST}
)
target_link_libraries(test_tb_enum tb_enum::tb_enum-implementation Catch2::Catch2)
target_include_directories(test_tb_enum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_tb_enum PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(test_tb_enum PRIVATE /W4 /WX /wd4251)
endif()

add_test(NAME test_tb_enum COMMAND $<TARGET_FILE:test_tb_enum>)
endif(BUILD_TESTING)

install(TARGETS tb_enum-implementation
        EXPORT Tb_enumImplementationTargets)
# install includes
FILE(GLOB Tb_enum_INCLUDES *.h)
install(FILES ${Tb_enum_INCLUDES}
        DESTINATION include/tb_enum/implementation)

export(EXPORT Tb_enumImplementationTargets
  NAMESPACE tb_enum::
)

install(EXPORT Tb_enumImplementationTargets
  FILE Tb_enumImplementationTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_enum::
)
