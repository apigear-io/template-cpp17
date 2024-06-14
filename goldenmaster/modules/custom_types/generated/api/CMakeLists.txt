set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES
    datastructs.api.cpp
)
add_library(custom_types-api SHARED ${SOURCES})
add_library(custom_types::custom_types-api ALIAS custom_types-api)
target_include_directories(custom_types-api
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(custom_types-api PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(custom_types-api PRIVATE /W4 /WX /wd4251)
endif()

# install binary files
install(TARGETS custom_types-api
        EXPORT Custom_typesApiTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/custom_types/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Custom_typesApiTargets
  NAMESPACE custom_types::
)

install(EXPORT Custom_typesApiTargets
  FILE Custom_typesApiTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE custom_types::
)
