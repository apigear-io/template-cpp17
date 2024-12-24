set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
set (SOURCES_CORE_SUPPORT
    tb_enum.json.adapter.cpp
    test_struct_helper.cpp
    enuminterface.publisher.cpp
    enuminterface.threadsafedecorator.cpp
)
add_library(tb_enum-core SHARED ${SOURCES_CORE_SUPPORT})
add_library(tb_enum::tb_enum-core ALIAS tb_enum-core)
target_include_directories(tb_enum-core
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_enum-core PUBLIC tb_enum::tb_enum-api nlohmann_json::nlohmann_json)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_enum-core PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_enum-core PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_enum-core
        EXPORT Tb_enumCoreTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_enum/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_enumCoreTargets
  NAMESPACE tb_enum::
)

install(EXPORT Tb_enumCoreTargets
  FILE Tb_enumCoreTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_enum::
)
