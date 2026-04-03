set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (SOURCES
    datastructs.api.cpp
)
add_library(tb_struct_array-api SHARED ${SOURCES})
add_library(tb_struct_array::tb_struct_array-api ALIAS tb_struct_array-api)
target_include_directories(tb_struct_array-api
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_struct_array-api PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wnon-virtual-dtor -Woverloaded-virtual -Wcast-align -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_struct_array-api PRIVATE /W4 /WX /wd4251)
endif()

# install binary files
install(TARGETS tb_struct_array-api
        EXPORT Tb_struct_arrayApiTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_struct_array/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_struct_arrayApiTargets
  NAMESPACE tb_struct_array::
)

install(EXPORT Tb_struct_arrayApiTargets
  FILE Tb_struct_arrayApiTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_struct_array::
)
