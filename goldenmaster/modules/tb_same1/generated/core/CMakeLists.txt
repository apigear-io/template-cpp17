set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
find_package(apigear REQUIRED utilities)
set (SOURCES_CORE_SUPPORT
    tb_same1.json.adapter.cpp
    test_struct_helper.cpp
    samestruct1interface.publisher.cpp
    samestruct1interface.threadsafedecorator.cpp
    samestruct2interface.publisher.cpp
    samestruct2interface.threadsafedecorator.cpp
    sameenum1interface.publisher.cpp
    sameenum1interface.threadsafedecorator.cpp
    sameenum2interface.publisher.cpp
    sameenum2interface.threadsafedecorator.cpp
)
add_library(tb_same1-core SHARED ${SOURCES_CORE_SUPPORT})
add_library(tb_same1::tb_same1-core ALIAS tb_same1-core)
target_include_directories(tb_same1-core
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_same1-core PUBLIC apigear::utilities tb_same1::tb_same1-api nlohmann_json::nlohmann_json)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_same1-core PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_same1-core PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_same1-core
        EXPORT Tb_same1CoreTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_same1/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_same1CoreTargets
  NAMESPACE tb_same1::
)

install(EXPORT Tb_same1CoreTargets
  FILE Tb_same1CoreTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_same1::
)
