set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (SOURCES
    datastructs.api.cpp
)
add_library(testbed2-api SHARED ${SOURCES})
add_library(testbed2::testbed2-api ALIAS testbed2-api)
target_include_directories(testbed2-api
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(testbed2-api PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(testbed2-api PRIVATE /W4 /WX /wd4251)
endif()

# install binary files
install(TARGETS testbed2-api
        EXPORT Testbed2ApiTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/testbed2/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Testbed2ApiTargets
  NAMESPACE testbed2::
)

install(EXPORT Testbed2ApiTargets
  FILE Testbed2ApiTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE testbed2::
)
