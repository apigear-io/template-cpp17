set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (SOURCES
    datastructs.api.cpp
)
add_library(tb_names-api SHARED ${SOURCES})
add_library(tb_names::tb_names-api ALIAS tb_names-api)
target_include_directories(tb_names-api
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_names-api PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_names-api PRIVATE /W4 /WX /wd4251)
endif()

# install binary files
install(TARGETS tb_names-api
        EXPORT Tb_namesApiTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_names/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_namesApiTargets
  NAMESPACE tb_names::
)

install(EXPORT Tb_namesApiTargets
  FILE Tb_namesApiTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_names::
)
