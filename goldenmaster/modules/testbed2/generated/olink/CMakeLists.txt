set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-olink)
set (SOURCES_OLINK
    manyparaminterfaceservice.cpp
    manyparaminterfaceclient.cpp
    nestedstruct1interfaceservice.cpp
    nestedstruct1interfaceclient.cpp
    nestedstruct2interfaceservice.cpp
    nestedstruct2interfaceclient.cpp
    nestedstruct3interfaceservice.cpp
    nestedstruct3interfaceclient.cpp
)
add_library(testbed2-olink SHARED ${SOURCES_OLINK})
add_library(testbed2::testbed2-olink ALIAS testbed2-olink)
target_include_directories(testbed2-olink
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(testbed2-olink
    PRIVATE
    testbed2::testbed2-core
    PUBLIC
    apigear::poco-olink
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(testbed2-olink PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(testbed2-olink PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS testbed2-olink
        EXPORT Testbed2OLinkTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/testbed2/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Testbed2OLinkTargets
  NAMESPACE testbed2::
)

install(EXPORT Testbed2OLinkTargets
  FILE Testbed2OLinkTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE testbed2::
)

if(BUILD_TESTING)
enable_testing()
add_subdirectory(tests)
endif()
