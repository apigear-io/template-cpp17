set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(tb_simple-api INTERFACE)
add_library(tb_simple::tb_simple-api ALIAS tb_simple-api)
target_include_directories(tb_simple-api
    INTERFACE
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)

# install binary files
install(TARGETS tb_simple-api
        EXPORT Tb_simpleApiTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_simple/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_simpleApiTargets
  NAMESPACE tb_simple::
)

install(EXPORT Tb_simpleApiTargets
  FILE Tb_simpleApiTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_simple::
)
