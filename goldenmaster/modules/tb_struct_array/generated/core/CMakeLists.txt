set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
find_package(apigear REQUIRED utilities)
set (SOURCES_CORE_SUPPORT
    tb_struct_array.json.adapter.cpp
    test_struct_helper.cpp
    structarrayfieldinterface.publisher.cpp
    structarrayfieldinterface.threadsafedecorator.cpp
)
add_library(tb_struct_array-core SHARED ${SOURCES_CORE_SUPPORT})
add_library(tb_struct_array::tb_struct_array-core ALIAS tb_struct_array-core)
target_include_directories(tb_struct_array-core
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_struct_array-core PUBLIC apigear::utilities tb_struct_array::tb_struct_array-api nlohmann_json::nlohmann_json)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_struct_array-core PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wnon-virtual-dtor -Woverloaded-virtual -Wcast-align -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_struct_array-core PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_struct_array-core
        EXPORT Tb_struct_arrayCoreTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_struct_array/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_struct_arrayCoreTargets
  NAMESPACE tb_struct_array::
)

install(EXPORT Tb_struct_arrayCoreTargets
  FILE Tb_struct_arrayCoreTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_struct_array::
)
