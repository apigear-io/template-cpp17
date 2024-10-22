set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
set (SOURCES_CORE_SUPPORT
    testbed1.json.adapter.cpp
    structinterface.publisher.cpp
    structinterface.threadsafedecorator.cpp
    structarrayinterface.publisher.cpp
    structarrayinterface.threadsafedecorator.cpp
)
add_library(testbed1-core SHARED ${SOURCES_CORE_SUPPORT})
add_library(testbed1::testbed1-core ALIAS testbed1-core)
target_include_directories(testbed1-core
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(testbed1-core PUBLIC testbed1::testbed1-api nlohmann_json::nlohmann_json)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(testbed1-core PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(testbed1-core PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS testbed1-core
        EXPORT Testbed1CoreTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/testbed1/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Testbed1CoreTargets
  NAMESPACE testbed1::
)

install(EXPORT Testbed1CoreTargets
  FILE Testbed1CoreTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE testbed1::
)
