set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
set (SOURCES_CORE_SUPPORT
    extern_types.json.adapter.cpp
)
add_library(extern_types-core SHARED ${SOURCES_CORE_SUPPORT})
add_library(extern_types::extern_types-core ALIAS extern_types-core)
target_include_directories(extern_types-core
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(extern_types-core PUBLIC extern_types::extern_types-api nlohmann_json::nlohmann_json)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(extern_types-core PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(extern_types-core PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS extern_types-core
        EXPORT Extern_typesCoreTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/extern_types/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Extern_typesCoreTargets
  NAMESPACE extern_types::
)

install(EXPORT Extern_typesCoreTargets
  FILE Extern_typesCoreTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE extern_types::
)
