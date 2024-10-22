set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
set (SOURCES_CORE_SUPPORT
    tb_same2.json.adapter.cpp
    samestruct1interface.publisher.cpp
    samestruct1interface.threadsafedecorator.cpp
    samestruct2interface.publisher.cpp
    samestruct2interface.threadsafedecorator.cpp
    sameenum1interface.publisher.cpp
    sameenum1interface.threadsafedecorator.cpp
    sameenum2interface.publisher.cpp
    sameenum2interface.threadsafedecorator.cpp
)
add_library(tb_same2-core SHARED ${SOURCES_CORE_SUPPORT})
add_library(tb_same2::tb_same2-core ALIAS tb_same2-core)
target_include_directories(tb_same2-core
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_same2-core PUBLIC tb_same2::tb_same2-api nlohmann_json::nlohmann_json)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_same2-core PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_same2-core PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_same2-core
        EXPORT Tb_same2CoreTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_same2/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_same2CoreTargets
  NAMESPACE tb_same2::
)

install(EXPORT Tb_same2CoreTargets
  FILE Tb_same2CoreTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_same2::
)
