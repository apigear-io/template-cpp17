set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES
    datastructs.api.cpp
)
add_library(tb_enum-api SHARED ${SOURCES})
add_library(tb_enum::tb_enum-api ALIAS tb_enum-api)
target_include_directories(tb_enum-api
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_enum-api PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_enum-api PRIVATE /W4 /WX /wd4251)
endif()

# install binary files
install(TARGETS tb_enum-api
        EXPORT Tb_enumApiTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_enum/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_enumApiTargets
  NAMESPACE tb_enum::
)

install(EXPORT Tb_enumApiTargets
  FILE Tb_enumApiTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_enum::
)
