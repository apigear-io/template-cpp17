set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
set (SOURCES_CORE_SUPPORT
    tb_names.json.adapter.cpp
    names.publisher.cpp
    names.threadsafedecorator.cpp
)
add_library(tb_names-core SHARED ${SOURCES_CORE_SUPPORT})
add_library(tb_names::tb_names-core ALIAS tb_names-core)
target_include_directories(tb_names-core
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_names-core PUBLIC tb_names::tb_names-api nlohmann_json::nlohmann_json)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_names-core PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_names-core PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_names-core
        EXPORT Tb_namesCoreTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_names/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_namesCoreTargets
  NAMESPACE tb_names::
)

install(EXPORT Tb_namesCoreTargets
  FILE Tb_namesCoreTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_names::
)
