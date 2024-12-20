set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
set (SOURCES_CORE_SUPPORT
    testbed2.json.adapter.cpp
    test_struct_helper.cpp
    manyparaminterface.publisher.cpp
    manyparaminterface.threadsafedecorator.cpp
    nestedstruct1interface.publisher.cpp
    nestedstruct1interface.threadsafedecorator.cpp
    nestedstruct2interface.publisher.cpp
    nestedstruct2interface.threadsafedecorator.cpp
    nestedstruct3interface.publisher.cpp
    nestedstruct3interface.threadsafedecorator.cpp
)
add_library(testbed2-core SHARED ${SOURCES_CORE_SUPPORT})
add_library(testbed2::testbed2-core ALIAS testbed2-core)
target_include_directories(testbed2-core
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(testbed2-core PUBLIC testbed2::testbed2-api nlohmann_json::nlohmann_json)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(testbed2-core PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(testbed2-core PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS testbed2-core
        EXPORT Testbed2CoreTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/testbed2/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Testbed2CoreTargets
  NAMESPACE testbed2::
)

install(EXPORT Testbed2CoreTargets
  FILE Testbed2CoreTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE testbed2::
)
