set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (SOURCES
    datastructs.api.cpp
)
add_library(tb_same1-api SHARED ${SOURCES})
add_library(tb_same1::tb_same1-api ALIAS tb_same1-api)
target_include_directories(tb_same1-api
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_same1-api PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_same1-api PRIVATE /W4 /WX /wd4251)
endif()

# install binary files
install(TARGETS tb_same1-api
        EXPORT Tb_same1ApiTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_same1/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_same1ApiTargets
  NAMESPACE tb_same1::
)

install(EXPORT Tb_same1ApiTargets
  FILE Tb_same1ApiTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_same1::
)
