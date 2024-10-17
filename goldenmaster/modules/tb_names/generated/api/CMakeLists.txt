set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(tb_names-api INTERFACE)
add_library(tb_names::tb_names-api ALIAS tb_names-api)
target_include_directories(tb_names-api
    INTERFACE
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)

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
