set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
set (SOURCES_CORE_SUPPORT
    custom_types.json.adapter.cpp
)
add_library(custom_types-core SHARED ${SOURCES_CORE_SUPPORT})
add_library(custom_types::custom_types-core ALIAS custom_types-core)
target_include_directories(custom_types-core
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(custom_types-core PUBLIC custom_types::custom_types-api nlohmann_json::nlohmann_json)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(custom_types-core PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(custom_types-core PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS custom_types-core
        EXPORT Custom_typesCoreTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/custom_types/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Custom_typesCoreTargets
  NAMESPACE custom_types::
)

install(EXPORT Custom_typesCoreTargets
  FILE Custom_typesCoreTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE custom_types::
)
