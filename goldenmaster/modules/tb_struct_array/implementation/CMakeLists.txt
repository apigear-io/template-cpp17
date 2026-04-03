set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set (SOURCES_CORE_IMPL
    structarrayfieldinterface.cpp
)
add_library(tb_struct_array-implementation SHARED ${SOURCES_CORE_IMPL})
add_library(tb_struct_array::tb_struct_array-implementation ALIAS tb_struct_array-implementation)
target_include_directories(tb_struct_array-implementation
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_struct_array-implementation PUBLIC tb_struct_array::tb_struct_array-api PRIVATE tb_struct_array::tb_struct_array-core Threads::Threads)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_struct_array-implementation PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wnon-virtual-dtor -Woverloaded-virtual -Wcast-align -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_struct_array-implementation PRIVATE /W4 /WX /wd4251)
endif()

# add test cases
if(BUILD_TESTING)

find_package(Catch2 REQUIRED)
find_package(apigear REQUIRED utilities)

set (SOURCES_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../generated/core/tb_struct_array.test.cpp
    structarrayfieldinterface.test.cpp
)
add_executable(test_tb_struct_array
    ${SOURCES_TEST}
)
target_link_libraries(test_tb_struct_array apigear::utilities tb_struct_array::tb_struct_array-implementation Catch2::Catch2)
target_include_directories(test_tb_struct_array PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_tb_struct_array PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wnon-virtual-dtor -Woverloaded-virtual -Wcast-align -Werror -fvisibility=hidden)
else()
  target_compile_options(test_tb_struct_array PRIVATE /W4 /WX /wd4251)
endif()

add_test(NAME test_tb_struct_array COMMAND $<TARGET_FILE:test_tb_struct_array>)
endif(BUILD_TESTING)

install(TARGETS tb_struct_array-implementation
        EXPORT Tb_struct_arrayImplementationTargets)
# install includes
FILE(GLOB Tb_struct_array_INCLUDES *.h)
install(FILES ${Tb_struct_array_INCLUDES}
        DESTINATION include/tb_struct_array/implementation)

export(EXPORT Tb_struct_arrayImplementationTargets
  NAMESPACE tb_struct_array::
)

install(EXPORT Tb_struct_arrayImplementationTargets
  FILE Tb_struct_arrayImplementationTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_struct_array::
)
