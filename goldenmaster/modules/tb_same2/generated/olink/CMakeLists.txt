set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear REQUIRED COMPONENTS poco-olink)
set (SOURCES_OLINK
    samestruct1interfaceservice.cpp
    samestruct1interfaceclient.cpp
    samestruct2interfaceservice.cpp
    samestruct2interfaceclient.cpp
    sameenum1interfaceservice.cpp
    sameenum1interfaceclient.cpp
    sameenum2interfaceservice.cpp
    sameenum2interfaceclient.cpp
)
add_library(tb_same2-olink SHARED ${SOURCES_OLINK})
add_library(tb_same2::tb_same2-olink ALIAS tb_same2-olink)
target_include_directories(tb_same2-olink
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(tb_same2-olink
    PRIVATE
    tb_same2::tb_same2-core
    PUBLIC
    apigear::poco-olink
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(tb_same2-olink PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(tb_same2-olink PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS tb_same2-olink
        EXPORT Tb_same2OLinkTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/tb_same2/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Tb_same2OLinkTargets
  NAMESPACE tb_same2::
)

install(EXPORT Tb_same2OLinkTargets
  FILE Tb_same2OLinkTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE tb_same2::
)
